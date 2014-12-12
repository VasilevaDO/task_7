#include "librdwr.h"

#define FILE_SIZE 1024*1024 

//надо переделать то, что сверху

void p(int signo) {}

int main(int argc, char** argv)
{
    int fd = open("mmap.dat", O_CREAT | O_RDWR, 0666); //создаём или открываем файл mmap.dat
    if(fd < 0)
    {
        printf("Сan't create/open file\n");
        exit(-1);
    }

    char* recieve = mmap(NULL, FILE_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0); 
//отображаем его в оперативку как в предыдущей проге (см. stat_wr)
    if(recieve == MAP_FAILED )
    {
        printf("Mapping failed!\n");
    }
/*
В последуюших 7 строчках мы ждём сигнала от первой проги, разрешающего нам работать.
Функции работы с сигналами полностью слизаны лекций, так что оно всё работает так, как надо
*/
    sigset_t set;

    struct sigaction sigact;
    sigact.sa_handler = p;
    sigfillset(&sigact.sa_mask);
    sigaction(SIGUSR1, &sigact, NULL);
    sigemptyset(&set);
    sigsuspend(&set);
//нам нужен (а нахрена, кстати? без него можно) размер файла mmap.dat
    struct stat* buf = (struct stat*)calloc(1, sizeof(struct stat));

    if(stat("mmap.dat"
            , buf) < 0)
    {
        printf("problem\n");
        exit(-1);
    }
//Пишем в mmap.dat коронную фразу и победоносно вылетаем из проги с освобождением памяти.
    strcat(recieve, "Work done\n");
    //NMUNMAPPING AND CLOSING
    if(munmap((void*)recieve, strlen(recieve)) < 0)
    {
        printf("mistake in manmap\n");
        exit(-1);
    }
    close(fd);
//Ура, товарищи!
}

