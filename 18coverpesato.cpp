#include <iostream>
#include <fstream>
#include <vector>

#define SIZE 300000

using namespace std;


int D[SIZE][2];
int N;

vector<vector<int> > adj;
vector<int> peso;


int cover(int i, bool covered) {

    if (D[i][covered % 2] == -1) {

        // lo prendo
        int prendo = peso[i];
        for (int k = 0; k < (int)adj[i].size(); k++) {
            int vicino = adj[i][k];
            prendo += cover(vicino, true);
        }

        // non lo prendo
        int non_prendo = 0;
        for (int k = 0; k < (int)adj[i].size(); k++) {
            int vicino = adj[i][k];
            non_prendo += cover(vicino, false);
        }

        if (i == 0) {  // radice
            // o lo prendo o tutti i figli devono essere presi
            //printf("Radice: prendo %d, non prendo %d", prendo, non_prendo);
            D[i][covered % 2] = min(prendo, non_prendo);
        }
        else {
            //printf("SONO %d ", i);
            if (!covered) {
                //printf("non sono coperto, mi prendo. %d\n", prendo);
                D[i][covered % 2] = prendo;
            }

            else {
                //printf("sono coperto, prendo (%d) o non prendo (%d)\n", prendo, non_prendo);
                D[i][covered % 2] = min(prendo, non_prendo);
            }
        }
    }

    return D[i][covered % 2];
}


int main() {
    ifstream in("input.txt");

    in >> N;
    adj.resize(N);

    for (int i = 0; i < N; i++) {
        int tmp;
        in >> tmp;
        peso.push_back(tmp);
    }

    for (int i = 0; i < N-1; i++) {
        int parent, child;
        in >> parent >> child;
        adj[parent].push_back(child);
    }

    in.close();

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < 2; j++) {
            D[i][j] = -1;
        }
    }

    ofstream out("output.txt");
    out << cover(0, false);
    out.close();
}
