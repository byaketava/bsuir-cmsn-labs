#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h> // для работы с семафорами
#include "initexit.h"
#include "producer.h"
#include "consumer.h"

static const char options[] = {"Menu:\n"
                               "[m] - Show menu\n"
                               "[1] - Start producer\n"
                               "[2] - Start consumer\n"
                               "[3] - Stop producer\n"
                               "[4] - Stop consumer\n"
                               "[e] - Exit"};

msg_queue *queue;               // структура для хранения сообщений в очереди
sem_t *mutex;                   // синхронизация меж процессами
sem_t *free_space;
sem_t *items;
pid_t producers[CHILD_MAX];     // массив производителей
size_t producers_amount;        // кол-во произв
pid_t consumers[CHILD_MAX];     // массив потребителей
size_t consumers_amount;        // кол-во потреб

int main(void)
{
    init();
    puts(options);
    while (1)
    {
        switch (getchar())
        {
            case 'm':
                puts(options);
                break;
            case '1':
                create_producer();
                break;
            case '2':
                create_consumer();
                break;
            case '3':
                remove_producer();
                break;
            case '4':
                remove_consumer();
                break;
            case 'e':
                exit(EXIT_SUCCESS);
            default:
                break;
        }
    }
}