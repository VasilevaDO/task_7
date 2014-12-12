/*
В библиотеке мы, ясен пень, объявляем функции, а также некоторые структуры, которые нам понадобятся
позже.
*/

#pragma once 	// Препроцессорная директива, разработанная для контроля за тем, чтобы 
				// конкретный исходный файл при компиляции подключался строго один раз.
				// Это своеборазная защита от «двойного подключения» заголовочных файлов.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <grp.h>
#include <signal.h>
#include <pwd.h>
#include <errno.h>
#include <dirent.h>

#define VAL_NUM 968

char* readBuf(int fd, char* message, int size);
void writeBuf(int fd, char* message, int size);

typedef struct message
{
    long mtype;
    int val[VAL_NUM];
    int str;
    int strnum;
    int numb;
}connect2;

typedef struct threadarg
{
    long mtype;
    int* val;
    int str;
    int strnum;
    int id;
    int numb;
    int clnum;
}threadarg;

typedef struct mes1
{
    long mtype;
    char text[60];
    int numb;
}connect1;

char* intochar(int num);
