/**********************************************
 * Description:
 * This file implements Huffman Compression, which is a lossless compression algorithm
 * The buildHuffmanTree function uses the MinHeap to construct a binary tree from the character frequencies
 * A good amount of code was given to me in a handout and the
 * rest was completed for the class
 **********************************************/

#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <sstream>
using namespace std;
struct Node {
    char data;
    unsigned freq;
    Node *left, *right;
    Node(char data, unsigned freq, Node* left = nullptr, Node* right = nullptr)
            : data(data), freq(freq), left(left), right(right) {}
};

class MinHeap {
    vector<Node*> heap;

    void heapify(int index) {
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        int smallest = index;
        if (left < heap.size() && heap[left]->freq < heap[smallest]->freq) {
            smallest = left;
        }
        if (right < heap.size() && heap[right]->freq < heap[smallest]->freq) {
            smallest = right;
        }
        if (smallest != index) {
            swap(heap[index], heap[smallest]);
            heapify(smallest);
        }
    }

    void percolateUp(int index) {
        while (index > 0 && heap[index]->freq < heap[(index - 1) / 2]->freq) {
            swap(heap[index], heap[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    }

public:
    MinHeap() = default;

    void insert(Node* val) {
        heap.push_back(val);
        int index = heap.size() - 1;
        percolateUp(index);
    }

    Node* extractMin() {
        if (heap.empty()) {
            throw runtime_error("Heap is empty");
        }
        Node* minVal = heap[0];
        heap[0] = heap.back();
        heap.pop_back();
        heapify(0);
        return minVal;
    }

    bool isEmpty() {
        return heap.empty();
    }

    int size() {
        return heap.size();
    }
};

// This function will populate the huffmanCode map with the corresponding bit patterns
void generateCodes(Node* root, string str, unordered_map<char, string>& huffmanCode) {
    if (root == nullptr)
        return;

    // This node stores data directly (i.e., it is a leaf)
    if (!root->left && !root->right) {
        huffmanCode[root->data] = str;
    }

    generateCodes(root->left, str + "0", huffmanCode);
    generateCodes(root->right, str + "1", huffmanCode);
}

string binaryToHex(string binary) {
    string hex;
    for (int i = 0; i < binary.length(); i += 4) {
        string byte = binary.substr(i, 4);
        char hChar;
        // Converts each byte to the corresponding hexadecimal char
        if (byte == "0000") hChar = '0';
        else if (byte == "0001") hChar = '1';
        else if (byte == "0010") hChar = '2';
        else if (byte == "0011") hChar = '3';
        else if (byte == "0100") hChar = '4';
        else if (byte == "0101") hChar = '5';
        else if (byte == "0110") hChar = '6';
        else if (byte == "0111") hChar = '7';
        else if (byte == "1000") hChar = '8';
        else if (byte == "1001") hChar = '9';
        else if (byte == "1010") hChar = 'A';
        else if (byte == "1011") hChar = 'B';
        else if (byte == "1100") hChar = 'C';
        else if (byte == "1101") hChar = 'D';
        else if (byte == "1110") hChar = 'E';
        else if (byte == "1111") hChar = 'F';
        else cout <<"something is very wrong here";

        hex += hChar;  // Append to the hex string;
    }
    return hex;
}

// This function will build the huffman tree after using the frequency count of each character
Node* buildHuffmanTree(const unordered_map<char, int>& freq) {
    MinHeap heap;
    for (auto pair : freq) {
        heap.insert(new Node(pair.first, pair.second));
    }
    while (heap.size() > 1) {
        Node* left = heap.extractMin();
        Node* right = heap.extractMin();

        int mergedFreq = left->freq + right->freq;
        Node* merged = new Node('_', mergedFreq, left, right); //no data so placeholder
        heap.insert(merged);
    }

    //remaining node is the root
    return heap.extractMin();
}
// This will take in the file name and create the corresponding compressed file in addition to
//the map file
void compress(const string& inputFilename, const string& outputFilename) {

    //opening input file
    ifstream inputFile;
    inputFile.open( inputFilename);

    if (!inputFile.is_open()) {
        cout << "Failed to open file: " << inputFilename << endl;
        return;
    }
    unordered_map<char, int> letterWeight;
    char ch;
    while(inputFile.get(ch)){
        letterWeight[ch]++;
    }
    inputFile.close();

    //to get path for each char and add to the frequency map
    Node* root = buildHuffmanTree(letterWeight);
    unordered_map<char, string> huffmanCode;
    generateCodes(root, "", huffmanCode);

    //open output file for hex
    ofstream compressedFile(outputFilename + "compress.txt");
    if(!compressedFile.is_open()){
        cout << "Failed to make compressed file: " << inputFilename << endl;
        return;
    }

    inputFile.open(  inputFilename);
    string binaryString;
    while(inputFile.get(ch)){
        binaryString += huffmanCode[ch];
    }
    inputFile.close();

    int padding = (4 - binaryString.length() % 4) % 4;
    binaryString.append(padding, '0');
    cout << "Padded Binary string: " << binaryString << endl;

    string hexString = binaryToHex(binaryString);
    cout << "Hex string: " << hexString << endl;

    compressedFile << hexString;
    compressedFile.close();

    ofstream mapFile(outputFilename + "_map.txt");
    for (const auto& pair : huffmanCode) {
        mapFile << pair.first << ":" << pair.second << "\n";
    }
    mapFile.close();

}

int main() {
    int choice;
    string inputFilename, outputFilename, compressedFilename;
    cout << "Huffman Compression/Decompression" << endl;
    cout << "1: Compress" << endl;
    cout << "2: Decompress" << endl;
    cout << "Select an option: ";
    cin >> choice;
    switch (choice) {
        case 1:
            cout << "Enter the name of the file to compress: ";
            cin >> inputFilename;
            outputFilename = inputFilename.substr(0, inputFilename.find_last_of("."));
            compress(inputFilename, outputFilename);
// This merely prints out it was saved, you will need to do this in compress
            cout << "Compressed files saved as " << outputFilename << "_map.txt and " <<
                 outputFilename << "_compressed.txt" << endl;
            break;
        case 2:
            cout << "Enter the name of the map file: ";
            cin >> inputFilename;
            cout << "Enter the name of the compressed file: ";
            cin >> compressedFilename;
            outputFilename = "decompressed_" + compressedFilename.substr(0,
                                                                         compressedFilename.find("_compressed")) + ".txt";
            //decompress(inputFilename, compressedFilename, outputFilename);
// This merely prints out it was saved, you will need to do this in decompress
            cout << "Decompressed file saved as " << outputFilename << endl;
            break;
        default:
            cout << "Invalid option. Please select 1 for compression or 2 for decompression." <<
                 endl;
            return 1;
    }
    return 0;
}
