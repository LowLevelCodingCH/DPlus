clean:
	rm dpc

build:
	gcc -static -o dpc src/dpc.cc -lstdc++ -lc -lm
