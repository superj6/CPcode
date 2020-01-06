import java.io.*;
import java.util.*;
import java.lang.*;


class nocross {
	static int[] s, t;

    public static void main(String[] args) throws IOException{
        BufferedReader f = new BufferedReader(new FileReader("nocross.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("nocross.out")));
        //BufferedReader f = new BufferedReader(new InputStreamReader(System.in));
		
		int n = Integer.parseInt(f.readLine());
		s = new int[n]; t = new int[n];
		int[][] a = new int[n][n];
		
		for(int i = 0; i < n; i++) s[i] = Integer.parseInt(f.readLine());
		for(int i = 0; i < n; i++) t[i] = Integer.parseInt(f.readLine());
		
		a[0][0] = add(0, 0);
    	
    	for(int i = 1; i < n; i++) a[i][0] = Math.max(a[i-1][0], add(i, 0));
    	for(int i = 1; i < n; i++) a[0][i] = Math.max(a[0][i-1], add(0, i));
    	
    	for(int i = 1; i < n; i++){
    		for(int j = 1; j < n; j++){
    			a[i][j] = Math.max(Math.max(a[i-1][j], a[i][j-1]), a[i-1][j-1] + add(i, j));
    		}
    	}
    	
    	out.println(a[n-1][n-1]);
        
        out.close();
    }
    
    public static int add(int a, int b){
    	if(Math.abs(s[a] - t[b]) <= 4) return 1;
    	return 0;
    }

}