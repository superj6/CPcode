import java.lang.*;
import java.util.*;
import java.io.*;
import java.math.BigInteger;

public class googol{
	static BufferedReader f = new BufferedReader(new InputStreamReader(System.in));
	static StringTokenizer st;
	static BigInteger two = new BigInteger("2");
	static BigInteger one = new BigInteger("1");
	static BigInteger zero = new BigInteger("0");
	
	static BigInteger countOf(BigInteger cur, BigInteger x) throws IOException{
		if(cur.equals(zero)) return zero;
		
		System.out.println(cur.toString());
		st = new StringTokenizer(f.readLine());
		
		BigInteger a = new BigInteger(st.nextToken());
		BigInteger b = new BigInteger(st.nextToken());
		
		if(x.mod(two).equals(zero)){
			BigInteger lft = x.divide(two);
			BigInteger rgt = countOf(b, lft.subtract(one));
			return one.add(lft.add(rgt));
		}else{
			BigInteger rgt = (x.subtract(one)).divide(two);
			BigInteger lft = countOf(a, rgt);
			return one.add(lft.add(rgt));
		}
	}
	
	static BigInteger count(BigInteger cur) throws IOException{
		System.out.println(cur.toString());
		st = new StringTokenizer(f.readLine());
		
		BigInteger a = new BigInteger(st.nextToken());
		BigInteger b = new BigInteger(st.nextToken());
		
		BigInteger rgt = count(b);
		BigInteger lft = countOf(a, rgt);
		
		return one.add(rgt.add(lft));
	}
	
	public static void main(String [] args) throws IOException{
		System.out.println("Answer " + count(one).toString());
	}
}