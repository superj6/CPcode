import java.io.*;
import java.util.*;
import java.lang.*;
import java.math.*;

class Solution{
    public static void main(String[] args) throws IOException{
        //BufferedReader f = new BufferedReader(new FileReader(""));
        //PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("")));
		BufferedReader f = new BufferedReader(new InputStreamReader(System.in));

		int n = Integer.parseInt(f.readLine());
		double x = n / 4, y = (n + 2) / 4;
		
		double ret = 100 * x * y + 2 * 18 * 10 * (x + y) + 3.14159 * 18 * 18;
		
		System.out.println(String.format("%.3f", ret));
        
        //out.close();
    }

}