# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <windows.h>
# include <time.h>
# define TIMES 25
# define MAX 50000

int *generate_number (int *data) {
	for (int i = 0; i < MAX; i++) {
		data[i] = rand() % 1000000 + 1;
		((i+1)%10 == 0) ? printf("%10d\n", data[i]) : printf("%10d ", data[i]);
	}
	return (int *) data;
}

void check_number (int *data) {
	for (int i = 1; i < MAX; i++) {
		((i+1)%10 == 0) ? printf("%10d\n", data[i]) : printf("%10d ", data[i]);
	}
}

double bubble_sort (int *data) {
	srand(time(NULL));
	clock_t t_start = clock();
	
	for (int i = 0; i < MAX; i++) {
		for (int j = 0; j < MAX-i-1; j++) {
			if (data[j] > data[j+1]) {
				int temp = data[j];
				data[j] = data[j+1];
				data[j+1] = temp;
			}
		}
	}
	
	clock_t t_end = clock();
	return ((double)t_end - t_start) / CLOCKS_PER_SEC;
}

int main () {
	int data[MAX] = {0};
	double times[TIMES] = {0};
	
	FILE *output = fopen("bubble_sort_output.txt", "w");
	
	for (int i = 0; i < TIMES; i++) {
		generate_number(data);
		printf("\n\t%2d times Sorting Start...\n\n\n", i + 1);
		
		times[i] = bubble_sort(data);
		sleep(1);
		
		printf("\n\t%2d times Sorting End...\n\n\n", i + 1);
		check_number(data);
		
		printf("\n\t%2d times -> Spend : %lf sec\n", i + 1, times[i]);
		sleep(2);
	}
	
	system("cls");
	
	for (int i = 0; i < TIMES; i++) {
		printf("%2d times -> Spend : %lf sec\n", i + 1, times[i]);
		fprintf(output, "%2d times -> Spend : %lf sec\n", i + 1, times[i]);
	}
	
	fclose(output);
	
	return 0;
} 
