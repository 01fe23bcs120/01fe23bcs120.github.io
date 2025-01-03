#include <iostream>
#include <vector>
#include <climits>
using namespace std;

#define INF INT_MAX
#define vert 4

void print(int dist[][vert]) {
    for (int i = 0; i < vert; i++) {
        for (int j = 0; j < vert; j++) {
            if (dist[i][j] == INF)
                cout << "INF ";
            else
                cout << dist[i][j] << " ";
        }
        cout << endl;
    }
}

void floyd(int dist[][vert]) {
    for (int k = 0; k < vert; k++) {
        for (int i = 0; i < vert; i++) {
            for (int j = 0; j < vert; j++) {
                if (dist[i][j] > dist[i][k] + dist[k][j] && dist[i][k] != INF && dist[k][j] != INF)
                    dist[i][j] = dist[i][k] + dist[k][j];
            }
        }
    }
    print(dist);
}

void fw_5() {
    int graph[vert][vert] = {{0, INF, 3, INF}, {2, 0, INF, INF}, {INF, 7, 0, 1}, {6, INF, INF, 0}};
    cout << "All pair shortest path between shelters and disaster zone: \n";
    floyd(graph);
}

void merge(vector<pair<int, int>> &b, vector<pair<int, int>> &c, vector<pair<int, int>> &a) {
    int i = 0, j = 0, k = 0, p = b.size(), q = c.size();
    while (i < p && j < q) {
        if (b[i].second >= c[j].second) {
            a[k] = b[i];
            i++;
        } else {
            a[k] = c[j];
            j++;
        }
        k++;
    }

    while (i < p) {
        a[k] = b[i];
        i++;
        k++;
    }
    while (j < q) {
        a[k] = c[j];
        j++;
        k++;
    }
}

void mergesort(vector<pair<int, int>> &a) {
    if (a.size() > 1) {
        int half = a.size() / 2;
        vector<pair<int, int>> b(a.begin(), a.begin() + half);
        vector<pair<int, int>> c(a.begin() + half, a.end());
        mergesort(b);
        mergesort(c);
        merge(b, c, a);
    }
}

void mergesort_8() {
    vector<pair<int, int>> tasks = {{1, 34}, {2, 0}, {3, 45}, {4, 6}, {5, 5}};
    cout << "Task number and their priority level: \n\nTask\tPriority\n\n";
    for (auto &pair : tasks) {
        cout << pair.first << " \t " << pair.second << endl;
    }
    cout << "\nOn sorting the tasks based on priority level: \n\nTask\tPriority\n\n";
    mergesort(tasks);
    for (auto &pair : tasks) {
        cout << pair.first << " \t " << pair.second << endl;
    }
}

void bfs(int m[10][10], int v, int source) {
    int queue[10], front = 0, rear = 0, visited[10];
    for (int i = 0; i < v; i++)
        visited[i] = 0;
    visited[source] = 1;
    queue[rear] = source;

    while (front <= rear) {
        int u = queue[front];
        front++;
        cout << u << " ";
        for (int i = 0; i < v; i++) {
            if (m[u][i] == 1 && visited[i] == 0) {
                visited[i] = 1;
                rear++;
                queue[rear] = i;
            }
        }
    }
}

void bfs_9() {
    int m[10][10] = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 1},
        {0, 0, 1, 0, 1},
        {1, 0, 1, 1, 0}};
    int v = 5;
    int source = 0;
    cout << "Connectivity of the road, thus allowing water flow in the following path (considering root source of flood is 0):\n ";
    bfs(m, v, source);
}

int main() {
    cout << "--- Floyd-Warshall Algorithm ---\n";
    fw_5();

    cout << "\n--- Merge Sort Tasks ---\n";
    mergesort_8();

    cout << "\n--- Breadth First Search ---\n";
    bfs_9();

    return 0;
}
