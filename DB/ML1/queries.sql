-- ---------------------------------------------
-- NOTE: DO NOT REMOVE ANY LINE FROM THIS SCRIPT
-- ---------------------------------------------

-- Fill in the script as shown below:
select 'Query 00' as '';		-- the number of the question
-- List all the aircrafts		-- the text of the question En
-- Lister tous les avions		-- the text of the question Fr
select * 						-- your answer on one 
from AIRCRAFTS; 				-- or several line

-- Instructs MySQL to conform to standard SQL for group by clauses
set session sql_mode = 'ONLY_FULL_GROUP_BY';

-- Your turn. Display the following information:
-- C'est à vous. Afficher les informations suivantes :

select 'Query 01' as '';
-- the ID of the aircrafts such that all pilots who can fly them earn more than $100,000
-- l'ID des avions tels que tous les pilotes pouvant les piloter gagnent plus de 100 000 $
select AID from CERTIFIED natural join 
	(SELECT EID FROM EMPLOYEES WHERE SALARY > 100000) AS bigmoney
GROUP BY AID;

select 'Query 02' as '';
-- for each pilot who can fly more than 3 aircrafts, the ID of the pilot and the ID of the planes whith the greatest cruising range he/she can fly
-- pour chaque pilote certifié sur plus de 3 avions, l'ID du pilote et l'ID des avions avec le plus grand rayon d'action qu'il/elle peut piloter
select ids.EID, max(AIRCRAFTS.CRUISINGRANGE) from CERTIFIED natural join 
	(select EID from CERTIFIED GROUP BY EID having count(*) > 3) AS ids
natural join AIRCRAFTS GROUP BY EID;

select 'Query 03' as '';
-- le name of the pilots whose salary is less that the cheapest route from Los Angeles to Honolulu
-- le nom des pilotes dont le salaire est inférieur au prix du vol le moins cher de Los Angeles to Honolulu
-- Select the employee whose salary is lower than...
select ename from EMPLOYEES where salary < (
	 -- ...the cheapest route from Los Angeles to Honolulu
	select min(PRICE) from FLIGHTS 
	where ORIGIN = 'Los Angeles' and DESTINATION = 'Honolulu'
	group by ORIGIN
);


select 'Query 04' as '';
-- for all aircrafts with cruising range greater than 1,000 miles, give its name and the average salary of the pilots who can fly it
-- pour tous les avions avec un rayon d'action de plus de 1 000 miles, donner son nom et le salaire moyen des pilotes pouvant le piloter


select 'Query 05' as '';
-- the routes (origin, destination) that can be flown by all the pilots who earn more than $ 100,000
-- les trajets (origin, destination) qui peuvent être assurés par tous les pilotes qui gagnent plus de 100 000 $
-- Find the routes where distance is less than...
select origin, destination from FLIGHTS join (
	-- ... the cruisedistance of the planes which can be operated by...
    select cruisingrange from AIRCRAFTS natural join CERTIFIED natural join
    (
		-- ... all the pilots who earn more than 100 000
		select EID from EMPLOYEES where salary > 100000) as bigmoney) as bigmoneyplanes
on distance < bigmoneyplanes.cruisingrange
group by origin, destination;

select 'Query 06' as '';
-- all the possibilities (departs, arrives) to go from Madison à New York with at most two changes
-- toutes les possibilités (departs, arrives) pour aller de Madison à New York en au plus deux changements 


select 'Query 07' as '';
-- the difference between the average salary of pilots and the average salary of employees, including pilots (average(pilot) - average(employees))
-- la différence entre le salaire moyen des pilotes et le salaire moyens des employées, y inclus les pilotes (moy(pilotes) - moy(salariés))
-- Difference 
SELECT pilots.meansalary - emp.meansalary as result from
	-- average salary of all the pilots
	(select avg(SALARY) as meansalary from (
		select eid, SALARY from EMPLOYEES natural join CERTIFIED group by eid, salary) as pilots
	) as pilots,
	-- average salary of all the non pilots
	(select avg(SALARY) as meansalary from EMPLOYEES) as emp;

select 'Query 08' as '';
-- the ID and the name of the pilots whose salary is greater than the average salary of employees, including pilots
-- l'ID et le nom des pilotes dont le salaire est plus haut que la moyenne des salaires des employés, y inclus les pilotes


select 'Query 09' as '';
-- the name of the pilots who can only fly aircrafts whith cruising range greater than 1,000 miles
-- le noms des pilotes qui ne peuvent piloter que des avions avec un rayon d'actions supérieur à 1 000 miles
-- Find all employees which are not in the following list :
select ename from EMPLOYEES left outer join
	(-- Find all pilots who can fly an aircraft of range less than 1,000
	select eid from EMPLOYEES natural join CERTIFIED natural join(
		-- Find aircrafts whose cruisingrange is less than or equal to 1,000
		select aid from AIRCRAFTS where cruisingrange <= 1000) as shortrange
	group by eid) as shortPilots
on EMPLOYEES.eid = shortPilots.eid
-- Make sure said employees are pilots
inner join CERTIFIED on EMPLOYEES.eid = CERTIFIED.eid
-- Only take the pilots who are not results from the subquery, ie pilots who are not
-- capable of flying a short range plane
where shortPilots.eid is null group by EMPLOYEES.ename;


select 'Query 10' as '';
-- the name of the pilots who can fly at least two planes with cruising range over 1,000 miles
-- le nom des pilotes qui peuvent piloter au moins deux avions de rayon d'action supérieur à 1 000 miles


select 'Query 11' as '';
-- the name of the pilots who can fly aircrafts with cruising range over 1,000 miles and who can fly a Boeing
-- le nom des pilotes qui peuvent piloter des avions avec un rayon d'action supérieur à 1 000 miles et un Boeing
select ename from EMPLOYEES natural join CERTIFIED natural join (
	-- Find all aircrafts id with cruising range over 1,000 miles or who are Boeings
	select aid from AIRCRAFTS where cruisingrange > 1000 or aname like '%Boeing%') as planes
group by ename;

select 'Query 12' as '';
-- the ID of the aircrafts that can be used on all flights from Los Angeles to Chicago (distance VS cruising range comparision)
-- l'ID des avions qui peuvent être uilisés sur tous les vols de Los Angeles to Chicago (comparaison ente distance et rayon d'action)


select 'Query 13' as '';
-- the name of the pilots who cannot fly any Boeing aircraft
-- le nom des pilotes qui ne peuvent pas piloter un avion boeing
-- Select all pilots who can fly one of though
select eid from EMPLOYEES natural join CERTIFIED natural join (
-- Select all Boeing plane ids
select aid from AIRCRAFTS where aname like '%Boeing%') as Boeings;

select 'Query 14' as '';
-- the name of the pilots who can fly a Boeing aircraft (at least)
-- le nom des pilotes qui peuvent piloter un avion Boeing (au moins)


select 'Query 15' as '';
-- the name of the pilots who can only fly Boeing aircrafts
-- le nom des pilotes qui ne peuvent piloter que des avions Boeing


select 'Query 16' as '';
-- the name of the pilots who can fly all the Boeing aircrafts (listed in the database)
-- le nom des pilotes qui peuvent piloter tous les avions Boeings (listés dans la base de données)


select 'Query 17' as '';
-- for each employee, their name, the number of aircrafts he/she can fly, the maximum cruising range of those aircrafts
-- pour chaque employé, son nom, le nombre d'avions qu'il/elle peut piloter, le rayon d'action maximum de ces avions


select 'Query 18' as '';
-- the name of the pilots who can fly the greatest number of routes (listed in the database)
-- le nom des pilotes qui peuvent assurer le plus grand nombre de trajets (listés dans la base de données)


select 'Query 19' as '';
-- for each aircraft, its name and the routes (origin, destination) it can operate
-- pour chaque avion, son nom et les trajets (origin, destination) qu'il peut assurer


select 'Query 20' as '';
-- the routes (origin, destination) flown by fligths with different distances
-- les trajets (origin, destination) réalisés par des vols avec des distances différentes

