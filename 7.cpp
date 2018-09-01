#include <iostream>
#include <fstream>
#include <sstream>
#include <array>
#include <vector>
#include <string>
#include <map>
using namespace std;

const int N = 1945;
const int NAME_LENGTH = 20;

struct Tree {
    public: 
        string name[N];
        int parent[N];
        int firstChild[N];
        int sibLeft[N];
        int sibRight[N];
        int weight[N];
        int treeWeight[N];
        int root;
        int size{0};

        int findOrCreate(string nameKey) {
            int idx = 0;
            while (idx < size) {
                if (name[idx] == nameKey) return idx;
                ++idx;
            }
            name[idx].assign(nameKey);
            size++;
            return idx;
        }

        Tree() {
            fill_n(parent, N, -1);
            fill_n(firstChild, N, -1);
            fill_n(sibLeft, N, -1);
            fill_n(sibRight, N, -1);
            fill_n(treeWeight, N, -1);
        }

};

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

// Input format: "dqrwhri (178) -> iztdlnf, hhjgskh"
void processLine(Tree* tree, string lineStr) {
        istringstream line(lineStr);

        string name;
        getline(line, name, ' ');
        int id = tree -> findOrCreate(name);
        if (name == "cyrupz") tree -> root = id;

        string weightStr;
        line.ignore(2, '(');
        getline(line, weightStr, ')');
        tree -> weight[id] = stoi(weightStr);
        // cout << "Inserting id " << id << " with name " << name << " weight " << weightStr << endl;
        
        if (!line.eof()) {
            line.ignore(3, '>'); 
            string child; int lastChildId = -1; int childId;
            while (line.good()) {
                line.get();
                getline(line, child, ',');
                childId = tree -> findOrCreate(child);
                tree -> parent[childId] = id;
                if (lastChildId == -1) {
                    tree -> firstChild[id] = childId;
                    // cout << "Child " << child << " has parent " << name << endl;
                } else {
                    tree -> sibRight[lastChildId] = childId;
                    tree -> sibLeft[childId] = lastChildId;
                    // cout << "Child " << child << " has sibling " << tree -> name[lastChildId] << endl;
                }
                lastChildId = childId;
            }
        }       
}

struct Tree* parseData(vector<string> data) {
    Tree* tree = new Tree;
    for (auto &lineStr : data) {
        processLine(tree, lineStr);
    }
    return tree;
}

int setTreeWeight(Tree* tree, int idx) {
    if (tree -> firstChild[idx] == -1) {
        int weight = tree -> weight[idx];
        tree -> treeWeight[idx] = weight;
        // cout << "set tree weight of " << idx << " to " << weight << endl;
        return weight;
    }
    int sumSubtreeWeight = 0;
    int nextKid = tree -> firstChild[idx];
    while (nextKid != -1) {
        if (tree -> treeWeight[nextKid] == -1) {
            setTreeWeight(tree, nextKid);
            sumSubtreeWeight += tree -> treeWeight[nextKid];
        }
        nextKid = tree -> sibRight[nextKid];
    }
    int myTreeWeight = sumSubtreeWeight + tree -> weight[idx];
    tree -> treeWeight[idx] = myTreeWeight;
    // cout << "set tree weight of " << idx << " to " << myTreeWeight << endl;
    return myTreeWeight;
}

// run this to find out which initial branch is unbalanced: 1433!
void startDetect(Tree* tree) {
    int root = tree -> root;
    root = 180;
    cout << root << ": " << tree -> treeWeight[root] << endl;
    int nextKid = tree -> firstChild[root];
    while (nextKid != -1) {
        cout << nextKid << ": " << tree -> treeWeight[nextKid] << endl;
        nextKid = tree -> sibRight[nextKid];
    }
}

int main() {
    vector<string> data = readIn();
    Tree* resultTree;
    resultTree  = parseData(data);
    setTreeWeight(resultTree, resultTree -> root);
    startDetect(resultTree);
}

/*
I just decided to do the rest of this manually because why not. I'm lazy.

Returns ideal weight of the node.
detectUnbalanced(Node, IdealTreeWeight) {
    If Leaf return IdealTreeWeight.

    Calculate ChildIdealTreeWeight of children. (IdealTreeWeight - weight / #ofChildren).
    If kids not balanced & one is not equal to IdealTreeWeight, detectUnbalanced(child, ChildIdealTreeWeight)
    If the kids are perfectly balanced, then my weight is off. 
        Return IdealTreeWeight - (sum of weight of Children).
        
}
*/