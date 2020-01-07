create table agdev
(
devgr int NOT NULL,
devid int NOT NULL,
value int,
primary key (devgr, devid),
foreign key (devgr) references devicegroups(devgr),
foreign key (devid) references devices(devid)
);
