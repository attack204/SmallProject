SELECT DISTINCT ShipName, SUBSTR(ShipName,0,INSTR(ShipName,'-')) FROM 'Order' WHERE ShipName LIKE '%-%' ORDER BY ShipName;
