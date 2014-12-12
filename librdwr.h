/*
В библиотеке мы, ясен пень, объявляем функции
Ненужные нам я стёрла к чертям собачим
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

char* intochar(int num);
