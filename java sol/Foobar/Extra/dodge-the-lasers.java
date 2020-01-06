import java.io.*;
import java.util.*;
import java.lang.*;
import java.math.*;

class Solution {
	static BigDecimal sq2 = BigDecimal.valueOf(2).sqrt(new MathContext(50));
 
	static BigInteger A(BigInteger n){
		BigInteger a = (new BigDecimal(n)).multiply(sq2).toBigInteger();
		BigInteger ret = a.multiply(a.add(BigInteger.ONE)).divide(BigInteger.valueOf(2));
		if(n.compareTo(BigInteger.valueOf(2)) > 0) ret = ret.subtract(B((new BigDecimal(n)).multiply(sq2.subtract(BigDecimal.ONE)).toBigInteger()));
		return ret;
	}

	static BigInteger B(BigInteger n){
		return n.multiply(n.add(BigInteger.ONE)).add(A(n));
	}

	public static String solution(String s){
		return A(new BigInteger(s)).toString();
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