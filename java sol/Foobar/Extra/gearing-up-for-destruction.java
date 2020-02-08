import java.io.*;
import java.util.*;
import java.lang.*;
import java.math.*;

class Solution {
	
	public static int[] solution(int[] a){
		int n = a.length;
		int ret = 0;
		for(int i = 1; i < n; i++){
			ret = a[i] - a[i - 1] - ret;
		}
		
		int[] ans = {-1, -1};
		if(n % 2 == 0){
			if(ret > 0){
				if(ret % 3 == 0) ans = new int[]{2 * ret / 3, 1};
				else ans = new int[]{2 * ret, 3};
			}
		}else{
			if(ret < 0) ans = new int[]{-2 * ret, 1};
		}
		
		double t = (double)ans[0] / ans[1];
		for(int i = 1; i < n; i++){
			t = a[i] - a[i - 1] - t;
			if(t < 1) return new int[]{-1, -1};
		}
		return ans;
	}

    public static void main(String[] args) throws IOException{
        //BufferedReader f = new BufferedReader(new FileReader(""));
        //PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("")));
        BufferedReader f = new BufferedReader(new InputStreamReader(System.in));

    	int n = Integer.parseInt(f.readLine());
    	
    	int[] a = new int[n];
    	StringTokenizer st = new StringTokenizer(f.readLine());
    	for(int i = 0; i < n; i++) a[i] = Integer.parseInt(st.nextToken());
    	
    	System.out.println(Arrays.toString(solution(a)));
        
        //out.close();
    }

}