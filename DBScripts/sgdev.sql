create table sgdev
(
devgr int,
devid int,
fromval int,
toval int,
primary key (devgr, devid),
foreign key (devgr) references devicegroups(devgr),
foreign key (devid) references devices(devid)
);
