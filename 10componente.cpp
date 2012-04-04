#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;

vector<vector<int> > adj;
vector<vector<int> > trans;
vector<bool> visitato;
stack<int> s;
int counter;

void dfs(int partenza) {
    visitato[partenza] = true;

    for (int j=0; j<adj[partenza].size(); j++) {
        int vicino = adj[partenza][j];
        if (!visitato[vicino]) {
            dfs(vicino);
        }
    }

    s.push(partenza);
}


void dfs_trans(int partenza) {
    visitato[partenza] = true;
    counter++;

    for (int j=0; j<trans[partenza].size(); j++) {
        int vicino = trans[partenza][j];
        if (!visitato[vicino]) {
            dfs_trans(vicino);
        }
    }
}


int main() {
    ifstream in("input.txt");
    int N, M;
    in >> N >> M;
    adj.resize(N);
    trans.resize(N);
    visitato.resize(N);

    for (int i=0; i<M; i++) {
        int from, to;
        in >> from >> to;
        adj[from].push_back(to);
        trans[to].push_back(from);  // Grafo trasposto
    }
    in.close();

    for (int i=0; i<N; i++) {
        visitato[i] = false;
    }

    // Ordinamento topologico
    for (int i=0; i<N; i++) {
        if (!visitato[i]) {
            dfs(i);
        }
    }

    int max;

    // resetto visitato
    for (int i=0; i<N; i++) {
        visitato[i] = false;
    }

    // Visito di nuovo, pero' trasposto
    while (!s.empty()) {
        int top = s.top();
        s.pop();
        counter = 0;

        if (!visitato[top]) {
            dfs_trans(top);

            if (counter > max) {
                max = counter;
            }
        }
    }

    ofstream out("output.txt");
    out << max << endl;
    out.close();

    return 0;
}
