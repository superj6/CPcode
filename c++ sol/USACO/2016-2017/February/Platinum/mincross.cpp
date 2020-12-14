#include <iostream>
#include <cstdio>
#include <algorithm>
#include <string.h>
using namespace std;
#define endl '\n'
 
const int maxn = 100001;
int bit[maxn];
 
void add(int ind){
    ind++;
   
    for(; ind < maxn; ind += ind & (-ind)) bit[ind]++;
}
 
int qry(int ind){
    ind++;
    int ret = 0;
   
    for(; ind > 0; ind -= ind & (-ind)) ret += bit[ind];
   
    return ret;
}
 
int main(){
    freopen("mincross.in", "r", stdin);
    freopen("mincross.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(NULL);
   
    memset(bit, 0, sizeof(bit));
   
    int n;
    cin >> n;
   
    int a[n], b[n], p[n];
    for(int i = 0; i < n; i++){
        int x;
        cin >> x;
        x--;
       
        p[x] = i;
    }

    for(int i = 0; i < n; i++){
        int x;
        cin >> x;
        x--;
       
        a[p[x]] = i;
        b[i] = p[x];
    }
   
    long tot = 0;
   
    for(int i = 0; i < n; i++){
        tot += a[i] - qry(a[i]);
        add(a[i]);
    }
   
    long minv = tot;
   
    for(int i = n - 1; i >= 0; i--){
        tot += 2 * a[i] + 1 - n;
        minv = min(minv, tot);
    }

    for(int i = n - 1; i >= 0; i--){
        tot += 2 * b[i] + 1 - n;
        minv = min(minv, tot);
    }
   
    cout << minv << endl;
 
    return 0;
}