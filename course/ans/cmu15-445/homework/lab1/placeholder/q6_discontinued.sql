SELECT
	r.a,
	r.b,
	r.c 
FROM
	(
	SELECT
		Product.ProductName AS a,
		Customer.CompanyName AS b,
		Customer.ContactName AS c 
	FROM
		OrderDetail
		LEFT JOIN Product ON OrderDetail.ProductId = Product.Id
		LEFT JOIN "Order" ON OrderDetail.OrderId = "Order".Id
		LEFT JOIN Customer ON "Order".CustomerId = Customer.Id 
	WHERE
		Product.Discontinued = 1 
	ORDER BY
		"Order".OrderDate 
	) AS r 
GROUP BY
	r.a 
ORDER BY
	r.a;
