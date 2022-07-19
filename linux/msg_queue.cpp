/*父进程创建消息队列和两个子进程p1和p2
子进程p1打开给定文件（如果没有，则创建文件），并向文件中写数据，写完关闭文件，然后向消息队列写入一条消息“ok”,目的是通知进程p2可以读取文件内容了。
子进程p2从消息队列读取消息，如果收到消息“ok”,则打开文件，读取文件内容，并将其输出道屏幕上，关闭文件。
*/
#include<stdio.h>
#include<sys/msg.h>
#include<fcntl.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#define NUM 100
//消息通信
//消息队列提供了一种由一个进程向另一个进程发送块数据的方法。
//每一个数据块被看作有一个类型，接收进程可以独立接收具有不同类型的数据块。
struct Mymsg
{
        long mytype;  //存储消息类型
        char mytext[NUM];//存储消息内容
};

int main()
{
        FILE *f;   //文件指针
        pid_t p1,p2;// 两个进程
        key_t key; 
        key = ftok(".", 't');
        //系统IPC键值的格式转换函数
        char s[20];
        int mgsid;
        if((mgsid=msgget(key,IPC_CREAT|0666))==-1)//打开一个队列或创建一个新队列

        {
                printf("creat error\n");
                return -1;
        }

        p1=fork();
        if(p1<0)
        {
        fprintf(stderr,"fork failed");
        exit(-1);
        }
        else if(p1==0)
        {
            printf("p1 pid is:%d\n",getpid());  //p1id
            printf("sending the massage...\n");
            sleep(1);  //本线程休眠1毫秒
            struct Mymsg msg1;
            msg1.mytype=getppid(); //父进程id
            if((f=fopen("hello.txt","w"))==NULL) //打开文件失败
            {
                    printf("the file %s not open\n","hello.txt");
                    return 0;
            }
            fputs("hello!",f);//送一个字符到一个流中 
            fclose(f);
            strcpy(msg1.mytext,"ok");  
            if(msgsnd(mgsid,&msg1,sizeof(msg1.mytext),0)<0)//往消息队列写消息，即发送消息。

            {
                    printf("sending error!\n");
                    exit(-1);
            }
            else
            {
                    printf("complete sending !\n");
                    exit(0);
            }

        }
        else
        {
            wait(NULL);
            p2=fork();
            if(p2<0)
            {
                    printf("fork creat error!\n");
                    exit(1);
            }
            else if(p2==0)
            {
                    printf("p2 pid is:%d\n",getpid());
                    printf("Receiving the massage...\n");
                    sleep(1);//本线程休眠1毫秒
                    struct Mymsg msg2;
                    msg2.mytype=getppid();
                    if(msgrcv(mgsid,&msg2,NUM,getppid(),0)<0)//从消息队列读消息，即接收消息
                    {
                            printf("receving error!!!\n");
                            exit(1);
                    }
                    else
                    {
                            printf("complete receving \n");

                            if(strcmp("ok",msg2.mytext)==0)
                            {
                                    if((f=fopen("hello.txt","r"))==NULL)
                                    {
                                            printf("the file %s no opend.\n","hello.txt");
                                            return 0;
                                    }
                                    while((fgets(s,20,f))!=NULL)//从流中读一行或指定个字符
                                    {
                                            printf("the massage is:%s\n",s);
                                    }
                                    fclose(f);
                            }
                    }

                }
                else
                {
                    wait(NULL);
                    exit(0);
                }
        }
        return 0;
}