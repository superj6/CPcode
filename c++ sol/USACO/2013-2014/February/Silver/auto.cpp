#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <iterator>
using namespace std;

int w, n;
vector<string> dict;
vector<int> num;

int main(){
	ifstream fin ("auto.in");
	ofstream fout ("auto.out");

	fin >> w >> n;
	
	dict.resize(w), num.resize(w);
	
	for(int i = 0; i < w; i++){
		fin >> dict[i];
		num[i] = i;
	}
	
	struct {
		bool operator()(int a, int b){
			return dict[a].compare(dict[b]) < 0;
		}
	} cmp;
	
	sort(num.begin(), num.end(), cmp);
	
	sort(dict.begin(), dict.end());
	
	for(int i = 0; i < n; i++){
		int add;
		string test;
		fin >> add >> test;
		
		int index;
		bool works = true;
		if((lower_bound(dict.begin(), dict.end(), test) - dict.begin()) + add - 1 >= w){
			works = false;
		}else{
			index = (lower_bound(dict.begin(), dict.end(), test) - dict.begin()) + add - 1;
			
			for(int i = 0; i < test.size(); i++){
				if(i == dict[index].size()){
					works = false;
					break;
				}
				
				if(dict[index][i] != test[i]){
					works = false;
					break;
				}
			}
		}
		
		
		if(works) fout << num[index] + 1 << endl;
		else fout << -1 << endl;
	}

	return 0;
}