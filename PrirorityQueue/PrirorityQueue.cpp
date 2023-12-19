#include <iostream>
using namespace std;

struct Node {
    int data;        
    int priority;    
    Node* next;    

    Node(int d, int p) {
        data = d;        
        priority = p;    
        next = nullptr;   
    }
};

class PriorityQueue {
private:
    Node* front;  

public:
    PriorityQueue() {
        front = nullptr;  
    }

    void enqueue(int data, int priority) {
        Node* newNode = new Node(data, priority);

        if (front == nullptr || priority < front->priority) {
            newNode->next = front;
            front = newNode;
        }
        else {
            Node* temp = front;
            while (temp->next != nullptr && temp->next->priority <= priority) {
                temp = temp->next;
            }
            newNode->next = temp->next;
            temp->next = newNode;
        }
    }

    int dequeue() {
        if (isEmpty()) {
            cerr << "Queue is empty.\n";
            return -1;  
        }

        Node* temp = front;
        int data = temp->data;
        front = front->next;
        delete temp;

        return data;
    }

    bool isEmpty() const {
        return front == nullptr;
    }

    void changePriority(int newData, int newPriority) {
        if (isEmpty()) {
            cerr << "Queue is empty.\n";
            return;
        }

        Node* temp = front;
        while (temp != nullptr && temp->data != newData) {
            temp = temp->next;
        }

        if (temp == nullptr) {
            cerr << "Element not found.\n";
        }
        else {
            temp->priority = newPriority;
        }
    }

    void printQueue() 
    {
        Node* temp = front;
        cout << "Queue: ";
        while (temp != nullptr) {
            cout << "(" << temp->data << ", " << temp->priority << ") ";
            temp = temp->next;
        }
        cout << std::endl;
    }
};


int main() {
    PriorityQueue priorityQueue;

    priorityQueue.enqueue(1, 3);
    priorityQueue.enqueue(2, 1);
    priorityQueue.enqueue(3, 2);

    priorityQueue.printQueue();  

    cout << "Dequeue: " << priorityQueue.dequeue() << endl;

    priorityQueue.changePriority(2, 4);

    priorityQueue.printQueue(); 

    while (!priorityQueue.isEmpty()) {
        cout << "Dequeue: " << priorityQueue.dequeue() << endl;
    }
    return 0;
}