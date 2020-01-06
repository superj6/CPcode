import java.io.*;
import java.util.*;
import java.lang.*;
 
 
class cbarn {
 
    public static void main(String[] args) throws IOException{
        BufferedReader f = new BufferedReader(new FileReader("cbarn.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("cbarn.out")));
        //BufferedReader f = new BufferedReader(new InputStreamReader(System.in));
	int n = Integer.parseInt(f.readLine());
        int[] array = new int[n];
 
        for(int i = 0; i < n; i++){
        	array[i] = Integer.parseInt(f.readLine());
        }
 
        int from = n-1, to = n-1;
 
        for(int i = n - 1; i >= 0; i--){
        	if(array[i] == 0){
        		to = i;
        		from = (i - 1 + n) % n;
        		break;
        	}
        }
 
        int result = 0;
        int count = 0;
 
 
        while(count < n){
        	if(array[to] == 0){
        		count = 0;
        		if(array[from] > 0){
        			array[from] -= 1;
        			array[to] = 1;
        			to = (to - 1 + n) % n;
 
        			result += Math.pow((to - from + n + 1) % n, 2);
        		}else{
        			from = (from - 1 + n) % n;
        		}
        	}else{
        		to = (to - 1 + n) % n;
        		count += 1;
        	}
 
        	//System.out.println(Arrays.toString(array));
        	//System.out.println(result);
        }
 
        out.println(result);
 
        out.close();
    }
 
}