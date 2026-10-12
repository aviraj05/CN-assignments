#include <iostream>
#include <vector>
#include <iomanip>
using namespace std;

int main() {
    int N;

    cout << "Enter the number of nodes: ";
    cin >> N;

    vector<vector<int>> cost(N, vector<int>(N));
    vector<vector<int>> dist(N, vector<int>(N));

    cout << "Enter the cost matrix (-1 for no direct link):\n";

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            if (i == j) {
                cost[i][j] = 0;
            } else {
                int c;
                cin >> c;

                if (c == -1)
                    cost[i][j] = 9999;
                else
                    cost[i][j] = c;
            }
        }
    }

    
    dist = cost;


    for (int k = 0; k < N; k++) {
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                if (dist[i][k] != 9999 &&
                    dist[k][j] != 9999 &&
                    dist[i][k] + dist[k][j] < dist[i][j]) {

                    dist[i][j] = dist[i][k] + dist[k][j];
                }
            }
        }
    }

    // Display the routing table for each node
    for (int i = 0; i < N; i++) {
        cout << "\nRouting Table for Node " << i << ":\n";
        cout << "Destination\tMinimum Cost\n";

        for (int j = 0; j < N; j++) {
            cout << j << "\t\t";

            if (dist[i][j] == 9999)
                cout << "INF";
            else
                cout << dist[i][j];

            cout << '\n';
        }
    }

    return 0;
}
