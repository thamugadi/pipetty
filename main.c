#include <sys/ioctl.h>
#include <sys/mman.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>
int sendTTY(int ptty_fd, char* message, int len)
{
        int success;
        for (int i = 0; i < len; i++) {
                success = ioctl(ptty_fd, TIOCSTI, message+i);
                if (success) return success;
        }
        return success;
}

int main(int argc, char** argv)
{
        if (argc != 3){
                printf("./program /dev/pts/N file\n");
                return -1;
        }
        unsigned char clearSymbols[] = {0x1B,0x63,0x0A};
        int fd = open(argv[2], O_RDONLY);
        int len = lseek(fd,0, SEEK_END);
        char* data = mmap(0, len, PROT_READ, MAP_PRIVATE, fd, 0);
        int pts_fd = open(argv[1], O_RDWR);
        int s;
        s = sendTTY(pts_fd, data, len);
        sleep(2);
        write(pts_fd, clearSymbols, 3);
}

