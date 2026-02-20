# 🚌 SmartTransit — Intelligent Bus Journey Planner

> A **Data Structures & Algorithms semester project** built with **C++ (backend)** and **Vanilla JavaScript (frontend)** that demonstrates real-world applications of graph algorithms and data structures for optimal transit route planning.

<img width="1364" height="723" alt="image" src="https://github.com/user-attachments/assets/511b7d65-d390-449e-b9b1-d636f159f514" />

---

## 📸 Screenshots

### 🏠 Dashboard — Plan Your Journey
<img width="1364" height="723" alt="image" src="https://github.com/user-attachments/assets/fa68cc2e-e96e-487d-a74f-632c29600c5e" />

### ✅ Route Result
<img width="1364" height="719" alt="image" src="https://github.com/user-attachments/assets/ca2805c0-3bf6-48d1-a891-dbc27f0652eb" />

### 📊 Route Comparison Table
<img width="1365" height="721" alt="image" src="https://github.com/user-attachments/assets/85c134d1-1886-4db6-a260-f7d8f8c5a4cf" />

### 🗺️ Interactive Network Map (Leaflet.js)
<img width="1365" height="721" alt="image" src="https://github.com/user-attachments/assets/04b21bfe-23a2-482a-be54-5fc6c5f82056" />

### 🔗 All Connections — Adjacency List View
<img width="1365" height="722" alt="image" src="https://github.com/user-attachments/assets/c784ddbc-d999-4327-95f0-03ba8ace445b" />

### 📈 Statistics & Chart
<img width="1365" height="719" alt="image" src="https://github.com/user-attachments/assets/4816cc47-9775-4fb7-930c-1be403dce478" />

### 🌙 Dark Mode
<img width="1365" height="722" alt="image" src="https://github.com/user-attachments/assets/5016361c-c3e8-4197-8435-c53e52a2b9e1" />

### 📱 Mobile View
![IMG_20260220_141420 jpg](https://github.com/user-attachments/assets/f7f1567f-c21e-4c20-8edf-e16eef97ded5)

![IMG_20260220_141324 jpg](https://github.com/user-attachments/assets/c9718d5c-ae8c-4fed-87d8-332a813b090b)

![IMG_20260220_141336 jpg](https://github.com/user-attachments/assets/2dda1f6d-f809-44b2-9ca9-3f7f05e8ee2a)

---

## ✨ Features

### 🎯 Journey Planning
- Select any start and end stop from the dropdown
- **Swap button** to instantly reverse the journey direction
- Three routing modes to choose from:
  - **Shortest Distance** — Dijkstra's algorithm minimizing total kilometers
  - **Lowest Fare** — Dijkstra's algorithm minimizing total cost (Rs.)
  - **Any Available Route** — Depth-First Search for quick pathfinding
- Results show the full stop-by-stop path, buses to board at each segment, total distance, fare, and number of stops

### 📊 Route Comparison
- Compare all three algorithms side-by-side for any origin-destination pair
- Best values for distance, fare, and stops are highlighted in green

### 🗺️ Interactive Map
- Leaflet.js powered map with all 12 stops plotted
- Network edges drawn as lines between connected stops
- Click any marker for stop details and connection count

### 🔗 Network Graph View
- Full adjacency list displayed as cards
- Each stop shows all direct connections with distance and fare

### 📈 Statistics
- Live count of stops, routes, buses, and average route distance
- Bar chart visualization using Chart.js

### ⭐ Saved & Recent Routes
- Save favourite journeys with the "Save Route" button (persisted in `localStorage`)
- Recent searches automatically tracked for quick re-use

### 🌙 Dark / Light Mode
- Toggle between themes from the sidebar, preference saved in `localStorage`

### 📱 Fully Responsive
| Breakpoint | Behaviour |
|---|---|
| > 1024px | Full sidebar + content |
| ≤ 1024px | Sidebar collapses to icon-only |
| ≤ 768px | Sidebar becomes off-canvas drawer via hamburger button |

---

## 🧠 Algorithms & Data Structures

### Algorithms

| Algorithm | Used For | Time Complexity | Space Complexity |
|---|---|---|---|
| **Dijkstra's (distance)** | Shortest distance path | O((V + E) log V) | O(V) |
| **Dijkstra's (fare)** | Cheapest fare path | O((V + E) log V) | O(V) |
| **Depth-First Search** | Any available path | O(V + E) | O(V) |

### Data Structures

| Structure | Where Used |
|---|---|
| **Graph — Adjacency List** (`unordered_map<string, vector<Edge>>`) | Core network representation |
| **Priority Queue — Min-Heap** | Dijkstra's algorithm efficiency |
| **Hash Map** (`unordered_map`) | Fast stop lookups and distance/fare tracking |
| **Hash Set** (`unordered_set`) | Tracking visited nodes in DFS |
| **Vectors** | Storing edges, stop names, and paths |
| **Call Stack** | Recursive DFS implementation |

![Algorithm Diagram](screenshots/algorithm-diagram.png)
> 💡 *Add a flowchart here showing how Dijkstra's traverses your graph step by step*

---

## 🛠️ Tech Stack

| Layer | Technology |
|---|---|
| **Backend** | C++ (C++11), cpp-httplib |
| **Frontend** | HTML5, CSS3, Vanilla JavaScript (ES6+) |
| **Maps** | Leaflet.js + OpenStreetMap |
| **Charts** | Chart.js |
| **Fonts** | Google Fonts — Inter |
| **Persistence** | Browser `localStorage` |

Zero npm packages. Zero build tools. Zero frameworks.

---

## 🗂️ Project Structure

```
SmartTransit/
│
├── index.html          # Complete frontend — UI, logic, built-in demo data
├── server.cpp          # C++ backend server with Graph class and HTTP endpoints
├── httplib.h           # Single-header HTTP library (download separately)
│
├── screenshots/        # 📸 Add your screenshots here (see list below)
│   ├── banner.png
│   ├── plan-journey.png
│   ├── route-result.png
│   ├── route-comparison.png
│   ├── network-map.png
│   ├── network-connections.png
│   ├── statistics.png
│   ├── dark-mode.png
│   ├── mobile.png
│   └── algorithm-diagram.png
│
└── README.md
```

### Backend — `server.cpp`

The C++ server contains a `Graph` class built on an adjacency list:

```
Graph
├── adjacencyList   → unordered_map<string, vector<Edge>>
├── stopNames       → vector<string>
├── addStop()
├── addRoute()          (bidirectional)
├── findShortestPath()  → Dijkstra (distance weight)
├── findCheapestPath()  → Dijkstra (fare weight)
├── findAnyPath()       → DFS (recursive)
├── getStatistics()
├── searchStops()
└── getAllBuses()
```

### Frontend — `index.html`

The frontend runs in **Demo Mode** with all 12 stops and 19 routes built in as JavaScript objects — no server required to open and test it. When the C++ backend is running, it connects to `http://localhost:8080` for live data.

---

## 🔌 API Reference

| Method | Endpoint | Params | Description |
|--------|----------|--------|-------------|
| GET | `/stops` | — | All bus stop names |
| GET | `/graph` | — | Full adjacency list |
| GET | `/route` | `from`, `to`, `algo` | Find route (`dijkstra` / `cheapest` / `dfs`) |
| GET | `/statistics` | — | Stop, route, bus, distance stats |
| GET | `/search` | `q` | Filter stops by name |
| GET | `/buses` | — | All bus service names |
| POST | `/addstop` | `name` | Add a new stop |
| POST | `/addroute` | `from`, `to`, `distance`, `fare`, `bus` | Add a new route |
| GET | `/health` | — | Server health check + timestamp |

---

## 🗺️ Pre-loaded Network

### 12 Bus Stops

| | | |
|---|---|---|
| 🏢 Central Station | 🛍️ City Mall | 🎓 University Campus |
| 🏥 General Hospital | ✈️ International Airport | 🏖️ Seaside Beach |
| 🌳 City Park | 🏟️ Sports Stadium | 💻 Tech Valley |
| 🏛️ Old Town Square | 🏦 Financial District | 🚂 Railway Terminal |

### 19 Bidirectional Routes (sample)

| From | To | Distance | Fare | Bus |
|---|---|---|---|---|
| Central Station | City Mall | 2.5 km | Rs. 15 | Metro Express 1 |
| Central Station | International Airport | 18.0 km | Rs. 60 | Airport Express |
| Seaside Beach | International Airport | 4.5 km | Rs. 16 | Beach Shuttle 10 |
| Tech Valley | Financial District | 4.3 km | Rs. 25 | Business Tech Link |
| … | … | … | … | … |

---

## 🚀 Getting Started

### Option A — Frontend Only (Demo Mode)

No installation needed. Just open `index.html` in any modern browser. All 12 stops and 19 routes are built into the page.

```bash
# Just double-click index.html, or serve it with Python for best results:
python -m http.server 8000
# Then open: http://localhost:8000
```

### Option B — Full Stack (C++ Backend)

#### 1. Clone the Repository

```bash
git clone https://github.com/YOUR_USERNAME/SmartTransit.git
cd SmartTransit
```

#### 2. Download cpp-httplib

Visit [https://github.com/yhirose/cpp-httplib](https://github.com/yhirose/cpp-httplib), download `httplib.h` and place it in the project root next to `server.cpp`.

#### 3. Compile

**Linux / Mac:**
```bash
g++ -std=c++11 -o server server.cpp -lpthread
```

**Windows (MinGW):**
```bash
g++ -std=c++11 -o server.exe server.cpp -lws2_32
```

**Windows (Visual Studio):**
```bash
cl /EHsc /std:c++11 server.cpp
```

#### 4. Run the Server

**Linux / Mac:**
```bash
./server
```

**Windows:**
```bash
server.exe
```

You should see the startup banner in your terminal:

![Server Running](screenshots/server-running.png)
> 💡 *Take a screenshot of your terminal showing the startup output and save it as `screenshots/server-running.png`*

The server starts on `http://localhost:8080`.

#### 5. Open the Frontend

Open `index.html` in your browser. The status indicator in the sidebar will show the live connection.

---

## 🎯 How to Use

### Plan a Journey

1. Open the **Plan Journey** tab (default)
2. Select **Starting From** and **Going To** stops
3. Use the ↕ button to swap stops instantly
4. Click one of the three option cards:
   - ⚡ **Shortest Distance** — fewest kilometers
   - 💰 **Lowest Fare** — cheapest ticket price
   - 🕐 **Any Available Route** — quick DFS path
5. The result card shows your full route, buses to board, and trip stats

### Compare Routes

1. Click **Compare Routes** in the sidebar
2. Select origin and destination
3. Click **Compare All Options**
4. The table shows all three algorithms side by side, with best values highlighted

### Save & Revisit

- Click **Save Route** on any result to bookmark it under **Saved Routes**
- Your last 5 searches appear as **Recent Searches** for one-click re-use
- Dark/Light mode preference is saved automatically

---

## 🐛 Troubleshooting

| Problem | Solution |
|---|---|
| Server won't start | Check port 8080 isn't in use; verify `httplib.h` is present; confirm g++ supports C++11 (`g++ --version`) |
| Frontend shows "Demo Mode" | The C++ server isn't running — this is normal, demo mode works without it |
| Route not found | Check both stops exist; verify there is a connected path between them |
| Map doesn't load | Check internet connection — Leaflet tiles load from OpenStreetMap CDN |
| Compiler error on Windows | Use MinGW with `-lws2_32` flag; cpp-httplib requires Winsock |

---

## 📈 Possible Enhancements

- [ ] Real-time bus tracking via GPS integration
- [ ] Time-based routing (scheduled departures/arrivals)
- [ ] Multi-modal transport (bus + metro + walking)
- [ ] User accounts with route history
- [ ] Bellman-Ford for negative-weight edge support
- [ ] A\* heuristic for faster pathfinding on large networks
- [ ] Mobile app wrapper (React Native / Flutter)
- [ ] Wheelchair-accessible route filtering
- [ ] Export route as PDF / share link

---

## 👤 Author

Created as a **Data Structures & Algorithms Semester Project**

---

## 🙏 Acknowledgments

- [cpp-httplib](https://github.com/yhirose/cpp-httplib) by Yuji Hirose — single-header C++ HTTP server
- [Leaflet.js](https://leafletjs.com/) — interactive maps
- [Chart.js](https://www.chartjs.org/) — network statistics charts
- [OpenStreetMap](https://www.openstreetmap.org/) — map tile data
- [Google Fonts — Inter](https://fonts.google.com/specimen/Inter) — UI typeface

---

## 📝 License

This project is created for **educational purposes** as a semester project for a Data Structures & Algorithms course. Not intended for commercial use.

---

<p align="center">Made with ❤️ as a DSA Semester Project</p>
