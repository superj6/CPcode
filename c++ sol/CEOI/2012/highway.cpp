//#include "office.h"
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <string.h>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second
 
int n;
int a, b, c, d;
vector<int> v[2];
 
bool works(int x, int y, int z){
    string s(3, ' ');
    s[0] = x + '0', s[1] = y + '0', s[2] = z + '0';
    sort(s.begin(), s.end());
    return s != "123" && s != "145";
}
 
int main(){
	ios::sync_with_stdio(0);
	cin.tie(0);
	
	n = GetN();
	
	for(a = 1, b = 2; b < n && v[0].size() < 2; b += 2){
	    v[isOnLine(a, b, b + 1)].push_back(b);
	}
	
	if(!v[1].empty() || v[0].size() < 2){
	    b = v[1][0];
	    c = v[0][0] + isOnLine(a, b, v[0][0]);
	    d = v[0].size() < 2 ? n : v[0][1] + isOnLine(a, b, v[0][1]);
	}else{
	    for(a = 1, d = 0; a < 3 && !d; a++)
	    for(b = a + 1; b < 6 && !d; b++)
        for(c = b + 1; c < 6 && !d; c++){
            d = works(a, b, c) && isOnLine(a, b, c);
        }
        if(!d) a = 4, b = 5, c = 6;
        a--, b--, c--;
        d = 15 - a - b - c;
        for(c = 1; c == a || c == b || c == 15 - a - b - d; c++);
        d -= c;
        if(d == 5 && isOnLine(a, b, d)){
            for(d = 6; d < n - 2 && isOnLine(d, d + 1, d + 2); d += 3);
            for(; d % 3 < 2 && isOnLine(a, b, d); d++);
        }
	}
	
	Answer(a, b, c, d);
 
	return 0;
}