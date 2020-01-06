import java.io.*;
import java.util.*;
import java.lang.*;


class div7 {

    public static void main(String[] args) throws IOException{
        BufferedReader f = new BufferedReader(new FileReader("div7.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("div7.out")));
        //BufferedReader f = new BufferedReader(new InputStreamReader(System.in));

    	int n = Integer.parseInt(f.readLine());
    	int[] array = new int[n + 1];
    	
    	for(int i = 0; i < n; i++){
    		array[i + 1] = Integer.parseInt(f.readLine()) % 7;
    		if(i != 0) array[i + 1] = (array[i + 1] + array[i]) % 7;
    	}
    	
    	//System.out.println(Arrays.toString(array));
    	
    	int[][] index = new int[7][2];
    	for(int i = 0; i < index.length; i++) Arrays.fill(index[i], -1);
    	
    	for(int i = 0; i < array.length; i++){
    		if(index[array[i]][0] == -1) index[array[i]][0] = i;
    		else index[array[i]][1] = i;
    	}
    	
    	int result = 0;
    	
    	for(int i = 0; i < index.length; i++) result = Math.max(result, index[i][1] - index[i][0]);
    	
    	out.println(result);
    	
        
        out.close();
    }

}