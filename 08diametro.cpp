#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
using namespace std;

vector<vector<int> > adj;
vector<bool> visitato;
vector<int> depth;


void bfs(int partenza) {
    queue<int> q;

    q.push(partenza);
    visitato[partenza] = true;

    while (!q.empty()) {
        partenza = q.front();
        q.pop();

        for (int j=0; j<adj[partenza].size(); j++) {
            int vicino = adj[partenza][j];
            if (!visitato[vicino]) {
                q.push(vicino);
                visitato[vicino] = true;
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
    visitato.resize(N);
    depth.resize(N);

    for (int i=0; i<M; i++) {
        int from, to;
        in >> from >> to;
        adj[from].push_back(to);
        adj[to].push_back(from);
    }
    in.close();

    int max = 0;
    for (int i=0; i<N; i++) {
        for (int j=0; j<N; j++) {
            visitato[j] = false;
            depth[j] = 0;
        }

        bfs(i);

        for (int j=0; j<N; j++) {
            if (depth[j] > max) {
                max = depth[j];
            }
        }
    }

    ofstream out("output.txt");
    out << max << endl;
    out.close();

    return 0;
}
