#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <time.h>
#include <stdlib.h>
#include <errno.h>
#include <fcntl.h>

//Arguments should be the file name , number of chapters and hws per chapter
int main(int argc, char *argv[])
{
    int students = 10;
    int managers = 0;
    int workers = 0;

    int grades;
    for (int i = 1; i < argc; i++)
    {
        printf("argv[%d]: %s\n", i, argv[i]);
    }

    int chapters = atoi(argv[2]);
    int hw_per_chapter = atoi(argv[3]);
    // Calculate total number of children to be created.
	int total_hw = chapters * hw_per_chapter;

	// Allocate memory.
	int *grades_list[students];
	for (int i = 0; i < students; i++) 
	{
		grades_list[i] = (int *) malloc(total_hw * sizeof(int));
		
	} 
	
	// Extract data from input file.
	FILE *input_file = fopen(argv[0], "r");
	for (int i = 0; i < students; i++) {
     	for (int j = 0; (j < total_hw) && ( (fscanf(input_file, "%d", &grades)) ) > 0 ; j++) {
			grades_list[i][j] = grades;
			}
		}
    // printf("This is my chapters and hw_per_chapter:\n%d\n%d", chapters, hw_per_chapter);
    // int total_hwk = chapters * hw_per_chapter;
    // int* grades_list[students];
    // for (int i = 0; i < students; i++) 
	// {
	// 	grades_list[i] = (int *) malloc(total_hwk * sizeof(int));
		
	// } 

    // printf("Total is: %d\n", total_hwk);

    // FILE *input_file = fopen(argv[0], "r");

    // for (int x = 0; x < students; x++)
    // {
    //     for (int y = 0; y < total_hwk && (fscanf(input_file, "%d", &grade)) > 0; y++)
    //     {
    //         printf("hello");
    //         printf("The grade: %d \n", grade);
    //         grades_list[x][y] = grade;
    //     }
    // }
    fclose(input_file);

    for (int x = 0; x < students; x++)
    {
        for (int y = 0; y < total_hw; y++)
        {

            printf("[%d][%d]: %d\n", x, y,grades_list[x][y]);
        }
    }

    return 0;
}