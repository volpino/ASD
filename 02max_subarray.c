#include <stdio.h>

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

int main() {
    FILE *filep;
    int a[1000000];
    int n = 0;
    int i;
    filep = fopen ("input.txt", "r");
    fscanf(filep, "%d\n", &n);
    for (i=0; i<n; i++) {
        fscanf(filep, "%d", a+i);
    }
    fclose(filep);

    filep = fopen("output.txt", "w");
    fprintf(filep, "%d\n", max_subarray(a, n));
    fclose(filep);
}
