import java.lang.Math;

class Prob3 {
    public static void main (String[] args) {
        int[][] arr = new int[11][11];
        fillArr(arr);
        print2DArr(arr);
    }

    private static void oddSquares () {
        int square = 0;
        for (int i = 0; square < 400000; ++i) {
            square = (int) Math.pow(i * 2 + 1, 2);
            System.out.println(i+"   "+square);
        }
    }

    // Draws a spiraling array where each new entry = sum of entries around it
    private static void fillArr (int[][] arr) {
        int start = (int) arr.length / 2;
        int i = start; int j = start; int squareSize = 1;
        arr[i][j] = 1;

        while (squareSize < arr.length-2) {
            // Move right one and increase level.
            squareSize += 2; ++j;
            drawLevel(arr, i, j, squareSize);
            ++i;
        }
    }    

    private static void drawLevel(int[][] arr, int i, int j, int squareSize) {
        // STAGE 1 - Start R of BR corner of previous level. add TL and L.
        arr[i][j] = arr[i-1][j-1] + arr[i][j-1];

        // STAGE 2 - Move up $squareSize-2 spaces. add TL, L, BL, B.
        for (int k = 1; k <= squareSize-2; ++k) {
            --i; 
            arr[i][j] = arr[i-1][j-1] + arr[i][j-1] + arr[i+1][j-1] + arr[i+1][j];
        }

        // STAGE 3 - Move left $squareSize-1 spaces. Add R, BR, B, BL.
        for (int k = 1; k <= squareSize-1; ++k) {
            --j;
            arr[i][j] = arr[i][j+1] + arr[i+1][j+1] + arr[i+1][j] + arr[i+1][j-1];
        }

        // STAGE 4 - Move down $squareSize-1 spaces. Add T, TR, R, BR.
        for (int k = 1; k <= squareSize-1; ++k) {
            ++i;
            arr[i][j] = arr[i-1][j] + arr[i-1][j+1] + arr[i][j+1] + arr[i+1][j+1];
        }

        // STAGE 5 - Move right $squareSize-1 spaces. Add L, TL, T, TR.
        for (int k = 1; k <= squareSize-1; ++k) {
            ++j;
            arr[i][j] = arr[i][j-1] + arr[i-1][j-1] + arr[i-1][j] + arr[i-1][j+1];
        }
    }

    private static void print2DArr (int[][] arr) {
        for (int i = 0; i < arr.length; ++i) {
            for (int j = 0; j < arr.length; ++j) {
                System.out.printf("%10d", arr[i][j]);
            }
            System.out.printf("%n");
        }
    }
}

// part 1 - 
// 605 squared = 366025. 302 steps away from 1.
// 607 squared = 368449. 303 steps away from 1.
// 303 steps away vertically. 607 long edge length. 
// (2i+1)^2 in corner = 368449. 303 + 303 away.
// (2i+1)^2 - i directly below = 368146. 303 away.
// 368078 is 68 to the left of 368146. 68 + 303 = 371 away.