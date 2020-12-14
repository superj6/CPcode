import java.io.*;
import java.util.*;
import java.lang.*;


public class comp3 {
    public static int[] initial;
    public static boolean[] sol = new boolean[2001];

    public static void main(String[] args) throws IOException{
        BufferedReader f = new BufferedReader(new FileReader("backforth.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("backforth.out")));
        //BufferedReader f = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(f.readLine());
        int output = 0;
        int[] first = new int[10], second = new int[10];
        
        for(int i = 0; i < 10; i++){
            first[i] = Integer.parseInt(st.nextToken());
        }
        
        initial = first.clone();
        st = new StringTokenizer(f.readLine());
        
        for(int i = 0; i < 10; i++){
            second[i] = Integer.parseInt(st.nextToken());
        }
        
        for(int i = 0; i <= 2; i++){
            exchanges(first, second, i);
        }
            
        for(int i = 0; i < sol.length; i++){
            if(sol[i]) output++;
        }
        
        out.println(output);
        
        out.close();
    }
    
    public static void exchanges(int[] a1, int[] a2, int n){
        if(n == 0){
            sol[1000 + sum(a1) - sum(initial)] = true;
            return;
        }
        
        for(int i = 0; i < 10; i++){
            for(int j = 0; j < 10; j++){
                int[] na1 = a1.clone(), na2 = a2.clone();
                na1[i] = a2[j];
                na2[j] = a1[i];
                
                exchanges(na1, na2, n - 1);
            }
        }
    }
    
    public static int sum(int[] array){
        int out = 0;
        
        for(int i = 0; i < array.length; i++){
            out += array[i];
        }
        
        return out;
    }
}