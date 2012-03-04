#include <stdio.h>
#define N 2000
#define DEBUG 0


int a[N][N];
int temp[N];


int max_subarray(int *a, int n) {
    int i;
    int max = 0;
    int curr_sum = 0;

    for (i=0; i<n; i++) {
        curr_sum += a[i];
        if (curr_sum > max) {
            max = curr_sum;
        }
        if (curr_sum < 0) {
            curr_sum = 0;
        }
    }
    return max;
}


void print_matrix(int r, int c) {
    int i, j;
    for (i=0; i<r; i++) {
        for (j=0; j<c; j++) {
            printf("%d ", a[i][j]);
        }
        printf("\n");
    }
}

void print_array(int *array, int n) {
    int i;
    for (i=0; i<n; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int max_submat(int r, int c) {
    int i, j, k;
    int max = 0;
    int sum;

    for (i=0; i<r; i++) {
        sum = 0;
        for (j=0; j<c; j++) {
            sum += a[i][j];
            a[i][j] = sum;
        }
    }

    if (DEBUG) {
        print_matrix(r, c);
    }

    sum = 0;
    for (i=-1; i<c; i++) {
        for (j=i+1; j<c; j++) {
            for (k=0; k<r; k++) {
                if (i == -1) {
                    temp[k] = a[k][j];
                }
                else {
                    temp[k] = a[k][j] - a[k][i];
                }
            }

            if (DEBUG) {
                printf("i=%d j=%d temp = \n", i, j);
                print_array(temp, r);
                printf("\n\n");
            }

            sum = max_subarray(temp, r);
            if (sum > max) {
                max = sum;
            }
        }
    }

    return max;
}


int main() {
    FILE *filep;
    int r, c, i, j;

    filep = fopen ("input.txt", "r");

    fscanf(filep, "%d %d", &r, &c);

    for (i=0; i<r; i++) {
        for (j=0; j<c; j++) {
            fscanf(filep, "%d", &a[i][j]);
        }
    }

    fclose(filep);

    filep = fopen("output.txt", "w");
    fprintf(filep, "%d\n", max_submat(r, c));
    fclose(filep);
}
