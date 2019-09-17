#include <iostream>
#include <cstdio>
#include <algorithm>
using namespace std;
#define endl '\n'

void answer(){
        int n;
        cin >> n;

   int ret = 0;
   for(int i = 0; i < n; i++){
       int x;
       cin >> x;

      ret ^= (x % 4);
   }

   cout << (ret ? "first" : "second") << endl;
}

int main() {
        ios::sync_with_stdio(0);
        cin.tie(0);

   int t;
   cin >> t;

   for(int i = 0; i < t; i++) answer();

        return 0;
}