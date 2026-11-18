CREATE DATABASE IF NOT EXISTS PerformanceTestDB;
USE PerformanceTestDB;

CREATE TABLE IF NOT EXISTS Orders (
    InvoiceNo VARCHAR(50),
    StockCode VARCHAR(50),
    Description TEXT,
    Quantity INT,
    InvoiceDate VARCHAR(50),
    UnitPrice DOUBLE,
    CustomerID VARCHAR(50),
    Country VARCHAR(50)
);