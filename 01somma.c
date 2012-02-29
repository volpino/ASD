#include <stdio.h>

/*
    Dummy code - Only for testing
*/

FILE *filei;
FILE *fileo;

int main() {
    int n, m;
    filei = fopen ("input.txt", "r");
    fscanf(filei, "%d", &n);
    fscanf(filei, "%d", &m);
    fclose(filei);

    fileo = fopen("output.txt", "w");
    fprintf(fileo, "%d\n", (n + m));
    fclose(fileo);

    return 0;
}
