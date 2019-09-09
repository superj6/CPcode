import java.io.*;
import java.util.*;
import java.lang.*;


public class planting {

    public static void main(String[] args) throws IOException{
        BufferedReader f = new BufferedReader(new FileReader("planting.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("planting.out")));
        //BufferedReader f = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;
        
        int n = Integer.parseInt(f.readLine());
        int[] amount = new int[n];
        
        for(int i = 0; i < n - 1 ; i++){
            st = new StringTokenizer(f.readLine());
            amount[(Integer.parseInt(st.nextToken()) - 1)]++;
            amount[(Integer.parseInt(st.nextToken()) - 1)]++;
        }
        
        int max = 0;
        
        for(int i = 0; i < n; i++) if(amount[i] > max) max = amount[i];
        
        out.println((max + 1));
        
        out.close();
    }

}
