#include <iostream>
#include <cstdio>
#include <algorithm>
#include <iomanip>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

int n;

void answer(){
  cin >> n;

  double min_v = 0, max_v = 1e9;
  for(int i = 1; i <= n; i++){
    int min_t, max_t;
    cin >> min_t >> max_t;
    min_v = max(min_v, (double)i / max_t);
    max_v = min(max_v, (double)i / min_t);
  }

  if(min_v > max_v){
    cout << -1 << endl;
    return;
  }

  cout << min_v << endl;
}

int main(){
  freopen("in.txt", "r", stdin);
	freopen("out.txt", "w", stdout);
	ios::sync_with_stdio(0);
	cin.tie(0);
  cout << fixed << setprecision(7);

	int t;
	cin >> t;

	for(int i = 1; i <= t; i++){
		cout << "Case #" << i << ": ";
		answer();
	}
	
	return 0;
}
