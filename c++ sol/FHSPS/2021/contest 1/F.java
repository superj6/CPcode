import java.io.*;
import java.util.*;
import java.lang.*;
import java.math.*;

class Solution{
	static BufferedReader f = new BufferedReader(new InputStreamReader(System.in));
	static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));

	static void answer() throws IOException{
		StringTokenizer st = new StringTokenizer(f.readLine());
		int n = Integer.parseInt(st.nextToken()), m = 30, k = Integer.parseInt(st.nextToken());
		int[][] a = new int[n + 1][m];
		
		st = new StringTokenizer(f.readLine());
		int ret = 0;
		for(int i = 1; i <= n; i++){
			int x = Integer.parseInt(st.nextToken()), y = 0;
			for(int j = 0; j < m; j++){
				a[i][j] = a[i - 1][j] + ((x >> j) & 1);
				if(i >= k && a[i][j] > a[i - k][j]) y |= 1 << j;
			}
			ret = Math.max(ret, y);
		}
		
		out.println(ret);
	}

    public static void main(String[] args) throws IOException{
        //BufferedReader f = new BufferedReader(new FileReader(""));
        //PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("")));
        
    	int t = Integer.parseInt(f.readLine());
    	
    	for(int i = 0; i < t; i++) answer();
        
        out.close();
    }

}