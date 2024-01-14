#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
#include <map>
#include <algorithm>
using namespace std;

class Path{
public:
    vector<int> shortestPath(const vector<int>& arr, int source, int destination);
    
    void printPath(const vector<int>& path, double distance, map<int, string> mpp);
    
    void allPathsUtil(vector<vector<pair<int, double>>>& adj, int source, int destination, vector<bool>& visited,
                    vector<int>& path, double distance, const map<int, string>& mpp);

    void allPaths(vector<vector<pair<int, double>>>& adj, int source, int destination, const map<int, string>& mpp);
    
    vector<int> shortestDistance(vector<vector<pair<int, double>>>& adj, int V, 
                        int source, int destination, map<int, string>& mpp);
};