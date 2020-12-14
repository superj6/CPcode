import java.io.*;
import java.util.*;
import java.lang.*;
import java.math.*;

class Solution{
    public static void main(String[] args) throws IOException{
        //BufferedReader f = new BufferedReader(new FileReader(""));
        //PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("")));
		BufferedReader f = new BufferedReader(new InputStreamReader(System.in));
		
		final int m = 300;
		
		int[] lp = new int[m];
		ArrayList<Integer> p = new ArrayList<Integer>();
		
		for(int i = 2; i < m; i++){
			if(lp[i] == 0) p.add(lp[i] = i);
			for(int j = 0; j < p.size() && p.get(j) <= lp[i] && i * p.get(j) < m; j++){
				lp[i * p.get(j)] = p.get(j);
			}
		}

		char[] a = f.readLine().toCharArray();
		int n = a.length;
		
		String s = "";
		long ret = 0;
		for(int i = 0, j = 0; i < n; i++){
			if(Character.isUpperCase(a[i])) s += a[i]; 
			else ret += (a[i] - 'a' + 1) * p.get(j++);
		}
		
		System.out.println(s + " " + ret);
        
        //out.close();
    }

}