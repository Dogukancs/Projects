# Relational vs. NoSQL Database Performance Benchmark (MySQL vs. MongoDB)

A C# (.NET 10.0) benchmarking tool designed to evaluate and compare the performance of **MySQL 8.0** (Relational/SQL) and **MongoDB** (Document-based/NoSQL) under high-volume data workloads. Using a scaled version of the UCI *Online Retail* dataset (**1,000,000 records**), the benchmark measures exact execution times across core CRUD operations and complex analytical queries.

## Tech Stack & Environment
* **Language & Framework:** C#, .NET 10.0
* **Databases:** MySQL 8.0 Server, MongoDB Community Server
* **Drivers & Libraries:** `MySql.Data`, `MongoDB.Driver`, `System.Diagnostics.Stopwatch`
* **Dataset:** UCI Machine Learning Repository – *Online Retail* (541K original records algorithmically scaled to 1M records)

## Benchmark Scenarios
All tests were executed sequentially on an isolated local environment (`localhost`) to ensure hardware parity:
1. **Bulk Insert:** Inserting 10K, 100K, and 1M records from scratch into both databases.
2. **Read / Select (Unindexed):** Executing 50 repeated single-record lookups and range queries (`Price` between 10 and 50) across 1M records to evaluate full table/collection scan behavior.
3. **Bulk Update:** Increasing prices by 10% for all orders originating from `"Germany"`.
4. **Bulk Delete:** Removing invalid/erroneous invoice records where `Quantity < 0`.
5. **Complex Analytical Query:** Calculating total revenue by country and ranking the top 5 countries (using `JOIN` in MySQL vs. `Aggregation Pipeline` in MongoDB).

## Key Benchmark Results (1,000,000 Records)

| Operation | MySQL 8.0 (ms) | MongoDB (ms) | Performance Difference |
| :--- | :---: | :---: | :--- |
| **Insert (10K Records)** | 2,113 ms | **180 ms** | MongoDB ~11.7x faster |
| **Insert (100K Records)** | 17,731 ms | **1,220 ms** | MongoDB ~14.5x faster |
| **Insert (1M Records)** | 167,106 ms | **5,147 ms** | MongoDB ~32.4x faster |
| **Single Select (50x)** | 28,946 ms | **15,749 ms** | MongoDB ~1.8x faster |
| **Range Select (50x)** | 26,192 ms | **22,148 ms** | MongoDB ~1.2x faster |
| **Bulk Update** | 1,224 ms | **1,001 ms** | MongoDB ~1.2x faster |
| **Bulk Delete** | 1,184 ms | **856 ms** | MongoDB ~1.4x faster |
| **Complex Query (JOIN vs. Aggregation)** | 3,341 ms | **750 ms** | MongoDB ~4.4x faster |

## Architectural Takeaways
* **Write Throughput:** MongoDB outperformed MySQL by over **32x** on 1M inserts due to schema-less BSON ingestion without ACID foreign-key/table-locking overhead.
* **Analytical Pipelines:** MongoDB's native Aggregation Pipeline (`$group`, `$multiply`) executed complex revenue aggregations **4.4x faster** than MySQL's in-memory `JOIN`.
* **System Design Conclusion:** MongoDB is ideal for high-throughput, write-heavy big data pipelines (IoT, logging, real-time analytics), whereas MySQL remains essential where strict ACID compliance and relational integrity (finance, inventory) are critical.