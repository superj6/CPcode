import java.io.*;
import java.util.*;
import java.lang.*;
import java.math.*;

class Solution {
	static int m;
	
	static int solve(int x){
		int ret = -1;
		for(int l = 1, r = m; r != x;){
			ret = r;
			int mid = (l + r) / 2;
			if(x < mid) r = mid - 1;
			else{
				l = mid; 
				r--;
			}
		}
		return ret;
	}
	
	public static int[] solution(int h, int[] a){
		int n = a.length;
		m = (1 << h) - 1;
		
		int[] ans = new int[n];
		for(int i = 0; i < n; i++) ans[i] = solve(a[i]);
		
		return ans;
	}

    public static void main(String[] args) throws IOException{
        //BufferedReader f = new BufferedReader(new FileReader(""));
        //PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("")));
        BufferedReader f = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(f.readLine());

    	int n = Integer.parseInt(st.nextToken()), h = Integer.parseInt(st.nextToken());
    	
    	int[] a = new int[n];
    	st = new StringTokenizer(f.readLine());
    	for(int i = 0; i < n; i++) a[i] = Integer.parseInt(st.nextToken());
    	
		System.out.println(Arrays.toString(solution(h, a)));
        
        //out.close();
    }

}