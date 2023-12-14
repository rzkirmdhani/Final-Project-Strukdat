#include <iostream>
#include <vector>
#include <algorithm> // for transform function
#include <limits>    // for clear buffer
#include <climits>
using namespace std;

// Kelas Abstract Node
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

// Kelas Abstract Graph
class Graph {
public:
    virtual ~Graph() {}

    virtual void addNode(Node* node) = 0;
    virtual void addEdge(int node1Index, int node2Index) = 0;
    virtual void display() const = 0;
};

// Kelas Concrete GraphAdjacencyMatrix yang mengimplementasikan Graph
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

    // Fungsi untuk menemukan indeks node berdasarkan namanya (case-insensitive)
    int findNodeIndex(const string& nodeName) {
        string lowerNodeName = nodeName;
        transform(lowerNodeName.begin(), lowerNodeName.end(), lowerNodeName.begin(), ::tolower);

        for (int i = 0; i < nodeCount; ++i) {
            string currentNodeName = nodes[i]->getName();
            transform(currentNodeName.begin(), currentNodeName.end(), currentNodeName.begin(), ::tolower);

            if (currentNodeName == lowerNodeName) {
                return i;
            }
        }
        return -1;
    }

protected:
    int nodeCount;
    vector<Node*> nodes;
    vector<vector<int>> adjacencyMatrix;
};

// Kelas TransportationRoute untuk menampilkan rute
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

// Kelas RuteTransportasiUmum yang merupakan turunan dari GraphAdjacencyMatrix
class RuteTransportasiUmum : public GraphAdjacencyMatrix {
public:
    RuteTransportasiUmum(int size) : GraphAdjacencyMatrix(size) {}

    // Fungsi untuk menampilkan rute antara dua lokasi menggunakan algoritma Dijkstra
    void tampilkanRute(const string& lokasiAwal, const string& lokasiTujuan) {
        int indexAwal = findNodeIndex(lokasiAwal);
        int indexTujuan = findNodeIndex(lokasiTujuan);

        if (indexAwal != -1 && indexTujuan != -1) {
            vector<int> path;
            dijkstra(indexAwal, indexTujuan, path);

            if (!path.empty()) {
                cout << "Rute dari " << lokasiAwal << " ke " << lokasiTujuan << ": ";
                for (int i : path) {
                    cout << nodes[i]->getName() << " >> ";
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
    // Fungsi untuk menjalankan algoritma Dijkstra untuk mencari jalur terpendek
    void dijkstra(int startNode, int targetNode, vector<int>& path) {
        vector<int> distance(nodeCount, INT_MAX);
        vector<int> previous(nodeCount, -1);
        vector<bool> visited(nodeCount, false);

        distance[startNode] = 0;

        for (int count = 0; count < nodeCount - 1; ++count) {
            int minDistance = INT_MAX;
            int minIndex = -1;

            for (int i = 0; i < nodeCount; ++i) {
                if (!visited[i] && distance[i] < minDistance) {
                    minDistance = distance[i];
                    minIndex = i;
                }
            }

            if (minIndex == -1) {
                break; // Tidak ada node yang dapat dicapai
            }

            visited[minIndex] = true;

            for (int i = 0; i < nodeCount; ++i) {
                if (!visited[i] && adjacencyMatrix[minIndex][i] && distance[minIndex] != INT_MAX &&
                    distance[minIndex] + adjacencyMatrix[minIndex][i] < distance[i]) {
                    distance[i] = distance[minIndex] + adjacencyMatrix[minIndex][i];
                    previous[i] = minIndex;
                }
            }
        }

        reconstructPath(targetNode, previous, path);
    }

    // Fungsi untuk merekonstruksi jalur terpendek dari algoritma Dijkstra
    void reconstructPath(int targetNode, const vector<int>& previous, vector<int>& path) {
        for (int at = targetNode; at != -1; at = previous[at]) {
            path.push_back(at);
        }

        reverse(path.begin(), path.end());
    }
};

int main() {
    // Membuat instance dari kelas RuteTransportasiUmum dengan kapasitas 10 node
    RuteTransportasiUmum transportasiUmum(10);

    // Menambahkan node yang merepresentasikan lokasi ke dalam graf
    transportasiUmum.addNode(new Node("ITS"));              //0
    transportasiUmum.addNode(new Node("UNAIR"));            //1
    transportasiUmum.addNode(new Node("GALAXY MALL"));      //2
    transportasiUmum.addNode(new Node("TUNJUNGAN PLAZA"));  //3
    transportasiUmum.addNode(new Node("GWALK"));            //4
    transportasiUmum.addNode(new Node("UNNESA"));           //5
    transportasiUmum.addNode(new Node("JODER"));            //6
    transportasiUmum.addNode(new Node("SURAMADU"));         //7
    transportasiUmum.addNode(new Node("BEBEK SINJAY"));     //8
    transportasiUmum.addNode(new Node("RUMAH SAKIT SUTOMO"));//9

    // Menambahkan sisi yang merepresentasikan hubungan antar lokasi
    transportasiUmum.addEdge(0, 1);  // ITS - UNAIR
    transportasiUmum.addEdge(0, 6);  // ITS - JODER
    transportasiUmum.addEdge(1, 2);  // UNAIR - GALAXY MALL
    transportasiUmum.addEdge(1, 9);  // UNAIR - SUTOMO
    transportasiUmum.addEdge(2, 3);  // GALAXY MALL - TUNJUNGAN PLAZA
    transportasiUmum.addEdge(3, 4);  // TUNJUNGAN PLAZA - GWALK
    transportasiUmum.addEdge(3, 7);  // TUNJUNGAN PLAZA - SURAMADU
    transportasiUmum.addEdge(4, 5);  // GWALK - UNNESA   
    transportasiUmum.addEdge(6, 2);  // JODER - GALAXY MALL
    transportasiUmum.addEdge(7, 8);  // SURAMADU - BEBEK SINJAY
    transportasiUmum.addEdge(9, 7);  // SUTOMO - SURAMADU

    // Menampilkan representasi matriks ketetanggaan graf
    transportasiUmum.display();
    

    // Membersihkan buffer input
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    // Meminta pengguna untuk memasukkan lokasi awal dan tujuan
    string lokasiAwal, lokasiTujuan;
    cout << "Masukkan lokasi awal: ";
    getline(cin, lokasiAwal);

    // Membersihkan buffer input
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Masukkan lokasi tujuan: ";
    getline(cin, lokasiTujuan);
    

    // Menampilkan rute transportasi menggunakan algoritma Dijkstra
    transportasiUmum.tampilkanRute(lokasiAwal, lokasiTujuan);

    return 0;
}
