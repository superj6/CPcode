import java.io.*;
import java.util.*;
import java.lang.*;
import java.math.*;

class Solution {
	
	public static int solution(int n){
		int ret = 0;
		for(int i = 1, j = 0, k = n; i <= k; ret++){
			k -= i;
			i += j;
			j = i - j;
		}
		for(int i = 1, k = n; i <= k; ret--){
			k -= i;
			i *= 2;
		}
		return ret;
	}

    public static void main(String[] args) throws IOException{
        //BufferedReader f = new BufferedReader(new FileReader(""));
        //PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("")));
        BufferedReader f = new BufferedReader(new InputStreamReader(System.in));

    	System.out.println(solution(Integer.parseInt(f.readLine())));
        
        //out.close();
    }

}