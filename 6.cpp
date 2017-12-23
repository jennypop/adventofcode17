#include <iostream>
#include <fstream>
#include <array>
#include <vector>
using namespace std;

array<int,16> readIn() {
    array<int,16> arr;
    ifstream inFile;

    inFile.open("6input");
    if (!inFile) {
        cout << "Unable to open file";
        exit(1);
    }

    for(int i = 0; i < 16; ++i) {
        inFile >> arr[i];
    }
    inFile.close();
    
    return arr;
}

int routine(array<int,16> arr) {
    vector<array<int,16>> history;
    history.push_back(arr);
    int turns = 0;
    int maxIdx = arr[0];
    int maxVal;

    while (1) {
        for (int i = 0; i < 16; ++i) {
            if (arr[i] > arr[maxIdx]) maxIdx = i;
            // cout << arr[i] << " ";
        }
        // cout << endl;
        maxVal = arr[maxIdx];
        arr[maxIdx] = 0;
        for (int j = 0; j < maxVal; ++j) {
            arr[(maxIdx+j+1) % 16]++;
        }
        turns++;
        
        for (auto it = history.begin(); it != history.end(); ++it) {
            if (*it == arr) return turns-(it - history.begin());
        }
        history.push_back(arr);
    }
    
}

int main() {
    array<int,16> arr;
    arr = readIn();
    int turns = routine(arr);
    cout << "turns: " << turns;
    return 0;
}

