#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#define DEBUG 0

vector<vector<int> > adj;
vector<bool> visitato;

void visita(int partenza) {
    visitato[partenza] = true;

    for(int j=0; j<adj[partenza].size(); j++) {
        int vicino = adj[partenza][j];
        if (DEBUG) {
            printf("Sono nel nodo %d, visito il vicino %d\n",
                   partenza, vicino);
        }
        if (!visitato[vicino]) {
            visita(vicino);
        }
    }
}

int main(){
    ifstream in("input.txt");
    int N, M, partenza;
    in >> N >> M >> partenza;
    adj.resize(N);
    visitato.resize(N);
    for (int i=0; i<M; i++) {
        int from, to;
        in >> from >> to;
        adj[from].push_back(to);
    }
    for (int i=0; i<N; i++) {
        visitato[i] = false;
    }
    in.close();

    visita(partenza);
    int count = 0;
    for (int i=0; i<visitato.size(); i++) {
        if (visitato[i]) {
            count++;
        }
    }

    ofstream out("output.txt");
    out << count << endl;
    out.close();

    return 0;
}
