import java.io.IOException;
import java.io.BufferedReader;
import java.io.FileReader;

class RepeatedDigitSum {
    public static void main(String[] args) {
        try {
            FileReader fr = new FileReader("1input");
            BufferedReader buf = new BufferedReader(fr);

            String line = buf.readLine();
            int sum = 0;
            for (int i = 0; i < line.length()-1; ++i) {
                if (line.charAt(i) == line.charAt(i+1)) 
                    sum += (line.charAt(i) - '0');
            }
            if (line.charAt(0) == line.charAt(line.length()-1)) 
                sum += (line.charAt(line.length()-1) - '0');
            System.out.println(sum);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}

class HalfwayAroundSum {
    public static void main(String[] args) {
        try {
            FileReader fr = new FileReader("1input");
            BufferedReader buf = new BufferedReader(fr);

            String line = buf.readLine();
            int sum = 0;
            int len = line.length();
            int halflen = len / 2;
            
            line = line + line;
            for (int i = 0; i < len; ++i) {
                if (line.charAt(i) == line.charAt(i+halflen)) 
                    sum += (line.charAt(i) - '0');
            }
            System.out.println(sum);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}