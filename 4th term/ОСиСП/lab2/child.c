#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[], char *envp[]) {
    printf("Child process %s\n", argv[0]);
    printf("File Name: %s\n", argv[1]);
    printf("PID: %d\n", getpid());
    printf("PPID: %d\n", getppid());
    printf("Environment variables:\n");

    FILE *file = fopen(argv[1], "r");
    if (file == NULL) {
        perror("Failed to open file");
        exit(1);
    }

    char var_name[100];
    while (fscanf(file, "%s", var_name) != EOF) {
        printf("%s: %s\n", var_name, getenv(var_name));
    }
    printf("\n");

    fclose(file);

    return 0;
}