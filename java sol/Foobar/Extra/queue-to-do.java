import java.io.*;
import java.util.*;
import java.lang.*;
import java.math.*;

class Solution {
	static int k = 31;
	
	static int xorsum(int x){
		int ret = ((x + 1) >> 1) & 1;
		for(int i = 1; i < k; i++) ret += (1 << i) * ((x + 1) & 1) * ((x >> i) & 1);
		return ret;
	}
	
	static int xorsum(int l, int r){
		return xorsum(r) ^ (l == 0 ? 0 : xorsum(l - 1));
	}
	
	public static int solution(int n, int m){
		int ret = 0;
		for(int i = 0; i < m; i++) ret ^= xorsum(n + m * i, n + (m - 1) * (i + 1));
		return ret;
	}

    public static void main(String[] args) throws IOException{
        //BufferedReader f = new BufferedReader(new FileReader(""));
        //PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("")));
        BufferedReader f = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(f.readLine());
		
		int n = Integer.parseInt(st.nextToken()), m = Integer.parseInt(st.nextToken());
		
		System.out.println(solution(n, m));
        
        //out.close();
    }

}
