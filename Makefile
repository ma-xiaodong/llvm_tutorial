LLVM_INC = -I/usr/include/llvm-6.0 -I/usr/include/llvm-c-6.0
LIBS = `llvm-config-6.0 --libs`

compiler: ./src/compiler.cc
	g++ -g -O0 ./src/compiler.cc -o ./build/compiler
run:
	./build/compiler < ./data/input
llvm_compiler: ./src/llvm_compiler.cc
	clang++ ${LLVM_INC} ./src/llvm_compiler.cc -o ./build/llvm_compiler ${LIBS}
