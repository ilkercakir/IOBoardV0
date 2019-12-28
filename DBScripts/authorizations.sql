create table authorizations
(
username char(20) NOT NULL,
devid integer NOT NULL,
level char(1),
primary key (username, devid),
foreign key (username) references users(username),
foreign key (devid) references devices(devid)
);