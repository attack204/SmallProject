SELECT * FROM
(
SELECT Region.RegionDescription, FirstName, LastName, Employee.BirthDate FROM EmployeeTerritory
LEFT JOIN Territory ON EmployeeTerritory.TerritoryId=Territory.Id
LEFT JOIN Employee ON EmployeeTerritory.EmployeeId=Employee.Id
LEFT JOIN Region ON Territory.RegionId=Region.Id
ORDER BY Employee.BirthDate DESC
) GROUP BY RegionDescription;
