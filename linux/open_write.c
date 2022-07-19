#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>


int main(int argc, char const *argv[]) {

    if ( argc != 2 ) {

        printf("usage:%s %s\n", argv[0], "filename");
        return -1;
    }

    int fd = -1;

    fd = open( argv[1], O_RDWR );

    if( -1 == fd ) {
        printf("文件打开失败,错误号:%d\n", errno );
        perror( "open" );
        return -1;
    }else {
        printf("文件打开成功\n");
    }

    char buf[] = "hello,程序猿编码";

    ssize_t count_num = write( fd, buf, sizeof(buf));
    printf("写入的字节数为%d", count_num);


    int count = lseek( fd, 0, SEEK_END );

    printf("文件大小为： %d\n", count);

    close( fd );
    return 0;
}

