#include <stdio.h>
#include <sys/shm.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    int segment_id;
    char * shared_memory;
    const int size = 4096;

    segment_id = shmget(IPC_PRIVATE, size, S_IRUSR | S_IWUSR);
    shared_memory = (char *) shmat(segment_id, NULL, 0);
    pid_t pid = fork();

    if (pid == 0) {
        shared_memory = (char *) shmat(segment_id, NULL, 0);
        printf("Child write: Hi There!\n");
        sprintf(shared_memory, "Hi There!");
    }

    else {
        wait(NULL);
        printf("Parent read: %s\n", shared_memory);
        shmdt(shared_memory);
        shmctl(segment_id, IPC_RMID, NULL);
    }
    return 0;
}