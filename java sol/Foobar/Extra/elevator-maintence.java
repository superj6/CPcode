import java.io.*;
import java.util.*;
import java.lang.*;
import java.math.*;

class Solution {
	
	public static String[] solution(String[] s){
		Arrays.sort(s, new Comparator<String>(){
		  public int compare(String a, String b){
		  	int[] x = new int[3], y = new int[3];
		  	x[0] = x[1] = x[2] = y[0] = y[1] = y[2] = -1;
		  	for(int i = 0, c = 0; i < a.length(); i++){
		  		if(a.charAt(i) == '.') x[++c] = 0;
		  		else x[c] = 10 * x[c] + (int)(a.charAt(i) - '0');
		  	}
		  	for(int i = 0, c = 0; i < b.length(); i++){
		  		if(b.charAt(i) == '.') y[++c] = 0;
		  		else y[c] = 10 * y[c] + (int)(b.charAt(i) - '0');
		  	}
		  	for(int i = 0; i < 3; i++){
		  		if(x[i] != y[i]) return Integer.compare(x[i], y[i]);
		  	}
		  	return 0;
		  }
		});
		return s;
	}

    public static void main(String[] args) throws IOException{
        //BufferedReader f = new BufferedReader(new FileReader(""));
        //PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("")));
        BufferedReader f = new BufferedReader(new InputStreamReader(System.in));

    	int n = Integer.parseInt(f.readLine());
    	
    	String[] s = new String[n];
    	for(int i = 0; i < n; i++) s[i] = f.readLine();
    	
    	System.out.println(Arrays.toString(solution(s)));
    	
        
        //out.close();
    }

}