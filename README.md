# Sqlite extension to sort by Debian version numbers

This is a simple extension for sqlite to perform sort by
debian version number. A example should demo how it works:

```
# load extension
sqlite> .load "/usr/lib/sqlite3/debversions.so"

# create table
sqlite> create table packages (name STRING, version STRING);
sqlite> insert into packages values("apt", "1.0-1");
sqlite> insert into packages values("apt", "1.0-1~ppa1");

# run with the custom collate to ensure its sorted according to debian versions
sqlite> SELECT version FROM packages ORDER BY version COLLATE debversion_compare;
1.0-1~ppa1
1.0-1
```

As opposed to the normal string sorting that results in:
```
sqlite> SELECT version FROM packages ORDER BY version;
1.0-1
1.0-1~ppa1
```
