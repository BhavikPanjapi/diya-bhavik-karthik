#include <stdio.h>
#include <string.h>

#define MAX 100


struct Customer {
    char name[50];
    char phoneNumber[15];
    float usage;
    float totalBill;
};


struct Stack {
    struct Customer customers[MAX];
    int top;
} customerStack;


struct Queue {
    struct Customer customers[MAX];
    int front, rear;
} paymentQueue;


void initStructures() {
    customerStack.top = -1;
    paymentQueue.front = -1;
    paymentQueue.rear = -1;
}


int isStackFull() {
    return customerStack.top == MAX - 1;
}

int isStackEmpty() {
    return customerStack.top == -1;
}

void pushToStack(struct Customer cust) {
    if (!isStackFull()) {
        customerStack.customers[++customerStack.top] = cust;
        printf("\nRecord added successfully!\n");
    } else {
        printf("\nStack overflow! Cannot add more records.\n");
    }
}

void popFromStack() {
    if (!isStackEmpty()) {
        customerStack.top--;
        printf("\nRecord removed successfully!\n");
    } else {
        printf("\nStack underflow! No records to remove.\n");
    }
}


int isQueueFull() {
    return (paymentQueue.rear + 1) % MAX == paymentQueue.front;
}

int isQueueEmpty() {
    return paymentQueue.front == -1;
}

void enqueuePayment(struct Customer cust) {
    if (!isQueueFull()) {
        if (paymentQueue.front == -1) paymentQueue.front = 0;
        paymentQueue.rear = (paymentQueue.rear + 1) % MAX;
        paymentQueue.customers[paymentQueue.rear] = cust;
        printf("\nPayment added to queue!\n");
    } else {
        printf("\nQueue overflow! Cannot add more payments.\n");
    }
}

void dequeuePayment() {
    if (!isQueueEmpty()) {
        printf("\nProcessing payment for: %s\tTotal Bill: %.2f\n", paymentQueue.customers[paymentQueue.front].name, paymentQueue.customers[paymentQueue.front].totalBill);
        if (paymentQueue.front == paymentQueue.rear) {
            paymentQueue.front = paymentQueue.rear = -1;  // Reset queue
        } else {
            paymentQueue.front = (paymentQueue.front + 1) % MAX;
        }
    } else {
        printf("\nNo payments in the queue to process.\n");
    }
}


void addRecord() {
    if (!isStackFull()) {
        struct Customer cust;
        printf("\nEnter name: ");
        scanf(" %[^\n]s", cust.name);
        printf("Enter phone number: ");
        scanf("%s", cust.phoneNumber);
        printf("Enter usage (in minutes): ");
        scanf("%f", &cust.usage);
        cust.totalBill = cust.usage * 0.1;

        pushToStack(cust);
        enqueuePayment(cust);
    }
}

void viewRecords() {
    printf("\nName\tPhone Number\tUsage(min)\tTotal Bill($)\n");
    for (int i = 0; i <= customerStack.top; i++) {
        printf("%s\t%s\t%.2f\t\t%.2f\n", customerStack.customers[i].name, customerStack.customers[i].phoneNumber, customerStack.customers[i].usage, customerStack.customers[i].totalBill);
    }
}

void deleteRecord() {
    if (!isStackEmpty()) {
        popFromStack();
    } else {
        printf("\nNo records to delete.\n");
    }
}

void processPayments() {
    if (!isQueueEmpty()) {
        dequeuePayment();
    } else {
        printf("\nNo payments to process.\n");
    }
}

void displayMenu() {
    printf("\n1. Add New Record\n");
    printf("2. View List of Records\n");
    printf("3. Delete Last Record\n");
    printf("4. Process Payment\n");
    printf("5. Exit\n");
}

int main() {
    int choice;
    initStructures();

    while (1) {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            addRecord();
            break;
        case 2:
            viewRecords();
            break;
        case 3:
            deleteRecord();
            break;
        case 4:
            processPayments();
            break;
        case 5:
            return 0;
        default:
            printf("\nInvalid choice! Please try again.\n");
        }
    }

    return 0;
}


















