#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>
#include <string.h>
#include <limits.h>


#define CODESIZE 1024 // Change this value as needed

/* Structure to inject into remote process. Contains 
 function pointers and code to execute. */
typedef struct _SELFDEL
{
    struct _SELFDEL *Arg0;      // pointer to self
    unsigned char opCodes[CODESIZE]; // code 
    pid_t hParent;              // parent process pid
    void (*fnWaitForSingleObject)(void *);
    void (*fnCloseHandle)(void *);
    int (*fnUnlink)(const char *);
    void (*fnSleep)(unsigned int);
    void (*fnExit)(int);
    int fRemDir;
    char szFileName[PATH_MAX];  // file to delete
} SELFDEL;

/* Routine to execute in remote process.  */
static void remote_thread(SELFDEL *remote)
{
    // wait for parent process to terminate
    void *status;
    pthread_join(pthread_self(), &status);
    // try to delete the executable file 
    while(remote->fnUnlink(remote->szFileName) == -1)
    {
        // failed - try again in one second's time
        remote->fnSleep(1);
    }
    // finished! exit so that we don't execute garbage code
    remote->fnExit(0);
}

/*  Delete currently running executable and exit     */
int SelfDelete(int fRemoveDirectory, const char *executableName)
{
    SELFDEL local = {0};
    pid_t pid = fork();

    if (pid == 0) { // child process
        // copy in binary code
        memcpy(local.opCodes, &remote_thread, CODESIZE);
        local.fnWaitForSingleObject = (void (*)(void *))pthread_join;
        local.fnCloseHandle = (void (*)(void *))pthread_detach;
        local.fnUnlink = unlink;
        local.fnSleep = (void (*)(unsigned int))sleep;
        local.fnExit = exit;
        local.fRemDir = fRemoveDirectory;
        getcwd(local.szFileName, PATH_MAX);
        strcat(local.szFileName, "/");
        strcat(local.szFileName, executableName);
        // Give remote process a copy of our own process pid
        local.hParent = getpid();
        // create detached thread
        pthread_attr_t attr;
        pthread_attr_init(&attr);
        pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
        pthread_t tid;
        int rc = pthread_create(&tid, &attr, (void *(*)(void *))&remote_thread, &local);
        pthread_attr_destroy(&attr);

        // sleep for a second before exiting
        sleep(1);
        return 0;
}
}

int main(int argc, char *argv[])
{
    SelfDelete(1, argv[0]);
}