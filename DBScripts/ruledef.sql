create table ruledef
(
rulid int NOT NULL,
sgrid int NOT NULL,
agrid int NOT NULL,
primary key (rulid),
foreign key (sgrid) references devicegroups(devgr),
foreign key (agrid) references devicegroups(devgr)
);
