#include <iostream>
#include <algorithm>
#include <cstdio>
using namespace std;
#define endl '\n'
#define pi pair<int, int>


const int maxn = 100;
int n, m;
int cnt[maxn];
int maxv, sum, ret;


int main(){
        freopen("gangs.in", "r", stdin);
        freopen("gangs.out", "w", stdout);
        ios::sync_with_stdio(0);
        cin.tie(0);


        cin >> n >> m;


        cin >> ret;
        for(int i = 1; i < m; i++){
                cin >> cnt[i];
                maxv = max(maxv, cnt[i]);
                sum += cnt[i];
        }


        cnt[0] = max(sum % 2, 2 * maxv - sum);
        ret -= cnt[0];
        sum += cnt[0];


        if(ret <= 0){
                cout << "NO" << endl;
                return 0;
        }


        cout << "YES" << endl;
        cout << ret << endl;


        for(int c = 0, ci = -1; sum; sum--){
                for(int i = 0; i < m; i++){
                        if(!cnt[i]) continue;
                        if(i == ci || !c){
                                cout << i + 1 << endl;
                                cnt[i]--;
                                ci = i;
                                c++;
                                break;
                        }else{
                                bool works = 1;
                                for(int j = 0; j < m; j++){
                                        if(j == i || j == ci) continue;
                                        if(sum + c - 2 < 2 * cnt[j]) works = 0;
                                }
                                if(works){
                                        cout << i + 1 << endl;
                                        cnt[i]--;
                                        c--;
                                        break;
                                }
                        }
                }
        }


        for(int i = 0; i < ret; i++) cout << 1 << endl;


        return 0;
}