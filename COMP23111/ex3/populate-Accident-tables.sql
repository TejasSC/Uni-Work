
insert into person values (1, 'Jane Rowling', 'Yate');
insert into person values (2, 'Kelly Woolf', 'Kensington');
insert into person values (3, 'Penelope Byatt', 'Sheffield');
insert into person values (4, 'Antonia Austen', 'Steventon');
insert into person values (5, 'Thomas Thackeray', 'Kolkata');
insert into person values (6, 'William Hardy', 'Stinsford');
insert into person values (7, 'George Wells', 'Bromley');
insert into person values (8, 'Herbert Orwell', 'Motihari');

insert into car values ('CGZ 2085', 'Ford Fiesta', 2000);
insert into car values ('CGZ 2140', 'Nissan Pulsar', 2016);
insert into car values ('KUY 629', 'Renault Megane', 2013);
insert into car values ('2 TPO', 'Ford Mondeo', 2010);
insert into car values ('550 MPC', 'Mini Convertible', 2016);
insert into car values ('790 GXC', 'Mazda 5', 2016 );
insert into car values ('567 UYJ', 'Ford Fiesta', 2001);
insert into car values ('JNP 6', 'Ford Fiesta', 2005);
insert into car values ('JD 8645', 'Renault Megane', 2013 );
insert into car values ('KUY 926', 'Renault Megane', 2013 );

insert into accident values (7879432, '07-JUL-05' , 'Manchester');
insert into accident values (8779342, '07-JUL-15' , 'Bolton');
insert into accident values (7784932, '08-JUL-10' , 'Burnley');
insert into accident values (7798432, '31-MAR-07' , 'Manchester');
insert into accident values (7794382, '28-FEB-16' , 'Manchester');
insert into accident values (7897423, '24-DEC-12' , 'Stockport');

insert into owns values (1, 'CGZ 2085');
insert into owns values (1, 'CGZ 2140');
insert into owns values (2, 'KUY 629');
insert into owns values (8, '2 TPO');
insert into owns values (6, '550 MPC');
insert into owns values (3, '790 GXC');
insert into owns values (4, '567 UYJ');
insert into owns values (2, 'JNP 6');
insert into owns values (7, 'JD 8645');
insert into owns values (5, 'KUY 926');

insert into participated values (7879432, 'CGZ 2140', 1, 1000);
insert into participated values (8779342, 'CGZ 2140', 2, 2000);
insert into participated values (7784932, '2 TPO', 6, 500);
insert into participated values (7784932, 'CGZ 2085', 1, 3500);
insert into participated values (7897423, 'JD 8645', 6, 4000);
insert into participated values (7897423, 'JNP 6', 2, 2000);
insert into participated values (7897423, 'KUY 629', 5, 250);


