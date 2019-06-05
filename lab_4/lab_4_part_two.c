#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>


int main (int argc, char *argv[]) {
	
	int students = 10;
	int grades;
	int managers = 0;
    int workers = 0;
	int column = 0;
    int total = 0;
	int chapters = atoi(argv[2]);			
	int chapter_hwks = atoi(argv[3]);		
	
	int total_hw = chapters * chapter_hwks;
	int grades_list[students][total_hw];
	FILE *grade_file = fopen(argv[1], "r");
	for (int i = 0; i < students; i++) {
     	for (int j = 0; (j < total_hw) && ( (fscanf(grade_file, "%d", &grades)) ) > 0 ; j++) {
			grades_list[i][j] = grades;
			}
		}
	fclose(grade_file);
	
	for (int i = 0; i < chapters; i++) {
		managers = fork();
		if (managers < 0) {
			return 1;
		}
		else if (managers == 0) {
			for (int j = 0; j < chapter_hwks; j++) {
				workers = fork();
				if (workers < 0) {
					return 1;
				}
				else if (workers == 0) {
					column += j;
					
					for ( int x = 0; x < 10; x++) {
						total += grades_list[x][column];
					}
					printf("The average from Homework %d ,Chapter %d: %0.2f\n", (j+1),(i+1) , total/10.0);
					return 1;
				}
			}
		return 1;
		}
		column += chapter_hwks;
	}
	
	return 0;
}