#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

// Node class for Huffman Tree
class Node {
public:
    char ch;
    int freq;
    Node* left;
    Node* right;

    Node(char c, int f) {
        ch = c;
        freq = f;
        left = right = nullptr;
    }
};

// Comparator for priority queue (min-heap)
class Compare {
public:
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq; // smaller freq has higher priority
    }
};

// Recursive function to generate Huffman Codes
void generateCodes(Node* root, string code, unordered_map<char, string>& huffmanCode) {
    if (!root) return;

    // Leaf node: store its code
    if (!root->left && !root->right)
        huffmanCode[root->ch] = code;

    generateCodes(root->left, code + "0", huffmanCode);
    generateCodes(root->right, code + "1", huffmanCode);
}

void huffmanEncoding(string text) {
    // Step 1: Count frequency of each character
    unordered_map<char, int> freq;
    for (char ch : text)
        freq[ch]++;

    // Step 2: Create min-heap (priority queue)
    priority_queue<Node*, vector<Node*>, Compare> pq;

    for (auto pair : freq)
        pq.push(new Node(pair.first, pair.second));

    // Step 3: Build Huffman Tree
    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        Node* newNode = new Node('\0', left->freq + right->freq);
        newNode->left = left;
        newNode->right = right;

        pq.push(newNode);
    }

    Node* root = pq.top();

    // Step 4: Generate Huffman Codes
    unordered_map<char, string> huffmanCode;
    generateCodes(root, "", huffmanCode);

    // Step 5: Print results
    cout << "Huffman Codes:\n";
    for (auto pair : huffmanCode)
        cout << pair.first << " : " << pair.second << endl;

    cout << "\nEncoded string: ";
    for (char ch : text)
        cout << huffmanCode[ch];
    cout << endl;
}

int main() {
    string text = "huffmanencodingexample";
    huffmanEncoding(text);
    return 0;
}
