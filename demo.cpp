#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
using namespace std;

#define BUF_SIZE 8

/*
 * Example function processing a C string (null terminated
 * character array) byte by byte.
 */
void processBuffer(char *buf)
{
	char *ptr;

	fprintf(stderr, "\nProcessing input string: '%s'\n", buf);
	fprintf(stderr, "character by character ...\n\n");
	for (ptr = buf; *ptr != '\0'; ptr++) {
		fprintf(stderr, "%c\n", *ptr);
	}
}

/*
 * handleInputV1: Contains buffer overflow vulnerability.
 */
void handleInputV1(const char *input)
{
	char buf[BUF_SIZE];

	sprintf(buf, "%s", input);

	processBuffer(buf);
}

/*
 * handleInputV2: Contains a potential buffer overflow vulnerability
 * thanks to non-null terminated string if input is longer than buffer.
 */
void handleInputV2(const char *input)
{
	char buf[BUF_SIZE];

	printf("input: %s\n", input);
	snprintf(buf, BUF_SIZE, "%s", input);

	processBuffer(buf);
}

/*
 * A correct C way to parse un-trusted input data.
 */
int handleInputV3(const char *input)
{
	char buf[BUF_SIZE];
	int ret;

	ret = snprintf(buf, BUF_SIZE, "%s", input);
	if (ret >= BUF_SIZE) {
		fprintf(stderr, "input string too long, truncating ...\n");
		buf[BUF_SIZE-1] = '\0';
	}

	processBuffer(buf);

	return 0;
}

int main(void)
{
	const char *str = "this is a long string yes it is";
	int version;
	int i;
	
	fprintf(stderr, "Running buffer overflow example functions.\n\n");
	fprintf(stderr, "Buffer size is: %d bytes\n", BUF_SIZE);
	fprintf(stderr, "Function argument is: '%s'\n", str);
	printf("\nEnter handleInput function version number [1-3]: ");
	scanf("%d", &version);

	switch(version) {
	case 1:
		handleInputV1(str);
		break;
	case 2:
		handleInputV2(str);
		break;
	case 3:
		handleInputV3(str);
		break;
	default:
		fprintf(stderr, "unknown version number: %d (please choose 1, 2, or 3)\n");
		exit(1);
	}
	exit(0);
}
