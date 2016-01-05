CC = icc

IPATH = ./

MKL_ROOT = /u/local/compilers/intel/13.0/mkl/
MKL_PATH = $(MKL_ROOT)/lib/intel64/
MKLFLAGS = -Wl,--start-group  $(MKL_PATH)/libmkl_intel_lp64.a $(MKL_PATH)/libmkl_gnu_thread.a $(MKL_PATH)/libmkl_core.a -Wl,--end-group
LDFLAGS = -lpthread -lm -ldl $(MKLFLAGS)

OUT = spaq
CFLAGS = -O3 -m64 -openmp -std=c99 -I$(IPATH)

all: spa_run

spa.o: spa.cpp spa.h spa_util.h spa_io.h spa_types.h
	$(CC) -c $(CFLAGS) spa.cpp

spa_util.o: spa_util.cpp spa_util.h
	$(CC) -c $(CFLAGS) spa_util.cpp

spa_io.o: spa_io.cpp spa_types.h
	$(CC) -c $(CFLAGS) spa_io.cpp

spa_run: spa.o spa_util.o spa_io.o
	$(CC) $(CFLAGS) spa.o spa_util.o spa_io.o $(LDFLAGS) -o $(OUT)

clean:
	rm -f *.o
	rm $(OUT)
