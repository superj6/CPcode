import java.io.*;
import java.util.*;
import java.lang.*;


public class cowpatibility {
    public static int count = 0, cool = 0;
    public static int[] sets;
    public static String[] subs = new String[31];
    public static HashMap<String, Integer> map = new HashMap<>();
    public static HashMap<Integer, Integer> amount = new HashMap<>();

    public static void main(String[] args) throws IOException{
        BufferedReader f = new BufferedReader(new FileReader("cowpatibility.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("cowpatibility.out")));
        //BufferedReader f = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st;
        
        int n = Integer.parseInt(f.readLine());
        int[][] cream = new int[n][5];
        sets = new int[31*n];
        int[] incexc = {1, -1, 1, -1, 1};
        long sol = n * (n - 1) / 2;
        
        for(int i = 0; i < n; i++){
            st = new StringTokenizer(f.readLine());
            for(int j = 0; j < 5; j++){
                cream[i][j] = Integer.parseInt(st.nextToken());
            }
            
            Arrays.sort(cream[i]);
        }

        int[] sethelp = {4, 3, 2, 1, 0};
        findsets(sethelp, "", 5);
        
        //System.out.println(Arrays.toString(subs));
        
        for(int i = 0; i < n; i++){
            setcount(cream[i]);
        }
        
        long over = 0;
        
        for(int i = 0; i < count; i++){
            over += incexc[amount.get(i)] * sets[i] * (sets[i] - 1) / 2;
        }
        
        sol -= over;
        
        out.println(sol);
        
        out.close();
    }
    
    public static void setcount(int[] array){
        for(int i = 0; i < subs.length; i++){
            StringTokenizer wow = new StringTokenizer(subs[i]);
            String out = "";
            int counter = 0;
            
            while(wow.hasMoreTokens()){
                out += Integer.toString(array[Integer.parseInt(wow.nextToken())]) + " ";
                counter++;
            }
            
            if(!map.containsKey(out)){
                map.put(out, count);
                amount.put(map.get(out), counter - 1);
                count++;
            }
            
            sets[map.get(out)]++;
        }
    }
    
    public static void findsets(int[] array, String output, int last){ 
        //System.out.println(output);
        if(output.length() > 0){
            subs[cool] = output;
            cool++;
        }
        
        if(array.length == 0 || last == 0) return;
        
        for(int i = 0; i < last; i++){
            int[] newar = new int[array.length - 1];
            String newout = output + Integer.toString(array[i]) + " ";
            for(int j = 0; j < array.length; j++){
                if(j > i){
                    newar[j - 1] = array[j];
                }else if(j < i){
                    newar[j] = array[j];
                }
            }
            
            findsets(newar, newout, i);
        }
    }

}
