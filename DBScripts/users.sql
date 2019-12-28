create table users
(
username char(20) NOT NULL,
password char(20),
superuser int,
primary key (username)
);