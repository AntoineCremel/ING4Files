-- ---------------------------------------------
-- NOTE: DO NOT REMOVE ANY LINE FROM THIS SCRIPT
-- ---------------------------------------------

-- Fill in the script as shown below:
select 'Query 00' as '';		-- the number of the question
-- List all the AIRCRAFTS		-- the text of the question En
-- Lister tous les avions		-- the text of the question Fr
select * 						-- your answer on one 
from AIRCRAFTS; 				-- or several line

-- Instructs MySQL to conform to standard SQL for group by clauses
set session sql_mode = 'ONLY_FULL_GROUP_BY';

-- Your turn. Display the following information:
-- C'est à vous. Afficher les informations suivantes :

select 'Query 01' as '';
-- the ID of the AIRCRAFTS such that all pilots who can fly them earn more than $100,000
-- l'ID des avions tels que tous les pilotes pouvant les piloter gagnent plus de 100 000 $
Select AID from 
(select AID, min(SALARY) as minsal from CERTIFIED natural join EMPLOYEES group by AID) as min100k 
where min100k.minsal>100000;

select 'Query 02' as '';
-- for each pilot who can fly more than 3 AIRCRAFTS, the ID of the pilot and the ID of the planes whith the greatest cruising range he/she can fly
-- pour chaque pilote certifié sur plus de 3 avions, l'ID du pilote et l'ID des avions avec le plus grand rayon d'action qu'il/elle peut piloter
select skilledemp.EID, max(AIRCRAFTS.CRUISINGRANGE) from CERTIFIED natural join 
(select EID, count(*) as nb_AIRCRAFTS from CERTIFIED group by EID having nb_AIRCRAFTS > 3) as skilledemp 
natural join AIRCRAFTS group by EID;

select 'Query 03' as '';
-- le name of the pilots whose salary is less that the cheapest route from Los Angeles to Honolulu
-- le nom des pilotes dont le salaire est inférieur au prix du vol le moins cher de Los Angeles to Honolulu
 -- Select the employee whose salary is lower than...
select ENAME from EMPLOYEES where SALARY < (
	 -- ...the cheapest route from Los Angeles to Honolulu
	select min(PRICE) from FLIGHTS 
	where ORIGIN = 'Los Angeles' and DESTINATION = 'Honolulu'
	group by ORIGIN
);

select 'Query 04' as '';
-- for all AIRCRAFTS with cruising range greater than 1,000 miles, give its name and the average salary of the pilots who can fly it
-- pour tous les avions avec un rayon d'action de plus de 1 000 miles, donner son nom et le salaire moyen des pilotes pouvant le piloter
select ANAME, avg(SALARY) from
(select * from AIRCRAFTS natural join CERTIFIED natural join EMPLOYEES where CRUISINGRANGE>1000) as tot
group by AID;

select 'Query 05' as '';
-- the routes (ORIGIN, DESTINATION) that can be flown by all the pilots who earn more than $ 100,000
-- les trajets (ORIGIN, DESTINATION) qui peuvent être assurés par tous les pilotes qui gagnent plus de 100 000 $
select ORIGIN, DESTINATION from FLIGHTS join (
	-- ... the cruisedistance of the planes which can be operated by...
    select CRUISINGRANGE from AIRCRAFTS natural join CERTIFIED natural join
    (
		-- ... all the pilots who earn more than 100 000
		select EID from EMPLOYEES where SALARY > 100000) as bigmoney) as bigmoneyplanes
on DISTANCE < bigmoneyplanes.CRUISINGRANGE
group by ORIGIN, DESTINATION;

select 'Query 06' as '';
-- all the possibilities (DEPARTS, ARRIVES) to go from Madison à New York with at most two changes
-- toutes les possibilités (DEPARTS, ARRIVES) pour aller de Madison à New York en au plus deux changements 
select 
	firstFlight.ORIGIN, firstFlight.DESTINATION,
	secondFlight.ORIGIN, secondFlight.DESTINATION,
	thirdFlight.ORIGIN, thirdFlight.DESTINATION
from 
-- Select all flights which leave from Madison
(select ORIGIN, DESTINATION, ARRIVES from FLIGHTS where ORIGIN = 'Madison') as firstFlight
left join FLIGHTS as secondFlight 
on firstFlight.DESTINATION = secondFlight.ORIGIN
	and timediff(firstFlight.ARRIVES, secondFlight.DEPARTS) <= 0
left join (
	-- Select all flights whose DESTINATION is New York
	select ORIGIN, DESTINATION, DEPARTS from FLIGHTS where DESTINATION = 'New York') as thirdFlight
on secondFlight.DESTINATION = thirdFlight.ORIGIN
	and timediff(secondFlight.ARRIVES, thirdFlight.DEPARTS) <= 0
    
-- Check that we do get to New York in the end
where firstFlight.DESTINATION = 'New York'
	or secondFlight.DESTINATION = 'New York'
    or thirdFlight.DESTINATION = 'New York';
    
select 'Query 07' as '';
-- the difference between the average salary of pilots and the average salary of employees, including pilots (average(pilot) - average(employees))
-- la différence entre le salaire moyen des pilotes et le salaire moyens des employées, y inclus les pilotes (moy(pilotes) - moy(salariés))
SELECT pilots.meansalary - emp.meansalary as result from
	-- average salary of all the pilots
	(select avg(SALARY) as meansalary from (
		select EID, SALARY from EMPLOYEES natural join CERTIFIED group by EID, SALARY) as pilots
	) as pilots,
	-- average salary of all the non pilots
	(select avg(SALARY) as meansalary from EMPLOYEES) as emp;

select 'Query 08' as '';
-- the ID and the name of the pilots whose salary is greater than the average salary of employees, including pilots
-- l'ID et le nom des pilotes dont le salaire est plus haut que la moyenne des salaires des employés, y inclus les pilotes
select EID, ENAME from 
(select ENAME, CERTIFIED.EID, EMPLOYEES.SALARY from EMPLOYEES right outer join CERTIFIED on EMPLOYEES.EID=CERTIFIED.EID) as tot 
where tot.SALARY>(select avg(SALARY) from EMPLOYEES);

select 'Query 09' as '';
-- the name of the pilots who can only fly AIRCRAFTS whith cruising range greater than 1,000 miles
-- le noms des pilotes qui ne peuvent piloter que des avions avec un rayon d'actions supérieur à 1 000 miles
-- Find all employees which are not in the following list :
select ename from EMPLOYEES left outer join
	(-- Find all pilots who can fly an aircraft of range less than 1,000
	select EID from EMPLOYEES natural join CERTIFIED natural join(
		-- Find AIRCRAFTS whose CRUISINGRANGE is less than or equal to 1,000
		select AID from AIRCRAFTS where CRUISINGRANGE <= 1000) as shortrange
	group by EID) as shortPilots
on EMPLOYEES.EID = shortPilots.EID
-- Make sure AID employees are pilots
inner join CERTIFIED on EMPLOYEES.EID = CERTIFIED.EID
-- Only take the pilots who are not results from the subquery, ie pilots who are not
-- capable of flying a short range plane
where shortPilots.EID is null group by EMPLOYEES.ename;

select 'Query 10' as '';
-- the name of the pilots who can fly at least two planes with cruising range over 1,000 miles
-- le nom des pilotes qui peuvent piloter au moins deux avions de rayon d'action supérieur à 1 000 miles
select ENAME from EMPLOYEES natural join 
(select *, count(*) as nb_AIRCRAFTS from CERTIFIED natural join AIRCRAFTS group by EID, CRUISINGRANGE having nb_AIRCRAFTS > 2 and CRUISINGRANGE >1000) as skilltable;


select 'Query 11' as '';
-- the name of the pilots who can fly AIRCRAFTS with cruising range over 1,000 miles and who can fly a Boeing
-- le nom des pilotes qui peuvent piloter des avions avec un rayon d'action supérieur à 1 000 miles et un Boeing 
select ename from EMPLOYEES natural join CERTIFIED natural join (
	-- Find all AIRCRAFTS id with cruising range over 1,000 miles or who are Boeings
	select aid from AIRCRAFTS where CRUISINGRANGE > 1000 or ANAME like '%Boeing%') as planes
group by ename;

select 'Query 12' as '';
-- the ID of the AIRCRAFTS that can be used on all flights from Los Angeles to Chicago (DISTANCE VS cruising range comparision)
-- l'ID des avions qui peuvent être uilisés sur tous les vols de Los Angeles to Chicago (comparaison ente DISTANCE et rayon d'action)
select AID from AIRCRAFTS where 
(select DISTANCE from FLIGHTS where ORIGIN="Los Angeles" and DESTINATION="Chicago") < AIRCRAFTS.CRUISINGRANGE 
group by AID;

select 'Query 13' as '';
-- the name of the pilots who cannot fly any Boeing aircraft
-- le nom des pilotes qui ne peuvent pas piloter un avion boeing
-- Select all pilots who are not capable of flying a Boeing
select EMPLOYEES.ENAME as name from EMPLOYEES 
-- Make sure we are only talking about pilots
natural join CERTIFIED
left outer join (
	-- Select all pilots who can fly one of those
	select EID, ENAME from EMPLOYEES natural join CERTIFIED natural join (
	-- Select all Boeing plane ids
		select aid from AIRCRAFTS where ANAME like '%Boeing%') as Boeings
	group by EID, ENAME) as boeingFlyers
on boeingFlyers.EID = EMPLOYEES.EID
where boeingFlyers.ENAME is null
group by EMPLOYEES.ENAME;

select 'Query 14' as '';
-- the name of the pilots who can fly a Boeing aircraft (at least)
-- le nom des pilotes qui peuvent piloter un avion Boeing (au moins)
select ENAME from EMPLOYEES natural join 
(select AID, EID from AIRCRAFTS natural join CERTIFIED where ANAME like "%Boeing%") as boeing 
where EMPLOYEES.EID=boeing.EID 
group by ENAME;

select 'Query 15' as '';
-- the name of the pilots who can only fly Boeing AIRCRAFTS
-- le nom des pilotes qui ne peuvent piloter que des avions Boeing
-- List the name of pilots
select ENAME from EMPLOYEES natural join CERTIFIED left join (
	-- List the ids of the pilots who can fly non Boeing AIRCRAFTS
	select EID from EMPLOYEES natural join CERTIFIED
	natural join (
		-- List of all the Boeing aricraft
		select aid from AIRCRAFTS where ANAME not like '%Boeing%') as notBoeing
	group by EID) as nonBoeingPilots
on EMPLOYEES.EID = nonBoeingPilots.EID
where nonBoeingPilots.EID is null
group by ENAME;

select 'Query 16' as '';
-- the name of the pilots who can fly all the Boeing AIRCRAFTS (listed in the database)
-- le nom des pilotes qui peuvent piloter tous les avions Boeings (listés dans la base de données)
select ENAME from EMPLOYEES natural join 
(select *, count(*) as nb_boeings from 
(select CERTIFIED.EID, boeings.AID from CERTIFIED inner join (select *  from AIRCRAFTS where ANAME LIKE "%Boeing%") as boeings on CERTIFIED.AID=boeings.AID) as EID 
group by EID) as tot where tot.nb_boeings=(select count(*) from AIRCRAFTS where ANAME like "%Boeing%");

select 'Query 17' as '';
-- for each employee, their name, the number of AIRCRAFTS he/she can fly, the maximum cruising range of those AIRCRAFTS
-- pour chaque employé, son nom, le nombre d'avions qu'il/elle peut piloter, le rayon d'action maximum de ces avions
-- The name of the employees with the number of aircraft they can fly
select ENAME, count(aid) as nbAircrafts, max(AIRCRAFTS.CRUISINGRANGE)
from EMPLOYEES
natural join CERTIFIED
natural join AIRCRAFTS
group by EMPLOYEES.ENAME;

select 'Query 18' as '';
-- the name of the pilots who can fly the greatest number of routes (listed in the database)
-- le nom des pilotes qui peuvent assurer le plus grand nombre de trajets (listés dans la base de données)
select * from EMPLOYEES natural join CERTIFIED natural join AIRCRAFTS 
where CRUISINGRANGE > (select max(DISTANCE) from FLIGHTS) 
group by EID;

select 'Query 19' as '';
-- for each aircraft, its name and the routes (ORIGIN, DESTINATION) it can operate
-- pour chaque avion, son nom et les trajets (ORIGIN, DESTINATION) qu'il peut assurer
select ANAME as ENAME, routes.ORIGIN as ORIGIN, routes.DESTINATION as DESTINATION from AIRCRAFTS left join (
	-- ORIGIN, DESTINATION, DISTANCE from each routes
	select ORIGIN, DESTINATION, DISTANCE from FLIGHTS) as routes
on AIRCRAFTS.CRUISINGRANGE >= routes.DISTANCE
order by ANAME;


select 'Query 20' as '';
-- the routes (ORIGIN, DESTINATION) flown by fligths with different distances
-- les trajets (ORIGIN, DESTINATION) réalisés par des vols avec des distances différentes
select distinct FLIGHTS.ORIGIN, FLIGHTS.DESTINATION from FLIGHTS;
