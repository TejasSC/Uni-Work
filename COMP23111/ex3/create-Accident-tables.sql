create table person (
       driver_id integer,
       name varchar(20),
       address varchar(20),
       primary key (driver_id)
);

create table car (
       license varchar(10),
       model varchar(20),
       year integer,
       primary key (license)
);

create table accident (
       report_number integer,
       accident_date date,
       location varchar(20),
       primary key (report_number)
);

create table owns (
       driver_id integer,
       license varchar(10),
       primary key (driver_id,license),
       foreign key (driver_id) references person,
       foreign key (license) references car
);

create table participated (
       report_number integer,
       license varchar(10),
       driver_id integer,
       damage_amount integer,
       primary key (report_number,license),
       foreign key (license) references car,
       foreign key (report_number) references accident
);
