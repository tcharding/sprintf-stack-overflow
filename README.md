Buffer overflow caused by use of sprintf()
==========================================

If the format string passed into sprintf() generates a string longer than the
destination buffer a buffer overflow will occur.

Usage
-----

Build and run.  Execution ends in seg fault due to buffer overflow.

	g++ -g -fno-stack-protector -no-pie -o demo demo.cpp
	./demo
	sprintf() buffer overflow demo.
	Please enter a string: randomstring
	buffer overflows here ->randomstring
	[1]    2521 segmentation fault (core dumped)  ./demo

Build without compiler stack protection

	g++ -g -o demo demo.cpp
	./demo
	sprintf() buffer overflow demo.
	Please enter a string: saontusaotneusaonteusaonte
	buffer overflows here ->saontusaotneusaonteusaonte
	*** stack smashing detected ***: <unknown> terminated
	[1]    2584 abort (core dumped)  ./demo
