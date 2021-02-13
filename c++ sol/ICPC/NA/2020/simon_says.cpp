#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const string t = "Simon says ";
const int m = t.size();
int n;
string s;

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> n;
	
	cin.ignore();
	for(int i = 0; i < n; i++){
		getline(cin, s);
		if(s.substr(0, m) == t) cout << s.substr(m, s.size() - m) << endl;
	}
	
	return 0;
}