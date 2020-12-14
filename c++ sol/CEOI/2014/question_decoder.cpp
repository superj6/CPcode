#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'
#define ll long long
#define pi pair<int, int>
#define f first
#define s second

const int maxn = 920;
int a[maxn];

int decode(int n, int x, int y){
    x--, y--;
    if(!a[0]) for(int i = 0, j = 0; i < n; i++, j++){
        while(__builtin_popcount(j) != 6) j++;
        a[i] = j;
    }
    return (a[x] >> y) & 1;
}