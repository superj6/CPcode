import java.io.*;
import java.util.*;
import java.lang.*;


public class practs2 {

    public static void main(String[] args) throws IOException{
        BufferedReader f = new BufferedReader(new FileReader("measurement.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("measurement.out")));
        //BufferedReader f = new BufferedReader(new InputStreamReader(System.in));
        StringTokenizer st = new StringTokenizer(f.readLine());
        int n = Integer.parseInt(st.nextToken()), g = Integer.parseInt(st.nextToken());
        Integer[] time = new Integer[n], id = new Integer[n], change = new Integer[n], index = new Integer[n];
        
        int w = 0;
        HashMap<Integer, Integer> map = new HashMap<>();
        
        int changes = 0;
        
        for(int i = 0; i < n; i++){
            index[i] = i;
            st = new StringTokenizer(f.readLine());
            time[i] = Integer.parseInt(st.nextToken());
            id[i] = Integer.parseInt(st.nextToken());
            change[i] = Integer.parseInt(st.nextToken());
            
            if(!map.containsKey(id[i])){
                map.put(id[i], w);
                w++;
            }
        }
        
        Integer[] current = new Integer[w + 1];
        boolean[] plargest = new boolean[w + 1];
        Arrays.fill(plargest, true);
        Arrays.fill(current, g);
        
        Integer[] previous = current.clone();
        boolean[] clargest = new boolean[w + 1];
        
        Arrays.sort(index, new Comparator<Integer>(){
            public int compare(Integer i1, Integer i2){
                return Double.compare(time[i1], time[i2]);
            }
        });
        
        for(int i = 0; i < n; i++){
            current[map.get(id[index[i]])] += change[index[i]];
            
            if(i < n - 1) if(time[index[i + 1]] != time[index[i]]){
                int max = 0;
                
                for(int j = 0; j < current.length; j++){
                    if(current[j] > max) max = current[j];
                }
                
                for(int j = 0; j < clargest.length; j++){
                    if(current[j] == max) clargest[j] = true;
                }
                
                //System.out.println(Arrays.toString(clargest));
                if(!Arrays.equals(clargest, plargest)) changes++;
                
                plargest = clargest.clone();
                previous = current.clone();
                clargest = new boolean[w + 1];
            }
            
            if(i == n - 1){
                int max = 0;
                
                for(int j = 0; j < current.length; j++){
                    if(current[j] > max) max = current[j];
                }
                
                for(int j = 0; j < clargest.length; j++){
                    if(current[j] == max) clargest[j] = true;
                }
                
                //System.out.println(Arrays.toString(clargest));
                if(!Arrays.equals(clargest, plargest)) changes++;
                
                plargest = clargest.clone();
                previous = current.clone();
                clargest = new boolean[w + 1];
            }
        }
        
        out.println(changes);
        
        out.close();
    }
}