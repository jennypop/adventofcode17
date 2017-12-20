import java.io.IOException;
import java.io.BufferedReader;
import java.io.FileReader;
import java.lang.Math;

class ProbTwo {
    public static void main (String[] args) {
        try {
            FileReader fr = new FileReader("2input");
            BufferedReader br = new BufferedReader(fr);
            String line;
            int sum = 0;

            while ((line = br.readLine()) != null) {
                String[] stringNums = line.split("\\s");
                int[] nums = new int[stringNums.length];
                for (int i = 0; i < stringNums.length; ++i) {
                    nums[i] = Integer.parseInt((stringNums[i]));
                }
                sum += evenDivisor(nums);
            }

            br.close();
            System.out.println(sum);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private static int evenDivisor (int[] input) {
        for (int i = 0; i < input.length-1; ++i) {
            for (int j = i+1; j < input.length; ++j) {
                if (input[i] % input[j] == 0) 
                    return input[i] / input[j];
                if (input[j] % input[i] == 0) 
                    return input[j] / input[i];
            }
        }
        return 0;
    }

    private static int checkSum (int[] input) {
        int min = input[0]; int max = input[0];
        for (int i = 0; i < input.length; ++i) {
            min = Math.min(input[i], min);
            max = Math.max(input[i], max);
        }
        return max - min;
    }
}