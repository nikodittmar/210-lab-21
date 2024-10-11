#include <iostream>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

const int NUM_NAMES = 15;
const int NUM_COLORS = 15;

class Goat {
private:
    int age;
    string name;
    string color;
    static string names[NUM_NAMES];
    static string colors[NUM_COLORS];
public:
    Goat() {
        age = rand() % 20 + 1;
        name = names[rand() % 15];
        color = colors[rand() % 15];
    }

    Goat(int a, string n, string c) {
        age = a;
        name = n;
        color = c;
    }

    void print() {
        cout << "Goat | Name: "<< name << " Age: " << age << " Color: " << color;
    }
};

string Goat::colors[NUM_COLORS] = {
    "White", "Black", "Brown", "Gray", "Golden",
    "Spotted", "Cream", "Tan", "Silver", "Beige",
    "Charcoal", "Chestnut", "Mahogany", "Pale Yellow", "Dark Brown"
};

string Goat::names[NUM_NAMES] = {
    "Billy", "Nanny", "Gruff", "Bucky", "Tilly",
    "Luna", "Bella", "Shadow", "Snowy", "Clover",
    "Willow", "Blanca", "Pebbles", "Mocha", "Hazel"
};

class DoublyLinkedList {
private:
    struct Node {
        Goat* goat;
        Node* prev;
        Node* next;
        Node(Goat *val, Node* p = nullptr, Node* n = nullptr) {
            goat = val; 
            prev = p;
            next = n;
        }
    };

    Node* head;
    Node* tail;

public:
    // constructor
    DoublyLinkedList() { head = nullptr; tail = nullptr; }

    void push_back(Goat *g) {
        Node* newNode = new Node(g);
        if (!tail)  // if there's no tail, the list is empty
            head = tail = newNode;
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(Goat *g) {
        Node* newNode = new Node(g);
        if (!head)  // if there's no head, the list is empty
            head = tail = newNode;
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void insert_after(Goat *g, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }

        Node* newNode = new Node(g);
        if (!head) {
            head = tail = newNode;
            return;
        }

        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;

        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }

        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode; // Inserting at the end
        temp->next = newNode;
    }

    void delete_node(Goat *g) {
        if (!head) return; // Empty list

        Node* temp = head;
        while (temp && temp->goat != g)
            temp = temp->next;

        if (!temp) return; // Value not found

        if (temp->prev) {
            temp->prev->next = temp->next;
        } else {
            head = temp->next; // Deleting the head
        }

        if (temp->next) {
            temp->next->prev = temp->prev;
        } else {
            tail = temp->prev; // Deleting the tail
        }

        delete temp;
    }

    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty" << endl;
            return;
        };
        while (current) {
            current->goat->print();
            cout << endl;
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) {
            cout << "List is empty" << endl;
            return;
        };
        while (current) {
            current->goat->print();
            cout << endl;
            current = current->prev;
        }
        cout << endl;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

// Driver program
int main() {
    srand(time(0));

    DoublyLinkedList list;

    cout << "Test print and print reverse.";
    list.print();
    list.print_reverse();

    int size = rand() % (MAX_LS-MIN_LS+1) + MIN_LS;

    for (int i = 0; i < size; ++i) {
        list.push_back(new Goat());
    }

    cout << "List forward: " << endl;
    list.print();

    cout << "List backward: " << endl;
    list.print_reverse();

    cout << "Deleting list, then trying to print.\n";
    list.~DoublyLinkedList();
    cout << "List forward: " << endl;
    list.print();


    return 0;
}
