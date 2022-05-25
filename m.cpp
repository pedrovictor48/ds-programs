#include <bits/stdc++.h>

using namespace std;

void merge(vector<int> &nomes) {
    int n = nomes.size();
    if(n == 1) return;
    vector<int> esq(n/2), dir(n - n/2);
    int ind = 0;
    for(int i = 0; i < n/2; i++) {
        esq[ind] = nomes[i];
        ind++;
    }
    ind = 0;
    for(int i = n/2; i < n; i++) {
        dir[ind] = nomes[i];
        ind++;
    }
    merge(esq);
    merge(dir);
    int tamEsq = esq.size(), tamDir = dir.size();
    int i, j, k;
    i = j = k = 0;
    while(j < tamEsq && k < tamDir) {
        if(esq[j] < dir[k]) {
            nomes[i] = esq[j];
            j++;
        }
        else {
            nomes[i] = dir[k];
            k++;
        }
        i++;
    }    
    while(j < tamEsq) {
        nomes[i] = esq[j];
        j++;
        i++;
    }
    while(k < tamDir) {
        nomes[i] = dir[k];
        k++;
        i++;
    }
}

int main() {
    int n; cin >> n;
    vector<int> q(n);
    for(int &x : q)
        cin >> x;
    merge(q);
    for(int x : q)
        cout << x << " ";
}