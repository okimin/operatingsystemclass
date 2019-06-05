#include <stdio.h>
#include <sys/types.h> // added
#include <sys/ipc.h>   // added
#include <sys/shm.h>   // added
#include <stdlib.h>

#include "sem.h"   // added
#define BUFSIZE 1  // added
#define PERMS 0666 // added

#define CHILD 0 /* Return value of child proc from fork call */
#define TRUE 0
#define FALSE 1

FILE *fp1, *fp2, *fp3, *fp4; /* File Pointers */
int *buffer;				 // added
int mutex;					 // added

FILE *fp5;

int main()
{
	int pid;		 // Process ID after fork call
	int i;			 // Loop index
	int N;			 // Number of times dad does update
	int N_Att;		 // Number of time sons allowed to do update
	int status;		 // Exit status of child process
	int bal1, bal2;  // Balance read by processes
	int flag, flag1; // End of loop variables

	int shmid = 1;
	// Create shared memory
	if ((shmid = shmget(1000, BUFSIZE, IPC_CREAT | PERMS)) < 0)
	{
		printf("\n unable to create shared memory");
		return 1;
	}
	// Allocate Shared Memory
	if ((buffer = (int *)shmat(shmid, (char *)0, 0)) == (int *)-1)
	{
		printf("\n Shared memory allocation error\n");
		exit(1);
	}
	// Create Semaphore
	if ((mutex = semget(IPC_PRIVATE, 1, PERMS | IPC_CREAT)) == -1)
	{
		printf("\n can't create mutex semaphore");
		exit(1);
	}
	sem_create(mutex, 1);

	// Initialize the file balance to be $100
	fp1 = fopen("balance", "w");
	bal1 = 100;
	fprintf(fp1, "%d\n", bal1);
	fclose(fp1);

	// Initialize the number of attempts to be 20
	fp4 = fopen("attempt", "w");
	N_Att = 25; //***********
	fprintf(fp4, "%d\n", N_Att);
	fclose(fp4);

	int dadWait = 0;  // will hold T(dad)
	int son1Wait = 0; // will hold T(son1)
	int son2Wait = 0; // will hold T(son2)

	//Create child processes that will do the updates
	if ((pid = fork()) == -1)
	{
		//fork failed!
		perror("fork");
		exit(1);
	}

	if (pid == CHILD)
	{
		//First Child Process. Dear old dad tries to do some updates.

		N = 5;
		for (i = 1; i <= N; i++)
		{
			printf("Dad is about to enter.\n");
			P(mutex); // Enter Critical Section

			son1Wait += 1;
			son2Wait += 1;
			printf("Wait Time  Dad: %d Son1: %d Son2: %d .\n", dadWait, son1Wait, son2Wait);

			printf("Dear old dad is trying to do update.\n");
			fp1 = fopen("balance", "r+");
			fscanf(fp1, "%d", &bal2);
			printf("Dear old dad reads balance = %d \n", bal2);

			//Dad has to think (0-14 sec) if his son is really worth it
			sleep(rand() % 15);
			fseek(fp1, 0L, 0);
			bal2 += 60;
			printf("Dear old dad writes new balance = %d \n", bal2);
			fprintf(fp1, "%d \n", bal2);
			fclose(fp1);
			printf("Dear old dad is done doing update. \n");
			sleep(rand() % 5); /* Go have coffee for 0-4 sec. */
			V(mutex);		   // Exit Critical Section
		}
	}

	else
	{
		//Parent Process. Fork off another child process.
		if ((pid = fork()) == -1)
		{
			//Fork failed!
			perror("fork");
			exit(1);
		}
		if (pid == CHILD)
		{
			printf("First Son's Pid: %d\n", getpid());
			//Second child process. First poor son tries to do updates.
			flag = FALSE;
			while (flag == FALSE)
			{
				printf("Poor SON_1 is about to enter.\n");
				P(mutex); // Enter Critical Section

				dadWait += 1;
				son2Wait += 1;
				printf("Wait Time  Dad: %d Son1: %d Son2: %d .\n", dadWait, son1Wait, son2Wait);

				fp3 = fopen("attempt", "r+");
				fscanf(fp3, "%d", &N_Att);
				if (N_Att == 0)
				{
					fclose(fp3);
					flag = TRUE;
				}
				else
				{
					printf("Poor SON_1 wants to withdraw money.\n");
					fp2 = fopen("balance", "r+");
					fscanf(fp2, "%d", &bal2);
					printf("Poor SON_1 reads balance. Available Balance: %d \n", bal2);
					if (bal2 == 0)
					{
						fclose(fp2);
						fclose(fp3);
					}
					else
					{
						sleep(rand() % 5);
						fseek(fp2, 0L, 0);
						bal2 -= 20;
						printf("Poor SON_1 write new balance: %d \n", bal2);
						fprintf(fp2, "%d\n", bal2);
						fclose(fp2);
						printf("poor SON_1 done doing update.\n");
						fseek(fp3, 0L, 0);
						N_Att -= 1;
						fprintf(fp3, "%d\n", N_Att);
						fclose(fp3);
					}
				}
				V(mutex); // Exit Critical Section
			}
		}
		else
		{
			//Parent Process. Fork off one more child process.
			if ((pid = fork()) == -1)
			{
				//fork failed!
				perror("fork");
				exit(1);
			}
			if (pid == CHILD)
			{
				printf("Second Son's Pid: %d\n", getpid());
				//Third child process. Second poor son tries to do updates.
				flag1 = FALSE;
				while (flag1 == FALSE)
				{
					printf("Poor SON_2 is about to enter.\n");
					P(mutex); // Enter Critical Section
					dadWait += 1;
					son1Wait += 1;

					printf("Wait Time  Dad: %d Son1: %d Son2: %d .\n", dadWait, son1Wait, son2Wait);

					fp3 = fopen("attempt", "r+");
					fscanf(fp3, "%d", &N_Att);
					if (N_Att == 0)
					{
						fclose(fp3);
						flag1 = TRUE;
					}
					else
					{
						printf("Poor SON_2 wants to withdraw money.\n");
						fp2 = fopen("balance", "r+");
						fscanf(fp2, "%d", &bal2);
						printf("Poor SON_2 reads balance. Available Balance: %d \n", bal2);
						if (bal2 == 0)
						{
							fclose(fp2);
							fclose(fp3);
						}
						else
						{
							sleep(rand() % 5);
							fseek(fp2, 0L, 0);
							bal2 -= 20;
							printf("Poor SON_2 write new balance: %d \n", bal2);
							fprintf(fp2, "%d\n", bal2);
							fclose(fp2);

							printf("poor SON_2 done doing update.\n");
							fseek(fp3, 0L, 0);
							N_Att -= 1;
							fprintf(fp3, "%d\n", N_Att);
							fclose(fp3);
						}
					}
					V(mutex); // Exit Critical Section
				}
			}
			else
			{
				//Now parent process waits for the child processes to finish
				pid = wait(&status);
				printf("Process(pid = %d) exited with the status %d. \n", pid, status);

				pid = wait(&status);
				printf("Process(pid = %d) exited with the status %d. \n", pid, status);

				pid = wait(&status);
				printf("Process(pid = %d) exited with the status %d. \n", pid, status);
			}
			exit(0);
		}
		exit(0);
	}
	exit(0);
}
