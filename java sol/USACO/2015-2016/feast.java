import java.io.*;
import java.util.*;
import java.lang.*;


class feast {

    public static void main(String[] args) throws IOException{
        BufferedReader f = new BufferedReader(new FileReader("feast.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("feast.out")));
        //BufferedReader f = new BufferedReader(new InputStreamReader(System.in));
		StringTokenizer st = new StringTokenizer(f.readLine());
		int t = Integer.parseInt(st.nextToken()), a = Integer.parseInt(st.nextToken()), b = Integer.parseInt(st.nextToken());
		boolean[] check = new boolean[t + 1];
		check[0] = true;
        check[(int)Math.floor((float)a/2)] = true;
        check[(int)Math.floor((float)b/2)] = true;
        if(a + b <= t) check[(int)Math.floor((float)(a + b)/2)] = true;
        int max = 0;
        
        for(int i = 0; i < check.length; i++){
        	if(i - a >= 0){
        		check[i] = check[i] || check[i - a];
        	}
        	if(i - b >= 0){
        		check[i] = check[i] || check[i - b];
        	}
        	if(check[i] == true) max = i;
        }
        
        out.println(max);
        //System.out.println(Arrays.toString(check));
        
        out.close();
    }

}