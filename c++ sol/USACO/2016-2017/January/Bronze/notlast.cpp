#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <string>
using namespace std;

int main() {
	ifstream fin ("notlast.in");
	ofstream fout ("notlast.out");
	
	map<string, int> name;
	
	name["Bessie"] = 0;
	name["Elsie"] = 1;
	name["Daisy"] = 2;
	name["Gertie"] = 3;
	name["Annabelle"] = 4;
	name["Maggie"] = 5;
	name["Henrietta"] = 6;
	
	string getname[] = {"Bessie", "Elsie", "Daisy", "Gertie", "Annabelle", "Maggie", "Henrietta"};
	
	int n, firstv = 10000000, secondv = 10000000, index = -1;
	bool tie = false;
	fin >> n;
	int amount[7];
	for(int i = 0; i < 7; i++) amount[i] = 0;
	
	for(int i = 0; i < n; i++){
		string curr;
		int add;
		fin >> curr >> add;
		
		amount[name.find(curr)->second] += add;
	}
		
		
	for(int i = 0; i < 7; i++){
		if(amount[i] < firstv){
			secondv = firstv;
			firstv = amount[i];
		}else if(amount[i] < secondv && amount[i] != firstv){
			secondv = amount[i];
		}
	}
	
	for(int i = 0; i < 7; i++){
		if(amount[i] == secondv){
			if(index == -1){
				index = i;
			}else{
				tie = true;
			}
		}
	}
	
	if(tie || index == -1){
		fout << "Tie";
	}else{
		fout << getname[index];
	}
	

	
	return 0;
}