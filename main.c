#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {

    char command[1024];
    char *args[64];

    while (1)
    {
        printf("mini-shell> ");
        fflush(stdout);

        if (fgets(command, sizeof(command), stdin) == NULL)
        {
            break;
        }
        char *newLine = strchr(command, '\n');
        if(newLine != NULL) {
            *newLine = '\0';
        }else {
            int ch = getchar();
            while(ch != '\n' && ch != EOF) {
                ch = getchar();
            }
            printf("%s\n", "shell: input too long");
            continue;
        }

        if (command[0] == '\0')
            continue;

        int i = 0;
        args[i] = strtok(command, " \t");
        while (args[i] != NULL && i < 63)
        {
            i++;
            args[i] = strtok(NULL, " \t");
        }
        if(args[i] != NULL) {
            printf("%s\n", "shell: too many arguments");
            continue;
        }
        args[i] = NULL;
        if (args[0] == NULL)
            continue;

        if (strcmp(args[0], "exit") == 0)
            break;

        if (strcmp(args[0], "cd") == 0)
        {
            char *target = args[1];
            if(args[1] != NULL && args[2] != NULL) {
                printf("%s\n", "cd: too many arguments");
                continue;
            }
            if(target == NULL) {
                target = getenv("HOME");
            }
            if(target == NULL) {
                printf("%s\n", "cd: HOME not set");
                continue;
            }
            if(chdir(target) == -1) {
                perror("cd");
            }
            continue;
        }

        pid_t pid = fork();
        if (pid == -1)
        {
            perror("fork");
            continue;
        }
        else if (pid == 0)
        {
            execvp(args[0], args);
            perror(args[0]);
            _exit(1);
        }
        else
        {
            waitpid(pid, NULL, 0);
        }
    }

    return 0;
}