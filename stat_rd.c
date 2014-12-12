#include "libbuf.h"

#define FILE "mmap.dat"
#define RESULT "Work done\n"

void func(int signo) {}

int main(int argc, char *argv[]) 
{
	sigset_t set;	
	struct sigaction act;
	act.sa_handler = func;
	sigfillset(&act.sa_mask);
	sigaction(SIGUSR1, &act, NULL);
	sigemptyset(&set);
	sigsuspend(&set);

	int fd;
	if((fd = open(FILE, O_RDWR)) < 0) 
	{
		printf("Can't open a file\n");
		exit(-1);
	}
	
	size_t length;
	length = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);

	int length_res;
	length_res = (length + strlen(RESULT)) * sizeof(char);

	if(ftruncate(fd, length_res) < 0) 
	{
		printf("Can't resize the file\n");
		exit(-1);
	}

	char *ptr;
	if((ptr = (char *)mmap(NULL, length_res, PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED) 
	{
		printf("Can't mmap a file\n");
		exit(-1);
	}

	if(close(fd) < 0) 
	{
		printf("Can't close the file\n");
	}

	char *tmp_ptr;
	tmp_ptr = ptr;
	strcat(tmp_ptr, RESULT);

	if(munmap((void *)ptr, length_res) < 0) 
	{
		printf("Can't stop mapping\n");
		exit(-1);
	}
}
