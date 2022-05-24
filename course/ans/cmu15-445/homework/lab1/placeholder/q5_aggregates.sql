SELECT
	CategoryName,
	count( * ),
	ROUND( AVG( UnitPrice ), 2 ),
	MIN( UnitPrice ),
	MAX( UnitPrice ),
	order_cnt 
FROM
	(
	SELECT
		CategoryId,
		CategoryName,
		cnt,
		order_cnt 
	FROM
		(
		SELECT
			CategoryId,
			CategoryName,
			COUNT( * ) AS cnt,
			SUM( UnitsOnOrder ) AS order_cnt 
		FROM
			Product
			LEFT JOIN Category ON Product.CategoryId = Category.Id 
		GROUP BY
			CategoryId 
		) 
	WHERE
		cnt > 10 
	) AS tmp
	LEFT JOIN Product ON tmp.CategoryId = Product.CategoryId 
GROUP BY
	Product.CategoryId 
ORDER BY
	Product.CategoryId;
