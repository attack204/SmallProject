#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/mman.h>

int main(int argc, char const *argv[]) {

    if ( argc != 2 ) {
        printf("usage:%s %s\n", argv[0], "filename");
        return -1;
    }
    int fd = -1;
    fd = open( argv[1], O_RDWR );
    if( -1 == fd ) {
	printf("error open file");
        return -1;
    } else {
	char *start;
    	char buf[10001];
	start = (char *)mmap(NULL, 128, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
	strcpy(start, "Hello World");
	munmap(start, 128);
    }
    close( fd );
    return 0;
}