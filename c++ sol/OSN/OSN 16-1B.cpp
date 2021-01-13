/*
	Query the intervals [n / 2 -> 1], [1 -> n / 2], [n -> n / 2 + 1], [n / 2 + 1 -> n], and keep track of what
the ith query is and what query numbers we get a beep after. Now you can test every wait time from 0 to n - 1 and
see which intervals will map to the same number for both beeps. There is a possibility that two wait times work,
corresponding to one number in the first half and one number in the second half. In that case you should use up to
n queries to test which interval it is in. However, in that case always querying the number in the first half seems
to get AC. If that's not the case, it is also possible you need more queries until you get the second beep, but that
is ok as it will take at most n more queries. Once you figure out the interval you can just query the number until
you get n beeps. Querying the intervals takes 2 * n queries, you could possibly need n more queries for the two cases
stated, and then it will take at most 2 * n more to get n beeps. That adds up to 5 * n beeps.
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
//#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

int n, m, k;
string s;
vector<int> a, v;

void f(int x, bool y){
	if(y && v.size() == 2) return;
	cout << (x + 1) << endl;
	cin >> s;
	if(s == "BIP") v.push_back(a.size());
	a.push_back(x);
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	cin >> s >> n >> m >> k;
	
	for(int i = 0; i < 2; i++){
			for(int j = (n + i) / 2 - 1; ~j; j--) f(i * (n / 2) + j, 1);
			for(int j = 0; j < (n + i) / 2; j++) f(i * (n / 2) + j, 1);
	}
	
	while(v.size() < 2) f(0, 1);
	
	int x = min(n - 1, v[0]);
	while(a[v[0] - x] != a[v[1] - x]) x--;
	
	while(v.size() < n) f(a[v[0] - x], 0);

	return 0;
}