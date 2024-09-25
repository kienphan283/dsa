#include <iostream>
#include <cmath>
#include <unordered_set>

using namespace std;

class Node {
public:
    int data;
    Node* next;
};

void insert_node(Node** head, int data) {
    Node* newNode = new Node();
    newNode->data = data;
    newNode->next = nullptr;

    if (*head == nullptr) {
        *head = newNode;
        return;
    }

    Node* temp = *head;
    while (temp->next != nullptr) {
        temp = temp->next;
    }

    temp->next = newNode;
}

void printList(Node* head) {
    while (head != nullptr) {
        cout << head->data << " ";
        head = head->next;
    }
    cout << endl;
}

// Bai 1: Find the Middle Node of a Linked List
void findMiddle(Node* head) {
    if (head == nullptr) {
        cout << "This list is empty" << endl;
        return;
    }

    // count node
    int count = 0;
    Node* current = head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }

    // find middle
    current = head;
    if (count % 2 == 0) {
        // even node
        int middleFloor = count / 2 - 1;
        int middleCeil = count / 2;

        for (int i = 0; i < middleCeil; i++) {
            if (i == middleFloor) {
                cout << "The middle floor element is: " << current->data << endl;
            }
            current = current->next;
        }
        cout << "The middle ceil element is: " << current->data << endl;
    } else {
        // odd node
        int middle = count / 2;
        for (int i = 0; i < middle; i++) {
            current = current->next;
        }
        cout << "The middle element is: " << current->data << endl;
    }
}

// Bai 2: Detect a Cycle in a Linked List
bool detectValueCycle(Node* head) {
    unordered_set<int> visitedValues; // Tập hợp để theo dõi các giá trị đã gặp
    Node* current = head;

    while (current != nullptr) {
        if (visitedValues.find(current->data) != visitedValues.end()) {
            return true;  // Giá trị đã được gặp, coi như có "vòng"
        }
        visitedValues.insert(current->data); // Thêm giá trị vào tập hợp
        current = current->next; // Di chuyển đến nút tiếp theo
    }

    return false;  // Không phát hiện vòng
}

// Bai 3: Combine Two Sorted Linked Lists
Node* mergeSortedLists(Node* l1, Node* l2) {
    if (!l1) return l2;
    if (!l2) return l1;

    if (l1->data < l2->data) {
        l1->next = mergeSortedLists(l1->next, l2);
        return l1;
    } else {
        l2->next = mergeSortedLists(l1, l2->next);
        return l2;
    }
}

// Bai 4: Find the Intersection of Two Linked Lists
int getLength(Node* head) {
    int length = 0;
    while (head) {
        length++;
        head = head->next;
    }
    return length;
}

Node* findIntersection(Node* headA, Node* headB) {
    int lenA = getLength(headA);
    int lenB = getLength(headB);

    while (lenA > lenB) {
        headA = headA->next;
        lenA--;
    }

    while (lenB > lenA) {
        headB = headB->next;
        lenB--;
    }

    while (headA && headB) {
        if (headA == headB) {
            return headA;
        }
        headA = headA->next;
        headB = headB->next;
    }

    return nullptr;
}

// Bai 5: Reverse a Linked List
Node* reverseList(Node* head) {
    Node* prev = nullptr;
    Node* current = head;
    Node* next = nullptr;

    while (current != nullptr) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    return prev;
}

// Bai 6: Eliminate Duplicates from a Sorted Linked List
void removeDuplicates(Node* head) {
    if (head == nullptr) return;

    Node* current = head;
    while (current->next != nullptr) {
        if (current->data == current->next->data) {
            Node* temp = current->next;
            current->next = current->next->next;
            delete temp;
        } else {
            current = current->next;
        }
    }
}

// Bai 7: Check if a Linked List is a Palindrome
bool isPalindrome(Node* head) {
    if (!head || !head->next) return true;

    Node* slow = head;
    Node* fast = head;
    while (fast->next && fast->next->next) {
        slow = slow->next;
        fast = fast->next->next;
    }

    Node* secondHalf = reverseList(slow->next);
    Node* firstHalf = head;

    while (secondHalf != nullptr) {
        if (firstHalf->data != secondHalf->data) {
            return false;
        }
        firstHalf = firstHalf->next;
        secondHalf = secondHalf->next;
    }

    return true;
}

/* Bai 8: Write a function to search for nodes with the value X in the list. If found, return
 the addresses of the nodes; if not found, return NULL. */
Node* search(Node* head, int X) {
    Node* current = head;
    while (current != nullptr) {
        if (current->data == X) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

int countList(Node* head){
    Node* current = head;
    int count = 0;
    while (current != nullptr){
        count++;
        current = current->next;
    }
    return count;
}

// Menu cho các chức năng
int main() {
    Node* head = nullptr;
    int choice, value;

    insert_node(&head, 1);
    insert_node(&head, 2);
    insert_node(&head, 3);
    insert_node(&head, 4);
    insert_node(&head, 5);
    insert_node(&head, 6);

    do {
        cout << "\nMenu:\n";
        cout << "1. Find the middle element\n";
        cout << "2. Detect cycle in the list\n";
        cout << "3. Merge two sorted lists\n";
        cout << "4. Find the intersection of two lists\n";
        cout << "5. Reverse the list\n";
        cout << "6. Remove duplicates from the list\n";
        cout << "7. Check if the list is a palindrome\n";
        cout << "8. Search for a node with value X\n";
        cout << "9. Print positions of elements\n";
        cout << "10. Print List\n";
        cout << "11. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            findMiddle(head);
            break;
        case 2:
            if (detectCycle(head)) {
                cout << "Cycle detected!" << endl;
            } else {
                cout << "No cycle detected." << endl;
            }
            break;
        case 3: {
            Node* list2 = nullptr;
            insert_node(&list2, 10);
            insert_node(&list2, 20);
            insert_node(&list2, 30);
            Node* merged = mergeSortedLists(head, list2);
            printList(merged);
            break;
        }
        case 4: {
            Node* list2 = nullptr;
            insert_node(&list2, 4);
            insert_node(&list2, 5);
            Node* intersection = findIntersection(head, list2);
            if (intersection) {
                cout << "Intersection at node with value: " << intersection->data << endl;
            } else {
                cout << "No intersection found." << endl;
            }
            break;
        }
        case 5: {
            head = reverseList(head);
            printList(head);
            break;
        }
        case 6: {
            removeDuplicates(head);
            printList(head);
            break;
        }
        case 7: {
            if (isPalindrome(head)) {
                cout << "The list is a palindrome." << endl;
            } else {
                cout << "The list is not a palindrome." << endl;
            }
            break;
        }
        case 8: {
            cout << "Enter value to search: ";
            cin >> value;
            Node* result = search(head, value);
            if (result) {
                cout << "Node found with value: " << result->data << " at address: " << result << endl;
            } else {
                cout << "Node not found." << endl;
            }
            break;
        }
        case 9: {
            cout << "Position: \n";
            Node* current = head;
            for (int i = 0; current != nullptr; i++) {
                cout << "Position " << i << ": " << current->data << endl;
                current = current->next; // Di chuyển đến nút tiếp theo
            }
            break;
        }
        case 10: {
            cout<<"Print List: ";
            printList(head);
            break;
        }
        case 11: {
            cout << "Exiting..." << endl;
            break;
        }
        default:{
            cout << "Invalid choice!" << endl;
            break;
        }
        }
    } while (choice != 11);

    return 0;
}
