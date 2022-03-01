#include <sys/ioctl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <unistd.h>
void sendTTY(int ptty_fd, char* message, int len)
{
        for (int i = 0; i < len; i++) ioctl(ptty_fd, TIOCSTI, message+i);
}

int main(int argc, char** argv)
{
        if (argc != 3) printf("./program /dev/pts/N file\n");
        else
        {
                int fd = open(argv[2], O_RDONLY);
                int len = lseek(fd,0, SEEK_END);
                char* data = mmap(0, len, PROT_READ, MAP_PRIVATE, fd, 0);
                int pts_fd = open(argv[1], O_RDWR);
                sendTTY(pts_fd, data, len);
        }
}
