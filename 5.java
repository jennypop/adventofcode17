import java.io.FileReader;
import java.io.BufferedReader;
import java.util.List;
import java.util.ArrayList;

class Prob5 {
    public static void main (String[] args) {
        int[] arr = readInput();
        System.out.println(countMoves(arr));
    }

    private static int[] readInput() {
        try {
            FileReader fr = new FileReader("5input");
            BufferedReader br = new BufferedReader(fr);
            String line;
            List<Integer> list = new ArrayList<Integer>();

            while ((line = br.readLine()) != null) {
                list.add(Integer.parseInt(line));
            }

            br.close();
            return list.stream().mapToInt(i->i).toArray();
        } catch (Exception e) {
            e.printStackTrace();
        }
        return null;
    }

    private static int countMoves(int[] map) {
        int moves = 0;
        int place = 0;
        int oldplace = 0;

        while (place >= 0 && place < map.length) {
            oldplace = place;
            place += map[place];
            moves++;
            if (map[oldplace] >= 3) 
                map[oldplace]--;
            else 
                map[oldplace]++;
        }

        return moves;
    }
}