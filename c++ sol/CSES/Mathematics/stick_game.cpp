#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'

const int maxn = 1000001, maxk = 100;
int n, k;
int p[maxk];
bool dp[maxn];

void precomp(){
        for(int i = 1; i <= n; i++){
                for(int j = 0; j < k; j++){
                        if(i - p[j] >= 0 && !dp[i - p[j]]){
                    dp[i] = 1;
                    break;
                        }
                }
        }
}

int main() {
        ios::sync_with_stdio(0);
        cin.tie(0);

        cin >> n >> k;

        for(int i = 0; i < k; i++) cin >> p[i];

        precomp();

        for(int i = 1; i <= n; i++) cout << (dp[i] ? 'W' : 'L');
        cout << endl;

        return 0;
}