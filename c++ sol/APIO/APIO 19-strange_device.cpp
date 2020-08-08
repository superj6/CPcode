/*

*/

#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define pi pair<long long, long long>
 
const long long inf = 2000000000000000000;
const int maxn = 2000001;
long long n, m, a, b;
pi p[maxn];
 
int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin >> n >> a >> b;
	m = min(inf / b, a / __gcd(a, b % a + 1)) * b;
	
	for(int i = 0; i < n; i++){
		cin >> p[i].first >> p[i].second;
		if(p[i].second - p[i].first >= m) p[i] = {0, m - 1};
		p[i].first %= m, p[i].second %= m;
		if(p[i].second < p[i].first){
			p[i + 1] = {p[i].first, m - 1};
			p[i].first = 0;
			i++, n++;
		}
	} 
	
	p[n] = {m, m};
	sort(p, p + n);
	
	long long ret = 0;
	for(long long i = 0, j = p[0].second, k = p[0].first; i < n; i++){
		j = max(j, p[i].second);
		if(j < p[i + 1].first){
			ret += j - k + 1;
			k = p[i + 1].first;
		}
	}
	
	cout << ret << endl;
	
	return 0;
}
