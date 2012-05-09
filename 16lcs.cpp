#include <iostream>
#include <fstream>

#define SIZE 1000

using namespace std;

string A;
string B;

int D[SIZE][SIZE];

int lcs(int i, int j) {
    if (i == A.size() || j == B.size()) {
        return 0;
    }

    if (D[i][j] == -1) {
        int prendo = 0;
        int avanzo_i = 0;
        int avanzo_j = 0;
        if (A[i] == B[j]) {
            prendo = lcs(i+1, j+1) + 1;
        }
        avanzo_i = lcs(i+1, j);
        avanzo_j = lcs(i, j+1);
        D[i][j] = max(prendo, max(avanzo_i, avanzo_j));
    }

    return D[i][j];
}


int main() {
    ifstream in("input.txt");
    in >> A;
    in >> B;

    in.close();

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            D[i][j] = -1;
        }
    }


    ofstream out("output.txt");
    out << lcs(0, 0);
    out.close();
}
