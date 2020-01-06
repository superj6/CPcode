import java.io.*;
import java.util.*;
import java.lang.*;


class highcard{

    public static void main(String[] args) throws IOException{
        BufferedReader f = new BufferedReader(new FileReader("highcard.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("highcard.out")));
        //BufferedReader f = new BufferedReader(new InputStreamReader(System.in));

		int n = Integer.parseInt(f.readLine());
		int[] elsie = new int[n], bessie = new int[n];
		boolean[] all = new boolean[2 * n];
		
		for(int i = 0; i < n; i++){
			elsie[i] = Integer.parseInt(f.readLine()) - 1;	
			all[elsie[i]] = true;
		} 
		
		Arrays.sort(elsie);
		
		int index = 0;
		
		for(int i = 0; i < all.length; i++){
			if(!all[i]){
				bessie[index] = i;
				index++;
			}
			
			
		}
		
		//System.out.println(Arrays.toString(bessie));
		//System.out.println(Arrays.toString(elsie));
		
		int result = 0;
		
        index = 0;
		
		for(int i = 0; i < n; i++){
			while(index < n - 1 && bessie[index] < elsie[i]) index++;
			
			if(bessie[index] > elsie[i]){ 
				result++;
				index++;
			}
			
			if(index == n) break;
		}
    	
    	out.println(result);
        
        out.close();
    }

}