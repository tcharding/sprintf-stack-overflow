all: demo

demo: demo.cpp
#	g++ -g -fno-stack-protector -no-pie -o demo demo.cpp
	g++ -g -o demo demo.cpp

clean:
	rm demo
