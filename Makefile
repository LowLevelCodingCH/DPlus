clean:
	rm dpc

build:
	gcc -o dpc src/dpc.cc -lstdc++ -lc -lm
