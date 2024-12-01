CC=g++ -std=c++20 -g -Wall

a:
	${CC} -o a.out dayDAYa.cpp

b:
	${CC} -o b.out dayDAYb.cpp

clean:
	rm -f a b

atest: a
	./a.out

btest: b
	./b.out

arun: a
	./a.out < input

brun: b
	./b.out < input

.PHONY: a b clean atest btest arun brun
