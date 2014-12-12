#include "libbuf.h"

#define FILE "mmap.dat"

int main(int argc, char* argv[]) 
{

	if(argc < 2) 
	{
		printf("Invalid arguments\n");
		exit(-1);
	}

	int fd;
	if((fd = open(FILE, O_WRONLY | O_CREAT, 0666)) < 0) 
	{
		printf("Can't open a file\n");
		exit(-1);
	}

	DIR *dir;
	if((dir = opendir(argv[1])) == NULL) 
	{
		printf("Can't open a stream for the directory\n");
		exit(-1);
	}

	struct dirent *file;
	struct stat attr;

	while((file = readdir(dir)) != NULL) 
	{
		char *name = (char *)calloc(500 + 1, sizeof(char));
		strcat(name, argv[1]);
		strcat(name, "/");
		strcat(name, file -> d_name);

		if(lstat(name, &attr) < 0) 
		{
			printf("Can't get attributes of a file\n");
			exit(-1);
		}
		
		free(name);
		//Да-да, мы знаем толк в извращениях, но работает ведь :)
		//Можно объединить всё это в одну строку, но пусть так живёт — так нагляднее
		//Если объединять, то везеде надо realloc делать, это замусорит код
		//Хотя куда уж мусорнее..
		
		if(S_ISLNK(attr.st_mode)) write_buf("l", fd);
		if(S_ISREG(attr.st_mode)) write_buf("-", fd);
		if(S_ISDIR(attr.st_mode)) write_buf("d", fd);
		if(S_ISCHR(attr.st_mode)) write_buf("c", fd);
		if(S_ISBLK(attr.st_mode)) write_buf("b", fd);
		if(S_ISFIFO(attr.st_mode)) write_buf("p", fd);
		if(S_ISSOCK(attr.st_mode)) write_buf("s", fd);

		if(((attr.st_mode) / 256) % 2) write_buf("r", fd);
		else write_buf("-", fd);
		if(((attr.st_mode) / 128) % 2) write_buf("w", fd);
		else write_buf("-", fd);
		if(((attr.st_mode) / 64) % 2) write_buf("x", fd);
		else write_buf("-", fd);
		if(((attr.st_mode) / 32) % 2) write_buf("r", fd);
		else write_buf("-", fd);
		if(((attr.st_mode) / 16) % 2) write_buf("w", fd);
		else write_buf("-", fd);
		if(((attr.st_mode) / 8) % 2) write_buf("x", fd);
		else write_buf("-", fd);
		if(((attr.st_mode) / 4) % 2) write_buf("r", fd);
		else write_buf("-", fd);
		if(((attr.st_mode) / 2) % 2) write_buf("w", fd);
		else write_buf("-", fd);
		if((attr.st_mode) % 2) write_buf("x", fd);
		else write_buf("-", fd);

		write_buf(" ", fd);
		char *str_nlink = (char *)calloc(1, sizeof(char));
		sprintf(str_nlink, "%d", attr.st_nlink);
		write_buf(str_nlink, fd);
		free(str_nlink);

		write_buf(" ", fd);
		write_buf((getpwuid(attr.st_uid)) -> pw_name, fd);

		write_buf(" ", fd);
		write_buf((getgrgid(attr.st_gid)) -> gr_name, fd);

		write_buf(" ", fd);
		char *str_size = (char *)calloc(1, sizeof(char));
		sprintf(str_size, "%jd", (intmax_t)attr.st_size);
		write_buf(str_size, fd);
		free(str_size);

		write_buf(" ", fd);
		write(fd, ctime(&attr.st_mtime) + 4, 3);

		write_buf(" ", fd);
		if(*(ctime(&attr.st_mtime) + 8) != ' ') 
		{
			write(fd, ctime(&attr.st_mtime) + 8, 2);
		} 
		else 
		{
			write(fd, ctime(&attr.st_mtime) + 9, 1);
		}
		
		write_buf(" ", fd);
		
		if(*(ctime(&attr.st_mtime) + 23) == '4') 
		{
			write(fd, ctime(&attr.st_mtime) + 11, 5);
		} 
		else 
		{
			write(fd, ctime(&attr.st_mtime) + 20, 4);
		}

		write_buf(" ", fd);
		write_buf(file -> d_name, fd);
		write_buf("\n", fd);

	}	

	if(closedir(dir) < 0) 
	{
		printf("Can't close a stream for the directory\n");
		exit(-1);
	}

	if(close(fd) < 0) 
	{
		printf("Can't close file\n");
	}
	
	kill(0, SIGUSR1);
}
