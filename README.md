# Final-Project-Strukdat
Pada final project strukdat kami membuat suatu program yang berfungsi untuk mencari rute terdekat untuk input lokasi yang telah ditentukan.
# Anggota
- Rizki Ramadhani
- Hafiz Santosa (5027221061)
- Naufan Zaki Luqmanulhakim (5027221065)
# Penjelasan Program

# Implementasi Materi

- Implementasi Class dan Method pada program tersebut dapat dilihat melalui class RuteTransportasiUmum. Class ini merupakan implementasi dari teori graf, yang didefinisikan melalui representasi matriks ketetanggaan atau adjacency list. Class ini memiliki beberapa property seperti array of pointer untuk menyimpan node, serta representasi matriks ketetanggaan dan adjacency list untuk menyimpan sisi graf.

```
Download
Copy code
class RuteTransportasiUmum {
    public:
        RuteTransportasiUmum(int n);
        ~RuteTransportasiUmum();

        void addNode(Node* node);
        void addEdge(int from, int to);
        void display();
        void tampilkanRute(string start, string end);
    private:
        vector<Node*> nodes;
        vector<vector<int>> adjMatrix;
        vector<vector<int>> adjList;
        vector<bool> visited;
};
```
- Class RuteTransportasiUmum memiliki constructor dan destructor. Constructor menginisialisasi representasi matriks ketetanggaan dan adjacency list dengan ukuran tertentu yang didefinisikan pada saat pembuatan objek. Destructor bertugas untuk membersihkan memory yang telah digunakan oleh objek.

```
RuteTransportasiUmum::RuteTransportasiUmum(int n) {
    nodes.resize(n);
    adjMatrix.resize(n, vector<int>(n, 0));
    adjList.resize(n, vector<int>());
    visited.resize(n, false);
}

RuteTransportasiUmum::~RuteTransportasiUmum() {
    for (int i = 0; i < nodes.size(); i++) {
        delete nodes[i];
    }
}
```

- Class RuteTransportasiUmum memiliki method-method seperti addNode, addEdge, display, dan tampilkanRute. Method-method ini digunakan untuk menambahkan node dan sisi pada graf, menampilkan representasi matriks ketetanggaan, serta menampilkan rute transportasi menggunakan algoritma Dijkstra.
```
Download
Copy code
void RuteTransportasiUmum::addNode(Node* node) {
    nodes.push_back(node);
}

void RuteTransportasiUmum::addEdge(int from, int to) {
    adjMatrix[from][to] = 1;
    adjList[from].push_back(to);
}

void RuteTransportasiUmum::display() {
    cout << "Adjacency Matrix:" << endl;
    for (int i = 0; i < adjMatrix.size(); i++) {
        for (int j = 0; j < adjMatrix[i].size(); j++) {
            cout << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

void RuteTransportasiUmum::tampilkanRute(string start, string end) {
    // Implementasi algoritma Dijkstra
}
```

- Encapsulation: Menggunakan Public / Private / Protected member, serta menggunakan Accessor (Getter) dan Mutator (Setter) untuk mengatur akses terhadap private member.
```
class RuteTransportasiUmum {
    public:
        RuteTransportasiUmum(int n);
        ~RuteTransportasiUmum();

        void addNode(Node* node);
        void addEdge(int from, int to);
        void display();
        void tampilkanRute(string start, string end);

    private:
        vector<Node*> nodes;
        vector<vector<int>> adjMatrix;
        vector<vector<int>> adjList;
        vector<bool> visited;
};
```

- Inheritance: Single inheritance (Mengimplementasikan class dari class lain).
```
class Kota {
    public:
        Kota(string nama, double lat, double long);
        ~Kota();

        string getNama() const;
        double getLat() const;
        double getLong() const;

    private:
        string nama;
        double latitude;
        double longitude;
};

class RuteTransportasiUmum : public Kota {
    // Implementasi class RuteTransportasiUmum
};
```

- Polymorphism: Menggunakan konsep Inheritance untuk membuat class baru yang berisi behavior dan data dari class lain.
```
class Transportasi {
    public:
        Transportasi(string nama);
        ~Transportasi();

        string getNama() const;

    private:
        string nama;
};

class Kota : public Transportasi {
    public:
        Kota(string nama, double lat, double long);
        ~Kota();

        double getLat() const;
        double getLong() const;

    private:
        double latitude;
        double longitude;
};

class RuteTransportasiUmum : public Kota {
    // Implementasi class RuteTransportasiUmum
};
```
Misalnya, pada implementasi di atas, kita dapat membuat objek dari class Kota, RuteTransportasiUmum, dan memanggil method getNama yang merupakan method dari class Transportasi yang telah diwarisi oleh class Kota dan RuteTransportasiUmum
