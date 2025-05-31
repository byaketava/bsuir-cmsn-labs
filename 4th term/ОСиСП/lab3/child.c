#define _XOPEN_SOURCE 500

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <signal.h>
#include <sys/prctl.h>

struct RacyStruct
{
    int a;
    int b;
} pair = {0, 0};

struct Stats
{
    int a0b0;
    int a0b1;
    int a1b0;
    int a1b1;
} stats = {0, 0, 0, 0};

volatile sig_atomic_t print = true;
char *CHILD_NAME;

void print_stats(bool action)
{
    if (action || print)
        printf("%s [PID %d] a0b0: %d a0b1: %d a1b0: %d a1b1: %d\n",
               CHILD_NAME, getpid(), stats.a0b0, stats.a0b1, stats.a1b0, stats.a1b1);
}

void alarm_handler(int sig)
{
    (void) sig;
    if (pair.a == 0 && pair.b == 0)
        stats.a0b0++;
    else if (pair.a == 0 && pair.b == 1)
        stats.a0b1++;
    else if (pair.a == 1 && pair.b == 0)
        stats.a1b0++;
    else if (pair.a == 1 && pair.b == 1)
        stats.a1b1++;
    signal(SIGALRM, alarm_handler);
    alarm(1);
}

void parent_handler(int sig, siginfo_t *info, void *ucontext)
{
    (void) sig;
    (void) ucontext;
    int cmd_type = info->si_value.sival_int;
    switch (cmd_type) {
        case 1:
            print = false;
            break;
        case 2:
            print = true;
            break;
        case 3:
            print_stats(true);
            break;
    }
}

void modify_racy()
{
    usleep(80000);
    if (pair.a == 0)
    {
        pair.a = 1;
        usleep(50000);
        pair.b = 1;
    } else
    {
        pair.a = 0;
        usleep(60000);
        pair.b = 0;
    }
}

int main(int argc, char *argv[])
{
    (void) argc;
    CHILD_NAME = argv[0];
    if (prctl(PR_SET_NAME, CHILD_NAME))
    {
        perror("prctl PR_SET_NAME");
        exit(EXIT_FAILURE);
    }
    printf("Child started\nName: %s\nPID: %d\nPPID: %d\n", CHILD_NAME, getpid(), getppid());

    signal(SIGALRM, alarm_handler);
    struct sigaction modify_act = {0};
    modify_act.sa_sigaction = &parent_handler;
    modify_act.sa_flags = SA_RESTART | SA_SIGINFO;

    if (sigaction(SIGRTMIN, &modify_act, NULL) == -1)
    {
        perror("sigaction");
        exit(EXIT_FAILURE);
    }
    alarm(1);

    int iters = 0;
    while (true)
    {
        modify_racy();
        iters++;
        if (iters > 10)
        {
            print_stats(false);
            iters = 0;
        }
    }
}