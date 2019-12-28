create table devicetypes
(
dtype integer NOT NULL,
dtext char(20),
dstat integer,
categ char(1),
dicon char(20),
primary key (dtype),
foreign key (categ) references devcat(categ)
);