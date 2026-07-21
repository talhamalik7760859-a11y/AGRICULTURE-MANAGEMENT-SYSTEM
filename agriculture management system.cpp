#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <utility>
#include <unordered_map>
#include <queue>
#include <set>
#include <limits>
#include <algorithm>
#include <functional>
#include <stdexcept>
#include <iomanip>
#include <filesystem>
using namespace std;

template <typename T>
class LinkedList {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    int count;

public:
    LinkedList() : head(nullptr), tail(nullptr), count(0) {}

    ~LinkedList() {
        clear();
    }

    void clear() {
        Node* cur = head;
        while (cur) {
            Node* nxt = cur->next;
            delete cur;
            cur = nxt;
        }
        head = tail = nullptr;
        count = 0;
    }

    void insertEnd(const T& value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
        } else {
            tail->next = newNode;
            tail = newNode;
        }
        count++;
    }

    bool removeIf(std::function<bool(const T&)> predicate) {
        Node* cur = head;
        Node* prev = nullptr;
        while (cur) {
            if (predicate(cur->data)) {
                if (prev) prev->next = cur->next;
                else head = cur->next;
                if (cur == tail) tail = prev;
                delete cur;
                count--;
                return true;
            }
            prev = cur;
            cur = cur->next;
        }
        return false;
    }

    T* find(std::function<bool(const T&)> predicate) {
        Node* cur = head;
        while (cur) {
            if (predicate(cur->data)) return &cur->data;
            cur = cur->next;
        }
        return nullptr;
    }

    void forEach(std::function<void(const T&)> visit) const {
        Node* cur = head;
        while (cur) {
            visit(cur->data);
            cur = cur->next;
        }
    }

    int size() const { return count; }
    bool isEmpty() const { return count == 0; }
};

template <typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* topNode;
    int count;

public:
    Stack() : topNode(nullptr), count(0) {}

    ~Stack() {
        while (!isEmpty()) pop();
    }

    void push(const T& value) {
        Node* newNode = new Node(value);
        newNode->next = topNode;
        topNode = newNode;
        count++;
    }

    T pop() {
        if (isEmpty()) throw std::runtime_error("Stack is empty");
        Node* temp = topNode;
        T value = temp->data;
        topNode = topNode->next;
        delete temp;
        count--;
        return value;
    }

    T peek() const {
        if (isEmpty()) throw std::runtime_error("Stack is empty");
        return topNode->data;
    }

    bool isEmpty() const { return topNode == nullptr; }
    int size() const { return count; }
};

template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(const T& value) : data(value), next(nullptr) {}
    };

    Node* frontNode;
    Node* rearNode;
    int count;

public:
    Queue() : frontNode(nullptr), rearNode(nullptr), count(0) {}

    ~Queue() {
        while (!isEmpty()) dequeue();
    }

    void enqueue(const T& value) {
        Node* newNode = new Node(value);
        if (!rearNode) {
            frontNode = rearNode = newNode;
        } else {
            rearNode->next = newNode;
            rearNode = newNode;
        }
        count++;
    }

    T dequeue() {
        if (isEmpty()) throw std::runtime_error("Queue is empty");
        Node* temp = frontNode;
        T value = temp->data;
        frontNode = frontNode->next;
        if (!frontNode) rearNode = nullptr;
        delete temp;
        count--;
        return value;
    }

    T front() const {
        if (isEmpty()) throw std::runtime_error("Queue is empty");
        return frontNode->data;
    }

    bool isEmpty() const { return frontNode == nullptr; }
    int size() const { return count; }
};

template <typename T>
class BST {
private:
    struct Node {
        int key;
        T data;
        Node* left;
        Node* right;
        Node(int k, const T& value) : key(k), data(value), left(nullptr), right(nullptr) {}
    };

    Node* root;
    int count;

    Node* insertNode(Node* node, int key, const T& value) {
        if (!node) { count++; return new Node(key, value); }
        if (key < node->key) node->left = insertNode(node->left, key, value);
        else if (key > node->key) node->right = insertNode(node->right, key, value);
        else node->data = value;
        return node;
    }

    Node* findNode(Node* node, int key) const {
        if (!node) return nullptr;
        if (key == node->key) return node;
        if (key < node->key) return findNode(node->left, key);
        return findNode(node->right, key);
    }

    Node* minValueNode(Node* node) const {
        while (node && node->left) node = node->left;
        return node;
    }

    Node* removeNode(Node* node, int key, bool& removed) {
        if (!node) return nullptr;
        if (key < node->key) node->left = removeNode(node->left, key, removed);
        else if (key > node->key) node->right = removeNode(node->right, key, removed);
        else {
            removed = true;
            if (!node->left) { Node* r = node->right; delete node; count--; return r; }
            if (!node->right) { Node* l = node->left; delete node; count--; return l; }
            Node* succ = minValueNode(node->right);
            node->key = succ->key;
            node->data = succ->data;
            bool dummy = false;
            node->right = removeNode(node->right, succ->key, dummy);
        }
        return node;
    }

    void inorderHelper(Node* node, std::function<void(const T&)> visit) const {
        if (!node) return;
        inorderHelper(node->left, visit);
        visit(node->data);
        inorderHelper(node->right, visit);
    }

    void destroy(Node* node) {
        if (!node) return;
        destroy(node->left);
        destroy(node->right);
        delete node;
    }

public:
    BST() : root(nullptr), count(0) {}
    ~BST() { destroy(root); }

    void insert(int key, const T& value) { root = insertNode(root, key, value); }

    T* search(int key) const {
        Node* n = findNode(root, key);
        return n ? &n->data : nullptr;
    }

    bool remove(int key) {
        bool removed = false;
        root = removeNode(root, key, removed);
        return removed;
    }

    void inorder(std::function<void(const T&)> visit) const { inorderHelper(root, visit); }

    int size() const { return count; }
    bool isEmpty() const { return count == 0; }
};

template <typename V>
class HashTable {
private:
    static const int DEFAULT_BUCKETS = 16;
    std::vector<std::list<std::pair<int, V>>> buckets;
    int itemCount;

    int hashFunc(int key) const {
        return (key % (int)buckets.size() + (int)buckets.size()) % (int)buckets.size();
    }

public:
    HashTable(int bucketCount = DEFAULT_BUCKETS) : buckets(bucketCount), itemCount(0) {}

    void insert(int key, const V& value) {
        int idx = hashFunc(key);
        for (auto& p : buckets[idx]) {
            if (p.first == key) { p.second = value; return; }
        }
        buckets[idx].push_back({key, value});
        itemCount++;
    }

    V* find(int key) {
        int idx = hashFunc(key);
        for (auto& p : buckets[idx]) {
            if (p.first == key) return &p.second;
        }
        return nullptr;
    }

    bool remove(int key) {
        int idx = hashFunc(key);
        auto& chain = buckets[idx];
        for (auto it = chain.begin(); it != chain.end(); ++it) {
            if (it->first == key) {
                chain.erase(it);
                itemCount--;
                return true;
            }
        }
        return false;
    }

    void clear() {
        for (auto& b : buckets) b.clear();
        itemCount = 0;
    }

    int size() const { return itemCount; }
    int bucketCount() const { return (int)buckets.size(); }

    int chainLength(int bucketIndex) const {
        if (bucketIndex < 0 || bucketIndex >= (int)buckets.size()) return -1;
        return (int)buckets[bucketIndex].size();
    }
};

class Graph {
private:
    std::unordered_map<std::string, std::vector<std::pair<std::string, int>>> adjList;

public:
    void addNode(const std::string& node) {
        if (adjList.find(node) == adjList.end())
            adjList[node] = {};
    }

    void addEdge(const std::string& a, const std::string& b, int distanceKm) {
        addNode(a);
        addNode(b);
        adjList[a].push_back({b, distanceKm});
        adjList[b].push_back({a, distanceKm});
    }

    bool hasNode(const std::string& node) const {
        return adjList.find(node) != adjList.end();
    }

    std::vector<std::string> bfs(const std::string& start) const {
        std::vector<std::string> order;
        if (!hasNode(start)) return order;
        std::set<std::string> visited;
        std::queue<std::string> q;
        q.push(start);
        visited.insert(start);
        while (!q.empty()) {
            std::string cur = q.front(); q.pop();
            order.push_back(cur);
            for (auto& edge : adjList.at(cur)) {
                if (!visited.count(edge.first)) {
                    visited.insert(edge.first);
                    q.push(edge.first);
                }
            }
        }
        return order;
    }

    void dfsHelper(const std::string& node, std::set<std::string>& visited,
                    std::vector<std::string>& order) const {
        visited.insert(node);
        order.push_back(node);
        for (auto& edge : adjList.at(node)) {
            if (!visited.count(edge.first)) dfsHelper(edge.first, visited, order);
        }
    }

    std::vector<std::string> dfs(const std::string& start) const {
        std::vector<std::string> order;
        if (!hasNode(start)) return order;
        std::set<std::string> visited;
        dfsHelper(start, visited, order);
        return order;
    }

    std::pair<int, std::vector<std::string>> shortestPath(const std::string& start,
                                                            const std::string& end) const {
        if (!hasNode(start) || !hasNode(end)) return {-1, {}};

        std::unordered_map<std::string, int> dist;
        std::unordered_map<std::string, std::string> prev;
        for (auto& kv : adjList) dist[kv.first] = std::numeric_limits<int>::max();
        dist[start] = 0;

        using PQItem = std::pair<int, std::string>;
        std::priority_queue<PQItem, std::vector<PQItem>, std::greater<PQItem>> pq;
        pq.push({0, start});

        while (!pq.empty()) {
            auto [d, node] = pq.top(); pq.pop();
            if (d > dist[node]) continue;
            for (auto& edge : adjList.at(node)) {
                int newDist = d + edge.second;
                if (newDist < dist[edge.first]) {
                    dist[edge.first] = newDist;
                    prev[edge.first] = node;
                    pq.push({newDist, edge.first});
                }
            }
        }

        if (dist[end] == std::numeric_limits<int>::max()) return {-1, {}};

        std::vector<std::string> path;
        std::string cur = end;
        while (cur != start) {
            path.push_back(cur);
            cur = prev[cur];
        }
        path.push_back(start);
        std::reverse(path.begin(), path.end());
        return {dist[end], path};
    }

    void displayNetwork() const {
        for (auto& kv : adjList) {
            std::cout << "  " << kv.first << " -> ";
            for (auto& edge : kv.second) {
                std::cout << "[" << edge.first << ", " << edge.second << "km] ";
            }
            std::cout << "\n";
        }
    }

    int nodeCount() const { return (int)adjList.size(); }
};

struct Farmer {
    int id;
    std::string name;
    std::string village;
    std::string contact;

    Farmer() : id(0) {}
    Farmer(int id, std::string name, std::string village, std::string contact)
        : id(id), name(std::move(name)), village(std::move(village)), contact(std::move(contact)) {}
};

struct Crop {
    int id;
    std::string name;
    int farmerId;
    double quantityKg;
    double pricePerKg;

    Crop() : id(0), farmerId(0), quantityKg(0), pricePerKg(0) {}
    Crop(int id, std::string name, int farmerId, double qty, double price)
        : id(id), name(std::move(name)), farmerId(farmerId), quantityKg(qty), pricePerKg(price) {}
};

struct Order {
    int orderId;
    int cropId;
    std::string buyerName;
    double quantityRequested;
    std::string status;

    Order() : orderId(0), cropId(0), quantityRequested(0), status("Pending") {}
    Order(int orderId, int cropId, std::string buyerName, double qty)
        : orderId(orderId), cropId(cropId), buyerName(std::move(buyerName)),
          quantityRequested(qty), status("Pending") {}
};

inline void merge(std::vector<Crop>& crops, int left, int mid, int right) {
    std::vector<Crop> leftPart(crops.begin() + left, crops.begin() + mid + 1);
    std::vector<Crop> rightPart(crops.begin() + mid + 1, crops.begin() + right + 1);

    int i = 0, j = 0, k = left;
    while (i < (int)leftPart.size() && j < (int)rightPart.size()) {
        if (leftPart[i].pricePerKg <= rightPart[j].pricePerKg) crops[k++] = leftPart[i++];
        else crops[k++] = rightPart[j++];
    }
    while (i < (int)leftPart.size()) crops[k++] = leftPart[i++];
    while (j < (int)rightPart.size()) crops[k++] = rightPart[j++];
}

inline void mergeSortByPrice(std::vector<Crop>& crops, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSortByPrice(crops, left, mid);
    mergeSortByPrice(crops, mid + 1, right);
    merge(crops, left, mid, right);
}

inline int binarySearchById(const std::vector<Crop>& crops, int id) {
    int low = 0, high = (int)crops.size() - 1;
    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (crops[mid].id == id) return mid;
        if (crops[mid].id < id) low = mid + 1;
        else high = mid - 1;
    }
    return -1;
}

LinkedList<Farmer> farmerList;
HashTable<Farmer> farmerHash;
BST<Crop> cropTree;
Queue<Order> orderQueue;
Stack<string> actionHistory;
Graph supplyChain;

int nextFarmerId = 1;
int nextCropId = 1;
int nextOrderId = 1;

const string FARMER_FILE = "data/farmers.txt";
const string CROP_FILE   = "data/crops.txt";

void pause() {
    cout << "\nPress Enter to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
}

void logAction(const string& msg) {
    actionHistory.push(msg);
}

int readInt(const string& prompt) {
    int val;
    cout << prompt;
    while (!(cin >> val)) {
        if (cin.eof()) { cout << "\nInput ended. Exiting.\n"; exit(0); }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. " << prompt;
    }
    return val;
}

int readMenuChoice() {
    int val;
    while (!(cin >> val)) {
        if (cin.eof()) { cout << "\nInput ended. Exiting.\n"; exit(0); }
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid choice, try again: ";
    }
    return val;
}

double readDouble(const string& prompt) {
    double val;
    cout << prompt;
    while (!(cin >> val)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Invalid input. " << prompt;
    }
    return val;
}

string readLine(const string& prompt) {
    string val;
    cout << prompt;
    cin >> ws;
    getline(cin, val);
    return val;
}

void addFarmer() {
    string name = readLine("Enter Farmer Name: ");
    string village = readLine("Enter Village: ");
    string contact = readLine("Enter Contact Number: ");

    Farmer f(nextFarmerId, name, village, contact);
    farmerList.insertEnd(f);
    farmerHash.insert(f.id, f);

    cout << "Farmer added successfully with ID: " << f.id << "\n";
    logAction("Added Farmer [ID " + to_string(f.id) + "] " + name);
    nextFarmerId++;
}

void listFarmers() {
    if (farmerList.isEmpty()) { cout << "No farmers found.\n"; return; }
    cout << left << setw(6) << "ID" << setw(20) << "Name" << setw(20) << "Village" << "Contact" << "\n";
    farmerList.forEach([](const Farmer& f) {
        cout << left << setw(6) << f.id << setw(20) << f.name << setw(20) << f.village << f.contact << "\n";
    });
}

void findFarmerById() {
    int id = readInt("Enter Farmer ID: ");
    Farmer* f = farmerHash.find(id);
    if (f) {
        cout << "Found -> ID: " << f->id << ", Name: " << f->name
             << ", Village: " << f->village << ", Contact: " << f->contact << "\n";
    } else {
        cout << "Farmer not found.\n";
    }
}

// ---------------- Crop Module (Binary Search Tree) ----------------
void addCrop() {
    string name = readLine("Enter Crop Name: ");
    int farmerId = readInt("Enter Farmer ID: ");
    double qty = readDouble("Enter Quantity (kg): ");
    double price = readDouble("Enter Price per Kg: ");

    Crop c(nextCropId, name, farmerId, qty, price);
    cropTree.insert(c.id, c);

    cout << "Crop added successfully with ID: " << c.id << "\n";
    logAction("Added Crop [ID " + to_string(c.id) + "] " + name);
    nextCropId++;
}

void listCropsSortedById() {
    if (cropTree.isEmpty()) { cout << "No crops found.\n"; return; }
    cout << left << setw(6) << "ID" << setw(15) << "Name" << setw(10) << "FarmerID"
         << setw(12) << "Qty(kg)" << "Price/kg" << "\n";
    cropTree.inorder([](const Crop& c) {
        cout << left << setw(6) << c.id << setw(15) << c.name << setw(10) << c.farmerId
             << setw(12) << c.quantityKg << c.pricePerKg << "\n";
    });
}

vector<Crop> collectAllCrops() {
    vector<Crop> crops;
    cropTree.inorder([&](const Crop& c) { crops.push_back(c); });
    return crops;
}

void searchCropByIdMenu() {
    if (cropTree.isEmpty()) { cout << "No crops found.\n"; return; }
    int id = readInt("Enter Crop ID to search: ");
    vector<Crop> crops = collectAllCrops();
    int idx = binarySearchById(crops, id);
    if (idx != -1) {
        Crop& c = crops[idx];
        cout << "Found -> ID: " << c.id << ", Name: " << c.name << ", FarmerID: " << c.farmerId
             << ", Qty: " << c.quantityKg << " kg, Price: " << c.pricePerKg << "/kg\n";
    } else {
        cout << "Crop not found.\n";
    }
}

void sortCropsByPriceMenu() {
    vector<Crop> crops = collectAllCrops();
    if (crops.empty()) { cout << "No crops to sort.\n"; return; }
    mergeSortByPrice(crops, 0, (int)crops.size() - 1);
    cout << "Crops sorted by price (ascending):\n";
    for (auto& c : crops) {
        cout << "  ID: " << c.id << ", Name: " << c.name << ", Price/kg: " << c.pricePerKg << "\n";
    }
}

// ---------------- Order Module (Queue) ----------------
void placeOrder() {
    int cropId = readInt("Enter Crop ID: ");
    Crop* c = cropTree.search(cropId);
    if (!c) { cout << "Crop ID not found.\n"; return; }

    string buyer = readLine("Enter Buyer Name: ");
    double qty = readDouble("Enter Quantity Requested (kg): ");

    Order o(nextOrderId, cropId, buyer, qty);
    orderQueue.enqueue(o);

    cout << "Order placed with ID: " << o.orderId << "\n";
    logAction("Placed Order [ID " + to_string(o.orderId) + "] by " + buyer);
    nextOrderId++;
}

void processNextOrder() {
    if (orderQueue.isEmpty()) { cout << "No pending orders.\n"; return; }
    Order o = orderQueue.dequeue();
    o.status = "Processed";
    cout << "Processed Order ID " << o.orderId << " for buyer " << o.buyerName
         << " (Crop ID " << o.cropId << ", Qty " << o.quantityRequested << " kg)\n";
    logActio
