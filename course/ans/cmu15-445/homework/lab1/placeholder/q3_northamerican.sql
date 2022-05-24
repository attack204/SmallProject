SELECT Id, ShipCountry, (CASE WHEN ShipCountry in ('USA', 'Mexico', 'Canada') THEN 'NorthAmerica' ELSE 'OtherPlace' END) from 'Order' WHERE Id>=15445 ORDER BY Id ASC limit 20;
