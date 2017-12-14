#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <memory.h>

#define BUFSIZE		10*1024*1024
#define TEST_TIMES	30
int main(int argc, char** argv)
{
	int i = 0;
	int times = 0;
	int checksum_src = 0;
	int checksum_des = 0;
	char ch = 0x5A;
	char *bufsrc;
	char *bufdes;

	int test_time = 0;
	int test_size = 0;

	if(argc < 3)
	{
		test_time = TEST_TIMES;
		test_size = BUFSIZE;
		printf("	use defaut paras\n");			
		printf("	usage: ./ddr_testing times size(M)\n");
	}
	else
	{
		test_time = atoi(argv[1]);
		test_size = atoi(argv[2])*1024*1024;

		if(test_time < 1|| test_size < 1)
		{
			printf("	error paras\n");	
			printf("	use defaut paras\n");	
			test_time = TEST_TIMES;
			test_size = BUFSIZE;	
		}
	}

	printf("    DDR copy test start\n");
	printf("    Size: %dMB\n", test_size/1024/1024);
	printf("    Times: %d\n", test_time);

	for (times=0; times<test_time; times++)
	{
		bufsrc = (char*)malloc(test_size);
		bufdes = (char*)malloc(test_size);

		checksum_src = 0;
		checksum_des = 0;

		for (i=0; i<test_size-1; i++) {
			bufsrc[i] = ch;
			ch++;
			checksum_src = bufsrc[i] ^ checksum_src;
		}

		bufsrc[test_size-1] = checksum_src;

		memset(bufdes, test_size-1, 0xA5);
		memcpy(bufdes, bufsrc, test_size-1);

		for (i=0; i<test_size-1; i++) {
			checksum_des = bufdes[i] ^ checksum_des;
		} 

		if (checksum_des != checksum_src) {
			printf("    DDR CheckSum ERROR ... %d\ttimes=%d\n", checksum_des, times);
			return -1;
		} else {
			printf("    DDR CheckSum OK ... %d\ttimes=%d\n", checksum_des, times);
		}

		free(bufsrc);
		free(bufdes);
	}
	printf("    DDR test end\n");

	return 0;
}

