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
Select AID from (select AID, min(SALARY) as minsal from CERTIFIED natural join EMPLOYEES group by AID) as min100k where min100k.minsal>100000;

select 'Query 02' as '';
-- for each pilot who can fly more than 3 aircrafts, the ID of the pilot and the ID of the planes whith the greatest cruising range he/she can fly
-- pour chaque pilote certifié sur plus de 3 avions, l'ID du pilote et l'ID des avions avec le plus grand rayon d'action qu'il/elle peut piloter
select skilledemp.EID, max(aircrafts.CRUISINGRANGE) from certified natural join 
(select EID, count(*) as nb_aircrafts from certified group by EID having nb_aircrafts > 3) as skilledemp 
natural join aircrafts group by EID;

select 'Query 03' as '';
-- le name of the pilots whose salary is less that the cheapest route from Los Angeles to Honolulu
-- le nom des pilotes dont le salaire est inférieur au prix du vol le moins cher de Los Angeles to Honolulu
 

select 'Query 04' as '';
-- for all aircrafts with cruising range greater than 1,000 miles, give its name and the average salary of the pilots who can fly it
-- pour tous les avions avec un rayon d'action de plus de 1 000 miles, donner son nom et le salaire moyen des pilotes pouvant le piloter
select ANAME, avg(SALARY) from
(select * from AIRCRAFTS natural join CERTIFIED natural join EMPLOYEES where CRUISINGRANGE>1000) as tot
group by AID;

select 'Query 05' as '';
-- the routes (origin, destination) that can be flown by all the pilots who earn more than $ 100,000
-- les trajets (origin, destination) qui peuvent être assurés par tous les pilotes qui gagnent plus de 100 000 $


select 'Query 06' as '';
-- all the possibilities (departs, arrives) to go from Madison à New York with at most two changes
-- toutes les possibilités (departs, arrives) pour aller de Madison à New York en au plus deux changements 


select 'Query 07' as '';
-- the difference between the average salary of pilots and the average salary of employees, including pilots (average(pilot) - average(employees))
-- la différence entre le salaire moyen des pilotes et le salaire moyens des employées, y inclus les pilotes (moy(pilotes) - moy(salariés))


select 'Query 08' as '';
-- the ID and the name of the pilots whose salary is greater than the average salary of employees, including pilots
-- l'ID et le nom des pilotes dont le salaire est plus haut que la moyenne des salaires des employés, y inclus les pilotes
select EID, ENAME from 
(select ENAME, CERTIFIED.EID, EMPLOYEES.SALARY from EMPLOYEES right outer join CERTIFIED on EMPLOYEES.EID=CERTIFIED.EID) as tot 
where tot.SALARY>(select avg(SALARY) from EMPLOYEES);

select 'Query 09' as '';
-- the name of the pilots who can only fly aircrafts whith cruising range greater than 1,000 miles
-- le noms des pilotes qui ne peuvent piloter que des avions avec un rayon d'actions supérieur à 1 000 miles


select 'Query 10' as '';
-- the name of the pilots who can fly at least two planes with cruising range over 1,000 miles
-- le nom des pilotes qui peuvent piloter au moins deux avions de rayon d'action supérieur à 1 000 miles
select ENAME from EMPLOYEES natural join 
(select *, count(*) as nb_aircrafts from CERTIFIED natural join AIRCRAFTS group by EID having nb_aircrafts > 2 and CRUISINGRANGE >1000) as skilltable;


select 'Query 11' as '';
-- the name of the pilots who can fly aircrafts with cruising range over 1,000 miles and who can fly a Boeing
-- le nom des pilotes qui peuvent piloter des avions avec un rayon d'action supérieur à 1 000 miles et un Boeing 


select 'Query 12' as '';
-- the ID of the aircrafts that can be used on all flights from Los Angeles to Chicago (distance VS cruising range comparision)
-- l'ID des avions qui peuvent être uilisés sur tous les vols de Los Angeles to Chicago (comparaison ente distance et rayon d'action)
select AID from AIRCRAFTS where 
(select DISTANCE from FLIGHTS where ORIGIN="Los Angeles" and DESTINATION="Chicago") < AIRCRAFTS.CRUISINGRANGE group by AID;

select 'Query 13' as '';
-- the name of the pilots who cannot fly any Boeing aircraft
-- le nom des pilotes qui ne peuvent pas piloter un avion boeing


select 'Query 14' as '';
-- the name of the pilots who can fly a Boeing aircraft (at least)
-- le nom des pilotes qui peuvent piloter un avion Boeing (au moins)
select ENAME from EMPLOYEES natural join 
(select AID, EID from AIRCRAFTS natural join CERTIFIED where ANAME like "%Boeing%") as boeing 
where EMPLOYEES.EID=boeing.EID group by ENAME;

select 'Query 15' as '';
-- the name of the pilots who can only fly Boeing aircrafts
-- le nom des pilotes qui ne peuvent piloter que des avions Boeing


select 'Query 16' as '';
-- the name of the pilots who can fly all the Boeing aircrafts (listed in the database)
-- le nom des pilotes qui peuvent piloter tous les avions Boeings (listés dans la base de données)
select ENAME from EMPLOYEES natural join 
(select *, count(*) as nb_boeings from 
(select CERTIFIED.EID, boeings.AID from CERTIFIED inner join (select *  from aircrafts where ANAME LIKE "%Boeing%") as boeings on CERTIFIED.AID=boeings.AID) as eid_nb_boeing 
group by EID) as tot where tot.nb_boeings=(select count(*) from aircrafts where ANAME like "%Boeing%");
select 'Query 17' as '';
-- for each employee, their name, the number of aircrafts he/she can fly, the maximum cruising range of those aircrafts
-- pour chaque employé, son nom, le nombre d'avions qu'il/elle peut piloter, le rayon d'action maximum de ces avions


select 'Query 18' as '';
-- the name of the pilots who can fly the greatest number of routes (listed in the database)
-- le nom des pilotes qui peuvent assurer le plus grand nombre de trajets (listés dans la base de données)
select * from EMPLOYEES natural join CERTIFIED natural join AIRCRAFTS 
where CRUISINGRANGE > (select max(DISTANCE) from FLIGHTS) group by EID;

select 'Query 19' as '';
-- for each aircraft, its name and the routes (origin, destination) it can operate
-- pour chaque avion, son nom et les trajets (origin, destination) qu'il peut assurer


select 'Query 20' as '';
-- the routes (origin, destination) flown by fligths with different distances
-- les trajets (origin, destination) réalisés par des vols avec des distances différentes
select distinct FLIGHTS.ORIGIN, FLIGHTS.DESTINATION from flights;
