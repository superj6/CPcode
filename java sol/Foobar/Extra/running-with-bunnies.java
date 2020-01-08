import java.io.*;
import java.util.*;
import java.lang.*;
import java.math.*;

class Solution {
	static int n, l;
	static int[][] t;
	static int ret[] = new int[0];
	
	static void solve(int[] a, boolean[] used){
		int m = a.length;
		if(m > ret.length){
			int lt = t[0][a[0] + 1] + t[a[m - 1] + 1][n - 1];
			for(int i = 0; i < m - 1; i++) lt += t[a[i] + 1][a[i + 1] + 1];
			if(lt <= l) ret = a.clone();
			else return;
		}
		if(m == n - 2) return;
		
		int[] na = new int[m + 1];
		for(int i = 0; i < m; i++) na[i] = a[i];
		for(int i = 0; i < n - 2; i++){
			if(!used[i]){
				na[m] = i;
				used[i] = true;
				solve(na, used);
				used[i] = false;
			}
		}
	}

	public static int[] solution(int[][] tt, int ll){
		n = tt.length;
		l = ll;
		t = tt;
		
		for(int k = 0; k < n; k++)
		for(int i = 0; i < n; i++)
		for(int j = 0; j < n; j++){
			t[i][j] = Math.min(t[i][j], t[i][k] + t[k][j]);
		}
		
		for(int i = 0; i < n; i++){
			if(t[i][i] < 0){
				ret = new int[n - 2];
				for(int j = 0; j < n - 2; j++) ret[j] = j;
				return ret;
			}
		}
		
		solve(new int[0], new boolean[n - 2]);
		
		Arrays.sort(ret);
		return ret;
	}

    public static void main(String[] args) throws IOException{
        //BufferedReader f = new BufferedReader(new FileReader(""));
        //PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("")));
        BufferedReader f = new BufferedReader(new InputStreamReader(System.in));
		
		int l = 1;
		int[][] t = {{0, 2, 2, 2, -1}, {9, 0, 2, 2, -1}, {9, 3, 0, 2, -1}, {9, 3, 2, 0, -1}, {9, 3, 2, 2, 0}};
		
    	System.out.println(Arrays.toString(solution(t, l)));
        
        //out.close();
    }

}