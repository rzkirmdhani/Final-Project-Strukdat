#include <iostream>
#include <vector>
#include <algorithm> // for transform function

using namespace std;

// Abstract Class Node
class Node {
public:
    Node(const string& nodeName) : name(nodeName) {}
    virtual ~Node() {}

    string getName() const {
        return name;
    }

protected:
    string name;
};

// Abstract Class Graph
class Graph {
public:
    virtual ~Graph() {}

    virtual void addNode(Node* node) = 0;
    virtual void addEdge(int node1Index, int node2Index) = 0;
    virtual void display() const = 0;
};

// Concrete Class GraphAdjacencyMatrix implementing Graph
class GraphAdjacencyMatrix : public Graph {
public:
    GraphAdjacencyMatrix(int size) : nodeCount(0), adjacencyMatrix(size, vector<int>(size, 0)) {}

    ~GraphAdjacencyMatrix() override {
        for (int i = 0; i < nodeCount; i++) {
            delete nodes[i];
        }
    }

    void addNode(Node* node) override {
        nodes.push_back(node);
        nodeCount++;
    }

    void addEdge(int node1Index, int node2Index) override {
        adjacencyMatrix[node1Index][node2Index] = 1;
        adjacencyMatrix[node2Index][node1Index] = 1;
    }

    void display() const override {
        cout << "Graph Rute Transportasi Umum (Adjacency Matrix):" << endl;

        for (int i = 0; i < nodeCount; i++) {
            cout << nodes[i]->getName() << " terhubung dengan: ";

            for (int j = 0; j < nodeCount; j++) {
                if (adjacencyMatrix[i][j] == 1) {
                    cout << nodes[j]->getName() << " ";
                }
            }

            cout << endl;
        }
    }

protected:
    int nodeCount;
    vector<Node*> nodes;
    vector<vector<int>> adjacencyMatrix;
};

class TransportationRoute {
public:
    TransportationRoute(const string& start, const string& end) : startLocation(start), endLocation(end) {}

    void displayRoute() const {
        cout << "Rute Transportasi dari " << startLocation << " ke " << endLocation << endl;
    }

private:
    string startLocation;
    string endLocation;
};

class RuteTransportasiUmum : public GraphAdjacencyMatrix {
public:
    RuteTransportasiUmum(int size) : GraphAdjacencyMatrix(size) {}

    void tampilkanRute(const string& lokasiAwal, const string& lokasiTujuan) {
        int indexAwal = findNodeIndex(lokasiAwal);
        int indexTujuan = findNodeIndex(lokasiTujuan);

        if (indexAwal != -1 && indexTujuan != -1) {
            vector<int> visited(nodeCount, 0);
            vector<int> path;
            bool found = false;

            dfs(indexAwal, indexTujuan, visited, path, found);

            if (found) {
                cout << "Rute dari " << lokasiAwal << " ke " << lokasiTujuan << ": ";
                for (int i : path) {
                    cout << nodes[i]->getName() << " ";
                }
                cout << endl;

                TransportationRoute route(lokasiAwal, lokasiTujuan);
                route.displayRoute();
            } else {
                cout << "Tidak ada rute dari " << lokasiAwal << " ke " << lokasiTujuan << endl;
            }
        } else {
            cout << "Lokasi awal atau tujuan tidak valid." << endl;
        }
    }

private:
    void dfs(int currentNode, int targetNode, vector<int>& visited, vector<int>& path, bool& found) {
        visited[currentNode] = 1;
        path.push_back(currentNode);

        if (currentNode == targetNode) {
            found = true;
            return;
        }

        for (int i = 0; i < nodeCount; ++i) {
            if (adjacencyMatrix[currentNode][i] == 1 && !visited[i]) {
                dfs(i, targetNode, visited, path, found);
                if (found) {
                    return;
                }
            }
        }

        path.pop_back();
    }

    int findNodeIndex(const string& nodeName) {
    // Convert the input and node names to lowercase for case-insensitive comparison
    string lowerNodeName = nodeName;
    transform(lowerNodeName.begin(), lowerNodeName.end(), lowerNodeName.begin(), ::tolower);

    for (int i = 0; i < nodeCount; ++i) {
        string currentNodeName = nodes[i]->getName();
        transform(currentNodeName.begin(), currentNodeName.end(), currentNodeName.begin(), ::tolower);

        cout << "Comparing: " << lowerNodeName << " with " << currentNodeName << endl;

        if (currentNodeName == lowerNodeName) {
            return i;
        }
    }
    return -1;
}

};

int main() {
    RuteTransportasiUmum transportasiUmum(10);

    transportasiUmum.addNode(new Node("ITS")); //0
    transportasiUmum.addNode(new Node("UNAIR")); //1
    transportasiUmum.addNode(new Node("GALAXY MALL")); //2
    transportasiUmum.addNode(new Node("TUNJUNGAN PLAZA")); //3
    transportasiUmum.addNode(new Node("GWALK")); //4
    transportasiUmum.addNode(new Node("UNNESA")); //5
    transportasiUmum.addNode(new Node("JODER")); //6
    transportasiUmum.addNode(new Node("SURAMADU")); //7
    transportasiUmum.addNode(new Node("BEBEK SINJAY")); //8
    transportasiUmum.addNode(new Node("RUMAH SAKIT SUTOMO")); //9

    transportasiUmum.addEdge(0, 1); // ITS - UNAIR
    transportasiUmum.addEdge(1, 2); // UNAIR - GALAXY MALL
    transportasiUmum.addEdge(2, 3); // GALAXY MALL - TUNJUNGAN PLAZA
    transportasiUmum.addEdge(3, 4); // TUNJUNGAN PLAZA - GWALK
    transportasiUmum.addEdge(4, 5); // GWALK - UNNESA
    transportasiUmum.addEdge(0, 6); // ITS - JODER
    transportasiUmum.addEdge(6, 3); // JODER - GALAXY MALL
    transportasiUmum.addEdge(3, 7); // TUNJUNGAN PLAZA - SURAMADU
    transportasiUmum.addEdge(7, 8); // SURAMADU - BEBEK SINJAY
    transportasiUmum.addEdge(1, 9); // UNAIR - SUTOMO
    transportasiUmum.addEdge(9, 7); // SUTOMO SURAMADU

    transportasiUmum.display();

    transportasiUmum.display();

    string lokasiAwal, lokasiTujuan;
    cout << "Masukkan lokasi awal: ";
    getline(cin, lokasiAwal);

    cout << "Masukkan lokasi tujuan: ";
    getline(cin, lokasiTujuan);

    transportasiUmum.tampilkanRute(lokasiAwal, lokasiTujuan);

    return 0;
}
