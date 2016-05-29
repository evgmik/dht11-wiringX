# dht11 read out with wiringX library

The source of dht11.c was taken [from](http://www.rpiblog.com/2012/11/interfacing-temperature-and-humidity.html) and modified to be used with [wiringX](http://wiringx.org/). I was also using wiringX blinker example to do initial setup.

To compile and use:

- get the copy of [wiringX](http://wiringx.org/), I was using [rewrite branch](https://github.com/wiringX/wiringX/tree/rewrite)
- get this repository
- adjust makefile to point to the wiringX directory
- say `make`

I was testing it with bananaPI m2, so to execute I type
~~~~~~~
./dht11 bananapim2 1  
~~~~~~

Note that data pin of the dht11 chip is connected to gpio 1. See the wiringX documentation to verify its match  to the hardware pin 12.

