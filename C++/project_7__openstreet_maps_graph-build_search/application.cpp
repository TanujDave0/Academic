// application.cpp <Starter Code>
// <Your name>
//
// University of Illinois at Chicago
// CS 251: Fall 2020
// Project #7 - Openstreet Maps
//
// References:
// TinyXML: https://github.com/leethomason/tinyxml2
// OpenStreetMap: https://www.openstreetmap.org
// OpenStreetMap docs:
//   https://wiki.openstreetmap.org/wiki/Main_Page
//   https://wiki.openstreetmap.org/wiki/Map_Features
//   https://wiki.openstreetmap.org/wiki/Node
//   https://wiki.openstreetmap.org/wiki/Way
//   https://wiki.openstreetmap.org/wiki/Relation
//

#include <iostream>
#include <iomanip>  /*setprecision*/
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <cstdlib>
#include <cstring>
#include <cassert>
#include <limits>   /*numeric_limits*/
#include "tinyxml2.h"
#include "dist.h"
#include "osm.h"
#include "graph.h"


using namespace std;
using namespace tinyxml2;

class prioritize {
    public:
    bool operator()(const pair<long long, double>& p1,
                    const pair<long long, double>& p2) const {
              if (p1.second == p2.second) {
                  return p1.first > p2.first;
              }
              return p1.second > p2.second;
          }
};

vector<long long> myDijkstra(graph<long long, double>& G, long long startV,
                           map<long long, double>& distances,
                           map<long long, long long>& previous) {
    const double INF = numeric_limits<double>::max();
    vector<long long> visited;
    set<long long> visitedSet;
    double edgeWeight;
    double altEdgeWeight;
    long long currV;

    priority_queue<pair<long long, double>, vector<pair<long long, double>>,
                  prioritize> frontierQueue;

    vector<long long> vertex = G.getVertices();
    for (long long v : vertex) {
        frontierQueue.push(make_pair(v, INF));
        distances[v] = INF;
        previous[v] = -1;
    }

    frontierQueue.push(make_pair(startV, 0));
    distances[startV] = 0;

    while (!frontierQueue.empty()) {
        currV = frontierQueue.top().first;
        double weight = frontierQueue.top().second;
        frontierQueue.pop();

        if (distances[currV] == INF) {
            break;
        } else if (weight == INF) {
            break;
        } else if (visitedSet.count(currV) > 0) {
            continue;
        } else {
            visited.push_back(currV);
            visitedSet.insert(currV);
        }

        set<long long> adj = G.neighbors(currV);
        for (long long v : adj) {
            G.getWeight(currV, v, edgeWeight);
            altEdgeWeight = distances[currV] + edgeWeight;

            if (altEdgeWeight < distances[v]) {
                frontierQueue.push(make_pair(v, altEdgeWeight));
                previous[v] = currV;
                distances[v] = altEdgeWeight;
            }
        }
    }

    return visited;
}

void buildGraph(graph<long long, double> &G, map<long long,
                Coordinates> Nodes, vector<FootwayInfo> Footways,
                vector<BuildingInfo> Buildings) {
    for (auto e : Nodes) {
        G.addVertex(e.first);
    }

    for (FootwayInfo path : Footways) {
        for (int i = 0; i < path.Nodes.size() - 1; i++) {
            Coordinates cor1 = Nodes[path.Nodes[i]];
            Coordinates cor2 = Nodes[path.Nodes[i + 1]];
            double dist = distBetween2Points(cor1.Lat, cor1.Lon,
                                             cor2.Lat, cor2.Lon);
            G.addEdge(path.Nodes[i], path.Nodes[i + 1], dist);
            G.addEdge(path.Nodes[i + 1], path.Nodes[i], dist);
        }
    }
}

int partialMatch(vector<BuildingInfo> buildings, string name) {
    for (int j = 0; j < buildings.size(); j++) {
        bool ans = false;
        string b = buildings[j].Fullname;

        int pos = 0;
        int ini = b.find("(");
        if (ini == string::npos) {
            for (int i = 0; i < b.size(); i = b.find(" ", i + 1) + 1) {
                if (name[pos] != b[i]) {
                    ans = false;
                    break;
                }
                ans = true;
                pos++;
            }
            if (ans || b.find(name) != string::npos) {
                return j;
            }
        } else {
            ini++;
            for (int i = 0; i < name.size(); i++) {
                if (name[i] != b[i + ini]) {
                    ans = false;
                    break;
                }
                ans = true;
            }
            if (ans || b.find(name) != string::npos) {
                return j;
            }
        }
    }
    return -1;
}

long long findNearestPath(map<long long, Coordinates> Nodes, vector<FootwayInfo> footways, BuildingInfo from) {
    long long ans;
    double distance = numeric_limits<double>::max();

    for (auto f : footways) {
        for (auto e : f.Nodes) {
            double lat1 = from.Coords.Lat;
            double lon1 = from.Coords.Lon;
            double lat2 = Nodes[e].Lat;
            double lon2 = Nodes[e].Lon;
            double temp = distBetween2Points(lat1, lon1, lat2, lon2);
            if (temp < distance) {
                ans = e;
                distance = temp;
            }
        }
    }
    return ans;
}

bool getInputs(map<long long, Coordinates> Nodes, vector<FootwayInfo> footways, vector<BuildingInfo> buildings, long long &start, long long &end) {
    string startBuilding, destBuilding;

    cout << "Enter start (partial name or abbreviation), or #> ";
    getline(cin, startBuilding);

    if (startBuilding == "#") {
        return false;
    }

    cout << "Enter destination (partial name or abbreviation)> ";
    getline(cin, destBuilding);

    int s = partialMatch(buildings, startBuilding);
    int e = partialMatch(buildings, destBuilding);
    while (s == -1 || e == -1) {
        if (s == -1) {
            cout << "Start building not found" << endl;
        } else {
            cout << "Destination building not found" << endl;
        }
        cout << "Enter start (partial name or abbreviation), or #> ";
        getline(cin, startBuilding);

        if (startBuilding == "#") {
            return false;
        }

        cout << "Enter destination (partial name or abbreviation)> ";
        getline(cin, destBuilding);
        s = partialMatch(buildings, startBuilding);
        e = partialMatch(buildings, destBuilding);
    }
    BuildingInfo first = buildings[s];
    BuildingInfo second = buildings[e];

    start = findNearestPath(Nodes, footways, first);
    end = findNearestPath(Nodes, footways, second);

    cout << "Starting point:" << endl;
    cout << " " << first.Fullname << endl;
    cout << " (" << first.Coords.Lat << ", " << first.Coords.Lon << ")" << endl;

    cout << "Destination point:" << endl;
    cout << " " << second.Fullname << endl;
    cout << " (" << second.Coords.Lat << ", " << second.Coords.Lon << ")" << endl
         << endl;

    return true;
}

void printPath(map<long long, long long> predecessors, long long start, long long end) {
    stack<long long> myStack;
    long long current = end;
    while (current != start) {
        myStack.push(current);
        current = predecessors[current];
    }

    cout << start;
    while (!myStack.empty()) {
        cout << "->" << myStack.top();
        myStack.pop();
    }
    cout << endl << endl;
}

int main() {
    const double INF = numeric_limits<double>::max();
  // maps a Node ID to it's coordinates (lat, lon)
  map<long long, Coordinates>  Nodes;
  // info about each footway, in no particular order
  vector<FootwayInfo>          Footways;
  // info about each building, in no particular order
  vector<BuildingInfo>         Buildings;
  XMLDocument                  xmldoc;

  cout << "** Navigating UIC open street map **" << endl;
  cout << endl;
  cout << std::setprecision(8);

  string def_filename = "uic.osm";
  string filename;

  cout << "Enter map filename> ";
  getline(cin, filename);

  if (filename == "") {
    filename = def_filename;
  }

  //
  // Load XML-based map file
  //
  if (!LoadOpenStreetMap(filename, xmldoc)) {
    cout << "**Error: unable to load open street map." << endl;
    cout << endl;
    return 0;
  }

  //
  // Read the nodes, which are the various known positions on the map:
  //
  int nodeCount = ReadMapNodes(xmldoc, Nodes);

  //
  // Read the footways, which are the walking paths:
  //
  int footwayCount = ReadFootways(xmldoc, Footways);

  //
  // Read the university buildings:
  //
  int buildingCount = ReadUniversityBuildings(xmldoc, Nodes, Buildings);

  //
  // Stats
  //
  assert(nodeCount == (int)Nodes.size());
  assert(footwayCount == (int)Footways.size());
  assert(buildingCount == (int)Buildings.size());

  cout << endl;
  cout << "# of nodes: " << Nodes.size() << endl;
  cout << "# of footways: " << Footways.size() << endl;
  cout << "# of buildings: " << Buildings.size() << endl;


  //
  // TO DO: build the graph, output stats:
  //
  graph<long long, double> G;

    buildGraph(G, Nodes, Footways, Buildings);


    cout << "# of vertices: " << G.NumVertices() << endl;
    cout << "# of edges: " << G.NumEdges() << endl;
    cout << endl;

  //
  // Navigation from building to building
  //
    long long start, end;

  while (getInputs(Nodes, Footways, Buildings, start, end)) {
    cout << "Nearest start node:" << endl << " " << start << endl;
    cout << " (" << Nodes[start].Lat << ", " << Nodes[start].Lon << ")" << endl;
    
    cout << "Nearest destination node:" << endl << " " << end << endl;
    cout << " (" << Nodes[end].Lat << ", " << Nodes[end].Lon << ")"
         << endl << endl;

    cout << "Navigating with Dijkstra..." << endl;

    map<long long, double> distances;
    map<long long, long long> predecessors;

    vector<long long> ans = myDijkstra(G, start, distances, predecessors);
    if (distances[end] == INF) {
        cout << "Sorry, destination unreachable" << endl;
        continue;
    }

    cout << "Distance to dest: " << distances[end] << " miles" << endl;
    cout << "Path: ";

    printPath(predecessors, start, end);
  }

  //
  // done:
  //
  cout << "** Done **" << endl;
  return 0;
}
