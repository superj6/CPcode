#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
using namespace std;

vector<int> array;

int maxright(int index, int radius);
int maxleft(int index, int raduis);

int main() {
	ifstream fin ("angry.in");
	ofstream fout ("angry.out");
	
	int n;
	fin >> n;
	array.resize(n);
	
	for(int i = 0; i < n; i++) fin >> array[i];
	
	sort(array.begin(), array.end());
	//for(int i = 0; i < n; i++) fout << array[i] << " ";
	
	int out = 0;
	
	for(int i = 0; i < n; i++){
		out = max(out,  maxright(i , 1) - maxleft(i, 1) + 1);
	}
	
	fout << out;
	
	return 0;
}


int maxright(int index, int radius){
	if(index == array.size() - 1){
		return index;
	}else if(array[index + 1] - array[index] > radius){
		return index;
	}
	
	int next = index;
	
	while(array[next + 1] - array[index] <= radius){
		next++;
		if(next == array.size() - 1){
			return next;
		}
	}
	
	return maxright(next, radius + 1);
}

int maxleft(int index, int radius){
	if(index == 0){
		return index;
	}else if(array[index] - array[index - 1] > radius){
		return index;
	}
	
	int next = index;
	
	while(array[index] - array[next - 1] <= radius){
		next--;
		if(next == 0){
			return next;
		}
	}
	
	return maxleft(next, radius + 1);
}	