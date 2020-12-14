import java.io.*;
import java.util.*;
import java.lang.*;
import java.math.*;

class Solution{
    public static void main(String[] args) throws IOException{
        //BufferedReader f = new BufferedReader(new FileReader(""));
        //PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("")));
		BufferedReader f = new BufferedReader(new InputStreamReader(System.in));

		int T = Integer.parseInt(f.readLine());
		
		for(int tt = 0; tt < T; tt++){
			int n = Integer.parseInt(f.readLine());
			int[] a = new int[n];
			
			StringTokenizer st = new StringTokenizer(f.readLine());
			
			int ret = 0;
			for(int i = 0; i < n; i++){
				a[i] = Integer.parseInt(st.nextToken());
				if(a[i] > a[ret]) ret = i;
			}
			
			System.out.println(ret + 1);
		}
        
        //out.close();
    }

}