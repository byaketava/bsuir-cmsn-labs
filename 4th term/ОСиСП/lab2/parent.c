#define _POSIX_C_SOURCE 200112L

#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

extern char **environ;

int cmp(const void* str1, const void* str2) {
    return strcmp(*(const char**) str1, *(const char**) str2);
}

void print_sorted_environment() {
    int env_count = 0;
    while (environ[env_count] != NULL) {
        env_count++;
    }

    char **env = malloc(sizeof(char *) * (env_count + 1));
    if (env == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }

    for (int i = 0; i<env_count; i++) {
        env[i] = environ[i];
        if (env[i] == NULL) {
            perror("Memory allocation failed");
            exit(1);
        }
    }
    env[env_count] = NULL;

    qsort(env, env_count, sizeof(char *), cmp);

    for (int j = 0; env[j] != NULL; j++) {
        printf("%s\n", env[j]);
    }
    printf("\n");

    free(env);
}

int main(int argc, char *argv[], char *envp[]) {
    if(argc < 2) {
        printf("Incorrect number of arguments\n");
        exit(1);
    }

    if(setenv("LC_COLLATE", "C", 1)==-1) {
        printf("LC_COLLATE was not set\n");
    }

    char *child_path = getenv("CHILD_PATH");

    if (child_path == NULL) {
        printf("CHILD_PATH environment variable not set\n");
        exit(1);
    }

    int child_count = 0;

    print_sorted_environment();

    while (1) {
        char c = getchar();
        switch (c) {
            case '+': {
                switch(fork()) {
                    case -1:
                        perror("Fork failed");
                    exit(1);
                    case 0: // Child process
                    {
                        char child_name[10];
                        snprintf(child_name, sizeof(child_name), "child_%02d", child_count);
                        char *child_argv[] = {child_name,argv[1], NULL};
                        execve(getenv("CHILD_PATH"), child_argv, environ);
                        perror("Execve failed");
                        exit(1);
                    }
                    default: // Parent process
                        wait(NULL);
                        child_count++;
                    break;
                }
                break;
            }
            case '*': {
                switch(fork()) {
                    case -1:
                        perror("Fork failed");
                    exit(1);
                    case 0: // Child process
                    {
                        char child_name[10];
                        snprintf(child_name, sizeof(child_name), "child_%02d", child_count);
                        char *child_argv[] = {child_name,argv[1], NULL};
                        child_path = NULL;
                        for (int i = 0; envp[i] != NULL; i++) {
                            if (strncmp(envp[i], "CHILD_PATH=", 11) == 0) {
                                child_path = envp[i] + 11;
                                break;
                            }
                        }
                        if (child_path == NULL) {
                            printf("CHILD_PATH variable was not found\n");
                            exit(1);
                        }
                        execve(child_path, child_argv, environ);
                        perror("Execve failed");
                        exit(1);
                    }
                    default: // Parent process
                        wait(NULL);
                        child_count++;
                    break;
                }
                break;
            }
            case '&': {
                switch(fork()) {
                    case -1:
                        perror("Fork failed");
                    exit(1);
                    case 0: // Child process
                    {
                        char child_name[10];
                        snprintf(child_name, sizeof(child_name), "child_%02d", child_count);
                        char *child_argv[] = {child_name,argv[1], NULL};
                        child_path = NULL;
                        for (int i = 0; environ[i] != NULL; i++) {
                            if (strncmp(environ[i], "CHILD_PATH=", 11) == 0) {
                                child_path = environ[i] + 11;
                                break;
                            }
                        }
                        if (child_path == NULL) {
                            printf("CHILD_PATH variable was not found\n");
                            exit(1);
                        }
                        execve(child_path, child_argv, environ);
                        perror("Execve failed");
                        exit(1);
                    }
                    default: // Parent process
                        wait(NULL);
                        child_count++;
                    break;
                }
                break;
            }
            case 'q':
                printf ("End of parent process\n");
            exit(0);
            default:
                break;
        }
    }
    return 0;
}