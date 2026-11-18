using CsvHelper;
using PerformansTest;
using System.Globalization;
using MySql.Data.MySqlClient;
using MongoDB.Driver;
using MongoDB.Bson;
using System.Diagnostics;

Console.WriteLine("=== VERİTABANI PERFORMANS KARŞILAŞTIRMA TESTİ (MySQL vs MongoDB) ===\n");
Console.WriteLine("Veri Seti Okunuyor... Lütfen bekleyin.");

string csvFilePath = @"C:\Users\Dodo\Desktop\Proje1\data.csv";
string mysqlConnString = "Server=localhost;Database=PerformanceTestDB;Uid=root;Pwd=dodo123;Pooling=false;";
string mongoConnString = "mongodb://localhost:27017";

List<RetailData> allData = new List<RetailData>();
try
{
    using (var reader = new StreamReader(csvFilePath))
    using (var csv = new CsvReader(reader, CultureInfo.InvariantCulture))
    {
        allData = csv.GetRecords<RetailData>().ToList();
    }
    Console.WriteLine($"-> Toplam {allData.Count} satır veri belleğe alındı.\n");
}
catch (Exception ex)
{
    Console.WriteLine($"HATA: Veri okunamadı. {ex.Message}");
    return;
}

// ---------------------------------------------------------
// DENEY 1: INSERT (YAZMA) TESTLERİ (10K, 100K, 1M)
// ---------------------------------------------------------
int[] insertScenarios = { 10000, 100000, 1000000 };
foreach (int size in insertScenarios)
{
    Console.WriteLine($"\n--- DENEY 1: {size} KAYIT İÇİN INSERT TESTİ ---");
    List<RetailData> currentData = GenerateTestData(allData, size);

    long mysqlTime = RunMysqlInsert(currentData, mysqlConnString);
    Console.WriteLine($"[MySQL] Insert Süresi   : {mysqlTime} ms");

    long mongoTime = RunMongoInsert(currentData, mongoConnString);
    Console.WriteLine($"[MongoDB] Insert Süresi : {mongoTime} ms");
}

Console.WriteLine("\n=======================================================");
Console.WriteLine("SONRAKİ TESTLER 1 MİLYON KAYIT ÜZERİNDEN YAPILACAKTIR");
Console.WriteLine("=======================================================\n");

// ---------------------------------------------------------
// DENEY 2: SELECT (OKUMA) TESTLERİ
// ---------------------------------------------------------
Console.WriteLine("--- DENEY 2: SELECT (OKUMA) TESTLERİ ---");
RunSelectTests(mysqlConnString, mongoConnString);

// ---------------------------------------------------------
// DENEY 3: UPDATE (GÜNCELLEME) TESTLERİ
// ---------------------------------------------------------
Console.WriteLine("\n--- DENEY 3: UPDATE (GÜNCELLEME) TESTLERİ ---");
RunUpdateTests(mysqlConnString, mongoConnString);

// ---------------------------------------------------------
// DENEY 4: DELETE (SİLME) TESTLERİ
// ---------------------------------------------------------
Console.WriteLine("\n--- DENEY 4: DELETE (SİLME) TESTLERİ ---");
RunDeleteTests(mysqlConnString, mongoConnString);

// ---------------------------------------------------------
// DENEY 5: COMPLEX QUERY (JOIN vs AGGREGATION)
// ---------------------------------------------------------
Console.WriteLine("\n--- DENEY 5: COMPLEX QUERY (JOIN & AGGREGATION) ---");
RunComplexQueryTests(mysqlConnString, mongoConnString);

Console.WriteLine("\n*** TÜM TESTLER BAŞARIYLA TAMAMLANDI! ***");
Console.ReadLine();


// =========================================================================================
// YARDIMCI METOTLAR VE TEST FONKSİYONLARI
// =========================================================================================

static List<RetailData> GenerateTestData(List<RetailData> source, int requiredSize)
{
    List<RetailData> result = new List<RetailData>(requiredSize);
    while (result.Count < requiredSize)
    {
        int remaining = requiredSize - result.Count;
        int takeCount = Math.Min(source.Count, remaining);
        result.AddRange(source.Take(takeCount));
    }
    return result;
}

static long RunMysqlInsert(List<RetailData> data, string connStr)
{
    Stopwatch watch = new Stopwatch();
    using (MySqlConnection conn = new MySqlConnection(connStr))
    {
        if (conn.State == System.Data.ConnectionState.Closed) conn.Open();
        new MySqlCommand("TRUNCATE TABLE Orders", conn).ExecuteNonQuery();

        watch.Start();
        using (var transaction = conn.BeginTransaction())
        {
            using (var cmd = new MySqlCommand())
            {
                cmd.Connection = conn;
                cmd.Transaction = transaction;
                cmd.CommandText = "INSERT INTO Orders (InvoiceNo, StockCode, Description, Quantity, InvoiceDate, UnitPrice, CustomerID, Country) VALUES (@InvoiceNo, @StockCode, @Description, @Quantity, @InvoiceDate, @UnitPrice, @CustomerID, @Country)";

                cmd.Parameters.Add("@InvoiceNo", MySqlDbType.VarChar);
                cmd.Parameters.Add("@StockCode", MySqlDbType.VarChar);
                cmd.Parameters.Add("@Description", MySqlDbType.Text);
                cmd.Parameters.Add("@Quantity", MySqlDbType.Int32);
                cmd.Parameters.Add("@InvoiceDate", MySqlDbType.VarChar);
                cmd.Parameters.Add("@UnitPrice", MySqlDbType.Double);
                cmd.Parameters.Add("@CustomerID", MySqlDbType.VarChar);
                cmd.Parameters.Add("@Country", MySqlDbType.VarChar);

                foreach (var item in data)
                {
                    cmd.Parameters["@InvoiceNo"].Value = (object)item.InvoiceNo ?? DBNull.Value;
                    cmd.Parameters["@StockCode"].Value = (object)item.StockCode ?? DBNull.Value;
                    cmd.Parameters["@Description"].Value = (object)item.Description ?? DBNull.Value;
                    cmd.Parameters["@Quantity"].Value = item.Quantity;
                    cmd.Parameters["@InvoiceDate"].Value = (object)item.InvoiceDate ?? DBNull.Value;
                    cmd.Parameters["@UnitPrice"].Value = item.UnitPrice;
                    cmd.Parameters["@CustomerID"].Value = (object)item.CustomerID ?? DBNull.Value;
                    cmd.Parameters["@Country"].Value = (object)item.Country ?? DBNull.Value;
                    cmd.ExecuteNonQuery();
                }
            }
            transaction.Commit();
        }
        watch.Stop();
    }
    return watch.ElapsedMilliseconds;
}

static long RunMongoInsert(List<RetailData> data, string connStr)
{
    Stopwatch watch = new Stopwatch();
    var client = new MongoClient(connStr);
    var db = client.GetDatabase("PerformanceTestDB");
    var collection = db.GetCollection<RetailData>("Orders");

    db.DropCollection("Orders");

    watch.Start();
    collection.InsertMany(data);
    watch.Stop();

    return watch.ElapsedMilliseconds;
}

static void RunSelectTests(string mysqlStr, string mongoStr)
{
    int iterasyon = 50;

    // MySQL Select (COUNT ile RAM şişmesini engelleme amacımız var)
    Stopwatch mysqlSingle = new Stopwatch(), mysqlRange = new Stopwatch();
    using (MySqlConnection conn = new MySqlConnection(mysqlStr))
    {
        if (conn.State == System.Data.ConnectionState.Closed) conn.Open();

        mysqlSingle.Start();
        for (int i = 0; i < iterasyon; i++)
        {
            using (var cmd = new MySqlCommand("SELECT COUNT(*) FROM Orders WHERE InvoiceNo = '536365'", conn))
            { cmd.ExecuteScalar(); }
        }
        mysqlSingle.Stop();

        mysqlRange.Start();
        for (int i = 0; i < iterasyon; i++)
        {
            using (var cmd = new MySqlCommand("SELECT COUNT(*) FROM Orders WHERE UnitPrice BETWEEN 10 AND 50", conn))
            { cmd.ExecuteScalar(); }
        }
        mysqlRange.Stop();
    }

    // MongoDB Select (CountDocuments ile hızı ölçüyoruz)
    Stopwatch mongoSingle = new Stopwatch(), mongoRange = new Stopwatch();
    var client = new MongoClient(mongoStr);
    var coll = client.GetDatabase("PerformanceTestDB").GetCollection<RetailData>("Orders");

    mongoSingle.Start();
    for (int i = 0; i < iterasyon; i++)
    {
        var filter = Builders<RetailData>.Filter.Eq(x => x.InvoiceNo, "536365");
        coll.CountDocuments(filter);
    }
    mongoSingle.Stop();

    mongoRange.Start();
    for (int i = 0; i < iterasyon; i++)
    {
        var filter = Builders<RetailData>.Filter.And(
            Builders<RetailData>.Filter.Gte(x => x.UnitPrice, 10.0),
            Builders<RetailData>.Filter.Lte(x => x.UnitPrice, 50.0));
        coll.CountDocuments(filter);
    }
    mongoRange.Stop();

    Console.WriteLine($"[MySQL] Tek Kayıt Sorgu ({iterasyon} Kez)  : {mysqlSingle.ElapsedMilliseconds} ms");
    Console.WriteLine($"[MongoDB] Tek Kayıt Sorgu ({iterasyon} Kez): {mongoSingle.ElapsedMilliseconds} ms");
    Console.WriteLine($"[MySQL] Aralık Sorgusu ({iterasyon} Kez)   : {mysqlRange.ElapsedMilliseconds} ms");
    Console.WriteLine($"[MongoDB] Aralık Sorgusu ({iterasyon} Kez) : {mongoRange.ElapsedMilliseconds} ms");
}

static void RunUpdateTests(string mysqlStr, string mongoStr)
{
    Stopwatch mysqlWatch = new Stopwatch();
    using (MySqlConnection conn = new MySqlConnection(mysqlStr))
    {
        if (conn.State == System.Data.ConnectionState.Closed) conn.Open();
        mysqlWatch.Start();
        using (var cmd = new MySqlCommand("UPDATE Orders SET UnitPrice = UnitPrice * 1.1 WHERE Country = 'Germany'", conn))
        { cmd.ExecuteNonQuery(); }
        mysqlWatch.Stop();
    }

    Stopwatch mongoWatch = new Stopwatch();
    var coll = new MongoClient(mongoStr).GetDatabase("PerformanceTestDB").GetCollection<RetailData>("Orders");
    mongoWatch.Start();
    var filter = Builders<RetailData>.Filter.Eq(x => x.Country, "Germany");
    var update = Builders<RetailData>.Update.Mul(x => x.UnitPrice, 1.1);
    coll.UpdateMany(filter, update);
    mongoWatch.Stop();

    Console.WriteLine($"[MySQL] Toplu Güncelleme Süresi   : {mysqlWatch.ElapsedMilliseconds} ms");
    Console.WriteLine($"[MongoDB] Toplu Güncelleme Süresi : {mongoWatch.ElapsedMilliseconds} ms");
}

static void RunDeleteTests(string mysqlStr, string mongoStr)
{
    Stopwatch mysqlWatch = new Stopwatch();
    using (MySqlConnection conn = new MySqlConnection(mysqlStr))
    {
        if (conn.State == System.Data.ConnectionState.Closed) conn.Open();
        mysqlWatch.Start();
        using (var cmd = new MySqlCommand("DELETE FROM Orders WHERE Quantity < 0", conn))
        { cmd.ExecuteNonQuery(); }
        mysqlWatch.Stop();
    }

    Stopwatch mongoWatch = new Stopwatch();
    var coll = new MongoClient(mongoStr).GetDatabase("PerformanceTestDB").GetCollection<RetailData>("Orders");
    mongoWatch.Start();
    var filter = Builders<RetailData>.Filter.Lt(x => x.Quantity, 0);
    coll.DeleteMany(filter);
    mongoWatch.Stop();

    Console.WriteLine($"[MySQL] Toplu Silme Süresi   : {mysqlWatch.ElapsedMilliseconds} ms");
    Console.WriteLine($"[MongoDB] Toplu Silme Süresi : {mongoWatch.ElapsedMilliseconds} ms");
}

// 5. COMPLEX QUERY (JOIN & AGGREGATION)
static void RunComplexQueryTests(string mysqlStr, string mongoStr)
{
    // =====================================
    // MYSQL: JOIN TESTİ
    // =====================================
    Stopwatch mysqlWatch = new Stopwatch();
    using (MySqlConnection conn = new MySqlConnection(mysqlStr))
    {
        if (conn.State == System.Data.ConnectionState.Closed) conn.Open();

        mysqlWatch.Start();

        string joinQuery = @"
            SELECT c.Country, SUM(o.Quantity * o.UnitPrice) as TotalRevenue 
            FROM Orders o 
            JOIN (SELECT DISTINCT CustomerID, Country FROM Orders WHERE CustomerID IS NOT NULL AND CustomerID != '') c 
            ON o.CustomerID = c.CustomerID 
            GROUP BY c.Country 
            ORDER BY TotalRevenue DESC LIMIT 5";

        using (var cmd = new MySqlCommand(joinQuery, conn))
        {
            cmd.CommandTimeout = 600; // 10 Dakika zaman aşımı izni
            using (var reader = cmd.ExecuteReader()) { while (reader.Read()) { } }
        }
        mysqlWatch.Stop();
    }

    // =====================================
    // MONGODB: AGGREGATION PIPELINE TESTİ
    // =====================================
    Stopwatch mongoWatch = new Stopwatch();
    var client = new MongoClient(mongoStr);
    var db = client.GetDatabase("PerformanceTestDB");
    var coll = db.GetCollection<BsonDocument>("Orders");

    mongoWatch.Start();

    var pipeline = new[]
    {
        BsonDocument.Parse("{ $match: { CustomerID: { $nin: [null, ''] } } }"),
        BsonDocument.Parse("{ $group: { _id: '$Country', TotalRevenue: { $sum: { $multiply: ['$Quantity', '$UnitPrice'] } } } }"),
        BsonDocument.Parse("{ $sort: { TotalRevenue: -1 } }"),
        BsonDocument.Parse("{ $limit: 5 }")
    };

    // 1 Milyon kayıtta RAM dolarsa diye diskin kullanımına izin veriyoruz
    var options = new AggregateOptions { AllowDiskUse = true };

    coll.Aggregate<BsonDocument>(pipeline, options).ToList();
    mongoWatch.Stop();

    Console.WriteLine($"[MySQL] JOIN İşlemi Süresi         : {mysqlWatch.ElapsedMilliseconds} ms");
    Console.WriteLine($"[MongoDB] Aggregation İşlemi Süresi: {mongoWatch.ElapsedMilliseconds} ms");
}