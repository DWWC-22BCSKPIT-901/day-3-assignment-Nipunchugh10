#include <iostream>
#include <vector> // Include vector header
using namespace std;

// Definition for singly-linked list.
struct ListNode {
    int val;
    ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

// Function to reverse a linked list
ListNode* reverseList(ListNode* head) {
    ListNode* prev = nullptr;
    ListNode* curr = head;
    while (curr != nullptr) {
        ListNode* nextTemp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nextTemp;
    }
    return prev;
}

// Function to check if the linked list is a palindrome
bool isPalindrome(ListNode* head) {
    if (head == nullptr || head->next == nullptr) return true;

    // Step 1: Find the middle of the linked list
    ListNode* slow = head;
    ListNode* fast = head;
    while (fast != nullptr && fast->next != nullptr) {
        slow = slow->next;
        fast = fast->next->next;
    }

    // Step 2: Reverse the second half of the list
    ListNode* secondHalf = reverseList(slow);

    // Step 3: Compare the two halves
    ListNode* firstHalf = head;
    ListNode* temp = secondHalf; // To restore the list later
    bool isPalin = true;

    while (temp != nullptr) {
        if (firstHalf->val != temp->val) {
            isPalin = false;
            break;
        }
        firstHalf = firstHalf->next;
        temp = temp->next;
    }

    // Step 4: Restore the list to its original state
    reverseList(secondHalf);

    return isPalin;
}

// Helper function to create a linked list from an array
ListNode* createLinkedList(const vector<int>& values) {
    if (values.empty()) return nullptr;
    ListNode* head = new ListNode(values[0]);
    ListNode* current = head;
    for (size_t i = 1; i < values.size(); i++) {
        current->next = new ListNode(values[i]);
        current = current->next;
    }
    return head;
}

// Helper function to free the linked list
void freeLinkedList(ListNode* head) {
    while (head != nullptr) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

// Main function to test the implementation
int main() {
    vector<int> values = {1, 2, 2, 1}; // Example 1
    // vector<int> values = {1, 2}; // Example 2

    ListNode* head = createLinkedList(values);
    if (isPalindrome(head)) {
        cout << "The linked list is a palindrome." << endl;
    } else {
        cout << "The linked list is not a palindrome." << endl;
    }

    // Free the linked list to avoid memory leaks
    freeLinkedList(head);

    return 0;
}