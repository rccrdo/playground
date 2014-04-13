SHELL = /bin/sh
CC = gcc -g -O2 -Wall

# ************     libla     **************
LIBLA_CFLAGS = -DLA_SCALAR_DOUBLE -I/home/riccardo/projects/libla/src
LIBLA_LDFLAGS = -lm

# ************     libplayground     **************
LIBPLAYGROUND_OBJ = src/pg.o
LIBPLAYGROUND_OBJ_BUILD_CFLAGS = -fPIC
LIBPLAYGROUND_BUILD_CFLAGS =
LIBPLAYGROUND_BUILD_LDFLAGS =
LIBPLAYGROUND_NAME = ./src/libplayground.so

LIBPLAYGROUND_CFLAGS = -I/home/riccardo/projects/playground/src
LIBPLAYGROUND_LDFLAGS = -L/home/riccardo/projects/playground/src -lplayground

.PHONY: all
    all: libplayground


.PHONY: libplayground
    libplayground: purge $(LIBPLAYGROUND_OBJ)
	$(CC) -shared -o $(LIBPLAYGROUND_NAME)  $(LIBPLAYGROUND_BUILD_LDFLAGS) $(LIBPLAYGROUND_OBJ)

# ************     libplayground objs rules     **************
./src/pg.o: ./src/pg.c
	$(CC) $(LIBPLAYGROUND_OBJ_BUILD_CFLAGS) $(LIBLA_CFLAGS) -c $^ -o $@



# ************       tests      **************
.PHONY: test-headers_sanity
test-headers_sanity: libplayground
	$(CC) -o $(LIBPLAYGROUND_NAME) -shared $(LIBPLAYGROUND_BUILD_LDFLAGS) $(LIBPLAYGROUND_OBJ)
	$(CC) -o ./test/headers_sanity $(LIBLA_CFLAGS) $(LIBLA_LDFLAGS) $(LIBPLAYGROUND_CFLAGS) $(LIBPLAYGROUND_LDFLAGS) ./test/headers_sanity.c
	exec ./test/headers_sanity

.PHONY: test-playground
test-playground: libplayground
	$(CC) -o $(LIBPLAYGROUND_NAME) -shared $(LIBPLAYGROUND_BUILD_LDFLAGS) $(LIBPLAYGROUND_OBJ)
	$(CC) -o ./test/playground $(LIBLA_CFLAGS) $(LIBLA_LDFLAGS) $(LIBPLAYGROUND_CFLAGS) $(LIBPLAYGROUND_LDFLAGS) ./test/playground.c
	exec ./test/playground


# ************     test objs rules     **************


# ************       clean and purge      **************
.PHONY: purge
purge: 
	-rm -f ./src/*~
	-rm -f ./src/*#
	-rm -f ./test/*~
	-rm -f ./test/*#
	-rm -f ./test/headers_sanity
	-rm -f *~
	-rm -f *#

