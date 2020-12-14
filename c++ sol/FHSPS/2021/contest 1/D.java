import java.io.*;
import java.util.*;
import java.lang.*;
import java.math.*;

class Solution{
	static BufferedReader f = new BufferedReader(new InputStreamReader(System.in));
	static PrintWriter out = new PrintWriter(new BufferedWriter(new OutputStreamWriter(System.out)));
	
	static void answer() throws IOException{
		int n = Integer.parseInt(f.readLine());
		int[] d = new int[n], g = new int[n];
		Arrays.fill(d, 0);

		for(int i = 0; i < n - 1; i++){
			StringTokenizer st = new StringTokenizer(f.readLine());
			int u = Integer.parseInt(st.nextToken()) - 1, v = Integer.parseInt(st.nextToken()) - 1;
			g[u] = v; d[v]++;
		}
		
		int x = 0;
		while(d[x] > 0) x++;
		
		StringBuilder s = new StringBuilder(Integer.toString(x + 1));
		for(int i = 0; i < n - 1; i++){
			x = g[x];
			s.append(" " + Integer.toString(x + 1));
		}
		out.println(s.toString());
	}
	
    public static void main(String[] args) throws IOException{
        //BufferedReader f = new BufferedReader(new FileReader(""));
        //PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("")));
		
		int t = Integer.parseInt(f.readLine());
		
		for(int i = 0; i < t; i++) answer();
        
        out.close();
    }

}