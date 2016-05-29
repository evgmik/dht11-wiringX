GCC_INCLUDE = /root/src/wiringX/src
GCC_LIBDIRS = /root/src/wiringX/build
GCC_LIBS = wiringX

dht11: dht11.c
	gcc -I$(GCC_INCLUDE) -L$(GCC_LIBDIRS) -l$(GCC_LIBS) $< -o $@

	
