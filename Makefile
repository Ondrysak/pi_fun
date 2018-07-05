build:
	gcc zalivka.c -o zalivka bcm2835.c
run: build
	sudo ./zalivka zalivka.conf
