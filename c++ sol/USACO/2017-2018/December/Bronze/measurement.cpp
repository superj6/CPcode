#include <iostream>
#include <fstream>
#include <algorithm>
#include <map>
#include <string>
using namespace std;

int main() {
	ifstream fin ("measurement.in");
	ofstream fout ("measurement.out");
	
	map<string, int> name;
	name["Bessie"] = 0;
	name["Elsie"] = 1;
	name["Mildred"] = 2;
	
	int n;
	fin >> n;
	int timetable[101][3];
	
	for(int i = 0; i < 101; i++){
		for(int j = 0; j < 3; j++){
			timetable[i][j] = 7;
		}
	}
	
	for(int i = 0; i < n; i++){
		int day, index, change;
		string cow;
		fin >> day >> cow >> change;
		index = name.find(cow)->second;
		
		for(int j = day; j < 101; j++){
			timetable[j][index] += change;
		}
	}
	
	int changes = 0;
	bool highest[3];
	for(int i = 0; i < 3; i++) highest[i] = true;
	
	for(int i = 0; i < 101; i++){
		bool newhigh[3];
		for(int j = 0; j < 3; j++) newhigh[j] = false;
		
		int high = 0;
		for(int j = 0; j < 3; j++){
			high = max(high, timetable[i][j]);
		}
		
		for(int j = 0; j < 3; j++){
			if(timetable[i][j] == high) newhigh[j] = true;
		}
		
		for(int j = 0; j < 3; j++){
			if(highest[j] != newhigh[j]){
				changes++;
				break;
			}
		}
		
		for(int j = 0; j < 3; j++){
			highest[j] = newhigh[j];
		}
	}
	
	fout << changes;
	
	return 0;
}