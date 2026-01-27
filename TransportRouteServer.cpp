#include "httplib.h"
#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
#include <ctime>
#include <sstream>
#include <iomanip>

using namespace std;

struct Edge {
    string to;
    double distance;
    int fare;
    string bus;
};

class Graph {
public:
    unordered_map<string, vector<Edge>> adjacencyList;
    vector<string> stopNames;

    void addStop(string name) {
        if (adjacencyList.find(name) != adjacencyList.end()) {
            cout << "[!] Stop already exists: " << name << endl;
            return;
        }

        vector<Edge> emptyRouteList;
        adjacencyList[name] = emptyRouteList;
        stopNames.push_back(name);
        cout << "[+] Added stop: " << name << endl;
    }

    void addRoute(string from, string to, double distance, int fare, string busName) {
        Edge forwardEdge;
        forwardEdge.to = to;
        forwardEdge.distance = distance;
        forwardEdge.fare = fare;
        forwardEdge.bus = busName;

        Edge reverseEdge;
        reverseEdge.to = from;
        reverseEdge.distance = distance;
        reverseEdge.fare = fare;
        reverseEdge.bus = busName;

        adjacencyList[from].push_back(forwardEdge);
        adjacencyList[to].push_back(reverseEdge);

        cout << "[+] Added route: " << from << " <-> " << to;
        cout << " (" << distance << " km, Rs." << fare << ", " << busName << ")" << endl;
    }

    string findShortestPath(string startStop, string endStop) {
        cout << "\n[SHORTEST DISTANCE] Finding optimal route..." << endl;
        cout << "   From: " << startStop << endl;
        cout << "   To:   " << endStop << endl;

        priority_queue<
            pair<double, string>,
            vector<pair<double, string>>,
            greater<pair<double, string>>
        > priorityQueue;

        unordered_map<string, double> shortestDistance;
        double INFINITY_VALUE = 999999.0;

        for (const string& stopName : stopNames) {
            shortestDistance[stopName] = INFINITY_VALUE;
        }

        shortestDistance[startStop] = 0;
        unordered_map<string, string> previousStop;
        unordered_map<string, Edge> previousEdge;

        priorityQueue.push(make_pair(0.0, startStop));

        while (!priorityQueue.empty()) {
            pair<double, string> current = priorityQueue.top();
            priorityQueue.pop();

            string currentStop = current.second;
            double currentDistance = current.first;

            if (currentDistance > shortestDistance[currentStop]) {
                continue;
            }

            vector<Edge> routes = adjacencyList[currentStop];

            for (const Edge& route : routes) {
                string neighborStop = route.to;
                double distanceThroughCurrent = shortestDistance[currentStop] + route.distance;

                if (distanceThroughCurrent < shortestDistance[neighborStop]) {
                    shortestDistance[neighborStop] = distanceThroughCurrent;
                    previousStop[neighborStop] = currentStop;
                    previousEdge[neighborStop] = route;
                    priorityQueue.push(make_pair(distanceThroughCurrent, neighborStop));
                }
            }
        }

        return buildResultJSON(startStop, endStop, previousStop, previousEdge, "Shortest Distance (Dijkstra's Algorithm)");
    }

    string findCheapestPath(string startStop, string endStop) {
        cout << "\n[LOWEST FARE] Finding most economical route..." << endl;
        cout << "   From: " << startStop << endl;
        cout << "   To:   " << endStop << endl;

        priority_queue<
            pair<int, string>,
            vector<pair<int, string>>,
            greater<pair<int, string>>
        > priorityQueue;

        unordered_map<string, int> cheapestFare;
        int INFINITY_VALUE = 999999;

        for (const string& stopName : stopNames) {
            cheapestFare[stopName] = INFINITY_VALUE;
        }

        cheapestFare[startStop] = 0;
        unordered_map<string, string> previousStop;
        unordered_map<string, Edge> previousEdge;

        priorityQueue.push(make_pair(0, startStop));

        while (!priorityQueue.empty()) {
            pair<int, string> current = priorityQueue.top();
            priorityQueue.pop();

            string currentStop = current.second;
            int currentFare = current.first;

            if (currentFare > cheapestFare[currentStop]) {
                continue;
            }

            vector<Edge> routes = adjacencyList[currentStop];

            for (const Edge& route : routes) {
                string neighborStop = route.to;
                int fareThroughCurrent = cheapestFare[currentStop] + route.fare;

                if (fareThroughCurrent < cheapestFare[neighborStop]) {
                    cheapestFare[neighborStop] = fareThroughCurrent;
                    previousStop[neighborStop] = currentStop;
                    previousEdge[neighborStop] = route;
                    priorityQueue.push(make_pair(fareThroughCurrent, neighborStop));
                }
            }
        }

        return buildResultJSON(startStop, endStop, previousStop, previousEdge, "Lowest Fare (Dijkstra's Algorithm - Fare Optimized)");
    }

    string findAnyPath(string startStop, string endStop) {
        cout << "\n[QUICK PATHFINDING] Finding available route..." << endl;
        cout << "   From: " << startStop << endl;
        cout << "   To:   " << endStop << endl;

        unordered_set<string> visitedStops;
        vector<string> currentPath;
        vector<Edge> edgesUsed;

        bool pathFound = dfsRecursive(startStop, endStop, visitedStops, currentPath, edgesUsed);

        if (!pathFound) {
            cout << "   Result: No path found!" << endl;
            return "{\"found\":false}";
        }

        double totalDistance = 0;
        int totalFare = 0;

        for (const Edge& edge : edgesUsed) {
            totalDistance += edge.distance;
            totalFare += edge.fare;
        }

        cout << "   Result: Found path with " << currentPath.size() << " stops!" << endl;

        string result = "{\"found\":true,";
        result += "\"algorithm\":\"Quick Pathfinding (Depth-First Search)\",";
        result += "\"distance\":" + to_string(totalDistance) + ",";
        result += "\"fare\":" + to_string(totalFare) + ",";
        result += "\"stops\":" + to_string(currentPath.size()) + ",";

        result += "\"path\":[";
        for (size_t i = 0; i < currentPath.size(); i++) {
            if (i > 0) result += ",";
            result += "\"" + currentPath[i] + "\"";
        }
        result += "],";

        result += "\"buses\":[";
        for (size_t i = 0; i < edgesUsed.size(); i++) {
            if (i > 0) result += ",";
            result += "\"" + edgesUsed[i].bus + "\"";
        }
        result += "]}";

        return result;
    }

    // Get all unique bus numbers
    vector<string> getAllBuses() {
        unordered_set<string> busSet;
        for (const auto& pair : adjacencyList) {
            for (const Edge& edge : pair.second) {
                busSet.insert(edge.bus);
            }
        }
        return vector<string>(busSet.begin(), busSet.end());
    }

    // Get network statistics
    string getStatistics() {
        int totalRoutes = 0;
        double totalDistance = 0;
        int totalFare = 0;
        unordered_set<string> uniqueBuses;

        for (const auto& pair : adjacencyList) {
            for (const Edge& edge : pair.second) {
                totalRoutes++;
                totalDistance += edge.distance;
                totalFare += edge.fare;
                uniqueBuses.insert(edge.bus);
            }
        }

        totalRoutes /= 2; // Each route is counted twice
        totalDistance /= 2;
        totalFare /= 2;

        double avgDistance = totalRoutes > 0 ? totalDistance / totalRoutes : 0;
        double avgFare = totalRoutes > 0 ? (double)totalFare / totalRoutes : 0;

        string result = "{";
        result += "\"stops\":" + to_string(stopNames.size()) + ",";
        result += "\"routes\":" + to_string(totalRoutes) + ",";
        result += "\"buses\":" + to_string(uniqueBuses.size()) + ",";
        result += "\"totalDistance\":" + to_string(totalDistance) + ",";
        result += "\"avgDistance\":" + to_string(avgDistance) + ",";
        result += "\"avgFare\":" + to_string(avgFare) + "}";

        return result;
    }

    // Search stops by name
    string searchStops(string query) {
        vector<string> results;
        string lowerQuery = query;
        transform(lowerQuery.begin(), lowerQuery.end(), lowerQuery.begin(), ::tolower);

        for (const string& stop : stopNames) {
            string lowerStop = stop;
            transform(lowerStop.begin(), lowerStop.end(), lowerStop.begin(), ::tolower);
            if (lowerStop.find(lowerQuery) != string::npos) {
                results.push_back(stop);
            }
        }

        string result = "[";
        for (size_t i = 0; i < results.size(); i++) {
            if (i > 0) result += ",";
            result += "\"" + results[i] + "\"";
        }
        result += "]";

        return result;
    }

private:
    bool dfsRecursive(
        string currentStop,
        string endStop,
        unordered_set<string>& visitedStops,
        vector<string>& path,
        vector<Edge>& edges
    ) {
        visitedStops.insert(currentStop);
        path.push_back(currentStop);

        if (currentStop == endStop) {
            return true;
        }

        vector<Edge> routes = adjacencyList[currentStop];

        for (const Edge& route : routes) {
            string neighborStop = route.to;

            if (visitedStops.find(neighborStop) == visitedStops.end()) {
                edges.push_back(route);

                if (dfsRecursive(neighborStop, endStop, visitedStops, path, edges)) {
                    return true;
                }

                edges.pop_back();
            }
        }

        path.pop_back();
        return false;
    }

    string buildResultJSON(
        string startStop,
        string endStop,
        unordered_map<string, string>& previousStop,
        unordered_map<string, Edge>& previousEdge,
        string algorithmName
    ) {
        if (startStop == endStop) {
            string result = "{\"found\":true,";
            result += "\"algorithm\":\"" + algorithmName + "\",";
            result += "\"distance\":0,";
            result += "\"fare\":0,";
            result += "\"stops\":1,";
            result += "\"path\":[\"" + startStop + "\"],";
            result += "\"buses\":[]}";
            return result;
        }

        if (previousStop.find(endStop) == previousStop.end()) {
            cout << "   Result: No path found!" << endl;
            return "{\"found\":false}";
        }

        vector<string> path;
        vector<Edge> edges;
        string current = endStop;

        while (current != startStop) {
            path.insert(path.begin(), current);
            edges.insert(edges.begin(), previousEdge[current]);
            current = previousStop[current];
        }

        path.insert(path.begin(), startStop);

        double totalDistance = 0;
        int totalFare = 0;

        for (const Edge& edge : edges) {
            totalDistance += edge.distance;
            totalFare += edge.fare;
        }

        cout << "   Result: Found path with " << path.size() << " stops, ";
        cout << totalDistance << " km, Rs." << totalFare << endl;

        string result = "{\"found\":true,";
        result += "\"algorithm\":\"" + algorithmName + "\",";
        result += "\"distance\":" + to_string(totalDistance) + ",";
        result += "\"fare\":" + to_string(totalFare) + ",";
        result += "\"stops\":" + to_string(path.size()) + ",";

        result += "\"path\":[";
        for (size_t i = 0; i < path.size(); i++) {
            if (i > 0) result += ",";
            result += "\"" + path[i] + "\"";
        }
        result += "],";

        result += "\"buses\":[";
        for (size_t i = 0; i < edges.size(); i++) {
            if (i > 0) result += ",";
            result += "\"" + edges[i].bus + "\"";
        }
        result += "]}";

        return result;
    }
};

Graph busNetwork;

string getCurrentTimestamp() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    stringstream ss;
    ss << put_time(ltm, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

int main() {
    cout << endl;
    cout << "============================================================" << endl;
    cout << "                                                            " << endl;
    cout << "   SMARTTRANSIT - Intelligent Bus Journey Planner           " << endl;
    cout << "   C++ Backend Server with Advanced Graph Algorithms        " << endl;
    cout << "                                                            " << endl;
    cout << "============================================================" << endl;
    cout << endl;

    cout << "[*] Initializing transit network..." << endl;
    cout << "------------------------------------------------------------" << endl;

    // Load comprehensive sample data
    busNetwork.addStop("Central Station");
    busNetwork.addStop("City Mall");
    busNetwork.addStop("University Campus");
    busNetwork.addStop("General Hospital");
    busNetwork.addStop("International Airport");
    busNetwork.addStop("Seaside Beach");
    busNetwork.addStop("City Park");
    busNetwork.addStop("Sports Stadium");
    busNetwork.addStop("Tech Valley");
    busNetwork.addStop("Old Town Square");
    busNetwork.addStop("Financial District");
    busNetwork.addStop("Railway Terminal");

    cout << endl;
    cout << "[*] Loading route connections..." << endl;
    cout << "------------------------------------------------------------" << endl;

    // Main routes
    busNetwork.addRoute("Central Station", "City Mall", 2.5, 15, "Metro Express 1");
    busNetwork.addRoute("Central Station", "City Park", 1.8, 10, "Local Bus 2");
    busNetwork.addRoute("Central Station", "International Airport", 18.0, 60, "Airport Express");
    busNetwork.addRoute("Central Station", "Railway Terminal", 3.2, 20, "Metro Line 3");

    busNetwork.addRoute("City Mall", "University Campus", 3.2, 18, "Campus Shuttle");
    busNetwork.addRoute("City Mall", "Sports Stadium", 4.1, 15, "City Loop 4");
    busNetwork.addRoute("City Mall", "Financial District", 2.8, 22, "Business Express");

    busNetwork.addRoute("University Campus", "General Hospital", 2.3, 12, "Health Link 5");
    busNetwork.addRoute("University Campus", "Tech Valley", 3.5, 16, "Tech Corridor");

    busNetwork.addRoute("General Hospital", "International Airport", 12.5, 35, "Airport Link 6");
    busNetwork.addRoute("General Hospital", "Old Town Square", 4.2, 14, "Heritage Route");

    busNetwork.addRoute("City Park", "Sports Stadium", 2.1, 10, "Green Line 7");
    busNetwork.addRoute("City Park", "Seaside Beach", 5.5, 18, "Coastal Route 8");
    busNetwork.addRoute("City Park", "Old Town Square", 3.8, 15, "Park Connector");

    busNetwork.addRoute("Sports Stadium", "International Airport", 8.2, 28, "Stadium Express 9");
    busNetwork.addRoute("Sports Stadium", "Tech Valley", 5.8, 20, "Innovation Line");

    busNetwork.addRoute("Seaside Beach", "International Airport", 4.5, 16, "Beach Shuttle 10");
    busNetwork.addRoute("Seaside Beach", "Old Town Square", 6.2, 22, "Scenic Route");

    busNetwork.addRoute("Tech Valley", "Financial District", 4.3, 25, "Business Tech Link");
    busNetwork.addRoute("Tech Valley", "Railway Terminal", 6.5, 24, "Tech Express");

    busNetwork.addRoute("Financial District", "Railway Terminal", 2.9, 18, "Downtown Connector");
    busNetwork.addRoute("Financial District", "Old Town Square", 3.5, 16, "Heritage Business");

    busNetwork.addRoute("Old Town Square", "Railway Terminal", 4.8, 20, "Historical Line");

    cout << endl;
    cout << "============================================================" << endl;
    cout << "  NETWORK READY - Sample Routes Available                   " << endl;
    cout << "============================================================" << endl;
    cout << "                                                            " << endl;
    cout << "  Try these interesting journeys:                           " << endl;
    cout << "                                                            " << endl;
    cout << "  1. Central Station → International Airport                " << endl;
    cout << "     • Direct: 18.0 km (Rs. 60) via Airport Express         " << endl;
    cout << "     • Budget: Multiple routes available                    " << endl;
    cout << "                                                            " << endl;
    cout << "  2. University Campus → Seaside Beach                      " << endl;
    cout << "     • Scenic route via City Park                           " << endl;
    cout << "                                                            " << endl;
    cout << "  3. Tech Valley → Financial District                       " << endl;
    cout << "     • Business corridor connection                         " << endl;
    cout << "                                                            " << endl;
    cout << "============================================================" << endl;
    cout << endl;

    httplib::Server server;

    // CORS headers for all responses
    server.set_default_headers({
        {"Access-Control-Allow-Origin", "*"},
        {"Access-Control-Allow-Methods", "GET, POST, OPTIONS, DELETE"},
        {"Access-Control-Allow-Headers", "Content-Type, Authorization"},
        {"Access-Control-Max-Age", "3600"}
        });

    // Handle OPTIONS requests for CORS preflight
    server.Options(".*", [](const httplib::Request& req, httplib::Response& res) {
        res.status = 200;
        });

    // Get all stops
    server.Get("/stops", [](const httplib::Request& req, httplib::Response& res) {
        cout << "\n[API] GET /stops - " << getCurrentTimestamp() << endl;

        string jsonResult = "[";
        for (size_t i = 0; i < busNetwork.stopNames.size(); i++) {
            if (i > 0) jsonResult += ",";
            jsonResult += "\"" + busNetwork.stopNames[i] + "\"";
        }
        jsonResult += "]";

        res.set_content(jsonResult, "application/json");
        });

    // Get network graph
    server.Get("/graph", [](const httplib::Request& req, httplib::Response& res) {
        cout << "\n[API] GET /graph - " << getCurrentTimestamp() << endl;

        string jsonResult = "{";
        bool isFirstStop = true;

        for (const auto& pair : busNetwork.adjacencyList) {
            if (!isFirstStop) jsonResult += ",";
            isFirstStop = false;

            jsonResult += "\"" + pair.first + "\":[";

            for (size_t i = 0; i < pair.second.size(); i++) {
                if (i > 0) jsonResult += ",";

                jsonResult += "{";
                jsonResult += "\"to\":\"" + pair.second[i].to + "\",";
                jsonResult += "\"distance\":" + to_string(pair.second[i].distance) + ",";
                jsonResult += "\"fare\":" + to_string(pair.second[i].fare) + ",";
                jsonResult += "\"bus\":\"" + pair.second[i].bus + "\"";
                jsonResult += "}";
            }

            jsonResult += "]";
        }

        jsonResult += "}";
        res.set_content(jsonResult, "application/json");
        });

    // Find route
    server.Get("/route", [](const httplib::Request& req, httplib::Response& res) {
        string fromStop = req.get_param_value("from");
        string toStop = req.get_param_value("to");
        string algorithm = req.get_param_value("algo");

        cout << "\n[API] GET /route - " << getCurrentTimestamp() << endl;
        cout << "   From: " << fromStop << endl;
        cout << "   To: " << toStop << endl;
        cout << "   Algorithm: " << algorithm << endl;

        string result;

        if (algorithm == "cheapest") {
            result = busNetwork.findCheapestPath(fromStop, toStop);
        }
        else if (algorithm == "dfs") {
            result = busNetwork.findAnyPath(fromStop, toStop);
        }
        else {
            result = busNetwork.findShortestPath(fromStop, toStop);
        }

        res.set_content(result, "application/json");
        });

    // Get statistics
    server.Get("/statistics", [](const httplib::Request& req, httplib::Response& res) {
        cout << "\n[API] GET /statistics - " << getCurrentTimestamp() << endl;
        string result = busNetwork.getStatistics();
        res.set_content(result, "application/json");
        });

    // Search stops
    server.Get("/search", [](const httplib::Request& req, httplib::Response& res) {
        string query = req.get_param_value("q");
        cout << "\n[API] GET /search - Query: " << query << " - " << getCurrentTimestamp() << endl;
        string result = busNetwork.searchStops(query);
        res.set_content(result, "application/json");
        });

    // Get all buses
    server.Get("/buses", [](const httplib::Request& req, httplib::Response& res) {
        cout << "\n[API] GET /buses - " << getCurrentTimestamp() << endl;
        vector<string> buses = busNetwork.getAllBuses();

        string result = "[";
        for (size_t i = 0; i < buses.size(); i++) {
            if (i > 0) result += ",";
            result += "\"" + buses[i] + "\"";
        }
        result += "]";

        res.set_content(result, "application/json");
        });

    // Add stop
    server.Post("/addstop", [](const httplib::Request& req, httplib::Response& res) {
        string stopName = req.get_param_value("name");
        cout << "\n[API] POST /addstop - " << getCurrentTimestamp() << endl;
        cout << "   Adding: " << stopName << endl;

        busNetwork.addStop(stopName);
        res.set_content("{\"success\":true,\"message\":\"Stop added successfully\"}", "application/json");
        });

    // Add route
    server.Post("/addroute", [](const httplib::Request& req, httplib::Response& res) {
        string fromStop = req.get_param_value("from");
        string toStop = req.get_param_value("to");
        double distance = stod(req.get_param_value("distance"));
        int fare = stoi(req.get_param_value("fare"));
        string busName = req.get_param_value("bus");

        cout << "\n[API] POST /addroute - " << getCurrentTimestamp() << endl;

        busNetwork.addRoute(fromStop, toStop, distance, fare, busName);
        res.set_content("{\"success\":true,\"message\":\"Route added successfully\"}", "application/json");
        });

    // Health check
    server.Get("/health", [](const httplib::Request& req, httplib::Response& res) {
        string result = "{\"status\":\"healthy\",\"timestamp\":\"" + getCurrentTimestamp() + "\"}";
        res.set_content(result, "application/json");
        });

    cout << "============================================================" << endl;
    cout << "                                                            " << endl;
    cout << "   SERVER STARTING...                                       " << endl;
    cout << "                                                            " << endl;
    cout << "   Server URL: http://localhost:8080                        " << endl;
    cout << "   Frontend: Open index.html in your browser                " << endl;
    cout << "                                                            " << endl;
    cout << "   API Endpoints Available:                                 " << endl;
    cout << "   • GET  /stops       - List all bus stops                 " << endl;
    cout << "   • GET  /graph       - Network graph data                 " << endl;
    cout << "   • GET  /route       - Find optimal route                 " << endl;
    cout << "   • GET  /statistics  - Network statistics                 " << endl;
    cout << "   • GET  /search      - Search stops                       " << endl;
    cout << "   • GET  /buses       - List all buses                     " << endl;
    cout << "   • POST /addstop     - Add new stop                       " << endl;
    cout << "   • POST /addroute    - Add new route                      " << endl;
    cout << "   • GET  /health      - Server health check                " << endl;
    cout << "                                                            " << endl;
    cout << "   Press Ctrl+C to stop the server                          " << endl;
    cout << "                                                            " << endl;
    cout << "============================================================" << endl;
    cout << endl;
    cout << "Server is running... Waiting for requests..." << endl;
    cout << endl;

    server.listen("0.0.0.0", 8080);

    return 0;
}