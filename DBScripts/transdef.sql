create table transdef
(
 traid int NOT NULL,
 staidfrom int NOT NULL,
 staidto int NOT NULL,
 agrid int NOT NULL,
 primary key (traid),
 foreign key (staidfrom) references states(staid),
 foreign key (staidto) references states(staid),
 foreign key (agrid) references agdev(devgr)
);