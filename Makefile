all: build

build:
	g++ -o cs424p3 -std=c++17 -lpthread *.cpp

vscode_build:
	g++ -o p3main -std=c++17 -lpthread *.cpp

test1manual: build
	./cs424p3 manual ./424-p3-test1.txt

test1auto: build
	./cs424p3 auto ./424-p3-test1.txt

test2manual: build
	./cs424p3 manual ./424-p3-test2.txt

test2auto: build
	./cs424p3 auto ./424-p3-test2.txt

clean:
	rm a.out
	rm cs424p3