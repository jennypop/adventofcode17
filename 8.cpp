#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <map>
using namespace std;

vector<string> readIn() {
    ifstream file;
    string temp;
    vector<string> data;
    file.open("8input.txt");
    while (getline(file, temp)) {
        data.push_back(temp);
    }
    file.close();
    return data;
}

vector<vector<string>> splitInstructions(vector<string> data) {
    vector<vector<string>> instructions;
    
    for (auto t: data) {
        istringstream iss (t);
        vector<string> splitLine(std::istream_iterator<string>{iss},
                                 std::istream_iterator<string>());
        instructions.push_back(splitLine);
    }

    return instructions;
}

vector<string> processRegNames(vector<vector<string>> instructions) {
    vector<string> regNames;
    for (auto t: instructions) {
        string name = t.at(0);
        if ( !std::any_of(regNames.begin(), regNames.end(), [=](string s){return s == name;}) ) {
            regNames.push_back(name);
        }
        name = t.at(4);
        if ( !std::any_of(regNames.begin(), regNames.end(), [=](string s){return s == name;}) ) {
            regNames.push_back(name);
        }
    }
    return regNames;
}

int findIndex(vector<string> regNames, string name) {
    auto i = find(regNames.begin(), regNames.end(), name);
    return distance(regNames.begin(), i);
}

enum Operator {
    lessThan,
    lessThanOrEq,
    greaterThan,
    greaterThanOrEq,
    eq,
    notEq
};

map<string, Operator> operatorMap;
void initOperatorMap() {
    operatorMap["<"] = lessThan;
    operatorMap["<="] = lessThanOrEq;
    operatorMap[">"] = greaterThan;
    operatorMap[">="] = greaterThanOrEq;
    operatorMap["=="] = eq;
    operatorMap["!="] = notEq;
}

bool processCondition(int* regValues, int reg, string op, int testValue) {
    initOperatorMap();
    switch(operatorMap[op]) {
        case lessThan: 
            return regValues[reg] < testValue; break;
        case lessThanOrEq:
            return regValues[reg] <= testValue; break;
        case greaterThan:
            return regValues[reg] > testValue; break;
        case greaterThanOrEq:
            return regValues[reg] >= testValue; break;
        case eq:
            return regValues[reg] == testValue; break;
        case notEq:
            return regValues[reg] != testValue; break;
    }
}

void processInstructions(vector<vector<string>> instructions, 
    vector<string> regNames, 
    int* regValues
) {
    int maxValue = 0;
    for (auto instruction: instructions) {
        int reg = findIndex(regNames, instruction.at(0)); 
        int testReg = findIndex(regNames, instruction.at(4));
        bool test = processCondition(regValues, testReg, instruction.at(5), stoi(instruction.at(6)));
        if (test) {
            int amount = stoi(instruction.at(2));
            if (instruction.at(1) == "inc") {
                regValues[reg] += amount;
                maxValue = max(maxValue, regValues[reg]);
            }
            else 
                regValues[reg] -= amount;
                                maxValue = max(maxValue, regValues[reg]);

        }
    }
    cout << maxValue;
}

int main(void) {
    vector<string> data = readIn();
    vector<vector<string>> instructions = splitInstructions(data);
    vector<string> regNames = processRegNames(instructions);
    int regValues[regNames.size()] = { };
    processInstructions(instructions, regNames, regValues);
    // for (int i = 0; i < regNames.size(); ++i) {
    //     cout << regValues[i] << endl;
    // }
}