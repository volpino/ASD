#include <stdio.h>
#define MIN(a,b)  ((a) < (b) ? (a) : (b))
#define DEBUG 1

/*
    Number of swappings to order an array
    Complexity: O(n)
*/

void swap(int *a, int *b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int min_count(int *a, int n) {
    int i = 0;
    int count = 0;
    while (i<n-1) {
        if (a[i] != i+1) {
            swap(&a[i], &(a[a[i]-1]));
            count++;
        }
        else if (a[i+1] > a[i]) {
            i++;
        }
    }

    return count;
}

int min_weight(int *a, int n) {
    int weight = 0;
    int s1, s2;
    int i;
    int done = 0;
    int current_sum, current_n, to_add;

    int b[100000];  // array for inverse lookup
    for (i=0; i<n; i++) {
        b[a[i] - 1] = i;
    }

    for (done=0; done<n; done++) {
        i = b[done];
        if (a[i] == i+1) {
            continue;
        }

        current_sum = 0;
        current_n = 0;

        if (DEBUG) printf("Nuovo ciclo, parte da %d\n", a[i]);

        // ciclo di scambi
        while (a[i] != i+1) {
            s1 = b[i];  // indici da scambiare
            s2 = i;

            current_sum += a[s1];
            current_n++;

            printf("scambio %d %d \n", a[s1], a[s2]);

            swap(&a[s1], &a[s2]);

            b[a[s1] - 1] = s1;  // aggiorno b
            b[a[s2] - 1] = s2;
            i = b[done];
        }

        if (DEBUG) {
            printf("fine ciclo\n");
            printf("Il ciclo normale costa: %d\n", current_sum+a[i]*current_n);
            printf("Il ciclo con prestito dell'1 costa: %d\n",
                   2*(1 + a[i]) + current_sum + 1 * current_n);
        }

        to_add = MIN(current_sum + a[i] * current_n,
                     2*(1 + a[i]) + current_sum + 1 * current_n);
        weight += to_add;
    }

    return weight;
}

int main() {
    FILE *filep;
    int a[100000];
    int b[100000];
    int n = 0;
    int i;
    int tmp;
    filep = fopen ("input.txt", "r");
    fscanf(filep, "%d\n", &n);
    for (i=0; i<n; i++) {
        fscanf(filep, "%d", &tmp);
        a[i] = tmp;
        b[i] = tmp;
    }
    fclose(filep);

    filep = fopen("output.txt", "w");
    fprintf(filep, "%d %d\n", min_count(a, n), min_weight(b, n));
    fclose(filep);

    return 0;
}
