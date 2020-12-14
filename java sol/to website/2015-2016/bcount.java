import java.io.*;
import java.util.*;
import java.lang.*;


class bcount {

    public static void main(String[] args) throws IOException{
        BufferedReader f = new BufferedReader(new FileReader("bcount.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("bcount.out")));
        //BufferedReader f = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(f.readLine());
		
		int n = Integer.parseInt(st.nextToken()), q = Integer.parseInt(st.nextToken());
		int[][] sum = new int[3][n];
		
		for(int i = 0; i < n; i++){
			int x = Integer.parseInt(f.readLine()) - 1;
			
			if(i > 0){
				for(int j = 0; j < 3; j++) sum[j][i] = sum[j][i-1]; 
			}
			
			sum[x][i]++;
		}
		
		for(int r = 0; r < q; r++){
			st = new StringTokenizer(f.readLine());
			int a = Integer.parseInt(st.nextToken()) - 1, b = Integer.parseInt(st.nextToken()) - 1;
			
			for(int i = 0; i < 3; i++){
				int result = sum[i][b];
				if(a > 0) result-= sum[i][a - 1];
				
				out.print(result);
				
				if(i != 2) out.print(" ");
			}
			
			out.println();
		}
		
     
        
        out.close();
    }

}