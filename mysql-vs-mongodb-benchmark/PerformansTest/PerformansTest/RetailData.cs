using CsvHelper.Configuration.Attributes;
using System;
using System.Collections.Generic;
using System.Text;
using MongoDB.Bson.Serialization.Attributes;

namespace PerformansTest
{
    [BsonIgnoreExtraElements]
    public class RetailData
    {
        [Name("InvoiceNo")]
        public string InvoiceNo { get; set; }

        [Name("StockCode")]
        public string StockCode { get; set; }

        [Name("Description")]
        public string Description { get; set; }

        [Name("Quantity")]
        public int Quantity { get; set; }

        [Name("InvoiceDate")]
        public string InvoiceDate { get; set; }

        [Name("UnitPrice")]
        public double UnitPrice { get; set; }

        [Name("CustomerID")]
        public string CustomerID { get; set; }

        [Name("Country")]
        public string Country { get; set; }
    }
}

