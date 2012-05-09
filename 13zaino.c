#include <stdio.h>
#include <limits.h>

#define MAX(a,b) ((a) > (b) ? (a) : (b))
#define DEBUG 1
#define SIZE1 2
#define SIZE2 100001

int D[SIZE1][SIZE2];
int p[1000];
int v[1000];
int n;
int c;

int zaino() {
    int i = 0;
    int j;
    int i_curr, i_prev;

    for (j=0; j <= c; j++) {
        D[0][j] = 0;
    }

    for (i = 1; i <= n; i++) {
        i_curr = i % 2;
        i_prev = (i-1) % 2;

        D[i_curr][0] = 0;

        for (j=1; j <= c; j++) {
            if (p[n-i] > j) {  // se non posso prenderlo
                D[i_curr][j] = D[i_prev][j];
            }
            else {
                D[i_curr][j] = MAX(D[i_prev][j], D[i_prev][j-p[n-i]] + v[n-i]);
            }
        }
    }

    return D[n % 2][c];
}

int main() {
    FILE *filep;
    int tmp1, tmp2;
    int i;

    filep = fopen ("input.txt", "r");
    fscanf(filep, "%d %d\n", &c, &n);

    for (i = 0; i < n; i++) {
        fscanf(filep, "%d %d", &tmp1, &tmp2);
        p[i] = tmp1;
        v[i] = tmp2;
    }
    fclose(filep);

    filep = fopen("output.txt", "w");
    fprintf(filep, "%d\n", zaino());
    fclose(filep);

    return 0;
}
