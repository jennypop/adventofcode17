#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include <vector>
#include <string>
#include <map>
using namespace std;

// readIn: array of strings.
// only include lines that have a ->
// 

vector<string> readIn() {
    ifstream file;
    string temp;
    vector<string> data;
    file.open("7input");
    while (getline(file, temp)) {
        data.push_back(temp);
    }
    file.close();
    return data;
}

// Builds a map of higherString -> lowerString
map<string, string> parseData(vector<string> data) {
    map<string, string> map;
    for (auto &lineStr : data) {
        if (lineStr.find("->") != string::npos) {
            istringstream line(lineStr);
            string val;
            getline(line, val, ' ');
            line.ignore(200, '>');
            while (line.good()) {
                line.get();
                string key;
                getline(line, key, ',');
                // cout << "putting in " << key << " " << val << endl;
                map.insert(pair<string, string>(key, val));
            }
        }
    }
    return map;
}

string followMap(map<string,string> words) {
    map<string,string>::iterator it;
    string curr = words.begin()->second;
    while ((it = words.find(curr)) != words.end()) {
        curr = it->second;
    }
    return curr;
}

int main() {
    vector<string> data;
    map<string,string> words;
    data = readIn();
    words = parseData(data);
    cout << followMap(words);
}