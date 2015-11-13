import java.util.Random;
import java.io.*;

public class DataGenerator {
    public static void main (String [] args) {
        if (args.length != 3) {
            System.err.println ("\nUsage:");
            System.err.println ("$ java DataGenerator [# of data points] [# of dimensions] [max value]\n");
        } else {
            int count = Integer.parseInt (args[0]);
            int dim = Integer.parseInt (args[1]);
            int maxval = Integer.parseInt (args[2]);

            File fd = new File ("data.txt");

            try {
                PrintWriter pw = new PrintWriter (fd);
                Random rand = new Random ();

                pw.println (count + " " + dim);

                for (int i = 0; i < count; i++) {
                    String line = "";
                    for (int j = 0; j < dim - 1; j++) {
                        int next = rand.nextInt (maxval);
                        line += next + " ";
                    }
                    line += rand.nextInt (maxval);
                    pw.println (line);
                }
                pw.close ();
            } catch (IOException e) {

            }
        }
    }
}
