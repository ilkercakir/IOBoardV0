create table rules
(
rulid int NOT NULL,
rultx char(30),
intid int,
primary key (rulid),
foreign key intid references intervals(intid)
);
