#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>

#define MAX_TRANSACTIONS 100

struct Account {
    char name[20];
    char address[200];
    char dob[15];
    char occupation[50];
    char mobileNo[15];
    char aadharNo[20];
    int acc_no;
    int pin;
    int balance;
    int transactionCount;
};

struct Transaction {
    char type[20];
    int amount;
    char timestamp[30];
};

struct Account account;
struct Transaction transactions[MAX_TRANSACTIONS];
int transactionIndex = 0;

enum MenuOptions {
    DEPOSIT = 1,
    WITHDRAW,
    TRANSFER,
    ACCOUNT_DETAILS,
    TRANSACTION_DETAILS,
    UPDATE_DETAILS,
    UPDATE_KYC_DETAILS,
    EXIT
};

void menu();
void performOperation(int option);
void depositMoney();
void withdrawMoney();
void transferMoney();
void checkAccountDetails();
void displayTransactionDetails();
void updateAccountDetails();
void updateKYCDetails();
void saveAccountData();
void loadAccountData();
void driverFunction(); // Declaration of the driver function

int main() {
    driverFunction(); // Call the driver function to collect user information
    loadAccountData(); // Load the account data from the file

    // Prompt user to enter PIN
    int attempt;
    printf("Enter Your Pin to continue: ");
    scanf("%d", &attempt);

    if (attempt == account.pin) {
        int option;
        do {
            menu();
            printf("Enter Your Choice: ");
            scanf("%d", &option);
            performOperation(option);
        } while (option != EXIT);
    } else {
        printf("Entered pin is incorrect\n");
    }
    return 0;
}

void menu() {
    printf("\n\tMENU\n");
    printf("1. Deposit Money\n");
    printf("2. Withdraw Money\n");
    printf("3. Transfer Money\n");
    printf("4. Account Details\n");
    printf("5. Transaction Details\n");
    printf("6. Update Details\n");
    printf("7. Update KYC Details\n");
    printf("8. Exit\n");
}

void performOperation(int option) {
    switch (option) {
        case DEPOSIT:
            depositMoney();
            break;
        case WITHDRAW:
            withdrawMoney();
            break;
        case TRANSFER:
            transferMoney();
            break;
        case ACCOUNT_DETAILS:
            checkAccountDetails();
            break;
        case TRANSACTION_DETAILS:
            displayTransactionDetails();
            break;
        case UPDATE_DETAILS:
            updateAccountDetails();
            break;
        case UPDATE_KYC_DETAILS:
            updateKYCDetails();
            break;
        case EXIT:
            saveAccountData();
            break;
        default:
            printf("**Invalid choice**\n");
    }
}

void depositMoney() {
    time_t currentTime;
    time(&currentTime);
    struct tm *localTime = localtime(&currentTime);

    printf("* DEPOSITING MONEY *\n");
    printf("Enter the amount you want to deposit: ");
    int depositAmount;
    scanf("%d", &depositAmount);
    account.balance += depositAmount;
    printf("Money Deposited: Rs %d\n", depositAmount);
    printf("Current Balance: Rs %d\n", account.balance);

    // Updating transaction details
    strcpy(transactions[transactionIndex].type, "Deposit");
    transactions[transactionIndex].amount = depositAmount;
    strftime(transactions[transactionIndex].timestamp, 30, "%Y-%m-%d %H:%M:%S", localTime);
    transactionIndex++;
}

void withdrawMoney() {
    time_t currentTime;
    time(&currentTime);
    struct tm *localTime = localtime(&currentTime);

    printf("* WITHDRAWING MONEY *\n");
    printf("Enter the amount you want to withdraw: ");
    int withdrawAmount;
    scanf("%d", &withdrawAmount);

    if (account.balance < withdrawAmount) {
        printf("Insufficient balance\n");
    } else {
        account.balance -= withdrawAmount;
        printf("Money Withdrawn: Rs %d\n", withdrawAmount);
        printf("Current Balance: Rs %d\n", account.balance);

        // Updating transaction details
        strcpy(transactions[transactionIndex].type, "Withdraw");
        transactions[transactionIndex].amount = withdrawAmount;
        strftime(transactions[transactionIndex].timestamp, 30, "%Y-%m-%d %H:%M:%S", localTime);
        transactionIndex++;
    }
}

void transferMoney() {
    time_t currentTime;
    time(&currentTime);
    struct tm *localTime = localtime(&currentTime);

    printf("* TRANSFERRING MONEY *\n");
    printf("Enter the account no. to which you want to transfer money: ");
    int recipientAccount;
    scanf("%d", &recipientAccount);

    printf("Enter the amount you want to transfer: ");
    int transferAmount;
    scanf("%d", &transferAmount);

    if (account.balance < transferAmount) {
        printf("Insufficient balance\n");
    } else {
        account.balance -= transferAmount;
        printf("Money Transferred: Rs %d to Account No. %d\n", transferAmount, recipientAccount);
        printf("Current Balance: Rs %d\n", account.balance);

        // Updating transaction details
        strcpy(transactions[transactionIndex].type, "Transfer");
        transactions[transactionIndex].amount = transferAmount;
        strftime(transactions[transactionIndex].timestamp, 30, "%Y-%m-%d %H:%M:%S", localTime);
        transactionIndex++;
    }
}

void checkAccountDetails() {
    printf("ACCOUNT DETAILS\n");
    printf("Name: %s\n", account.name);
    printf("Account No: %d\n", account.acc_no);
    printf("Mobile No: %s\n", account.mobileNo);
    printf("Aadhar No: %s\n", account.aadharNo);
    printf("Address: %s\n", account.address);
    printf("Date of Birth: %s\n", account.dob);
    printf("Occupation: %s\n", account.occupation);
    printf("Total Balance: Rs %d\n", account.balance);
    printf("Transaction Count: %d\n", account.transactionCount);
}

void displayTransactionDetails() {
    printf("TRANSACTION DETAILS\n");
    for (int i = 0; i < transactionIndex; i++) {
        printf("Type: %s, Amount: Rs %d, Timestamp: %s\n", 
            transactions[i].type, transactions[i].amount, transactions[i].timestamp);
    }
}

void updateAccountDetails() {
    printf("UPDATE ACCOUNT DETAILS\n");
    printf("Enter Updated Mobile No.: ");
    scanf("%s", account.mobileNo);
    printf("Enter Updated Aadhar No.: ");
    scanf("%s", account.aadharNo);
    printf("Enter Updated Address: ");
    scanf("%s", account.address);
    printf("Enter Updated Date of Birth (DD-MM-YYYY): ");
    scanf("%s", account.dob);
    printf("Enter Updated Occupation: ");
    scanf("%s", account.occupation);
}

void updateKYCDetails() {
    printf("UPDATE KYC DETAILS\n");
    printf("Enter Updated Mobile No.: ");
    scanf("%s", account.mobileNo);
    printf("Enter Updated Name: ");
    scanf("%s", account.name);
    printf("Enter Updated Date of Birth (DD-MM-YYYY): ");
    scanf("%s", account.dob);
    printf("Enter Updated Occupation: ");
    scanf("%s", account.occupation);
}

void saveAccountData() {
    FILE *file = fopen("AccountData.txt", "w");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        return;
    }

    fprintf(file, "Name: %s\n", account.name);
    fprintf(file, "Account No: %d\n", account.acc_no);
    fprintf(file, "Mobile No: %s\n", account.mobileNo);
    fprintf(file, "Aadhar No: %s\n", account.aadharNo);
    fprintf(file, "Address: %s\n", account.address);
    fprintf(file, "Balance: %d\n", account.balance);
    fprintf(file, "Transaction Count: %d\n", transactionIndex);
    fprintf(file, "Date of Birth: %s\n", account.dob);
    fprintf(file, "Occupation: %s\n", account.occupation);

    fclose(file);
}

void loadAccountData() {
    FILE *file = fopen("AccountData.txt", "r");
    if (file == NULL) {
        printf("Error opening file for reading!\n");
        return;
    }

    fscanf(file, "Name: %s\n", account.name);
    fscanf(file, "Account No: %d\n", &account.acc_no);
    fscanf(file, "Mobile No: %s\n", account.mobileNo);
    fscanf(file, "Aadhar No: %s\n", account.aadharNo);
    fscanf(file, "Address: %s\n", account.address);
    fscanf(file, "Balance: %d\n", &account.balance);
    fscanf(file, "Transaction Count: %d\n", &transactionIndex);
    fscanf(file, "Date of Birth: %s\n", account.dob);
    fscanf(file, "Occupation: %s\n", account.occupation);

    fclose(file);
}

void driverFunction() {
    FILE *ptr = fopen("Account.txt", "w");

    printf("Enter Your Name: ");
    scanf("%s", account.name);
    fprintf(ptr, "Name : %s\n", account.name);
    printf("Enter Your Mobile No.: ");
    scanf("%s", account.mobileNo);
    fprintf(ptr, "Mobile No. : %s\n", account.mobileNo);
    printf("Enter Your Address: ");
    scanf("%s", account.address);
    fprintf(ptr, "Address : %s\n", account.address);
    printf("Enter Your Aadhar No: ");
    scanf("%s", account.aadharNo);
    fprintf(ptr, "Aadhar No. : %s\n", account.aadharNo);
    printf("Enter Your Date of Birth (DD-MM-YYYY): ");
    scanf("%s", account.dob);
    fprintf(ptr, "Date of Birth : %s\n", account.dob);
    printf("Enter Your Occupation: ");
    scanf("%s", account.occupation);
    fprintf(ptr, "Occupation : %s\n", account.occupation);
    printf("Create Your 4 Digit pin: ");
    scanf("%d", &account.pin);
    fprintf(ptr, "PIN : %d\n", account.pin);
    
    fclose(ptr);
}
