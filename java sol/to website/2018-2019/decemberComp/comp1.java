import java.io.*;
import java.util.*;
import java.lang.*;


public class comp1 {

    public static void main(String[] args) throws IOException{
        BufferedReader f = new BufferedReader(new FileReader("mixmilk.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("mixmilk.out")));
        //BufferedReader f = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;
        int[] capacity = new int[3], amount = new int[3];
        for(int i = 0; i < 3; i++){
            st = new StringTokenizer(f.readLine());
            
            capacity[i] = Integer.parseInt(st.nextToken());
            amount[i] = Integer.parseInt(st.nextToken());
        }
        
        
        for(int i = 0; i < 100; i++){
            int c = i % 3;
            int change = Math.min(amount[c], capacity[(c + 1) % 3] - amount[(c + 1) % 3]);
            
            amount[c] -= change;
            amount[(c + 1) % 3] += change;
        }
        
        for(int i = 0; i < 3; i++){
            out.println(amount[i]);
        }
        
        out.close();
    }
}
