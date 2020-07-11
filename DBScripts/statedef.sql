create table statedef
(
staid int NOT NULL,
sgrid int NOT NULL,
primary key (staid),
foreign key (sgrid) references devicegroups(devgr)
);