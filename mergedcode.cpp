#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <limits>
using namespace std;

const int INF = numeric_limits<int>::max();

// Function 1: Shelter-to-Zone Connectivity Analysis (Floyd-Warshall)
void floydWarshall(vector<vector<int>>& graph) {
    int V = graph.size();
    vector<vector<int>> dist = graph;

    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                if (dist[i][k] != INF && dist[k][j] != INF && dist[i][j] > dist[i][k] + dist[k][j]) {
                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    cout << "Shortest path matrix:" << endl;
    for (const auto& row : dist) {
        for (int val : row) {
            if (val == INF) cout << "INF ";
            else cout << val << " ";
        }
        cout << endl;
    }
}

// Function 2: Task Scheduling for Rescue Operations (Merge Sort)
struct Task {
    string name;
    int deadline;
};

void merge(vector<Task>& tasks, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<Task> L(n1), R(n2);
    for (int i = 0; i < n1; ++i) L[i] = tasks[left + i];
    for (int i = 0; i < n2; ++i) R[i] = tasks[mid + 1 + i];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].deadline <= R[j].deadline) {
            tasks[k++] = L[i++];
        } else {
            tasks[k++] = R[j++];
        }
    }

    while (i < n1) tasks[k++] = L[i++];
    while (j < n2) tasks[k++] = R[j++];
}

void mergeSort(vector<Task>& tasks, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(tasks, left, mid);
        mergeSort(tasks, mid + 1, right);
        merge(tasks, left, mid, right);
    }
}

// Function 3: Flood Path Prediction (BFS)
void floodPrediction(const vector<vector<int>>& graph, vector<int> sources) {
    int V = graph.size();
    vector<int> floodedTime(V, -1);
    queue<int> q;

    for (int source : sources) {
        floodedTime[source] = 0;
        q.push(source);
    }

    while (!q.empty()) {
        int node = q.front();
        q.pop();

        for (int neighbor = 0; neighbor < V; ++neighbor) {
            if (graph[node][neighbor] && floodedTime[neighbor] == -1) {
                floodedTime[neighbor] = floodedTime[node] + 1;
                q.push(neighbor);
            }
        }
    }

    cout << "Flood times for regions:" << endl;
    for (int i = 0; i < V; ++i) {
        cout << "Region " << i << ": ";
        if (floodedTime[i] == -1) cout << "Not Flooded";
        else cout << "Flooded at time " << floodedTime[i];
        cout << endl;
    }
}

// Main function with menu
int main() {
    int choice;
    cout << "Select an operation:" << endl;
    cout << "1. Shelter-to-Zone Connectivity Analysis (Floyd-Warshall)" << endl;
    cout << "2. Task Scheduling for Rescue Operations (Merge Sort)" << endl;
    cout << "3. Flood Path Prediction (BFS)" << endl;
    cout << "Enter your choice: ";
    cin >> choice;

    switch (choice) {
        case 1: {
            int V;
            cout << "Enter number of nodes: ";
            cin >> V;
            vector<vector<int>> graph(V, vector<int>(V));
            cout << "Enter adjacency matrix (use " << INF << " for no connection):" << endl;
            for (int i = 0; i < V; ++i) {
                for (int j = 0; j < V; ++j) {
                    cin >> graph[i][j];
                }
            }
            floydWarshall(graph);
            break;
        }

        case 2: {
            int n;
            cout << "Enter number of tasks: ";
            cin >> n;
            vector<Task> tasks(n);
            cout << "Enter tasks (name and deadline):" << endl;
            for (int i = 0; i < n; ++i) {
                cin >> tasks[i].name >> tasks[i].deadline;
            }
            mergeSort(tasks, 0, n - 1);
            cout << "Sorted tasks by deadline:" << endl;
            for (const auto& task : tasks) {
                cout << task.name << " - Deadline: " << task.deadline << endl;
            }
            break;
        }

        case 3: {
            int V, E, sourceCount;
            cout << "Enter number of regions: ";
            cin >> V;
            vector<vector<int>> graph(V, vector<int>(V, 0));
            cout << "Enter number of connections: ";
            cin >> E;
            cout << "Enter connections (u v):" << endl;
            for (int i = 0; i < E; ++i) {
                int u, v;
                cin >> u >> v;
                graph[u][v] = graph[v][u] = 1;
            }
            cout << "Enter number of flood sources: ";
            cin >> sourceCount;
            vector<int> sources(sourceCount);
            cout << "Enter flood source nodes:" << endl;
            for (int i = 0; i < sourceCount; ++i) {
                cin >> sources[i];
            }
            floodPrediction(graph, sources);
            break;
        }

        default:
            cout << "Invalid choice!" << endl;
    }

    return 0;
}
