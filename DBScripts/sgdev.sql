create table sgdev
(
devgr int NOT NULL,
devid int NOT NULL,
fromval int,
toval int,
primary key (devgr, devid),
foreign key (devgr) references devicegroups(devgr),
foreign key (devid) references devices(devid)
);
