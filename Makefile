.PHONY: all
all: build ubuild

bin:
	mkdir bin
# To generate compiled main file
./bin/main: bin main.cpp ./include/graphAlgos.h ./include/myfn.h ./solve.cpp
	g++ -g -O2 -std=c++17 ./main.cpp -o ./bin/main

./bin/maintest: bin tester.cpp 
	g++ -g -O2 -std=c++17 ./tester.cpp -lgtest -lgtest_main -pthread -o ./bin/maintest

.PHONY: sample
sample: ./bin/main ./sample.input
	time ./bin/main < sample.input 

.PHONY: test
test: ./bin/main
	time ./scripts/test.sh

.PHONY: build
build: ./bin/main

ubuild: ./bin/maintest


.PHONY: clean
clean:
	rm -rf bin
	rm -f main
	rm -rf *.dSYM

.PHONY: ttest
ttest: 
	@WITHTIME=TRUE ./scripts/test.sh >& /tmp/test.time
	@egrep "test|real|---" /tmp/test.time