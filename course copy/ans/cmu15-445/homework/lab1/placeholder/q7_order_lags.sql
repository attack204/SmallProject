SELECT
	Id,
	OrderDate,
	pre,
	ROUND( JULIANDAY( OrderDate ) * 1.0 - JULIANDAY( pre ), 2 ) 
FROM
	( SELECT Id, OrderDate, lag( OrderDate, 1, '2012-07-22 23:11:15' ) OVER ( ORDER BY OrderDate ASC ) AS pre FROM "Order" WHERE CustomerId = 'BLONP' LIMIT 10 ) AS tmp;
