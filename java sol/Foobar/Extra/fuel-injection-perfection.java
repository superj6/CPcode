import java.io.*;
import java.util.*;
import java.lang.*;
import java.math.*;

class Solution {
	
	public static int solution(String s){
		BigInteger x = new BigInteger(s);
		int ret = 0;
		for(; x.compareTo(BigInteger.ONE) != 0; ret++){
			if(x.and(BigInteger.ONE).compareTo(BigInteger.ZERO) == 0){
				x = x.shiftRight(1);
			}else if(x.compareTo(BigInteger.valueOf(3)) == 0 || x.and(x.add(BigInteger.ONE)).compareTo(x.subtract(BigInteger.ONE).and(x.subtract(BigInteger.TWO))) > 0){
				x = x.subtract(BigInteger.ONE);
			}else{
				x = x.add(BigInteger.ONE);
			}
		}
		return ret;
	}

    public static void main(String[] args) throws IOException{
        //BufferedReader f = new BufferedReader(new FileReader(""));
        //PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("")));
        BufferedReader f = new BufferedReader(new InputStreamReader(System.in));

		System.out.println(solution(f.readLine()));     
        
        //out.close();
    }

}