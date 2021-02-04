/*
 * util.h
 * CS 251 - Project 6 - Fall 2020
 * Name: Tanuj Dave, netId: tdave6
 *       Heet Parikh, netId: hparik5
 *
 */
#pragma once

#include <fstream>
#include <map>
#include "hashmap.h"
#include "bitstream.h"
#include "priorityqueue.h"

typedef hashmap hashmapF;
typedef unordered_map <int, string> hashmapE;

struct HuffmanNode {
    int character;
    int count;
    HuffmanNode* zero;
    HuffmanNode* one;
};

//
// This method frees the memory allocated for the Huffman tree.
//
void freeTree(HuffmanNode* &node) {
    if (node == nullptr) {  // if the node DNE.
        return;
    }

    freeTree(node->zero);  // clear the left first.
    freeTree(node->one);  // clear the right.
    delete node;

    node = nullptr;  // set it to nullptr.
}

//
// This function build the frequency map.  If isFile is true, then it reads
// from filename.  If isFile is false, then it reads from a string filename.
//
void buildFrequencyMap(string filename, bool isFile, hashmapF &theMap) {
    if (isFile) {  // if rading from a file.
        ifstream file;
        file.open(filename);  // opening the file.

        int key, value;
        char temp;

        while (file.get(temp)) {  // while there are characters in the file.
            if (theMap.containsKey((int)temp)) {  // if the key already exists.
                // adding 1 to its vlaue.
                theMap.put((int)temp, theMap.get((int)temp) + 1);
            } else {                             // if the key DNE.
                theMap.put((int)temp, 1);  // adding 1 to its vlaue.
            }
        }

        theMap.put(256, 1);  // adding the PSEUDO_EOF.
    } else {  // if reading from a string.
        stringstream ss;
        ss << filename;  // inputting the string in a string stream for ease.

        int key, value;
        char temp;

        while (ss.get(temp)) {  // while there are characters in string.
            if (theMap.containsKey((int)temp)) {  // if the key already exists.
                theMap.put((int)temp, theMap.get((int)temp) + 1);
            } else {                             // if the key DNE.
                theMap.put((int)temp, 1);
            }
        }

        theMap.put(256, 1);  // adding the PSEUDO_EOF.
    }
}

//
// This function builds an encoding tree from the frequency map.
//
HuffmanNode* buildEncodingTree(hashmapF &map) {
    // buildign a vector with all the characters(as ints).
    vector<int> tempVec = map.keys();
    // declaring the priorityqueue.
    priorityqueue<HuffmanNode> huff;
  // enqueueing all the characters and counts as HuffmanNodes.
    for (int e : tempVec) {
        HuffmanNode node;  // copying all the fields
        node.character = e;
        node.count = map.get(e);
        node.zero = nullptr;
        node.one = nullptr;
        huff.enqueue(node, map.get(e));  // enqueueing it in the queue.
    }

    HuffmanNode node;
    int size = huff.Size();
    int count;

    // looping over the priorityqueue to make a tree.
    while (huff.Size() != 1) {
        // huff.begin();

        HuffmanNode* copy1 = new HuffmanNode;  // copying the first node.
        node = huff.dequeue();  // removing the first node and storing it.
        copy1->character = node.character;
        copy1->count = node.count;
        copy1->zero = node.zero;
        copy1->one = node.one;

        HuffmanNode* copy2 = new HuffmanNode;  // copying the second node.
        node = huff.dequeue();  // removing the second node and storing it.
        copy2->character = node.character;
        copy2->count = node.count;
        copy2->zero = node.zero;
        copy2->one = node.one;

        HuffmanNode newNode;  // making a new node to add in the queue.
        newNode.character = NOT_A_CHAR;
        newNode.count = copy1->count + copy2->count;
        // adding the first and second nodes to the left and right.
        newNode.zero = copy1;
        newNode.one = copy2;

         // adding the newNode to priorityqueue.
        huff.enqueue(newNode, newNode.count);
    }

    huff.begin();
    huff.next(node, count);

    HuffmanNode* ans = new HuffmanNode;  // creating the root node for the tree.
    ans->character = node.character;
    ans->count = count;
    ans->zero = node.zero;
    ans->one = node.one;
    huff.clear();  // removing the only item left in the priorityqueue.

    return ans;  // returning the root of the tree.
}

//
// Recursive helper function for building the encoding map.
//
void _buildEncodingMap(HuffmanNode* node, hashmapE &encodingMap, string str, HuffmanNode* prev) {
    if (node == nullptr) {  // if the node DNE.
        return;
    }
    if (node->character != NOT_A_CHAR) {  // if its a leaf node.
        encodingMap[node->character] = str;
    }
    _buildEncodingMap(node->zero, encodingMap, str + "0", node);  // go to left.
    _buildEncodingMap(node->one, encodingMap, str + "1", node);  // go to right.
}

//
// This function builds the encoding map from an encoding tree.
//
hashmapE buildEncodingMap(HuffmanNode* tree) {
    hashmapE encodingMap;  // declaring a encoding map.

      // building the map recursively.
    _buildEncodingMap(tree, encodingMap, "", nullptr);
    return encodingMap;
}

//
// This function encodes the data in the input stream into the output stream
// using the encodingMap.  This function calculates the number of bits
// written to the output stream and sets result to the size parameter, which is
// passed by reference.  This function also returns a string representation of
// the output file, which is particularly useful for testing.
//
string encode(ifstream& input, hashmapE &encodingMap, ofbitstream& output,
              int &size, bool makeFile) {
    string ans = "";
    stringstream ss;
    char c;
// Iterating to get each character from the input stream and encoding it 
    while (input.get(c)) {
        ss << encodingMap[c];
    }
    ss << encodingMap[PSEUDO_EOF];
    ss >> ans;
// storing the size of the encoded file
    size = ans.size();

    if (makeFile) {
// Iterating to write encoded data to the outputstream
        for (char e : ans) {
            output.writeBit(e - '0');
        }
    }
    return ss.str();
}
// Recursive helper function to search the tree
int searchTree(ifbitstream &input, HuffmanNode* encodingTree, int& read) {
// Returns the character found in the tree
    if (encodingTree->character != NOT_A_CHAR) {
        return encodingTree->character;
    }
    int bit = input.readBit();
    read++;
// Goes to the left branch if there is a 0 in the encoded data
    if (bit == 0) {
        if (encodingTree->zero != nullptr) {
            return searchTree(input, encodingTree->zero, read);
        }
    }
// Goes to the right branch if there is a 1 in the encoded data
    return searchTree(input, encodingTree->one, read);
}

//
// This function decodes the input stream and writes the result to the output
// stream using the encodingTree.  This function also returns a string
// representation of the output file, which is particularly useful for testing.
//
string decode(ifbitstream &input, HuffmanNode* encodingTree, ofstream &output) {
    string ans = "";
    int temp;
    int read = 0;
// Decodes all the charcters of the encoded data
    while (true) {
        temp = searchTree(input, encodingTree, read);
        if (temp == 256) {  // Breaks if PSEUDO_EOF is found
            break;
        }
        ans += (char)temp;  // Appends all the characters decoded as one string
        output << (char)temp;
    }
    return ans;  // returns the decoded string
}

//
// This function completes the entire compression process.  Given a file,
// filename, this function (1) builds a frequency map; (2) builds an encoding
// tree; (3) builds an encoding map; (4) encodes the file (don't forget to
// include the frequency map in the header of the output file).  This function
// should create a compressed file named (filename + ".huf") and should also
// return a string version of the bit pattern.
//
string compress(string filename) {
    hashmapF frequencyMap;
    HuffmanNode* encodingTree = nullptr;
    hashmapE encodingMap;
// Calling the function to build the frequency Map
    buildFrequencyMap(filename, true, frequencyMap);
// Calling the function to build the encoding tree
    encodingTree = buildEncodingTree(frequencyMap);
// Calling the function to  build the encoding map
    encodingMap = buildEncodingMap(encodingTree);
// Creating an ouput stream for the .huf file
    ofbitstream output(filename + ".huf");
    ifstream input(filename);
    stringstream ss;
    // note: << is overloaded for the hashmap class.  super nice!
    ss << frequencyMap;
    output << frequencyMap;  // add the frequency map to the file
    int size = 0;
    string codeStr = encode(input, encodingMap, output, size, true);
    // count bytes in frequency map header
    size = ss.str().length() + ceil((double)size / 8);
    output.close();
    freeTree(encodingTree);  // frees the encoding tree

    return codeStr;
}

//
// This function completes the entire decompression process.  Given the file,
// filename (which should end with ".huf"), (1) extract the header and build
// the frequency map; (2) build an encoding tree from the frequency map; (3)
// using the encoding tree to decode the file.  This function should create a
// compressed file using the following convention.
// If filename = "example.txt.huf", then the uncompressed file should be named
// "example_unc.txt".  The function should return a string version of the
// uncompressed file.  Note this function should reverse what the compress
// function did.
//
string decompress(string filename) {
    hashmapF frequencyMap;
    HuffmanNode* encodingTree = nullptr;
    hashmapE encodingMap;

    ifbitstream input(filename);

    input >> frequencyMap;
// Calling the function to build the encoding tree
    encodingTree = buildEncodingTree(frequencyMap);
// Calling the function to build the encoding map
    encodingMap = buildEncodingMap(encodingTree);
// Finding the position of first '.'
    int pos1 = filename.find(".");
// Finding the position of second '.'
    int pos = filename.find(".", pos1 + 1);
// Creating the string '.txt' and stroing it in
    string ext = filename.substr(pos1, pos - pos1);

    filename = filename.substr(0, pos1);
// Creating and storing an outputstream with the required filename
    ofstream output(filename + "_unc" + ext);
// Storing the decoded string
    string decodeStr  = decode(input, encodingTree, output);
    output.close();
    freeTree(encodingTree);
// returning the decoded the string
    return decodeStr;
}

// rm example.txt.huf example.txt.huf.huf bitstream.h example.txt example_unc.txt hashmap.cpp hashmap.h main.cpp makefile medium.txt medium.txt.huf medium_unc.txt pq.h program.exe priorityqueue.h
