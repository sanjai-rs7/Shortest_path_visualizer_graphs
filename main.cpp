#include <iostream>
#include <vector>
#include "RoadNetwork.h"
#include "makeGraph.h"
using namespace std;

int getUserInput(const string& prompt) {
    int userInput;
    cout << prompt;
    cin >> userInput;
    return userInput;
}

void getSourceAndDestination(int& source, int& destination, int& V, vector<int>& shortestPathInt,
vector<string>& shortestPathString, vector<vector<pair<int, double>>>& adjacencyList,map<int, string>& mpp, Path& p){
    source = getUserInput("Enter the ID of the source location: ");
    destination = getUserInput("Enter the ID of the destination location: ");

    if (mpp.find(source) == mpp.end() || mpp.find(destination) == mpp.end()) {
        cout << "Invalid location IDs entered. Please try again with valid IDs." << endl;
        return;
    }

    cout << "Source Location: " << mpp[source] << endl;
    cout << "Destination Location: " << mpp[destination] << endl;
    // Dijkstras will take care of the printig of Shortest path.
    shortestPathInt = p.shortestDistance(adjacencyList, V, source, destination, mpp); 
    for (int i = 0; i < shortestPathInt.size(); i++) {
        shortestPathString.push_back(mpp[shortestPathInt[i]]);
    }
    return;
}

int main(){
    Path p;
    int V = 54;
    vector<vector<pair<int, double>>> adjacencyList(V+1);
    MakeGraph mg;
    mg.addLocations();
    mg.addEdge(adjacencyList);
    // for (int i = 1; i < adjacencyList.size(); ++i) {
    //     cout << "Vertex " << i << ": ";
    //     for (const auto& neighbor : adjacencyList[i]) {
    //         cout << "{" << neighbor.first << ", " << neighbor.second << "} ";
    //     }
    //     cout << endl;
    // }
    // return 0;
    map<int, string> mpp = mg.returnLocationNames();

    int source = -1, destination = -1;
    int choice;
    vector<int> shortestPathInt; 
    vector<string> shortestPathString;
    while(true){
        cout << endl;
        cout << "1.Display all the available Locations list " << endl;
        cout << "2.Display the whole Map " << endl;
        cout << "3.Shortest Path in text" << endl;
        cout << "4.Shortest Path in Map" << endl;
        cout << "5.Print All Possible Paths" << endl;
        cout << "6.Close the map" << endl;
        cout << endl;

        cout << "Enter your option : ";
        cin >> choice;
        cout << endl;
        switch (choice)
        {
        case 1:
            mg.displayLocationList();
            cout << endl;
            cout << "Location List is displayed Successfully!" << endl;
            break;
        case 2:
            cout << "1.Organized Map" << endl;
            cout << "2.Random Map" << endl;
            cout <<"\nEnter your type of Map : ";
            cin >> choice;
            if(choice == 1){
                mg.displayMap(true);
            } else {
                mg.displayMap(false);
            }
            cout << "Map is displayed successfully!";
            cout << endl;
            break;
        case 3:
            getSourceAndDestination(source, destination, V, shortestPathInt, shortestPathString, adjacencyList, mpp, p);
            shortestPathInt.clear();
            cout << "Displayed Shortest Path in Text SuccessFully" << endl;
            cout << endl;
            break;
        case 4:
            if(shortestPathString.empty()){
                cout << "\nPlease Enter the Source and Destination by pressing option 3!";
                cout << endl;
                continue;
            }
            cout << "1.Organized Map" << endl;
            cout << "2.Random Map" << endl;
            cout <<"\n Enter your type of Map : ";
            cin >> choice;
            if(choice == 1){
                mg.displayShortestPath(shortestPathString, true);
            } else {
                mg.displayShortestPath(shortestPathString, false);
            }
            shortestPathString.clear();
            cout << "Displayed Shortest Path in Map SuccessFully" << endl;
            break;
        case 5:
            if(source == -1 || destination == -1){
                cout << "Please Enter the Source and Destination by pressing option 3!";
                continue;
            }
            p.allPaths(adjacencyList, source, destination, mpp);
            cout << "Displayed All Paths SuccessFully" << endl;
            break;
        case 6:
            cout << "Closing the Map!, BYE BYE!" << endl;
            return 0;
        default:
            cout << "Invalid Option";
            continue;
        }
    }

    return 0;
}
