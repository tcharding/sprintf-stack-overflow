#include <iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;

#define MSG "buffer overflows here ->"
#define BUF_SIZE sizeof(MSG)

void overflowBuffer(string word) {
	char buf[BUF_SIZE];

	sprintf(buf, "%s%s", MSG, word.c_str());
	printf("%s\n", buf);
}

int main(void) {
	string input;
	
	cout << "sprintf() buffer overflow demo." << endl;
	cout << "Please enter a string: ";

	cin >> input;
	overflowBuffer(input);
	return 0;
}
