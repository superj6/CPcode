import java.io.*;
import java.util.*;
import java.lang.*;


public class sort {
    public static int count = 0;

    public static void main(String[] args) throws IOException{
        BufferedReader f = new BufferedReader(new FileReader("sort.in"));
        PrintWriter out = new PrintWriter(new BufferedWriter(new FileWriter("sort.out")));
        //BufferedReader f = new BufferedReader(new InputStreamReader(System.in));

        int[] array = new int[Integer.parseInt(f.readLine())];
        
        for(int i = 0; i < array.length; i++){
          array[i] = Integer.parseInt(f.readLine());
        }

        bubsort(array);

        out.println(count);
        
        out.close();
    }

    public static void bubsort(int[] array){
      int[] test = array.clone();
      Arrays.sort(test);

      for(int i = 0; i < array.length; i++){
        if(test[i] != array[i]
      }
    }
}