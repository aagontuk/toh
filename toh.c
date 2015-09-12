/*
 * [PROG]    - toh(Tower of Hanoi)
 * [AUTHOR]  - Ashfaqur Rahman <sajib.finix@gmail.com>
 * [PURPOSE] - Solve classical Tower of Hanoi problem & some fun!
 *
 * [DESCRIPTION] - Mainly 2 options. Only Count time needed to solve toh with specified disks.
 *				   Solve toh by moving disks form one tower to another. Optionaly show moves.
 *				   also count time.Optionaly output can be saved in a disk file rather than
 *				   standard output.
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <time.h>

#define STRSIZE 100 /* Max char in file names */

struct toh{
	int diskno;
	int shwPrcnt;
	int shwMoves;
	char fromPeg;
	char toPeg;
};

void move_disks(struct toh, FILE *);
void move_time(int);
void solve_toh(char, char, int, int, int, FILE *);

int main(int argc, char *argv[]){
	char c;
	char toFile[STRSIZE];
	int isMove = 0, tcount = 0;
	struct toh thanoi;

	thanoi.shwPrcnt = 0;
	thanoi.shwMoves = 0;
	strcpy(toFile, "stdout");

	while(--argc > 0 && (*++argv)[0] == '-'){
		c = *++argv[0];
		switch(c){
			/* Count time needed to move diskno disk from one peg to another */
			case 'c':
				tcount = 1;
				break;

			/* Move the disk from one peg to another */
			case 'm':
				isMove = 1;
				break;

			/* Number of disk */
			case 'd':
				thanoi.diskno = atoi(*++argv);
				argc--;
				break;
			
			/* from peg*/
			case 'f':
				thanoi.fromPeg = toupper((*++argv)[0]);
				argc--;
				break;
		
			/* to peg */
			case 't':
				thanoi.toPeg = toupper((*++argv)[0]);
				argc--;
				break;

			/* Specify frequency of showing progress */
			case 'p':
				thanoi.shwPrcnt = atoi(*++argv);
				argc--;
				break;

			case 's':
				thanoi.shwMoves = 1;
				break;

			default:
				printf("Unknown switch %c\n", c);
				break;
		}
	}

	/* only one file specified */
	if(argc == 1){
		strcpy(toFile, *argv);
		argc--;
	}

	clock_t begin, end;
	double tspent;

	if(isMove){
		if(strcmp(toFile, "stdout") != 0){
			FILE *fp;
			
			if((fp = fopen(toFile, "a")) == NULL){
				fprintf(stderr, "toh: Can't open %s\n", toFile);
				exit(1);
			}

			begin = clock();
			move_disks(thanoi, fp);
			end = clock();

			fclose(fp);
		}else{
			begin = clock();
			move_disks(thanoi, stdout);
			end = clock();
		}

		tspent = (double)(end - begin) / CLOCKS_PER_SEC;

		unsigned long long year, day, hour, min;
		double sec;
		
		year = (unsigned long long)tspent / 3153600;
		day = ((unsigned long long)tspent - (year * 3153600)) / 86400;
		hour = ((unsigned long long)tspent - ((year * 3153600) + (day * 86400))) / 3600;
		min = ((unsigned long long)tspent - ((year * 3153600) + (hour * 3600) + (day * 86400))) / 60;
		sec = tspent - ((year * 3153600) + (day * 86400) + (hour * 3600) + (min * 60));
		
		printf("It took: %lluy, %llud, %lluh, %llum, %lfs\n", year, day, hour, min, sec);
	}

	if(tcount && !isMove){
		begin = clock();
		solve_toh('A', 'B', 20, 0, 0, NULL);
		end = clock();
		
		tspent = (double)(end - begin) / CLOCKS_PER_SEC;
		tspent *= ((pow(2, thanoi.diskno) - 1) / (pow(2, 20)	- 1));

		unsigned long long year, day, hour, min;
		double sec;
		
		year = (unsigned long long)tspent / 3153600;
		day = ((unsigned long long)tspent - (year * 3153600)) / 86400;
		hour = ((unsigned long long)tspent - ((year * 3153600) + (day * 86400))) / 3600;
		min = ((unsigned long long)tspent - ((year * 3153600) + (hour * 3600) + (day * 86400))) / 60;
		sec = tspent - ((year * 3153600) + (day * 86400) + (hour * 3600) + (min * 60));
	
		printf((thanoi.diskno == 64) ? "Your universe will survive:\n\n" : "It took: ");
		printf("%lluy, %llud, %lluh, %llum, %lfs\n", year, day, hour, min, sec);
		printf((thanoi.diskno == 64) ? "\nSo enjoy your time! And make good impact.\n" : "");
	}

	return 0;
}

#define SIZE 65

void fill_tower(char, int);
int is_fill_correct(char, int);
void show_towers_status(FILE *fp);
char get_spare_peg(char, char);
void move_disk(char, char);
void solve_toh(char, char, int, int, int, FILE *);
void show_progress(int, FILE *);

char A[SIZE] = "", B[SIZE] = "", C[SIZE] = "";
int aPos = 0, bPos = 0, cPos = 0, flag = 1, saveProgress;
unsigned long long moves, totalMoves;

void move_disks(struct toh thanoi, FILE *fp){
	printf("###### Towers Of Hanoi ######\n\n");
	fill_tower(thanoi.fromPeg, thanoi.diskno);
	show_towers_status(fp);

	fprintf(fp, "\nTransferring All Disks From %c ===> To %c Peg\n", thanoi.fromPeg, thanoi.toPeg);

	totalMoves = (unsigned long long)(pow(2, thanoi.diskno) - 1);
	solve_toh(thanoi.fromPeg, thanoi.toPeg, thanoi.diskno, thanoi.shwPrcnt, thanoi.shwMoves, fp);

	printf("\n###### Towers Of Hanoi ######\n\n");
	show_towers_status(fp);

	fprintf(fp, "\nI needed %llu Moves!\n", moves);
}

void solve_toh(char fromPeg, char toPeg, int numDisks, int shwPrcnt, int shwMoves, FILE *fp){
	if(numDisks == 0){
		return;
	}

	solve_toh(fromPeg, get_spare_peg(fromPeg, toPeg), numDisks - 1, shwPrcnt, shwMoves, fp);
	move_disk(fromPeg, toPeg);

	if(shwMoves){
		fprintf(fp, "Move Disk %d: Form %c To %c\n", numDisks, fromPeg, toPeg);
	}

	moves++;
	
	if(shwPrcnt){
		show_progress(shwPrcnt, fp);
	}

	solve_toh(get_spare_peg(fromPeg, toPeg), toPeg, numDisks - 1, shwPrcnt, shwMoves, fp);

	return;
}

void fill_tower(char peg, int disks){
	int i;	

	switch(peg){
		case 'A':
			for(i = 0; i < disks; i++){
				if(i < 10){
					A[aPos++] = i + '0';
				}
				else if(i < 36){
					A[aPos++] = i + 'A' - 10;
				}
				else if(i < 62){
					A[aPos++] = i + 'a' - 36;
				}
				else{
					A[aPos++] = i + 35 - 62;
				}
			}
			A[aPos] = '\0';
			break;

		case 'B':
			for(i = 0; i < disks; i++){
				if(i < 10){
					B[bPos++] = i + '0';
				}
				else if(i < 36){
					B[bPos++] = i + 'A' - 10;
				}
				else if(i < 62){
					B[bPos++] = i + 'a' - 36;
				}
				else{
					B[bPos++] = i + 35 - 62;
				}
			}
			B[bPos] = '\0';
			break;

		case 'C':
			for(i = 0; i < disks; i++){
				if(i < 10){
					A[aPos++] = i + '0';
				}
				else if(i < 36){
					A[aPos++] = i + 'A' - 10;
				}
				else if(i < 62){
					A[aPos++] = i + 'a' - 36;
				}
				else{
					A[aPos++] = i + 35 - 62;
				}
			}
			C[cPos] = '\0';
			break;
	}
}

int is_fill_correct(char peg, int disks){
	int i;
	
	switch(peg){
		case 'A':
			if(strlen(A) != disks){
				return 1;
			}
			break;

		case 'B':
			if(strlen(B) != disks){
				return 1;
			}
			break;

		case 'C':
			if(strlen(A) != disks){
				return 1;
			}
			break;
	}

	for(i = 0; i < disks; i++){
		if(A[i] != (i + 1 + '0')){
			return 2;
		}
	}

	return 0;
}

void show_towers_status(FILE *fp){
	fprintf(fp, "Tower A: ");
	fprintf(fp, (strlen(A) == 0) ? "Empty!\n" : "%s\n", A);
	fprintf(fp, "Tower B: ");
	fprintf(fp, (strlen(B) == 0) ? "Empty!\n" : "%s\n", B);
	fprintf(fp, "Tower C: ");
	fprintf(fp, (strlen(C) == 0) ? "Empty!\n" : "%s\n", C);
}

void show_progress(int afterProgress, FILE *fp){

	int progress = (int)((((double)moves) / ((double)totalMoves)) * 100);
	if(progress % afterProgress == 0){
		if(flag){
			fprintf(fp, "Progress: %d %%\n", progress);
		}
		saveProgress = progress;
		if(saveProgress == progress){
			flag = 0;
		}
	}
	
	if(saveProgress != progress){
		flag = 1;
	}
}

char get_spare_peg(char fromPeg, char toPeg){
	int tmp = fromPeg + toPeg;

	switch(tmp){
		case 131:
			return 'C';

		case 132:
			return 'B';

		case 133:
			return 'A';
	}

	return '\0';
}

void move_disk(char fromPeg, char toPeg){
	char diskToMove;

	/* Take top disk of fromPeg */
	switch(fromPeg){
		case 'A':
			diskToMove = A[--aPos];
			A[aPos] = '\0';	
			break;

		case 'B':
			diskToMove = B[--bPos];
			B[bPos] = '\0';
			break;

		case 'C':
			diskToMove = C[--cPos];
			C[cPos] = '\0';
			break;
	}

	/* Insert disk in the top of toPeg */
	switch(toPeg){
		case 'A':
			A[aPos++] = diskToMove;
			A[aPos] = '\0';
			break;

		case 'B':
			B[bPos++] = diskToMove;
			B[bPos] = '\0';
			break;

		case 'C':
			C[cPos++] = diskToMove;
			C[cPos] = '\0';
			break;
	}
}
