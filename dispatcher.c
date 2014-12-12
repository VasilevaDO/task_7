#include "libbuf.h"

int main(int argc, char *argv[]) 
{

	pid_t res = fork();

    if(res > 0) 
	{
		execl("stat_wr", "stat_wr", "/bin", (char*) NULL);
		printf("Can't run stat_wr\n");
		exit(-1);
	} 
	else if(res == 0) 
	{
		execl("stat_rd", "stat_rd", "-o", (char*) NULL);
		printf("Can't run stat_rd\n");
		exit(-1);
	} 
	else 
	{
		printf("Can't fork a child\n");
		exit(-1);
	}
}

