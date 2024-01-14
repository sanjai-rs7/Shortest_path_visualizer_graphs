#include <iostream>
#include <map>
#include <fstream> 
#include <set>
using namespace std;

class MakeGraph{
private:
    map<int,string> getLocationName;
    map<string,int> getLocationId;
public:
    void addEdge(vector<vector<pair<int, double>>>& adj);
    void addLocations();
    map<int, string> returnLocationNames();
    map<string, int> returnLocationId();
    vector<string> extractWords(const string& input);
    void displayMap(bool organized);
    vector<string> splitString(const string& inputStr, char delimiter);
    void displayLocationList();
    void runDotFile(string fileName, bool organized);
    void displayShortestPath(const vector<string>& path, bool organized);
};