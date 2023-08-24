// Discrete_Project.cpp

/*
Muhammad Riyan Aslam - i210428
Tayyaab Ali Sajid - i212546
Ayesha Faisal - i210739
*/

#include <iostream>
#include <fstream>

using namespace std;

// generic templatized stack class
template<class T>
class node {
public:
    T val;
    node* next;

    node() {
        val = 0;
        next = nullptr;
    }
    node(T val) {
        this->val = val;
        next = nullptr;
    }
};

template<class T>
class stack {
    node<T>* head;
    int count;
public:
    stack() {
        count = 0;
        head = nullptr;
    }

    ~stack() {
        clear();
    }

    void push(T val) {
        node<T>* newNode = new node<T>(val);
        count++;
        if (!head) {
            head = newNode;
            return;
        }

        newNode->next = head;
        head = newNode;
    }

    T pop() {
        if (!head) {
            cout << "STACK IS EMPTY!!!!!";
            return 0;
        }
        node<T>* tempNode = new node<T>;
        tempNode = head;
        T val = head->val;
        head = head->next;
        delete tempNode;
        count--;
        return val;
    }

    node<T>* Peek() {
        if (!head) {
            cout << "STACK IS EMPTY!!!!!";
            return 0;
        }
        return head;
    }

    void clear() {
        while (head) {
            pop();
        }
    }

    int sizeofstack() {
        return count;
    }

    bool isEmpty() {
        return (head == nullptr);
    }
};


template <class T>
class graphNode { // templatized node class for storing graph data

public:

    T data;
    graphNode<T>* next;

    graphNode() { // default constructor
        data = '\0';
        next = nullptr;
    }
    graphNode(T data) { // parameterized constructor
        this->data = data;
        next = nullptr;

    }

};




template <class T>
class Graph { // templatized class: Graph


    void DFSTraverse(graphNode<T>* curNode, bool* visited, stack<T>& s) { // 

        if (!curNode) // returns from function if curNode is NULL
            return;

        if (visited[curNode->data]) { // returns from function is node has already been visted
            return;
        }
        visited[curNode->data] = true; // sets the current node to true to mark it as visited
        graphNode<T>* nextNode = curNode;
        while (nextNode) { // DFS traversl through all the destination nodes of curNode
            DFSTraverse(head[nextNode->data], visited, s);
            nextNode = nextNode->next;
        }
        s.push(curNode->data);

    }

    void DFSUntilTraverse(graphNode<T>* curNode, bool* visited, int* count) { // traversal for each component

        if (!curNode) // returns from function if curNode is NULL
            return;

        if (visited[curNode->data]) { // returns from function is node has already been visted
            return;
        }
        visited[curNode->data] = true; // setting node to true (visited)
        cout << curNode->data << ", "; // printing the nodes
        (*count)++; // incrementing the number of nodes in a component
        graphNode<T>* nextNode = curNode;
        while (nextNode) { // DFS traversl through all the destination nodes of curNode
            DFSUntilTraverse(head[nextNode->data], visited, count);
            nextNode = nextNode->next;
        }
    }


public:
    int noOfNodes;
    graphNode<T>** head; // to create matrix of adjacency list

    Graph() { // default constructor
        noOfNodes = 0;
        head = nullptr;
    }
    Graph(int nodes) { // parameterized constructor
        noOfNodes = nodes;
        head = new graphNode<T>*[nodes]; // creating an array with size of the number of nodes

        for (int i = 0; i < nodes; i++)
            head[i] = new graphNode<T>(i);
    }

    void insert(T s, T d) { // insert function for graph edges
                            // paramters s(from_node) & d(to_node)
        if (!head) // returns from function if head is NULL
            return;

        graphNode<T>* curNode = head[s]; // setting the source node of the edge
        while (curNode->next) { // traversing till the end of the list
            curNode = curNode->next;
        }

        graphNode<T>* tempNode = new graphNode<T>(d); // adding the destination node of the edge at the end of the list
        curNode->next = tempNode;
    }

    void printGraph() { // function to print the graph


        if (!head) // returns from function if head is NULL
            return;


        for (int i = 0; i < noOfNodes; i++) { // visits all the source nodes

            cout << i << ": "; // printing source nodes

            graphNode<T>* curNode = head[i];

            while (curNode) { // printing destination nodes
                cout << curNode->data << ", ";
                curNode = curNode->next;
            }

            cout << endl;
        }
    }
    void DFS(stack<T>& s) { // Depth First Search 


        if (!head) // returns from function if head is NULL
            return;

        bool* visited = new bool[noOfNodes] { false }; // creating a boolean array with the size of number of nodes 
                                                        // to check if a node has been visited
        for (int i = 0; i < noOfNodes; i++) // checking all the source nodes
            DFSTraverse(head[i], visited, s); // checking all the destination nodes

        delete[] visited;
    }


    void DFSUntil(stack<T>& s, int* max) { // DFS until a strong component ends


        bool* visited = new bool[noOfNodes] { false };// creating a boolean array with the size of number of nodes 
                                                        // to check if a node has been visited
       
        int count = 0; // variable to count the number of nodes in 1 component

        while (!s.isEmpty()) {
            count = 0; // resets count to 0 after every component is traversed
            if (!visited[s.Peek()->val]) {
                DFSUntilTraverse(head[s.pop()], visited, &count); // if node is traversed if it is not flagged as
                                                                    // visited
                cout << endl;
            }
            else
                s.pop(); // node is popped if visited


            if (count > *max)
                *max = count; // storing the max number of nodes in a component
        }

        delete[] visited;
    }
};

int findNode(int* arr, int node, int* NoNodes, bool insertion) { // finding the equivalent node

    for (int i = 0; i < *NoNodes; i++)
        if (arr[i] == node)
            return i;


    if (insertion)
        arr[(*NoNodes)++] = node;
    return -1;

}

int main()
{
    //string path = "twitter_combined.txt"; // setting the path to the file
    string path = "web-Google.txt";

    ifstream fin; // declaring file input object

    fin.open(path); // opening the file

    int* nodeEquivalency = new int[1000000] {-1};

    int node;
    int NoNodes = 0; // variable to store the number of nodes
    int fromNode; // reads the direction of the edge from the node
    int toNode; // read the direction of the edge to the node

    if (fin.is_open()) { // loop to find number of nodes & set equivalant node to every unique node
        while (!fin.eof()) {
            fin >> node;
            findNode(nodeEquivalency, node, &NoNodes, 1);

        }
    }
    if (!fin.eof() && fin.fail())
        cout << "error reading " << path << endl;
    fin.close(); // closing the file
    cout << NoNodes << endl;

    Graph<int> google(NoNodes); // declaring 2 graphs with size being the number of nodes
    Graph<int> googleT(NoNodes);

    fin.open(path);


    // fin >> maxNode;


    if (fin.is_open()) { // opening the file for reading again
        while (!fin.eof()) {

            fin >> fromNode >> toNode;


            fromNode = findNode(nodeEquivalency, fromNode, &NoNodes, 0);
            toNode = findNode(nodeEquivalency, toNode, &NoNodes, 0);
            //cout << fromNode << " -> " << toNode << endl;
            if (fromNode != -1 && toNode != -1) {
                google.insert(fromNode, toNode); // inserting edges to graph object
                googleT.insert(toNode, fromNode); // inserting the transposed edges to 2nd graph object
            }

        }

    }

    if (!fin.eof() && fin.fail())
        cout << "error reading " << path << endl;
    fin.close();

    stack<int> s; // creating a stack object
    int max = 0; // variable to store the length of the biggest Strongly Connected Component
    google.DFS(s); // depth-first traversal of the graph
    googleT.DFSUntil(s, &max); // depth-first traversal of transposed graph and finding value of max

    cout << "Max Length: " << max << endl; // displaying the max length of largest Strongly Connected Component

    return 0;
}