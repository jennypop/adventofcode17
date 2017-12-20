import java.io.BufferedReader;
import java.io.FileReader;
import java.util.List;
import java.util.ArrayList;
import java.util.Arrays;

class Prob4 {
    public static void main (String[] args) {
        int count = 0;
        List<String> input = readInput();
        for (String str: input) {
            if (verifyPassphrase1(deAnagram(str)))
                count++;
        }
        
        System.out.println(count);
    }

    private static List<String> readInput() {
        List<String> res = new ArrayList<String>();
        try {
            FileReader fr = new FileReader("4input");
            BufferedReader br = new BufferedReader(fr);
            String line;

            while ((line = br.readLine()) != null) {
                res.add(line);
            }

            br.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
        
        return res;
    }

    private static boolean verifyPassphrase1(String[] words) {
        for (int i = 0; i < words.length-1; ++i) {
            for (int j = i+1; j < words.length; ++j) {
                if (words[i].equals(words[j])) return false;
            }
        }

        return true;
    }

    private static String[] deAnagram(String passphrase) {
        String[] words = passphrase.split(" ");
        for (int i = 0; i < words.length; ++i) {
            char[] chars = words[i].toCharArray();
            Arrays.sort(chars);
            words[i] = new String(chars);
        }
        return words;
    }
}