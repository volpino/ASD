#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

using namespace std;

vector<vector<int> > adj;
vector<bool> visitato;
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


int main() {
    ifstream in("input.txt");
    int N, M;
    in >> N >> M;
    adj.resize(N);
    visitato.resize(N);

    for (int i=0; i<M; i++) {
        int from, to;
        in >> from >> to;
        adj[from].push_back(to);
    }
    in.close();

    for (int i=0; i<N; i++) {
        visitato[i] = false;
    }

    for (int i=0; i<N; i++) {
        if (!visitato[i]) {
            dfs(i);
        }
    }

    ofstream out("output.txt");
    int k = s.size();
    for (int i=0; i<k; i++) {
        out << s.top() << " ";
        s.pop();
    }
    out << endl;
    out.close();

    return 0;
}
