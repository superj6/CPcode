import java.io.*;
import java.util.*;
import java.lang.*;
import java.math.*;

class Solution {
	private static String[] b = {
		"100000", //a
		"110000", //b
		"100100", //c
		"100110", //d
		"100010", //e
		"110100", //f
		"110110", //g
		"110010", //h
		"010100", //i
		"010110", //j
		"101000", //k
		"111000", //l
		"101100", //m
		"101110", //n
		"101010", //o
		"111100", //p
		"111110", //q
		"111010", //r
		"011100", //s
		"011110", //t
		"101001", //u
		"111001", //v
		"010111", //w
		"101101", //x
		"101111", //y
		"101011", //z
		"000001", //capital
		"000000" //space
	};
	
	public static String solution(String s){
		char[] c = s.toCharArray();
		
		StringBuilder ret = new StringBuilder();
		for(char i : c){
			if('a' <= i && i <= 'z') ret.append(b[i - 'a']);
			else if('A' <= i && i <= 'Z') ret.append(b[26] + b[i - 'A']);
			else if(i == ' ') ret.append(b[27]);
		}
		
		return ret.toString();
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