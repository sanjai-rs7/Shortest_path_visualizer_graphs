#include <iostream>
#include <vector>
#include <sstream>
#include "makeGraph.h"
using namespace std;

vector<string> MakeGraph::splitString(const string& inputStr, char delimiter) {
    vector<string> result;
    stringstream ss(inputStr);
    string item;

    while(getline(ss, item, delimiter)) {
        result.push_back(item);
    }
    return result;
}

vector<string> MakeGraph::extractWords(const string& input) {
    vector<string> words;
    stringstream ss(input);
    //delimeter - ','
    string word;
    while (getline(ss, word, ',')) {
        // Remove leading/trailing whitespaces from the word
        size_t start = word.find_first_not_of(" ");
        size_t end = word.find_last_not_of(" ");
        if (start != string::npos && end != string::npos)
            words.push_back(word.substr(start, end - start + 1));
    }
    return words;
}

void MakeGraph::addLocations(){
    ifstream inputFile("DataSetList.txt", ios::in);
    if (!inputFile.is_open()){
        cout << "Error opening the file! DataSetList.txt" << endl;
        return; 
    }
    string line;
    while(getline(inputFile, line)){
        int id;
        string place;

        vector<string> words = splitString(line, '.');
        id = stoi(words[0]);
        place = words[1];
        getLocationId[place] = id;
        getLocationName[id] = place;
    }
    inputFile.close();
    return;
}


void MakeGraph::addEdge(vector<vector<pair<int, double>>>& adj){
    ifstream inputFile("DataSet.txt", ios::in);
    if (!inputFile.is_open()){
        cout << "Error opening the file! DataSet.txt" << endl;
        return; 
    }
    // cout << "At AddEdge, DataSet.txt\n";
    string line;
    vector<string> result = extractWords(line);
    while(getline(inputFile, line)){
        vector<string> result = extractWords(line);
        string place1 = result[0];
        string place2 = result[1];
        double distance = stod(result[2]);
        // cout << "Place 1 : " << place1 << ", Place 2 : " << place2 << ", Distance : " << distance << endl; 
        adj[getLocationId[place1]].push_back({getLocationId[place2], distance});
        adj[getLocationId[place2]].push_back({getLocationId[place1], distance});    
    }
    inputFile.close();
    return;
}

map<int, string> MakeGraph::returnLocationNames(){
    return getLocationName;
}

map<string, int> MakeGraph::returnLocationId(){
    return getLocationId;
}

void MakeGraph::displayMap(bool organised){
    ifstream inputFile("DataSet.txt");
    if (!inputFile) {
        cerr << "Error: Unable to open the input file." << endl;
        return;
    }

    ofstream outputFile("Graph.dot");
    if (!outputFile) {
        cerr << "Error: Unable to create the output .dot file." << endl;
        return;
    }

    outputFile << "graph G {" << endl;

    string line;
    while(getline(inputFile, line)){
        vector<string> result = extractWords(line);
        string source = result[0];
        string target = result[1];
        double weight = stod(result[2]);
        outputFile << "    \"" << source << "\" -- \"" << target << "\" [label=\"" << weight << "\"];\n";
    }

    outputFile << "}" << endl;
    cout << "Graph data written to 'graph.dot' successfully." << endl;
    cout << "Dot file 'Graph.dot' created successfully." << endl;

    inputFile.close();
    outputFile.close();

    runDotFile("graph", organised);
    return;
}


void MakeGraph::displayShortestPath(const vector<string>& path, bool organized) {
    ifstream inputFile("DataSet.txt");
    if (!inputFile) {
        cerr << "Error: Unable to open the input file." << endl;
        return;
    }

    ofstream outputFile("pathInGraph.dot");
    if (!outputFile) {
        cerr << "Error: Unable to create the output .dot file." << endl;
        return;
    }

    outputFile << "graph G {" << endl;

    string line;
    while (getline(inputFile, line)) {
        vector<string> result = extractWords(line);
        string source = result[0];
        string target = result[1];
        double weight = stod(result[2]);

        bool isHighlighted = false;
        for (size_t i = 0; i < path.size() - 1; i++) {
            if ((source == path[i] && target == path[i + 1]) || (source == path[i + 1] && target == path[i])) {
                isHighlighted = true;
                break;
            }
        }

        if (isHighlighted) {
            outputFile << "    \"" << source << "\" -- \"" << target << "\" [label=\"" << weight << "\", color=\"red\", penwidth=2.0];\n";
        } else {
            outputFile << "    \"" << source << "\" -- \"" << target << "\" [label=\"" << weight << "\"];\n";
        }
    }

    // Set different shapes for nodes in the path
    set<string> highlightedNodes(path.begin(), path.end()); // Convert the path vector to a set
    for (const auto& node : getLocationName) {
        string nodeName = node.second;
        if (highlightedNodes.find(nodeName) != highlightedNodes.end()) {
            outputFile << "    \"" << nodeName << "\" [shape=box, style=filled, fillcolor=green];\n";
        } else {
            outputFile << "    \"" << nodeName << "\";\n";
        }
    }

    outputFile << "}" << endl;

    cout << "Graph data written to 'pathInGraph.dot' successfully." << endl;
    cout << "Dot file 'pathInGraph.dot' created successfully." << endl;

    inputFile.close();
    outputFile.close();

    runDotFile("pathInGraph", organized);
    return;
}



void MakeGraph::runDotFile(string fileName, bool organized){
    string command;
    if(organized){
        command = "dot -Tpng -Gdpi=300 -o " + fileName + ".png " + fileName + ".dot";
    } else {
        command = "fdp -Tpng -Gdpi=300 -o " + fileName + ".png " + fileName + ".dot";
    }
    

    int result = system(command.c_str());

    if (result != 0) {
        cerr << "Error converting .dot to PNG." << endl;
        return;
    }

    cout << "Graph converted to 'graph.png' successfully." << endl;
    command = "start " + fileName + ".png";

    result = system(command.c_str());

    if (result != 0) {
        cerr << "Error opening the PNG file." << endl;
        return;
    }
    return;
}
void MakeGraph::displayLocationList(){
    ifstream inputFile("DataSetList.txt");
    if (!inputFile) {
        cerr << "Error: Unable to open the input file." << endl;
        return;
    }

    string line;
    while(getline(inputFile, line)){
        cout << line << endl;
    }
    return;
}