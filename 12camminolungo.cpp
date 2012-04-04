#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

vector<vector<int> > adj;
vector<bool> visitato;
vector<int> depth;
stack<int> s;

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


void bfs(int partenza) {
    queue<int> q;

    q.push(partenza);
    depth[partenza] = 0;

    while (!q.empty()) {
        partenza = q.front();
        q.pop();

        visitato[partenza] = true;

        for (int j=0; j<adj[partenza].size(); j++) {
            int vicino = adj[partenza][j];
            if (depth[vicino] == -1 || depth[partenza] + 1 > depth[vicino]) {
                q.push(vicino);
                depth[vicino] = depth[partenza] + 1;
            }
        }
    }
}


int main() {
    ifstream in("input.txt");
    int N, M;
    in >> N >> M;
    adj.resize(N);
    depth.resize(N);
    visitato.resize(N);

    for (int i=0; i<M; i++) {
        int from, to;
        in >> from >> to;
        adj[from].push_back(to);
    }
    in.close();

    // Inizializzazione
    for (int i=0; i<N; i++) {
        visitato[i] = false;
        depth[i] = -1;
    }

    // Ordinamento topologico
    for (int i=0; i<N; i++) {
        if (!visitato[i]) {
            dfs(i);
        }
    }

    for (int i=0; i<N; i++) {
        visitato[i] = false;
    }

    int max = 0;

    while (!s.empty()) {
        int partenza = s.top();
        s.pop();

        if (visitato[partenza]) {
            continue;
        }

        for (int i=0; i<N; i++) {
            depth[i] = -1;
        }

        bfs(partenza);

        for (int i=0; i<N; i++) {
            if (depth[i] > max) {
                max = depth[i];
            }
        }
    }

    ofstream out("output.txt");
    out << max << endl;
    out.close();

    return 0;
}
