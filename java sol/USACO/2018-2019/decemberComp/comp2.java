import java.io.*;
import java.util.*;
import java.lang.*;


public class comp2 {

    public static void main(String[] args) throws IOException{
        BufferedReader f = new BufferedReader(new FileReader("blist.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("blist.out")));
        //BufferedReader f = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;
        int n = Integer.parseInt(f.readLine()), max = 0, output = 0;
        int[] start = new int[n], end = new int[n], buckets = new int[n];
        
        for(int i = 0; i < n; i++){
            st = new StringTokenizer(f.readLine());
            start[i] = Integer.parseInt(st.nextToken());
            end[i] = Integer.parseInt(st.nextToken());
            buckets[i] = Integer.parseInt(st.nextToken());
            
            if(end[i] > max) max = end[i];
        }
        
        for(int i = 0; i <= max; i++){
            int sum = 0;
            
            for(int j = 0; j < n; j++){
                if(i >= start[j] && i <= end[j]) sum += buckets[j];
            }
            
            if(sum > output) output = sum;
        }
        
        out.println(output);
        
        out.close();
    }
}