SELECT
	late_cnt.CompanyName, ROUND(late_cnt.cnt*1.0/total_cnt.cnt*100, 2) AS ratio
FROM
	(
	SELECT
		Shipper.CompanyName,
		COUNT( * ) AS cnt 
	FROM
		'Order'
		LEFT JOIN Shipper ON "Order".ShipVia = Shipper.Id 
	WHERE
		ShippedDate > RequiredDate 
	GROUP BY
		"Order".ShipVia 
	) AS late_cnt LEFT JOIN
	(
	SELECT
		Shipper.CompanyName,
		COUNT( * ) AS cnt 
	FROM
		'Order'
		LEFT JOIN Shipper ON "Order".ShipVia = Shipper.Id 
	GROUP BY
	"Order".ShipVia 
	) AS total_cnt ON late_cnt.CompanyName=total_cnt.CompanyName ORDER BY ratio ASC;
