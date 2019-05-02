Buffer overflow caused by use of sprintf()
==========================================

If the format string passed into sprintf() generates a string longer than the
destination buffer a buffer overflow will occur.

Explanation
-----------

In performance critical C applications often a local character array, i.e. a
stack allocated buffer, is used since allocating memory using a memory allocator
call like malloc() can be slow.  For example:

	void fn()
	{
		char buf[COMPILE_TIME_CONSTANT];
		...
	}

What ever the size we choose for this buffer it must be known at compile time.
If data comes from an untrusted source and is to be put into this buffer care
must be taken.

We will iterate over a number of vulnerabilities in code that uses a stack
buffer like this, making continued attempts at fixing the vulnerability and
seeing what results.

The vulnerable function

	#define BUF_SIZE 8

	void handleInputV1(const char *input)
	{
		char buf[BUF_SIZE];
	
		sprintf(buf, "%s", input);
	
		processBuffer(buf);
	}

See demo.cpp for full function definitions.

Here sprintf does no bounds checking, writing whatever is passed into the
function to the buffer.  If the input string is longer than BUF_SIZE the buffer
will overflow and memory corruption will occur.  A buffer overflow of this sort
can be use to overwrite the function return address.  If you have completed
'Triple Word Score' you will remember this type of attack.

Attempted fix version 1

As mention in the 'Triple Word Score' lab and also 'Take Note' using the C++
standard libraries IO functions is often safer than using the C standard library
functions.  There are 'safer' functions within the C standard library however,
one of which is snprintf().

snprintf() attempts to mitigate buffer overflow by only writing 'n' bytes to the
destination buffer.  Let's have a go at fixing the vulnerability by using
snprintf().

	void handleInputV2(const char *input)
	{
		char buf[BUF_SIZE];
	
		printf("input: %s\n", input);
		snprintf(buf, BUF_SIZE, "%s", input);
	
		processBuffer(buf);
	}

Unfortunately this code still has a vulnerability.  Can you see it?  snprintf()
writes at most BUF_SIZE bytes to the buffer.  If the input string is longer than
BUF_SIZE the buffer will be left without a null terminating byte.  C strings are
expected to be null terminated.  Many functions in the standard library, expect
a terminating null byte and will keep iterating over bytes until null is found,
for example:

	void processBuffer(char *buf)
	{
		char *ptr;

		for (ptr = buf; *ptr != '\0'; ptr++) {
			fprintf(stderr, "%c\n", *ptr);
		}
	}


When code like this runs what ever is in memory above the buffer (the stack
grows down remember) will be processed until a null byte is found.  If there is
sensitive data on the stack further up the current call chain _before_ we reach
a null byte then this data may be leaked.

Let's see the C code with both vulnerabilities fixed.  Even safer is to use the
C++ standard IO library functions.

	int handleInputV3(const char *input)
	{
		char buf[BUF_SIZE];
		int ret;

		if (ret >= BUF_SIZE) {
			fprintf(stderr, "input string too long, truncating ...\n");
			buf[BUF_SIZE-1] = '\0';
		}

		processBuffer(buf);

		return 0;
	}
