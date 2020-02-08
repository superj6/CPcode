import java.io.*;
import java.util.*;
import java.lang.*;
import java.math.*;

class Solution {
	
	public static String solution(int[] a){
		int n = a.length;
		Arrays.sort(a);
		if(n == 1 || ((a[0] == 0 || (n == 2 && a[0] < 0)) && a[n - 1] == 0)) return Integer.toString(a[n - 1]);
		
		BigInteger ret = BigInteger.ONE;
		for(int i = 0; i < n; i++){
			if(a[i] != 0 && !(a[i] < 0 && (i < n - 1 ? a[i + 1] >= 0 : true) && ret.compareTo(BigInteger.ZERO) > 0)) ret = ret.multiply(BigInteger.valueOf(a[i]));
		} 
		
		return ret.toString();
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