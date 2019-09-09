

import java.util.*;
import java.lang.*;
import java.io.*;


class cardgame
{
	public static void main (String[] args) throws java.lang.Exception
	{
		BufferedReader f = new BufferedReader(new FileReader("cardgame.in"));
		PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("cardgame.out")));
		int n = Integer.parseInt(f.readLine());
		int[] arr1 = new int[n/2], arr2 = new int[n/2], fullarr = new int[n];
		
		for(int i = 0; i < n; i++){
			fullarr[i] = Integer.parseInt(f.readLine());
		}
		for(int i = 0; i < n/2; i++){
			arr1[i] = fullarr[i];
			arr2[i] = fullarr[i + n/2];
		}
		
		Arrays.sort(arr1);
		Arrays.sort(arr2);
		Arrays.sort(fullarr);
		
		int[] other1 = new int[n/2], other2 = new int[n/2], fullother = new int[n];
		int index1 = 0, index2 = 0;
		
		for(int i = 1; i <= 2*n; i++){

			if(index1 == n){
				fullother[index2] = i;
				index2++;
				continue;
			}
			
			if(i < fullarr[index1]){
				fullother[index2] = i;
				index2++;
			}else{
				index1++;
			}
		}

		for(int i = 0; i < n/2; i++){
			other1[i] = fullother[i];
			other2[i] = fullother[i + n/2];
		}
		
		int total = 0;
		index1 = 0;
		index2 = 0;
		
		while(index1 < n/2 && index2 < n/2){
			if(other1[index1] < arr2[index2]){
				total++;
				index1++;
				index2++;
			}else{
				index2++;
			}
		}
		
		index1 = n/2 - 1;
		index2 = n/2 - 1;
		
		while(index1 >= 0 && index2 >= 0){
			if(other2[index1] > arr1[index2]){
				total++;
				index1--;
				index2--;
			}else{
				index2--;
			}
		}
		
		out.println(total);
		out.close();
	}
}