#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

ll n;

void answer(){
	cin >> n;
	n--;
	
	ll x = 1, y = 1;
	while(n >= 9 * x * y) n -= 9 * x * y, x *= 10, y++;
	
	ll ret = n / y + x;
	for(int i = 0; i < y - n % y - 1; i++) ret /= 10;
	ret %= 10;
	
	cout << ret << endl;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int t;
	cin >> t;
	
	for(int i = 0; i < t; i++) answer();

	return 0;
}