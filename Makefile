compiler: ./src/compiler.cc
	g++ ./src/compiler.cc -o ./build/compiler
run:
	./build/compiler < ./data/input

