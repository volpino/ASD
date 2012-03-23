#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#define DEBUG 0

using namespace std;

vector<vector<int> > adj;
vector<bool> visitato;
vector<int> depth;


int bfs(int partenza, int arrivo) {
    queue<int> q;

    q.push(partenza);
    visitato[partenza] = true;

    while (!q.empty()) {
        partenza = q.front();
        q.pop();

        if (partenza == arrivo) {  // sono arrivato!
            return depth[partenza];
        }

        for (int j=0; j<adj[partenza].size(); j++) {
            int vicino = adj[partenza][j];
            if (!visitato[vicino]) {
                q.push(vicino);
                visitato[vicino] = true;
                depth[vicino] = depth[partenza] + 1;
            }
        }
    }
    return -1;
}


int numcammini(int partenza, int arrivo, int len) {
    queue<int> q;
    int count = 0;

    q.push(partenza);
    visitato[partenza] = true;
    depth[partenza] = 0;

    while (!q.empty()) {
        partenza = q.front();
        q.pop();

        if (partenza == arrivo) {
            count++;
        }

        for (int j=0; j<adj[partenza].size(); j++) {
            int vicino = adj[partenza][j];
            if (depth[partenza] + 1 <= len) {
                if (depth[vicino] == -1 || depth[partenza] < depth[vicino]) {
                    if (DEBUG) {
                        printf("Sono nel nodo %d, visito il vicino %d",
                               partenza, vicino);
                    }

                    depth[vicino] = depth[partenza] + 1;
                    q.push(vicino);
                }
            }
        }
    }
    return count;
}


int main(){
    ifstream in("input.txt");
    int N, M, partenza, arrivo;
    in >> N >> M >> partenza >> arrivo;
    adj.resize(N);
    visitato.resize(N);
    depth.resize(N);

    for (int i=0; i<M; i++) {
        int from, to;
        in >> from >> to;
        adj[from].push_back(to);
    }
    in.close();

    for (int i=0; i<N; i++) {
        depth[i] = 0;
        visitato[i] = false;
    }
    int len = bfs(partenza, arrivo);

    for (int i=0; i<N; i++) {
        depth[i] = -1;
        visitato[i] = false;
    }
    int num = numcammini(partenza, arrivo, len);

    ofstream out("output.txt");
    out << len << " " << num << endl;
    out.close();

    return 0;
}
