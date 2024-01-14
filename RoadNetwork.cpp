#include <iostream>
#include "RoadNetwork.h"
#include "makeGraph.h"
using namespace std;

vector<int> Path::shortestPath(const vector<int>& arr, int source, int destination){
    int node = destination;
    vector<int> path;
    while(arr[node] != node){
        path.push_back(node);
        node = arr[node];
    }
    path.push_back(source);
    reverse(path.begin(), path.end());
    return path;
}


void Path::printPath(const vector<int>& path, double distance, map<int, string> mpp){
    for (int i = 0; i < path.size(); i++) {
        cout << mpp.at(path[i]);
        if (i != path.size() - 1)
            cout << " -> ";
    }
    cout << endl;
    cout << "Distance: " << distance << endl;
    cout << endl;
}

void Path::allPathsUtil(vector<vector<pair<int, double>>>& adj, int source, int destination, vector<bool>& visited,
                    vector<int>& path, double distance, const map<int, string>& mpp) {
    
    visited[source] = true;
    path.push_back(source);

    if (source == destination) {
        printPath(path, distance, mpp);
    } else {
        for (auto ele : adj[source]) {
            int nearestPlace = ele.first;
            double edgeWeight = ele.second;
            if (!visited[nearestPlace]) {
                allPathsUtil(adj, nearestPlace, destination, visited, path, distance + edgeWeight, mpp);
            }
        }
    }

    path.pop_back();
    visited[source] = false;
}

void Path::allPaths(vector<vector<pair<int, double>>>& adj, int source, int destination, const map<int, string>& mpp) {

    vector<bool> visited(adj.size(), false);
    vector<int> path;
    double distance = 0.0;
    cout << "All possible paths between " << mpp.at(source) << " and " << mpp.at(destination) << " are:\n";
    allPathsUtil(adj, source, destination, visited, path, distance, mpp);
}

vector<int> Path::shortestDistance(vector<vector<pair<int, double>>>& adj, 
                    int V, int source, int destination, map<int, string>& mpp) { 
    
    // Min-Heap
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq; 
    vector<double> distance(V+1, 1e9);
    distance[source] = 0;
    pq.push({0, source});
    vector<int> prevLocation(V+1);
    for(int i = 1; i <= V; i++){
        prevLocation[i] = i;
    }
    while(!pq.empty()){
        double dist = pq.top().first;
        int location = pq.top().second;
        pq.pop();

        for(auto ele : adj[location]){
            int nearestPlace = ele.first;
            double nearestDistance = ele.second;

            if(nearestDistance + dist < distance[nearestPlace]){
                distance[nearestPlace] = nearestDistance + dist;
                pq.push({nearestDistance + dist, nearestPlace});
                prevLocation[nearestPlace] = location;
            }
        }
    }

    cout << endl;
    cout << "Source : " << mpp[source] << endl;
    cout << "Destination : " << mpp[destination] << endl;
    cout << "Shortest Distance : " << distance[destination] << endl;
    cout << "Shortest Path : ";
    vector<int> shortestPathInt = shortestPath(prevLocation, source, destination);
    printPath(shortestPathInt, distance[destination], mpp);
    return shortestPathInt;
}