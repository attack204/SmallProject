SELECT
	IFNULL(Customer.CompanyName, 'MISSING_NAME'), Customer.Id, ROUND(SUM(UnitPrice*Quantity),2) AS total_m
FROM
	OrderDetail
	LEFT JOIN "Order" ON OrderDetail.OrderId = "Order".Id
	LEFT JOIN Customer ON "Order".CustomerId = Customer.Id
	GROUP BY Customer.CompanyName
	ORDER BY total_m ASC;
