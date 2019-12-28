create table devices
(
devid integer NOT NULL,
dtext char(30),
dtype integer,
numstates integer,
initval integer,
dicon char(20),
primary key (devid),
foreign key (dtype) references devicetypes(dtype)
);