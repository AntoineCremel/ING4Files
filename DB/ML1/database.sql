USE ML1;

--drop table CERTIFIED;
--drop table EMPLOYEES;
--drop table AIRCRAFTS;
--drop table FLIGHTS;


create table FLIGHTS (
	FLNO 		integer,  
	ORIGIN 		varchar(30),  
	DESTINATION varchar(30),  
	DISTANCE 	integer,  
	DEPARTS 	datetime,  
	ARRIVES 	datetime,  
	PRICE 		integer, 
    constraint FLIGHTS_PK primary key (FLNO)
);

create table AIRCRAFTS (
	AID 			integer, 
	ANAME 			varchar(30), 
	CRUISINGRANGE 	integer, 
    constraint AIRCRAFTS_PK primary key (AID)
);

create table EMPLOYEES (
	EID 		integer, 
	ENAME 		varchar(30), 
	SALARY 		integer, 
	constraint AIRCRAFTS_PK primary key (EID)
);

create table CERTIFIED (
	EID 		integer, 
	AID 		integer, 
    constraint CERTIFIED_PK primary key (EID,  AID), 
    constraint CERTIFIED_FK_EID foreign key (EID) references EMPLOYEES(EID), 
    constraint CERTIFIED_FK_AcertifiedID foreign key (AID) references AIRCRAFTS(AID)
);

insert into FLIGHTS values (99, 'Los Angeles', 'Washington D.C.', 2308, '2005-04-12 09:30', '2005-04-12 21:40', 235.98);
insert into FLIGHTS values (13, 'Los Angeles', 'Chicago', 1749, '2005-04-12 08:45', '2005-04-12 20:45', 220.98);
insert into FLIGHTS values (346, 'Los Angeles', 'Dallas', 1251, '2005-04-12 11:50', '2005-04-12 19:05', 225.43);
insert into FLIGHTS values (387, 'Los Angeles', 'Boston', 2606, '2005-04-12 07:03', '2005-04-12 17:03', 261.56);
insert into FLIGHTS values (7, 'Los Angeles', 'Sydney', 7487, '2005-04-12 22:30', '2005-04-14 6:10', 1278.56);
insert into FLIGHTS values (2, 'Los Angeles', 'Tokyo', 5478, '2005-04-12 12:30', '2005-04-13 15:55', 780.99);
insert into FLIGHTS values (33, 'Los Angeles', 'Honolulu', 2551, '2005-04-12 09:15', '2005-04-12 11:15', 375.23);
insert into FLIGHTS values (34, 'Los Angeles', 'Honolulu', 2551, '2005-04-12 12:45', '2005-04-12 15:18', 425.98);
insert into FLIGHTS values (76, 'Chicago', 'Los Angeles', 1749, '2005-04-12 08:32', '2005-04-12 10:03', 220.98);
insert into FLIGHTS values (68, 'Chicago', 'New York', 802, '2005-04-12 09:00', '2005-04-12 12:02', 202.45);
insert into FLIGHTS values (7789, 'Madison', 'Detroit', 319, '2005-04-12 06:15', '2005-04-12 08:19', 120.33);
insert into FLIGHTS values (701, 'Detroit', 'New York', 470, '2005-04-12 08:55', '2005-04-12 10:26', 180.56);
insert into FLIGHTS values (702, 'Madison', 'New York', 789, '2005-04-12 07:05', '2005-04-12 10:12', 202.34);
insert into FLIGHTS values (4884, 'Madison', 'Chicago', 84, '2005-04-12 22:12', '2005-04-12 23:02', 112.45);
insert into FLIGHTS values (2223, 'Madison', 'Pittsburgh', 517, '2005-04-12 08:02', '2005-04-12 10:01', 189.98);
insert into FLIGHTS values (5694, 'Madison', 'Minneapolis', 247, '2005-04-12 08:32', '2005-04-12 09:33', 120.11);
insert into FLIGHTS values (304, 'Minneapolis', 'New York', 991, '2005-04-12 10:00', '2005-04-12 11:39', 101.56);
insert into FLIGHTS values (149, 'Pittsburgh', 'New York', 303, '2005-04-12 09:42', '2005-04-12 12:09', 116.50);

insert into AIRCRAFTS values (1, 'Boeing 747-400', 8430);
insert into AIRCRAFTS values (2, 'Boeing 737-800', 3383);
insert into AIRCRAFTS values (3, 'Airbus A340-300', 7120);
insert into AIRCRAFTS values (4, 'British Aerospace Jetstream 41', 1502);
insert into AIRCRAFTS values (5, 'Embraer ERJ-145', 1530);
insert into AIRCRAFTS values (6, 'SAAB 340', 2128);
insert into AIRCRAFTS values (7, 'Piper Archer III', 520);
insert into AIRCRAFTS values (8, 'Tupolev 154', 4103);
insert into AIRCRAFTS values (16, 'Schwitzer 2-33', 30);
insert into AIRCRAFTS values (9, 'Lockheed L1011', 6900);
insert into AIRCRAFTS values (10, 'Boeing 757-300', 4010);
insert into AIRCRAFTS values (11, 'Boeing 777-300', 6441);
insert into AIRCRAFTS values (12, 'Boeing 767-400ER', 6475);
insert into AIRCRAFTS values (13, 'Airbus A320', 2605);
insert into AIRCRAFTS values (14, 'Airbus A319', 1805);
insert into AIRCRAFTS values (15, 'Boeing 727', 1504);
insert into AIRCRAFTS values (123, 'Airbus', 1000);
insert into AIRCRAFTS values (302, 'Boeing', 5000);
insert into AIRCRAFTS values (306, 'Jet01', 5000);
insert into AIRCRAFTS values (378, 'Airbus380', 8000);

insert into EMPLOYEES values (242518965, 'James Smith', 120433);
insert into EMPLOYEES values (141582651, 'Mary Johnson', 178345);
insert into EMPLOYEES values (011564812, 'John Williams', 153972);
insert into EMPLOYEES values (567354612, 'Lisa Walker', 256481);
insert into EMPLOYEES values (552455318, 'Larry West', 101745);
insert into EMPLOYEES values (550156548, 'Karen Scott', 205187);
insert into EMPLOYEES values (390487451, 'Lawrence Sperry', 212156);
insert into EMPLOYEES values (274878974, 'Michael Miller', 99890);
insert into EMPLOYEES values (254099823, 'Patricia Jones', 24450);
insert into EMPLOYEES values (356187925, 'Robert Brown', 44740);
insert into EMPLOYEES values (355548984, 'Angela Martinez', 212156); 
insert into EMPLOYEES values (310454876, 'Joseph Thompson', 212156);
insert into EMPLOYEES values (489456522, 'Linda Davis', 127984);
insert into EMPLOYEES values (489221823, 'Richard Jackson', 23980);
insert into EMPLOYEES values (548977562, 'William Ward', 84476);
insert into EMPLOYEES values (310454877, 'Chad Stewart', 33546);
insert into EMPLOYEES values (142519864, 'Betty Adams', 227489);
insert into EMPLOYEES values (269734834, 'George Wright', 289950);
insert into EMPLOYEES values (287321212, 'Michael Miller', 48090);
insert into EMPLOYEES values (552455348, 'Dorthy Lewis', 92013);
insert into EMPLOYEES values (248965255, 'Barbara Wilson', 43723);
insert into EMPLOYEES values (159542516, 'William Moore', 48250);
insert into EMPLOYEES values (348121549, 'Haywood Kelly', 32899);
insert into EMPLOYEES values (090873519, 'Elizabeth Taylor', 32021);
insert into EMPLOYEES values (486512566, 'David Anderson', 743001);
insert into EMPLOYEES values (619023588, 'Jennifer Thomas', 54921);
insert into EMPLOYEES values (015645489, 'Donald King', 18050);
insert into EMPLOYEES values (556784565, 'Mark Young', 205187);
insert into EMPLOYEES values (573284895, 'Eric Cooper', 114323);
insert into EMPLOYEES values (574489456, 'William Jones', 105743);
insert into EMPLOYEES values (574489457, 'Milo Brooks', 20);

insert into CERTIFIED values (567354612, 1);
insert into CERTIFIED values (567354612, 2);
insert into CERTIFIED values (567354612, 10);
insert into CERTIFIED values (567354612, 11);
insert into CERTIFIED values (567354612, 12);
insert into CERTIFIED values (567354612, 15);
insert into CERTIFIED values (567354612, 7);
insert into CERTIFIED values (567354612, 9);
insert into CERTIFIED values (567354612, 3);
insert into CERTIFIED values (567354612, 4);
insert into CERTIFIED values (567354612, 5);
insert into CERTIFIED values (552455318, 2);
insert into CERTIFIED values (552455318, 14);
insert into CERTIFIED values (550156548, 1);
insert into CERTIFIED values (550156548, 12);
insert into CERTIFIED values (390487451, 3);
insert into CERTIFIED values (390487451, 13);
insert into CERTIFIED values (390487451, 14);
insert into CERTIFIED values (274878974, 10);
insert into CERTIFIED values (274878974, 12);
insert into CERTIFIED values (355548984, 8);
insert into CERTIFIED values (355548984, 9);
insert into CERTIFIED values (310454876, 8);
insert into CERTIFIED values (310454876, 9);
insert into CERTIFIED values (548977562, 7);
insert into CERTIFIED values (142519864, 1);
insert into CERTIFIED values (142519864, 11);
insert into CERTIFIED values (142519864, 12);
insert into CERTIFIED values (142519864, 10);
insert into CERTIFIED values (142519864, 3);
insert into CERTIFIED values (142519864, 2);
insert into CERTIFIED values (142519864, 13);
insert into CERTIFIED values (142519864, 7);
insert into CERTIFIED values (269734834, 1);
insert into CERTIFIED values (269734834, 2);
insert into CERTIFIED values (269734834, 3);
insert into CERTIFIED values (269734834, 4);
insert into CERTIFIED values (269734834, 5);
insert into CERTIFIED values (269734834, 6);
insert into CERTIFIED values (269734834, 7);
insert into CERTIFIED values (269734834, 8);
insert into CERTIFIED values (269734834, 9);
insert into CERTIFIED values (269734834, 10);
insert into CERTIFIED values (269734834, 11);
insert into CERTIFIED values (269734834, 12);
insert into CERTIFIED values (269734834, 13);
insert into CERTIFIED values (269734834, 14);
insert into CERTIFIED values (269734834, 15);
insert into CERTIFIED values (552455318, 7);
insert into CERTIFIED values (556784565, 5);
insert into CERTIFIED values (556784565, 2);
insert into CERTIFIED values (556784565, 3);
insert into CERTIFIED values (573284895, 3);
insert into CERTIFIED values (573284895, 4);
insert into CERTIFIED values (573284895, 5);
insert into CERTIFIED values (574489456, 8);
insert into CERTIFIED values (574489456, 6);
insert into CERTIFIED values (574489457, 7);
insert into CERTIFIED values (242518965, 2);
insert into CERTIFIED values (242518965, 10);
insert into CERTIFIED values (141582651, 2);
insert into CERTIFIED values (141582651, 10);
insert into CERTIFIED values (141582651, 12);
insert into CERTIFIED values (011564812, 2);
insert into CERTIFIED values (011564812, 10);
insert into CERTIFIED values (356187925, 6);
insert into CERTIFIED values (159542516, 5);
insert into CERTIFIED values (159542516, 7);
insert into CERTIFIED values (090873519, 6);
