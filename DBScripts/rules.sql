create table rules
(
sgrid int NOT NULL,
agrid int NOT NULL,
interval NOT NULL,
primary key (sgrid, agrid),
foreign key (sgrid) references devicegroups(devgr),
foreign key (sgrid) references devicegroups(devgr),
foreign key (interval) references intervals(intid),
);
