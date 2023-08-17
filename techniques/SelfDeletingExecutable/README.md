# Authorship information
* Nickname: 0xf00


# Technique Information
* Technique Title:  Self-Deletion: Process Manipulation
* Technique category:  Evasion
* Technique description: by utilizing threads and process manipulation within a Unix-like (OS) environment. This technique aims to achieve the deletion of the executable file during its own execution.


# Code snippet
```C
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
```

# Additional resources
https://0xf00i.github.io/2023/03/03/Self-Deleting-Executables.html