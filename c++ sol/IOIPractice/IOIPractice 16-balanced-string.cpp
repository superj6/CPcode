/*
  Turn AB string to 01 string for convenience. In the string, find the max and min consecutive length for both 0s and 1s. Assume the
max 0 length is larger than max 1 length. If the max 1 length is greater than 1, that means the max 0 length is as well, and that
would cause the tring to fail for size 2 substrings. Otherwise, if the min length 0 string + 1 is less than the max length 0 string,
that means the substring that is the min length 0 string borded by 1s will have the same size but 2 less 0s than another substring
that will exist with all 0s, so it will cause the string to fail for size 0 min length + 2 substrings. However, if neither of those
are the case, we are not finished. Realize with the two previous checks, the string can be composed of the two following sequences:
0000...[min length]1 and 0000...[max length]1. Realize we can create a new string such that the first sequence is a 0 and the second
sequence is a 1 in our new string, and the same conditions that must have applied to the original string must also apply to the new
one, since you can show otherwise it will correspond to a substring comprised of a combination of min lengths and max lengths that
fails. This means you can keep encoding and rerunning the algorithm on the string until it is length 0 or 1, since then it will
obviously work, and if the string doesn't fail at any stage it is a balanced string. Because the encoding divides the string length
by at least 2, you only reencode the string at max lgn times, for a total complexity of O(nlgn).
*/

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

int n;
string s;
vector<int> v, w;
int mn[2], mx[2];
void answer(){
	cin >> s;
	n = s.size();
	
	v.resize(n);
	for(int i = 0; i < n; i++) v[i] = s[i] == 'A';
	
	while(v.size() > 1){
		n = v.size();
		
		w.clear();
		while(~-v.size() && v.back() == v[0]){
			w.push_back(v.back());
			v.pop_back();
		}
		reverse(w.begin(), w.end());
		v.insert(v.begin(), w.begin(), w.end());
		
		mn[0] = mn[1] = n, mx[0] = mx[1] = 0;
		for(int i = 0, j = 1; i < n; i++, j++){
			if(i == n - 1 || v[i] != v[i + 1]){
				mn[v[i]] = min(mn[v[i]], j);
				mx[v[i]] = max(mx[v[i]], j);
				j = 0;
			}
		}
		
		if(mx[0] < mx[1]){
			swap(mn[0], mn[1]), swap(mx[0], mx[1]);
			for(int i = 0; i < n; i++) v[i] ^= 1;
		}
		
		if(v[0]) reverse(v.begin(), v.end());
		
		if(mn[0] + 1 < mx[0] || mx[1] > 1){
			cout << 0 << endl;
			return;
		}
		
		swap(v, w), v.clear();
		for(int i = mn[0]; i < n; i += !w[i] + mx[0]){
			v.push_back(w[i]);
		}
	}
	
	cout << 1 << endl;
}

int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	int t;
	cin >> t;
	
	for(int i = 0; i < t; i++) answer();

	return 0;
}
