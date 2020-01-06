import java.io.*;
import java.util.*;
import java.lang.*;
import java.math.*;


class Solution {
	
	public static String solution(String x, String y){
		BigInteger a = new BigInteger(x), b = new BigInteger(y);
		
		BigInteger ret = BigInteger.ZERO;
		while(true){
			if(a.compareTo(b) > 0){
				a = a.add(b);
				b = a.subtract(b);
				a = a.subtract(b);
			}
			
			if(a.compareTo(BigInteger.ZERO) == 0){
				return "impossible";
			}else if(a.compareTo(BigInteger.ONE) == 0){
				return ret.add(b).subtract(BigInteger.ONE).toString();
			}else{
				ret = ret.add(b.divide(a));
				b = b.subtract(b.divide(a).multiply(a));
			}
		}
	}

    public static void main(String[] args) throws IOException{
        //BufferedReader f = new BufferedReader(new FileReader(""));
        //PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("")));
        BufferedReader f = new BufferedReader(new InputStreamReader(System.in));
		
    	String x = f.readLine(), y = f.readLine();
    	
    	System.out.println(solution(x, y));
        
        //out.close();
    }

}
