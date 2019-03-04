

bing : main.o bing.o cJSON.o configure.o
	cc main.o bing.o cJSON.o configure.o -lcurl -o bing
	compile successfully, next using `make install` 

main.o : src/main.c
	cc -c src/main.c

bing.o : src/bing.c
	cc -c src/bing.c

cJSON.o : src/cJSON.c
	cc -c src/cJSON.c

configure.o : src/configure.c
	cc -c src/configure.c


# install application
install :
	-mkdir ~/.bing
	-mkdir ~/Bing
	cp doc/bing-configure.json ~/.bing/bing-configure.json
	sudo cp bing /usr/bin/bingbing

	echo installed successfully!

clean:
	rm -rf *.o
	rm -rf bing	
