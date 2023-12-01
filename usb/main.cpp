#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<termios.h>

int fd;

int open_serial()
{
    fd = open("/dev/ttyACM0",O_RDWR | O_NOCTTY | O_NONBLOCK);
    if(fd == -1)
    {
        perror("open serial porterror!\n");
        return -1;
    }

    printf("Open serial portsuccess!");
    return 0;
}

int main(int argc, char*argv[])
{
    unsigned char sbuf[] = {0};
    int retv;
    struct termios option;

    retv =open_serial();
    if(retv <0)
    {
        perror("open serial porterror!\n");
        return -1;
    }

    printf("Ready for sendingdata...\n");

    tcgetattr(fd,&option);
    cfmakeraw(&option);

    tcsetattr(fd, TCSANOW,&option);

    int length =sizeof(sbuf);
    retv = write(fd, sbuf,length);
    if(retv == -1)
    {
        perror("Write dataerror!\n");
        return -1;
    }

    printf("The number of charsent is %d\n", retv);
    return 0;
}