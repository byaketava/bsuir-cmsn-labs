#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <unistd.h>
#include <ctype.h>

typedef struct
{
    char *name;
    pid_t pid;
} child_t;

char *CHILD_PATH;
child_t *children = NULL;
int children_count = 0;
volatile sig_atomic_t wait_resume = false;

void launch_child()
{
    static int child_id = 0;
    char child_name[10];
    snprintf(child_name, sizeof(child_name), "child_%02d", child_id);
    char full_path[256];
    snprintf(full_path, strlen(CHILD_PATH) + 10, "%s/child", CHILD_PATH);

    printf("Prepare %s\n", full_path);
    if (access(full_path, X_OK))
    {
        printf("Child path not found or not executable\n");
        return;
    }

    printf("Launching %s\n", child_name);
    child_id++;
    if (child_id > 99)
    {
        printf("Child counter reset to 0\n");
        child_id = 0;
    }

    int pid = fork();
    if (pid == -1)
    {
        printf("Error forking: %s\n", strerror(errno));
        return;
    }
    if (pid == 0)
    {
        char *args[] = {child_name, NULL};
        execv(full_path, args);
    }
    else
    {
        children = realloc(children, sizeof(child_t) * (children_count + 1));
        children[children_count].name = strdup(child_name);
        children[children_count].pid = pid;
        children_count++;
    }
}

void kill_one(child_t child)
{
    printf("Killing %s (PID %d)\n", child.name, child.pid);
    kill(child.pid, SIGKILL);
    waitpid(child.pid, NULL, 0);
    free(child.name);
}

void kill_last()
{
    if (children_count == 0)
    {
        printf("No children to kill\n");
        return;
    }
    kill_one(children[children_count - 1]);
    children_count--;
}

void list_children()
{
    printf("Parent: %d\n", getpid());
    for (int i = 0; i < children_count; i++)
        printf("%s: %d\n", children[i].name, children[i].pid);
}

void kill_children()
{
    for (int i = 0; i < children_count; i++)
        kill_one(children[i]);
    free(children);
    children = NULL;
    children_count = 0;
}

void generic_child_action(int child_id, int action)
{
    if (child_id == -1)
    {
        for (int i = 0; i < children_count; i++)
            sigqueue(children[i].pid, SIGRTMIN, (union sigval){.sival_int = action});
    }
    else
    {
        if (child_id >= children_count)
        {
            printf("Child with id %d not found\n", child_id);
            return;
        }
        sigqueue(children[child_id].pid, SIGRTMIN, (union sigval){.sival_int = action});
    }
}

void disallow_stats(int child_id)
{
    generic_child_action(child_id, 1);
}

void allow_stats(int child_id)
{
    generic_child_action(child_id, 2);
}

void force_print_stats(int child_id)
{
    generic_child_action(child_id, 3);
}

void sigint_handler(int sig)
{
    (void)sig;
    kill_children();
}

void alarm_handler(int sig)
{
    (void)sig;
    if (!wait_resume)
        allow_stats(-1);
    signal(SIGALRM, alarm_handler);
}

int parse_number()
{
    int child_id = 0;
    bool is_num = false;
    while (true)
    {
        char next = getchar();
        if (isspace(next) || next == EOF)
            break;
        is_num = true;
        child_id = child_id * 10 + (next - '0');
    }
    return is_num ? child_id : -1;
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <child_path>\n", argv[0]);
        return 1;
    }

    CHILD_PATH = argv[1];
    if (access(CHILD_PATH, F_OK))
    {
        printf("Child path not found\n");
        return 1;
    }

    signal(SIGINT, sigint_handler);

    char c;
    while ((c = getchar()) != EOF)
    {
        switch (c)
        {
            case '+':
                launch_child();
                break;
            case '-':
                kill_last();
                break;
            case 'l':
                list_children();
                break;
            case 'k':
                kill_children();
                break;
            case 's':
                disallow_stats(parse_number());
                break;
            case 'g':
                wait_resume = true;
                allow_stats(parse_number());
                break;
            case 'p':
                disallow_stats(-1);
                force_print_stats(parse_number());
                wait_resume = false;

                struct sigaction alarm_act = {0};
                alarm_act.sa_handler = alarm_handler;
                alarm_act.sa_flags = SA_RESTART;

                sigaction(SIGALRM, &alarm_act, NULL);
                alarm(5);
                break;
            case 'q':
                kill_children();
                exit(EXIT_SUCCESS);
            case '\n':
                continue;
            default:
                printf("Unknown option: %d\n", c);
                break;
        }
    }
    return 0;
}