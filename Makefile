CXX=g++
INSTALL=install
CFLAGS=$(shell pkg-config --cflags sqlite3) -fPIC -I/usr/include/apt-pkg
LIBS=-lapt-pkg
prefix=/usr

.PHONY : install test clean

debversions.so : debversions.cc
	${CXX} -shared -o $@ ${CFLAGS} -W -Werror debversions.cc ${LIBS} -Wl,-z,defs

test:
	(cd test ; ./test.sh)

install : debversions.so
	${INSTALL} -pD -m755 debversions.so ${DESTDIR}${prefix}/lib/sqlite3/debversions.so

clean :
	-rm -f debversions.so
