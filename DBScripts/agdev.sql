create table agdev
(
devgr int,
devid int,
value int,
primary key (devgr, devid),
foreign key (devgr) references devicegroups(devgr),
foreign key (devid) references devices(devid)
);
