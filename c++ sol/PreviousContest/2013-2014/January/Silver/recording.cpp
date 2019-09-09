#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main(){
	ifstream fin ("recording.in");
	ofstream fout ("recording.out");

	int n;
	fin >> n;
	
	pair<int, int> a[n];
	
	for(int i = 0; i < n; i++){
		fin >> a[i].second >> a[i].first;
	}
	
	sort(a, a+n);
	
	int last1 = 0, last2 = 0, total = 0;
	
	for(int i = 0; i < n; i++){
		int begin = a[i].second, end = a[i].first;
		
		if(begin >= last1){
			total++;
			last1 = end;
		}else if(begin >= last2){
			total++;
			last2 = end;
		}
		
		if(last1 < last2){
			int temp = last1;
			last1 = last2;
			last2 = temp;
		}
	}
	
	fout << total << endl;

	return 0;
}