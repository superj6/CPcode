import java.io.*;
import java.util.*;
import java.lang.*;


class Solution {
	
	public static int solution(String s){
		char[] c = s.toCharArray();
		int ret = 0;
		for(int i = 0, cur = 0; i < c.length; i++){
			if(c[i] == '>') cur++;
			if(c[i] == '<') ret += cur;
		}
		
		for(int i = c.length - 1, cur = 0; i >= 0; i--){
			if(c[i] == '<') cur++;
			if(c[i] == '>') ret += cur;
		}
		
		return ret;
	}

    public static void main(String[] args) throws IOException{
        //BufferedReader f = new BufferedReader(new FileReader(""));
        //PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("")));
        BufferedReader f = new BufferedReader(new InputStreamReader(System.in));

    	String s = f.readLine();
    	
    	System.out.println(solution(s));
        
        //out.close();
    }

}