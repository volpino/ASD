#include <iostream>
#include <cstdio>
#include <climits>
#include <vector>

#define DEBUG 0
#define SIZE1 20
#define SIZE2 20000

using namespace std;

int A[SIZE1];
int C[5];

typedef struct
{
  bool array[SIZE2];
  vector<int> list;
} hashset;

hashset* D[SIZE1][SIZE1];

int N, K;


hashset* espressione(int i, int j) {

    if (D[i][j] == NULL) {
        D[i][j] = new hashset;
        for (int k = 0; k < SIZE2; k++) {
            (*D[i][j]).array[k] = false;
        }

        if (i == j) {
            if (!(*D[i][j]).array[A[i]]) {
                (*D[i][j]).array[A[i]] = true;
                (*D[i][j]).list.push_back(A[i]);
            }
        }

        else {
            for (int k = i; k < j; k++) {
                hashset* left = espressione(i, k);
                hashset* right = espressione(k+1, j);

                for (int s = 0; s < (int)(*left).list.size(); s++) {
                    for (int t = 0; t < (int)(*right).list.size(); t++) {
                        int a = (*left).list[s];
                        int b = (*right).list[t];
                        if (DEBUG) {
                            printf("ADDO: %d\n", a * b);
                            printf("ADDO: %d\n", a + b);
                        }

                        int res = a * b;
                        if (res < SIZE2 && !(*D[i][j]).array[res]) {
                            (*D[i][j]).list.push_back(res);
                            (*D[i][j]).array[res] = true;
                        }

                        res = a + b;
                        if (res < SIZE2 && !(*D[i][j]).array[res]) {
                            (*D[i][j]).list.push_back(res);
                            (*D[i][j]).array[res] = true;
                        }
                    }
                }
            }
        }
    }

    return D[i][j];
}


int main() {
    FILE *filep;
    int tmp;
    hashset* myset;

    filep = fopen("input.txt", "r");
    fscanf(filep, "%d %d\n", &N, &K);

    for (int i = 0; i < N; i++) {
        fscanf(filep, "%d", &tmp);
        A[i] = tmp;
    }

    for (int i = 0; i < K; i++) {
        fscanf(filep, "%d", &tmp);
        C[i] = tmp;
    }

    for (int i = 0; i < SIZE1; i++) {
        for (int j = 0; j < SIZE1; j++) {
            D[i][j] = NULL;
        }
    }

    fclose(filep);

    filep = fopen("output.txt", "w");

    myset = espressione(0, N-1);

    if (DEBUG) {
        for (int it = 0; it < (int)(*myset).list.size(); it++) {
            printf("%d ", (*myset).list[it]);
        }
        printf("\n");
    }

    for (int i = 0; i < K; i++) {

        if ((*myset).array[C[i]]) {
            fprintf(filep, "SI\n");
        }
        else {
            fprintf(filep, "NO\n");
        }
    }
    fclose(filep);

    return 0;
}
