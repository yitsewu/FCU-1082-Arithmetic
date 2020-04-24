# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <windows.h>
# include <time.h>
# define TIMES 25
# define MAX 50000

int *generate_number (int *data) {
	for (int i = 1; i < MAX; i++) {
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

void MaxHeapify(int *data, int root, int length) {
    int left_child = 2 * root; 
	int right_child = 2 * root + 1;
    int largest = 0;

    if (left_child <= length && data[left_child] > data[root]) {
		largest = left_child;
	} else {
		largest = root;
	}
	
    if (right_child <= length && data[right_child] > data[largest]) {
    	largest = right_child;
	}

    if (largest != root) {
        int temp = data[largest];
        data[largest] = data[root];
        data[root] = temp;
        MaxHeapify(data, largest, length);
    }
}

void BuildMaxHeap (int *data) {
	for (int i = MAX/2; i >= 1;i--) {
        MaxHeapify(data, i, MAX-1);   
    }
}

double heap_sort (int *data) {
	srand(time(NULL));
	clock_t t_start = clock();
	
	BuildMaxHeap(data);
	
	int size = MAX-1;
    for (int i = size; i>=2 ; i--) {
    	int temp = data[1];
        data[1] = data[i];
        data[i] = temp;
        size--;
        MaxHeapify(data, 1, size);
    }
    
	clock_t t_end = clock();
	return ((double)t_end - t_start) / CLOCKS_PER_SEC;
}

int main () {
	int data[MAX] = {0};
	double times[TIMES] = {0};
	
	FILE *output = fopen("heap_sort_output.txt", "w");
	
	
	for (int i = 0; i < TIMES; i++) {
		generate_number(data);
		printf("\n\t%2d times Sorting Start...\n\n\n", i + 1);
		
		times[i] = heap_sort(data);
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
