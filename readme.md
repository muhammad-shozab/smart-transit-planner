# SmartTransit - Intelligent Bus Journey Planner

A comprehensive Final Year Project implementing advanced graph algorithms and data structures for optimal transit route planning.

## 🚀 Features

### Core Functionality
- **Smart Route Planning** - Multiple pathfinding algorithms
  - Shortest Distance (Dijkstra's Algorithm)
  - Lowest Fare (Dijkstra's Algorithm - Fare Optimized)
  - Quick Pathfinding (Depth-First Search)
  
- **Route Comparison** - Compare all available routes side-by-side
- **Interactive Map** - Visual network representation using Leaflet.js
- **Recent Searches** - Quick access to previous routes
- **Saved Routes** - Save favorite journeys for later
- **Dark/Light Mode** - Comfortable viewing in any lighting
- **Fully Responsive** - Works on all devices (desktop, tablet, mobile)

### Network Management
- Add new bus stops
- Create route connections
- Real-time network statistics
- Network graph visualization
- Search functionality

### Data Structures Used
- **Graph (Adjacency List)** - Efficient representation of transit network
- **Priority Queue (Min-Heap)** - For Dijkstra's algorithm optimization
- **Hash Map (unordered_map)** - Fast lookups for stops and routes
- **Hash Set (unordered_set)** - Track visited nodes in DFS
- **Vectors** - Dynamic arrays for paths and edges
- **Stack (Call Stack)** - Recursive DFS implementation

## 🛠️ Technology Stack

**Frontend:**
- HTML5
- CSS3 (Custom Design System)
- Vanilla JavaScript (ES6+)
- Leaflet.js (Maps)
- Chart.js (Statistics)

**Backend:**
- C++ (C++11 or higher)
- cpp-httplib library (HTTP server)

## 📋 Prerequisites

### For Backend (C++)
- C++ compiler (g++, clang++, or MSVC)
- cpp-httplib library

### For Frontend
- Any modern web browser (Chrome, Firefox, Safari, Edge)
- No additional dependencies required

## 🔧 Installation & Setup

### 1. Download cpp-httplib

```bash
# Create a directory for the project
mkdir SmartTransit
cd SmartTransit

# Download cpp-httplib header file
# Visit: https://github.com/yhirose/cpp-httplib
# Download httplib.h and place it in your project directory
```

### 2. Compile the Backend

**On Linux/Mac:**
```bash
g++ -std=c++11 -o server server.cpp -lpthread
```

**On Windows (MinGW):**
```bash
g++ -std=c++11 -o server.exe server.cpp -lws2_32
```

**On Windows (Visual Studio):**
```bash
cl /EHsc /std:c++11 server.cpp
```

### 3. Run the Server

**On Linux/Mac:**
```bash
./server
```

**On Windows:**
```bash
server.exe
```

The server will start on `http://localhost:8080`

### 4. Open the Frontend

Simply open `index.html` in your web browser. The application will automatically connect to the backend server.

## 🎯 Usage Guide

### Planning a Journey

1. **Select Starting Point** - Choose your origin from the dropdown
2. **Select Destination** - Choose where you want to go
3. **Choose Preference:**
   - **Shortest Distance** - Minimize kilometers traveled
   - **Lowest Fare** - Save money on your journey
   - **Any Available Route** - Quick pathfinding
4. **View Results** - See your route, buses, and statistics

### Comparing Routes

1. Navigate to "Compare Routes"
2. Select origin and destination
3. Click "Compare All Options"
4. View side-by-side comparison of all algorithms

### Managing the Network

**Add a Stop:**
1. Go to "Add Stop"
2. Enter stop name
3. Click "Add Stop to Network"

**Add a Route:**
1. Go to "Add Route"
2. Select from and to stops
3. Enter distance, fare, and bus number
4. Click "Create Route"

### Viewing Network

- **Network Map** - Interactive visual representation
- **All Connections** - Complete adjacency list
- **Statistics** - Network metrics and analytics

## 🏗️ Architecture

### Backend Architecture
```
Graph Class
├── adjacencyList (unordered_map<string, vector<Edge>>)
├── stopNames (vector<string>)
├── findShortestPath() - Dijkstra's Algorithm
├── findCheapestPath() - Dijkstra's Algorithm (Fare)
├── findAnyPath() - Depth-First Search
└── Helper Methods (buildResultJSON, dfsRecursive)
```

### Algorithm Complexity

**Dijkstra's Algorithm:**
- Time Complexity: O((V + E) log V)
- Space Complexity: O(V)
- Best for: Shortest path in weighted graphs

**Depth-First Search:**
- Time Complexity: O(V + E)
- Space Complexity: O(V)
- Best for: Quick pathfinding

## 📊 API Endpoints

| Method | Endpoint | Description |
|--------|----------|-------------|
| GET | /stops | Get all bus stops |
| GET | /graph | Get network graph |
| GET | /route | Find route (params: from, to, algo) |
| GET | /statistics | Get network statistics |
| GET | /search | Search stops (param: q) |
| GET | /buses | Get all bus lines |
| POST | /addstop | Add new stop (param: name) |
| POST | /addroute | Add new route (params: from, to, distance, fare, bus) |
| GET | /health | Server health check |

## 🎨 Design Features

- **Modern UI/UX** - Clean, intuitive interface
- **Responsive Design** - Mobile-first approach
- **Dark Mode** - Eye-friendly dark theme
- **Smooth Animations** - Polished user experience
- **Accessibility** - WCAG compliant
- **Performance** - Optimized for speed

## 🔍 Sample Data

The application comes pre-loaded with a comprehensive transit network:

**12 Bus Stops:**
- Central Station
- City Mall
- University Campus
- General Hospital
- International Airport
- Seaside Beach
- City Park
- Sports Stadium
- Tech Valley
- Old Town Square
- Financial District
- Railway Terminal

**19 Routes** covering the entire network with realistic distances and fares.

## 🐛 Troubleshooting

**Server won't start:**
- Ensure port 8080 is not in use
- Check if cpp-httplib is properly included
- Verify compiler supports C++11

**Frontend can't connect:**
- Ensure server is running
- Check browser console for CORS errors
- Verify API_URL in index.html matches server address

**Routes not found:**
- Ensure both stops exist in the network
- Check if there's a connection path between stops
- Verify network data is loaded

## 📈 Future Enhancements

- Real-time bus tracking
- Time-based routing
- Multi-modal transport (bus + metro + walking)
- User accounts and preferences
- Route history analytics
- Mobile app version
- Integration with real transit APIs
- Traffic-aware routing
- Accessibility features (wheelchair accessible routes)

## 👨‍💻 Development

### Project Structure
```
SmartTransit/
├── index.html          # Frontend application
├── server.cpp          # Backend server
├── httplib.h          # HTTP library
└── README.md          # Documentation
```

### Code Style
- C++: Follow Google C++ Style Guide
- JavaScript: ES6+ with modern practices
- CSS: BEM-like naming convention

## 📝 License

This project is created for educational purposes as a Final Year Project.

## 👤 Author

Created as a Data Structures and Algorithms Final Year Project

## 🙏 Acknowledgments

- cpp-httplib by Yuji Hirose
- Leaflet.js for maps
- Chart.js for statistics
- OpenStreetMap contributors

## 📞 Support

For issues or questions, please check:
1. Troubleshooting section above
2. Browser console for error messages
3. Server console for backend logs

---

**Note:** This is an academic project demonstrating practical applications of graph algorithms and data structures in real-world transit planning scenarios.