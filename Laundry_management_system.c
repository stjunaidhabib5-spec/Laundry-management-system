#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 1. Struct to hold the input data
typedef struct {
    int room_num;
    char name[50];
    int num_clothes;
    char status[20]; // e.g., "Unwashed", "Washed & Ironed"
} Laundry;

// --- QUEUE IMPLEMENTATION (For Processing Laundry) ---
typedef struct QueueNode {
    Laundry data;
    struct QueueNode* next;
} QueueNode;

QueueNode* front = NULL;
QueueNode* rear = NULL;

void enqueue(Laundry item) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->data = item;
    newNode->next = NULL;
    if (rear == NULL) {
        front = rear = newNode;
        return;
    }
    rear->next = newNode;
    rear = newNode;
}

Laundry dequeue() {
    Laundry empty = {-1, "", 0, ""};
    if (front == NULL) return empty;
    
    QueueNode* temp = front;
    Laundry item = temp->data;
    front = front->next;
    
    if (front == NULL) rear = NULL;
    free(temp);
    return item;
}

int isQueueEmpty() {
    return front == NULL;
}

// --- BINARY SEARCH TREE IMPLEMENTATION (For Storage) ---
typedef struct BSTNode {
    Laundry data;
    struct BSTNode* left;
    struct BSTNode* right;
} BSTNode;

BSTNode* insertBST(BSTNode* root, Laundry item) {
    if (root == NULL) {
        BSTNode* newNode = (BSTNode*)malloc(sizeof(BSTNode));
        newNode->data = item;
        newNode->left = newNode->right = NULL;
        return newNode;
    }
    // Using Room Number as the key for the BST
    if (item.room_num < root->data.room_num) {
        root->left = insertBST(root->left, item);
    } else if (item.room_num > root->data.room_num) {
        root->right = insertBST(root->right, item);
    } else {
        // If room already exists, just update the data (for simplicity)
        root->data = item;
    }
    return root;
}

BSTNode* searchBST(BSTNode* root, int room_num) {
    if (root == NULL || root->data.room_num == room_num) {
        return root;
    }
    if (room_num < root->data.room_num) {
        return searchBST(root->left, room_num);
    }
    return searchBST(root->right, room_num);
}

// --- MAIN SYSTEM FUNCTIONS ---
BSTNode* storageRoot = NULL; // Global BST Root

void receiveOrder() {
    Laundry newOrder;
    printf("\n--- New Laundry Order ---\n");
    printf("Enter Room Number: ");
    scanf("%d", &newOrder.room_num);
    printf("Enter Name: ");
    scanf(" %[^\n]s", newOrder.name); // Space before % to consume newline
    printf("Enter Number of Clothes: ");
    scanf("%d", &newOrder.num_clothes);
    strcpy(newOrder.status, "Unwashed");
    
    enqueue(newOrder);
    printf("Order placed in processing queue.\n");
}

void processLaundry() {
    if (isQueueEmpty()) {
        printf("\nNo laundry in the queue to process.\n");
        return;
    }
    
    // Dequeue from processing queue
    Laundry current = dequeue();
    
    // Update status to Washed & Ironed
    strcpy(current.status, "Washed & Ironed");
    printf("\nProcessing Room %d's laundry...\n", current.room_num);
    printf("Washing and Ironing %d clothes...\n", current.num_clothes);
    
    // Move to BST Storage
    storageRoot = insertBST(storageRoot, current);
    printf("Laundry for Room %d is now in STORAGE.\n", current.room_num);
}

void checkStatus() {
    int room_to_search;
    printf("\nEnter Room Number to check: ");
    scanf("%d", &room_to_search);
    
    // First, check if it's in storage (BST)
    BSTNode* result = searchBST(storageRoot, room_to_search);
    if (result != NULL) {
        printf("\n--- Status: IN STORAGE ---\n");
        printf("Name: %s\n", result->data.name);
        printf("Clothes: %d\n", result->data.num_clothes);
        printf("Condition: %s\n", result->data.status);
        return;
    }
    
    // If not in BST, check if it's in the Queue
    QueueNode* temp = front;
    int position = 1;
    while (temp != NULL) {
        if (temp->data.room_num == room_to_search) {
            printf("\n--- Status: IN QUEUE ---\n");
            printf("Name: %s\n", temp->data.name);
            printf("Condition: %s\n", temp->data.status);
            printf("Queue Position: %d\n", position);
            return;
        }
        temp = temp->next;
        position++;
    }
    
    printf("\nNo record found for Room %d.\n", room_to_search);
}

// --- MAIN MENU ---
int main() {
    int choice;
    
    while (1) {
        printf("\n==================================\n");
        printf("    LAUNDRY MANAGEMENT SYSTEM     \n");
        printf("==================================\n");
        printf("1. Take New Laundry (Enqueue)\n");
        printf("2. Process Next Laundry (Dequeue -> BST)\n");
        printf("3. Check Laundry Status (Search BST/Queue)\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                receiveOrder();
                break;
            case 2:
                processLaundry();
                break;
            case 3:
                checkStatus();
                break;
            case 4:
                printf("Exiting system...\n");
                exit(0);
            default:
                printf("Invalid choice! Try again.\n");
        }
    }
    return 0;
}