import java.io.*;
import java.util.*;
import java.lang.*;


public class pract2 {

    public static void main(String[] args) throws IOException{
        BufferedReader f = new BufferedReader(new FileReader("shuffle.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("shuffle.out")));
        //BufferedReader t = new BufferedReader(new InputStreamReader(System.in));
        
        int n = Integer.parseInt(f.readLine());
        int[] shuffle = new int[n];
        int[] order = new int[n];
        
        StringTokenizer st = new StringTokenizer(f.readLine());
        
        for(int i = 0; i < shuffle.length; i++){
            shuffle[i] = Integer.parseInt(st.nextToken()) - 1;
        }
        
        st = new StringTokenizer(f.readLine());
        
        for(int i = 0; i < order.length; i++){
            order[i] = Integer.parseInt(st.nextToken());
        }
        
        int[] reverse = new int[n];
        
        for(int i = 0; i < shuffle.length; i++){
            reverse[shuffle[i]] = i;
        }
        
        int[] output = new int[n];
        
        for(int i = 0; i < order.length; i++){
            output[reverse[reverse[reverse[i]]]] = order[i];
        }
        
        for(int i = 0; i < output.length; i++){
            out.println(output[i]);
        }
        
        out.close();
    }
}
