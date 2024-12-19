CC=g++ -std=c++20 -g -Wall

a:
	${CC} -o a.out dayDAYa.cpp
	./a.out

b:
	${CC} -o b.out dayDAYb.cpp
	./b.out

.PHONY: a b
