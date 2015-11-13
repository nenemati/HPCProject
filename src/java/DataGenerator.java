import java.util.Random;
import java.io.*;

public class DataGenerator {
    public static void main (String [] args) {
        if (args.length != 2) {
            System.err.println ("\nUsage:");
            System.err.println ("$ java DataGenerator [# of data points] [# of dimensions]\n");
        } else {
            int count = Integer.parseInt (args[0]);
            int dim = Integer.parseInt (args[1]);

            File fd = new File ("data.txt");

            try {
                PrintWriter pw = new PrintWriter (fd);
                Random rand = new Random ();

                pw.println (count + " " + dim);

                for (int i = 0; i < count; i++) {
                    String line = "";
                    for (int j = 0; j < dim - 1; j++) {
                        int next = rand.nextInt (100);
                        line += next + " ";
                    }
                    line += rand.nextInt (100);
                    pw.println (line);
                }
                pw.close ();
            } catch (IOException e) {

            }
        }
    }
}
