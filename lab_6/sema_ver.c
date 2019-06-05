#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "sem.h"

int main()
{

    // Five semaphores to be used
    int lock;
    int tobacco;
    int paper;
    int match;
    int agent;
    int numTimes;

    // Other integers that will be used
    int ranNum;
    int child;

    // Create semaphores for each.
    if ((match = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT)) == -1)
    {
        perror("semget");
        exit(-1);
    }

    if ((lock = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT)) == -1)
    {
        perror("semget");
        exit(-1);
    }

    if ((paper = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT)) == -1)
    {
        perror("semget");
        exit(-1);
    }

    if ((tobacco = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT)) == -1)
    {
        perror("semget");
        exit(-1);
    }

    if ((agent = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT)) == -1)
    {
        perror("semget");
        exit(-1);
    }

    sem_create(match, 0);
    sem_create(lock, 1);
    sem_create(tobacco, 0);
    sem_create(paper, 0);
    sem_create(agent, 0);

    child = fork();

    if (child == 0)
    {
        while (1)
        {
            P(paper);
            P(lock);
            printf("Smoker with paper picks up tobacco and match and starts smoking\n");
            sleep(1);
            V(agent);
            V(lock);
        }
    }

    child = fork();
    if (child == 0)
    {
        while (1)
        {
            P(tobacco);
            P(lock);
            printf("Smoker with tobacco picks up match and paper and starts smoking\n");
            sleep(1);
            V(agent);
            V(lock);
        }
    }

    child = fork();
    if (child == 0)
    {
        while (1)
        {
            P(match);
            P(lock);
            printf("Smoker with match picks up paper and tobacco and starts smoking\n");
            sleep(1);
            V(agent);
            V(lock);
        }
    }

    for (numTimes = 0; numTimes < 10; numTimes++)
    {

        P(lock);
        ranNum = rand() % 3;

        // Pick a smoker randomly
        if (ranNum == 0)
        {
            printf("Agent placed tobacco and paper  on the table\n");
            sleep(1);
            V(match);
        }
        else if (ranNum == 1)
        {
            printf("Agent placed paper and match now on the table\n");
            sleep(1);
            V(tobacco);
        }
        else if (ranNum == 2)
        {
            printf("match and tobacco now on the table\n");
            sleep(1);
            V(paper);
        }

        V(lock);
        P(agent);
    }

    exit(0);
}