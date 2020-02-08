import java.io.*;
import java.util.*;
import java.lang.*;
import java.math.*;

class Solution {
	
	public static int solution(int[] a){
		int n = a.length;
		int[] dp = new int[n];
		int ret = 0;
		for(int i = 0; i < n; i++)
		for(int j = 0; j < i; j++){
			if(a[i] % a[j] == 0){
				dp[i]++;
				ret += dp[j];
			}
		}
		
		return ret;	
	}

    public static void main(String[] args) throws IOException{
        //BufferedReader f = new BufferedReader(new FileReader(""));
        //PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("")));
        BufferedReader f = new BufferedReader(new InputStreamReader(System.in));

    	int n = Integer.parseInt(f.readLine());
    	
    	int[] a = new int[n];
    	StringTokenizer st = new StringTokenizer(f.readLine());
    	for(int i = 0; i < n; i++) a[i] = Integer.parseInt(st.nextToken());
    	
    	System.out.println(solution(a));
        
        //out.close();
    }

}