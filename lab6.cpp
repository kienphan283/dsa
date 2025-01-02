#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <algorithm>
#include <limits>
#include <cmath>
#include <unordered_map>
using namespace std;

class Graph {
private:
    int V;
    vector<vector<int>> adjMatrix;
    vector<vector<pair<int, int>>> adjList;
    bool isDirected;
    bool isWeighted;

    void DFSUtil(int v, vector<bool>& visited) {
        visited[v] = true;
        cout << v << " ";
        for(auto& adj : adjList[v]) {
            if(!visited[adj.first]) DFSUtil(adj.first, visited);
        }
    }

    bool hasCycleUtil(int v, vector<bool>& visited, vector<bool>& recStack) {
        visited[v] = true;
        recStack[v] = true;
        for(auto& adj : adjList[v]) {
            if(!visited[adj.first] && hasCycleUtil(adj.first, visited, recStack))
                return true;
            else if(recStack[adj.first]) return true;
        }
        recStack[v] = false;
        return false;
    }

    void bridgeUtil(int u, vector<int>& disc, vector<int>& low, vector<int>& parent, vector<pair<int,int>>& bridges) {
        static int time = 0;
        disc[u] = low[u] = ++time;
        
        for(auto& adj : adjList[u]) {
            int v = adj.first;
            if(disc[v] == -1) {
                parent[v] = u;
                bridgeUtil(v, disc, low, parent, bridges);
                low[u] = min(low[u], low[v]);
                if(low[v] > disc[u]) bridges.push_back({u, v});
            }
            else if(v != parent[u]) low[u] = min(low[u], disc[v]);
        }
    }

    int findParent(vector<int>& parent, int i) {
        if(parent[i] == i) return i;
        return parent[i] = findParent(parent, parent[i]);
    }

    void unionSets(vector<int>& parent, vector<int>& rank, int x, int y) {
        int px = findParent(parent, x);
        int py = findParent(parent, y);
        if(rank[px] < rank[py]) parent[px] = py;
        else if(rank[px] > rank[py]) parent[py] = px;
        else {
            parent[py] = px;
            rank[px]++;
        }
    }

public:
    Graph(int vertices, bool directed = false, bool weighted = false) 
        : V(vertices), isDirected(directed), isWeighted(weighted) {
        adjMatrix.resize(V, vector<int>(V, 0));
        adjList.resize(V);
    }

    void addEdge(int u, int v, int weight = 1) {
        adjMatrix[u][v] = weight;
        adjList[u].push_back({v, weight});
        if(!isDirected) {
            adjMatrix[v][u] = weight;
            adjList[v].push_back({u, weight});
        }
    }

    void DFS(int start) {
        vector<bool> visited(V, false);
        cout << "DFS traversal: ";
        DFSUtil(start, visited);
        cout << endl;
    }

    void DFSIterative(int start) {
        vector<bool> visited(V, false);
        stack<int> s;
        s.push(start);
        cout << "DFS iterative: ";
        while(!s.empty()) {
            int v = s.top(); s.pop();
            if(!visited[v]) {
                visited[v] = true;
                cout << v << " ";
                for(auto it = adjList[v].rbegin(); it != adjList[v].rend(); ++it) {
                    if(!visited[it->first]) s.push(it->first);
                }
            }
        }
        cout << endl;
    }

    void BFS(int start) {
        vector<bool> visited(V, false);
        queue<int> q;
        visited[start] = true;
        q.push(start);
        cout << "BFS traversal: ";
        while(!q.empty()) {
            int v = q.front(); q.pop();
            cout << v << " ";
            for(auto& adj : adjList[v]) {
                if(!visited[adj.first]) {
                    visited[adj.first] = true;
                    q.push(adj.first);
                }
            }
        }
        cout << endl;
    }

    bool detectCycle() {
        vector<bool> visited(V, false);
        vector<bool> recStack(V, false);
        for(int i = 0; i < V; i++) {
            if(!visited[i] && hasCycleUtil(i, visited, recStack))
                return true;
        }
        return false;
    }

    void dijkstra(int src) {
        vector<int> dist(V, INT_MAX);
        set<pair<int,int>> pq;
        dist[src] = 0;
        pq.insert({0, src});

        while(!pq.empty()) {
            int u = pq.begin()->second;
            pq.erase(pq.begin());
            for(auto& adj : adjList[u]) {
                int v = adj.first;
                int weight = adj.second;
                if(dist[v] > dist[u] + weight) {
                    if(dist[v] != INT_MAX) 
                        pq.erase(pq.find({dist[v], v}));
                    dist[v] = dist[u] + weight;
                    pq.insert({dist[v], v});
                }
            }
        }
        for(int i = 0; i < V; i++)
            cout << "Distance to " << i << ": " << dist[i] << endl;
    }

    void findConnectedComponents() {
        vector<bool> visited(V, false);
        int components = 0;
        for(int i = 0; i < V; i++) {
            if(!visited[i]) {
                cout << "Component " << ++components << ": ";
                DFSUtil(i, visited);
                cout << endl;
            }
        }
        cout << "Total components: " << components << endl;
    }

    void findBridges() {
        vector<int> disc(V, -1), low(V, -1), parent(V, -1);
        vector<pair<int,int>> bridges;
        for(int i = 0; i < V; i++)
            if(disc[i] == -1) bridgeUtil(i, disc, low, parent, bridges);
        cout << "Bridges: ";
        for(auto& bridge : bridges)
            cout << "(" << bridge.first << ", " << bridge.second << ") ";
        cout << endl;
    }

    vector<double> pageRank(int iterations = 100) {
        vector<double> rank(V, 1.0/V);
        double damping = 0.85;
        for(int iter = 0; iter < iterations; iter++) {
            vector<double> newRank(V, 0);
            for(int i = 0; i < V; i++) {
                for(auto& adj : adjList[i]) {
                    newRank[adj.first] += rank[i] / adjList[i].size();
                }
            }
            for(int i = 0; i < V; i++)
                newRank[i] = (1-damping)/V + damping*newRank[i];
            rank = newRank;
        }
        return rank;
    }

    vector<int> shortestPathAStar(int start, int goal, const vector<pair<int,int>>& coordinates) {
        auto heuristic = [&](int node) {
            int dx = coordinates[node].first - coordinates[goal].first;
            int dy = coordinates[node].second - coordinates[goal].second;
            return sqrt(dx*dx + dy*dy);
        };

        vector<double> g_score(V, INT_MAX);
        vector<double> f_score(V, INT_MAX);
        vector<int> came_from(V, -1);
        set<pair<double,int>> openSet;
        
        g_score[start] = 0;
        f_score[start] = heuristic(start);
        openSet.insert({f_score[start], start});

        while(!openSet.empty()) {
            int current = openSet.begin()->second;
            if(current == goal) {
                vector<int> path;
                while(current != -1) {
                    path.push_back(current);
                    current = came_from[current];
                }
                reverse(path.begin(), path.end());
                return path;
            }
            openSet.erase(openSet.begin());

            for(auto& adj : adjList[current]) {
                int neighbor = adj.first;
                double tentative_g = g_score[current] + adj.second;
                
                if(tentative_g < g_score[neighbor]) {
                    came_from[neighbor] = current;
                    g_score[neighbor] = tentative_g;
                    f_score[neighbor] = g_score[neighbor] + heuristic(neighbor);
                    openSet.insert({f_score[neighbor], neighbor});
                }
            }
        }
        return vector<int>();
    }

    void louvainCommunityDetection() {
        vector<int> communities(V);
        for(int i = 0; i < V; i++) communities[i] = i;
        
        bool improvement = true;
        while(improvement) {
            improvement = false;
            for(int i = 0; i < V; i++) {
                int current_community = communities[i];
                unordered_map<int, double> community_gains;
                
                for(auto& adj : adjList[i]) {
                    int neighbor_community = communities[adj.first];
                    community_gains[neighbor_community] += adj.second;
                }
                
                double max_gain = 0;
                int best_community = current_community;
                
                for(auto& gain : community_gains) {
                    if(gain.second > max_gain) {
                        max_gain = gain.second;
                        best_community = gain.first;
                    }
                }
                
                if(best_community != current_community) {
                    communities[i] = best_community;
                    improvement = true;
                }
            }
        }
        
        cout << "Communities: ";
        for(int i = 0; i < V; i++)
            cout << i << "->" << communities[i] << " ";
        cout << endl;
    }
};

class DeliveryRouter {
private:
    int V;
    vector<vector<pair<int,int>>> routes;
    vector<pair<double,double>> locations;

public:
    DeliveryRouter(int vertices) : V(vertices) {
        routes.resize(V);
        locations.resize(V);
    }

    void addRoute(int u, int v, int time) {
        routes[u].push_back({v, time});
        routes[v].push_back({u, time});
    }

    void setLocation(int vertex, double x, double y) {
        locations[vertex] = {x, y};
    }

    vector<int> optimizeRoute(int start) {
        vector<bool> visited(V, false);
        vector<int> path;
        path.push_back(start);
        visited[start] = true;
        
        for(int i = 1; i < V; i++) {
            int next = -1;
            double minDist = numeric_limits<double>::max();
            int current = path.back();
            
            for(auto& route : routes[current]) {
                if(!visited[route.first]) {
                    double dx = locations[current].first - locations[route.first].first;
                    double dy = locations[current].second - locations[route.first].second;
                    double dist = sqrt(dx*dx + dy*dy) * route.second;
                    if(dist < minDist) {
                        minDist = dist;
                        next = route.first;
                    }
                }
            }
            if(next != -1) {
                path.push_back(next);
                visited[next] = true;
            }
        }
        return path;
    }
};

class SocialNetwork {
    int V;
    vector<vector<int>> friends;
    vector<double> influence;

public:
    SocialNetwork(int vertices) : V(vertices) {
        friends.resize(V);
        influence.resize(V);
    }

    void addFriendship(int u, int v) {
        friends[u].push_back(v);
        friends[v].push_back(u);
    }

    vector<int> findInfluencers() {
        vector<int> influencers;
        for(int i = 0; i < V; i++) {
            influence[i] = friends[i].size();
            if(influence[i] > V/10) 
                influencers.push_back(i);
        }
        return influencers;
    }
};

class TrafficSystem {
private:
   int V;
   vector<vector<pair<int,int>>> roads;
   vector<int> signalTiming;

public:
   TrafficSystem(int vertices) : V(vertices) {
       roads.resize(V);
       signalTiming.resize(V, 30);
   }

   void addRoad(int u, int v, int congestion) {
       roads[u].push_back({v, congestion});
       roads[v].push_back({u, congestion});
   }

   void optimizeSignals() {
       for(int i = 0; i < V; i++) {
           int totalFlow = 0;
           for(auto& road : roads[i])
               totalFlow += road.second;
           signalTiming[i] = max(20, min(60, totalFlow/10));
       }
   }
};

class RecommendationEngine {
private:
   int users, items;
   vector<vector<double>> ratings;

public:
   RecommendationEngine(int u, int i) : users(u), items(i) {
       ratings.resize(users, vector<double>(items, 0));
   }
   
   void addRating(int user, int item, double rating) {
       ratings[user][item] = rating;
   }

   vector<double> getRecommendations(int user) {
       vector<double> recommendations(items);
       for(int i = 0; i < items; i++) {
           if(ratings[user][i] == 0) {
               double sum = 0, count = 0;
               for(int j = 0; j < users; j++) {
                   if(j != user && ratings[j][i] > 0) {
                       sum += ratings[j][i];
                       count++;
                   }
               }
               recommendations[i] = count > 0 ? sum/count : 0;
           }
       }
       return recommendations;
   }
};

class NetworkOptimizer {
private:
   int V;
   vector<vector<pair<int,int>>> connections;

public:
   NetworkOptimizer(int vertices) : V(vertices) {
       connections.resize(V);
   }

   void addConnection(int u, int v, int bandwidth) {
       connections[u].push_back({v, bandwidth});
       connections[v].push_back({u, bandwidth});
   }

   vector<pair<int,int>> optimizeTopology() {
       vector<pair<int,int>> optimizedLinks;
       vector<bool> visited(V, false);
       priority_queue<pair<int,pair<int,int>>> pq;
       
       visited[0] = true;
       for(auto& conn : connections[0])
           pq.push({conn.second, {0, conn.first}});
           
       while(!pq.empty() && optimizedLinks.size() < V-1) {
           int u = pq.top().second.first;
           int v = pq.top().second.second;
           pq.pop();
           
           if(visited[v]) continue;
           visited[v] = true;
           optimizedLinks.push_back({u, v});
           
           for(auto& conn : connections[v]) {
               if(!visited[conn.first])
                   pq.push({conn.second, {v, conn.first}});
           }
       }
       return optimizedLinks;
   }
};

class GamePathfinder {
private:
   int rows, cols;
   vector<vector<bool>> grid;
   vector<pair<int,int>> directions = {{-1,0}, {1,0}, {0,-1}, {0,1}};

public:
   GamePathfinder(int r, int c) : rows(r), cols(c) {
       grid.resize(rows, vector<bool>(cols, false));
   }

   void addObstacle(int x, int y) {
       grid[x][y] = true;
   }

   vector<pair<int,int>> findPath(pair<int,int> start, pair<int,int> goal) {
       queue<pair<int,int>> q;
       vector<vector<bool>> visited(rows, vector<bool>(cols, false));
       vector<vector<pair<int,int>>> parent(rows, vector<pair<int,int>>(cols, {-1,-1}));
       
       q.push(start);
       visited[start.first][start.second] = true;
       
       while(!q.empty()) {
           auto [x, y] = q.front();
           q.pop();
           
           if(x == goal.first && y == goal.second) {
               vector<pair<int,int>> path;
               auto current = goal;
               while(current != start) {
                   path.push_back(current);
                   current = parent[current.first][current.second];
               }
               path.push_back(start);
               reverse(path.begin(), path.end());
               return path;
           }
           
           for(auto& dir : directions) {
               int nx = x + dir.first;
               int ny = y + dir.second;
               if(nx >= 0 && nx < rows && ny >= 0 && ny < cols && !grid[nx][ny] && !visited[nx][ny]) {
                   visited[nx][ny] = true;
                   parent[nx][ny] = {x, y};
                   q.push({nx, ny});
               }
           }
       }
       return vector<pair<int,int>>();
   }
};

int main() {
    int choice = 0, V;
    Graph* g = nullptr;
    
    while(true) {
        cout << "\nGRAPH ALGORITHMS\n";
        for(int i = 1; i <= 16; i++)
            cout << i << ". Exercise " << i << endl;
        cout << "0. Exit\n";
        cout << "Choice: ";
        cin >> choice;
        
        if(choice == 0) break;
        
        if(choice >= 1 && choice <= 16) {
            if(!g) {
                cout << "Vertices: ";
                cin >> V;
                g = new Graph(V, choice > 10);
            }
            
            switch(choice) {
                case 1: {
                    int u, v;
                    cout << "Edge (u v): ";
                    cin >> u >> v;
                    g->addEdge(u, v);
                    break;
                }
                case 2: {
                    int start;
                    cout << "Start vertex: ";
                    cin >> start;
                    g->DFS(start);
                    break;
                }
                case 3: {
                    int start;
                    cout << "Start vertex: ";
                    cin >> start;
                    g->BFS(start);
                    break;
                }
                case 4: {
                    if(g->detectCycle())
                        cout << "Cycle detected\n";
                    else
                        cout << "No cycle\n";
                    break;
                }
                case 5: {
                    int src;
                    cout << "Source: ";
                    cin >> src;
                    g->dijkstra(src);
                    break;
                }
                case 6:
                    g->findConnectedComponents();
                    break;
                case 7:
                    g->findBridges();
                    break;
                case 8:
                    g->louvainCommunityDetection();
                    break;
                case 9: {
                    vector<double> ranks = g->pageRank();
                    for(int i = 0; i < ranks.size(); i++)
                        cout << "Page " << i << ": " << ranks[i] << endl;
                    break;
                }
                case 10: {
                    vector<pair<int,int>> coords(V);
                    for(int i = 0; i < V; i++) {
                        cout << "Coordinates for vertex " << i << " (x y): ";
                        cin >> coords[i].first >> coords[i].second;
                    }
                    int start, goal;
                    cout << "Start and goal vertices: ";
                    cin >> start >> goal;
                    vector<int> path = g->shortestPathAStar(start, goal, coords);
                    cout << "Path: ";
                    for(int v : path) cout << v << " ";
                    cout << endl;
                    break;
                }
                case 11: {
                    DeliveryRouter* router = new DeliveryRouter(V);
                    int E;
                    cout << "Number of routes: ";
                    cin >> E;
                    for(int i = 0; i < E; i++) {
                        int u, v, t;
                        cout << "Route " << i << " (from to time): ";
                        cin >> u >> v >> t;
                        router->addRoute(u, v, t);
                    }
                    for(int i = 0; i < V; i++) {
                        double x, y;
                        cout << "Location " << i << " (x y): ";
                        cin >> x >> y;
                        router->setLocation(i, x, y);
                    }
                    int start;
                    cout << "Start point: ";
                    cin >> start;
                    vector<int> path = router->optimizeRoute(start);
                    cout << "Optimized route: ";
                    for(int p : path) cout << p << " ";
                    cout << endl;
                    delete router;
                    break;
                }

                case 12: {
                    SocialNetwork* social = new SocialNetwork(V);
                    int E;
                    cout << "Number of friendships: ";
                    cin >> E;
                    for(int i = 0; i < E; i++) {
                        int u, v;
                        cout << "Friendship " << i << " (user1 user2): ";
                        cin >> u >> v;
                        social->addFriendship(u, v);
                    }
                    vector<int> influencers = social->findInfluencers();
                    cout << "Influencers: ";
                    for(int i : influencers) cout << i << " ";
                    cout << endl;
                    delete social;
                    break;
                }
                
                case 13: {
                    TrafficSystem* traffic = new TrafficSystem(V);
                    int E;
                    cout << "Number of roads: ";
                    cin >> E;
                    for(int i = 0; i < E; i++) {
                        int u, v, c;
                        cout << "Road " << i << " (from to congestion): ";
                        cin >> u >> v >> c;
                        traffic->addRoad(u, v, c);
                    }
                    traffic->optimizeSignals();
                    delete traffic;
                    break;
                    }

                    case 14: {
                    int users, items;
                    cout << "Number of users and items: ";
                    cin >> users >> items;
                    RecommendationEngine* engine = new RecommendationEngine(users, items);
                    int R;
                    cout << "Number of ratings: ";
                    cin >> R;
                    for(int i = 0; i < R; i++) {
                        int u, item;
                        double rating;
                        cout << "Rating " << i << ": ";
                        cin >> u >> item >> rating;
                        engine->addRating(u, item, rating);
                    }
                    int targetUser;
                    cout << "Target user: ";
                    cin >> targetUser;
                    vector<double> recs = engine->getRecommendations(targetUser);
                    cout << "Recommendations: ";
                    for(double r : recs) cout << r << " ";
                    cout << endl;
                    delete engine;
                    break;
                    }

                    case 15: {
                    NetworkOptimizer* network = new NetworkOptimizer(V);
                    int E;
                    cout << "Number of connections: ";
                    cin >> E;
                    for(int i = 0; i < E; i++) {
                        int u, v, b;
                        cout << "Connection " << i << ": ";
                        cin >> u >> v >> b;
                        network->addConnection(u, v, b);
                    }
                    auto optimal = network->optimizeTopology();
                    cout << "Optimal connections:\n";
                    for(auto& p : optimal)
                        cout << p.first << " - " << p.second << endl;
                    delete network;
                    break;
                    }

                    case 16: {
                    int r, c;
                    cout << "Grid size (rows cols): ";
                    cin >> r >> c;
                    GamePathfinder* game = new GamePathfinder(r, c);
                    int O;
                    cout << "Number of obstacles: ";
                    cin >> O;
                    for(int i = 0; i < O; i++) {
                        int x, y;
                        cout << "Obstacle " << i << ": ";
                        cin >> x >> y;
                        game->addObstacle(x, y);
                    }
                    int sx, sy, gx, gy;
                    cout << "Start (x y): ";
                    cin >> sx >> sy;
                    cout << "Goal (x y): ";
                    cin >> gx >> gy;
                    auto path = game->findPath({sx,sy}, {gx,gy});
                    cout << "Path: ";
                    for(auto& p : path)
                        cout << "(" << p.first << "," << p.second << ") ";
                    cout << endl;
                    delete game;
                    break;
                    }
                default:
                    cout << "Implementation in progress\n";
            }
        } else {
            cout << "Invalid choice\n";
        }
    }
    
    delete g;
    return 0;
}