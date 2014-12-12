#include "libbuf.h"

#define BUF_SIZE 16

char* read_buf(int fd) 
{
	char* buffer = (char*)malloc(BUF_SIZE * sizeof(char));
	char* result_str = NULL;
	int readed = 0;
	while((readed = read(fd, buffer, BUF_SIZE)) > 0) 
	{
		if (result_str == NULL) 
		{
			result_str = (char*)calloc(readed + sizeof(char), 1);
		} 
		else 
		{
			result_str = realloc(result_str, (strlen(result_str) + 1) * sizeof(char) + readed);
		}
		strncat(result_str, buffer, readed);
	}
	if (readed < 0) 
	{
		printf("Can't read string\n");
		exit(-1);
	}
	free(buffer);
	return result_str;
}

void write_buf(char* str, int fd) 
{
	int size = strlen(str);
	int current = 0;
	    if(size < BUF_SIZE)
	    {
	        int len = write(fd, str, size);
	        if(len < 0)
	        {
	            printf("can't write\n");
	        }
	        while(len > 0)
	        {
	            current += len;
	            len = write(fd, str + current, size - current);
	        }
	    }
	    else
	    {
	        int len = write(fd, str, BUF_SIZE);
	        current = len;
	        if(len < 0)
	        {
	            printf("can't write\n");
	        }
	        while((len > 0) && (current != size))
	        {
	            if(size - current > BUF_SIZE)
	            {
	                len =  write(fd, str + current, BUF_SIZE);
	            }
	            else
	            {
	                len = write(fd, str + current, size - current);
	            }
	            current += len;
	        }
	    }
}
