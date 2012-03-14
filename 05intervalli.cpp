#include <cstdio>
#include <utility>
#include <algorithm>

using namespace std;

/*
   Find the "empty" interval
   Complexity: O(n*log(n))
*/

pair<int, int> interval(pair<int, int>* a, int n) {
    sort(a, a+n);
    pair<int, int> result;
    result = make_pair(0, 0);
    int max_second = 0;
    for (int i=0; i<n-1; i++) {
        if (a[i].second > max_second) {
            max_second = a[i].second;
        }
        if (a[i+1].first - max_second > result.second - result.first) {
            result = make_pair(max_second, a[i+1].first);
        }
    }
    return result;
}

bool operator < (const pair<int, int> a , const pair<int, int> b) {
  if (a.first == b.first) {
    return a.second < b.second;
  }
  else {
    return a.first < b.first;
  }
}


int main() {
    FILE *filep;
    int n, first, second;
    pair<int, int> a[100000];
    filep = fopen ("input.txt", "r");
    fscanf(filep, "%d\n", &n);

    for (int i=0; i<n; i++) {
        fscanf(filep, "%d %d", &first, &second);
        a[i] = make_pair<int, int>(first, second);
    }
    fclose(filep);

    filep = fopen("output.txt", "w");
    pair<int, int> result = interval(a, n);
    if (result.first != result.second) {
        fprintf(filep, "%d %d\n", result.first, result.second);
    }
    else {
        fprintf(filep, "0\n");
    }
    fclose(filep);

    return 0;
}
