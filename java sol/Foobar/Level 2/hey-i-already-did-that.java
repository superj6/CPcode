import java.io.*;
import java.util.*;
import java.lang.*;
import java.math.*;

class Solution {
	
	private static char[] reverse(char[] c){
		char[] ret = new char[c.length];
		for(int i = 0; i < c.length; i++) ret[i] = c[c.length - i - 1];
		return ret;
	}
	
	public static int solution(String s, int b){
		int i, cur = Integer.parseInt(s, b), k = s.length();
		HashMap<Integer, Integer> used = new HashMap<>();
		for(i = 0; !used.containsKey(cur); i++){
			used.put(cur, i);
			char[] c = Integer.toString(cur, b).toCharArray();
			Arrays.sort(c);
			int y = Integer.parseInt(new String(c), b);
			c = reverse(c);
			int x = Integer.parseInt(new String(c), b);
			while(x != 0 && x < Math.pow(b, k - 1)) x *= b;
			cur = x - y;
		}
		return i - used.get(cur);
	}

    public static void main(String[] args) throws IOException{
        //BufferedReader f = new BufferedReader(new FileReader(""));
        //PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("")));
        BufferedReader f = new BufferedReader(new InputStreamReader(System.in));

    	String s = f.readLine();
    	int b = Integer.parseInt(f.readLine());
    	
    	System.out.println(solution(s, b));
        
        //out.close();
    }

}