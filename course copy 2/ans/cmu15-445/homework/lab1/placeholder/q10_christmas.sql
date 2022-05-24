SELECT GROUP_CONCAT(Product.ProductName) FROM "Order" 
LEFT JOIN OrderDetail ON "Order".Id=OrderDetail.OrderId
LEFT JOIN Product ON OrderDetail.ProductId=Product.Id
WHERE "Order".CustomerId='QUEEN' AND date("Order".OrderDate)='2014-12-25'
ORDER BY Product.Id;
