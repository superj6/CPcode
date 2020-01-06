/* package whatever; // don't place package name! */

import java.util.*;
import java.lang.*;
import java.io.*;

/* Name of the class has to be "Main" only if the class is public. */
class shell{
	public static void main (String[] args) throws java.lang.Exception
	{
		BufferedReader f = new BufferedReader(new FileReader("shell.in"));
		PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("shell.out")));
		
		int n = Integer.parseInt(f.readLine());
		
		int[] amount = new int[3], current = new int[3];
		for(int i = 0; i < 3; i++){
			amount[i] = 0;
			current[i] = i;
		}
		
		for(int i = 0; i < n; i++){
			StringTokenizer st = new StringTokenizer(f.readLine());
			int a = Integer.parseInt(st.nextToken()) - 1, b = Integer.parseInt(st.nextToken()) - 1, c = Integer.parseInt(st.nextToken()) - 1;
			
			int temp = current[b];
			current[b] = current[a];
			current[a] = temp;
			
			amount[current[c]]++;
		}
		
		out.println(Math.max(amount[0], Math.max(amount[1], amount[2])));

		out.close();
	}
}