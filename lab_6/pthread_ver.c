#include <stdio.h>
#include <sys/types.h>
#include <pthread.h>

int occupied = 0;
int table[2];
char *item[] = {"tobacco", "paper", "matches"};
pthread_mutex_t mutex;
int numTimes = 0;

void *agent_process()
{
    // Initialize with no items.
    int agentOne = 0;
    int agentTwo = 0;

    while (1)
    {

        // Lock for this process.
        pthread_mutex_lock(&mutex);

        // Check the condition.
        if (!occupied)
        {

            // Take two random.
            agentOne = rand() % 3;
            agentTwo = rand() % 3;

            if (agentOne != agentTwo)
            {

                // Set items on the table.
                table[0] = agentOne;
                table[1] = agentTwo;
                printf("Agent placed %s and %s on the table.\n", item[agentOne], item[agentTwo]);
                sleep(1);

                // Condition is changed.
                occupied = 1;
            }
        }

        // Unlock thread for smokers

        pthread_mutex_unlock(&mutex);

        if (numTimes == 10)
        {
            return NULL;
        }
    }
}

void *smoker_process(int i)
{
    while (1)
    {
        // Lock for this process.
        pthread_mutex_lock(&mutex);

        // Check the condition.
        if (occupied)
        {

            // Check who is up to smoke.
            if (table[0] != i && table[1] != i)
            {

                if (i == 0)
                {
                    printf("Smoker with tobacco picks up match and paper and starts smoking.\n");
                    sleep(1);
                    numTimes++;
                }
                else if (i == 1)
                {
                    printf("Smoker with paper picks up tobacco and match and starts smoking.\n");
                    sleep(1);
                    numTimes++;
                }
                else if (i == 2)
                {
                    printf("Smoker with matches picks up paper and tobacco and starts smoking.\n");
                    sleep(1);
                    numTimes++;
                }

                // Condition is changed.
                occupied = 0;
            }
        }
        // Unlock the thread for the agent.
        pthread_mutex_lock(&mutex);
    }
    return NULL;
}

int main()
{

    pthread_t agent, smokers[3];

    int partsJoint[] = {0, 1, 2};

    pthread_create(&agent, NULL, agent_process, NULL);

    for (int i = 0; i < 3; i++)
    {
        pthread_create(&smokers[i], NULL, smoker_process, partsJoint[i]);
    }

    // Wait for threads to finish.
    pthread_join(agent, NULL);
    for (int i = 0; i < 3; i++)
    {
        pthread_join(&smokers[i], NULL);
    }

    printf("Done\n");
    return 0;
}