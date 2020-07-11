create table states
(
staid int NOT NULL,
statx char(30),
intid int,
primary key (staid),
foreign key (intid) references intervals(intid)
);