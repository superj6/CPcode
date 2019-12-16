/*
    The first thing to do for this problem is to find out the the amount of crosses in
the initial set up. To do this, you hold for each index on one side what the corresponding
index is on the other side, then you iterate through the indices on one side and store in a
bit the indices on the other side encountered so far. That means the amount crosses by a
particular pair as you iterate through is the index that you are currently at minus the amount
of end indices in the bit before it because that means all of those pairs have had both indices
sides before both of the current one, while all the other cross through it as they have
one index before it on a side and on the other side the index is after the current one on that
side. Lastly, to deal with cyclic shifts, you just think about rating both sides and for each
side realize for the last index currently on that every index on the other side currently
after the pair's other side index will be subtracted as those were all crossing because it was
on the end while all the indices before the pair's other side index will be added as the value
is moving to the otheer side so all must cross through the pair. The complexity is O(nlogn) due
to the bit.
*/

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
