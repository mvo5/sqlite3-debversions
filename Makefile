CXX=g++
INSTALL=install
CFLAGS=$(shell pkg-config --cflags sqlite3) -fPIC -I/usr/include/apt-pkg
LIBS=-lapt-pkg
prefix=/usr

.PHONY : install clean

debversions.so : debversions.c
	${CXX} -shared -o $@ ${CFLAGS} -W -Werror debversions.c ${LIBS} -Wl,-z,defs

install : debversions.so
	${INSTALL} -pD -m755 pcre.so ${DESTDIR}${prefix}/lib/sqlite3/debversions.so

clean :
	-rm -f debversions.so
