.load "../debversions.so"
create table versions (version STRING);
insert into versions values("1.0-1~lucid1");
insert into versions values("1.0-1");
SELECT version FROM versions ORDER BY version COLLATE debversion_compare;


