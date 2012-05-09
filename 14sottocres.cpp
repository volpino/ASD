#include <iostream>
#include <fstream>
#include <vector>

#define SIZE 10000

using namespace std;


int D[SIZE];
int N;

vector<int> data;


int sottocres(int i) {

    if (D[i] == -1) {
        int max = 0;
        for (int k = 0; k < i; k++) {
            int res = sottocres(k);
            if (data[k] <= data[i] && res > max) {
                max = res;
            }
        }
        D[i] = max + data[i];
    }

    return D[i];
}


int main() {
    ifstream in("input.txt");

    in >> N;

    int tmp;
    for (int i = 0; i < N; i++) {
        in >> tmp;
        data.push_back(tmp);
    }

    in.close();

    for (int i = 0; i < SIZE; i++) {
        D[i] = -1;
    }

    ofstream out("output.txt");
    int m = 0;
    for (int i = 0; i < N; i++) {
        int res = sottocres(i);
        if (res > m) {
            m = res;
        }
    }
    out << m << endl;
    out.close();
}
