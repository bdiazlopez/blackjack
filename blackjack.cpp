#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include "screen_utils.h"

struct Status {
    std::string input;
    int deck_num;
    bool valid;
    bool complete;
    bool exit;

    Status() {
        input = "\0";
        deck_num = 2;
        valid = false;
        complete = false;
        exit = false;
    }
} status;

struct Cards {
    const char* name;
    int value;
    int amount;
};

struct Node {
    int data;
    Node* next;

    Node(int value) {
        data = value;
        next = nullptr;
    }
};

class Deck {
private:
    Node* head;

protected:
    Cards rank[13];

public:
    Deck(const Status& status) {
        head = nullptr;

        rank[0].name = "Ace";    rank[0].value = 1;
        rank[1].name = "Two";    rank[1].value = 2;
        rank[2].name = "Three";  rank[2].value = 3;
        rank[3].name = "Four";   rank[3].value = 4;
        rank[4].name = "Five";   rank[4].value = 5;
        rank[5].name = "Six";    rank[5].value = 6;
        rank[6].name = "Seven";  rank[6].value = 7;
        rank[7].name = "Eight";  rank[7].value = 8;
        rank[8].name = "Nine";   rank[8].value = 9;
        rank[9].name = "Ten";    rank[9].value = 10;
        rank[10].name = "King";  rank[10].value = 10;
        rank[11].name = "Queen"; rank[11].value = 10;
        rank[12].name = "Jack";  rank[12].value = 10;

        for (int i = 0; i < 13; i++) {
            rank[i].amount = 4 * status.deck_num;
        }

    }

    ~Deck() {
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            delete current;
            current = next;
        }
    }

    void prepend(int value) {
        Node* newNode = new Node(value);
        newNode->next = head; // New node points to the current head
        head = newNode;       // Update head to the new node
    }

    void remove(int value) {
        if (head == nullptr) return; // Empty list

        if (head->data == value) {
            Node* temp = head;
            head = head->next; // Update head to the next node
            delete temp;       // Free memory
            return;
        }

        Node* current = head;
        while (current->next != nullptr && current->next->data != value) {
            current = current->next; // Traverse the list
        }

        if (current->next != nullptr) { // Node with the value found
            Node* temp = current->next;
            current->next = current->next->next; // Skip the node to be deleted
            delete temp;                         // Free memory
        }
    }

    void print() const {
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->data << " -> ";
            current = current->next;
        }
        std::cout << "nullptr" << std::endl;
    }
};

void welcome_message();
void input_prompt();
void invalid_user_input();
void completion_message();
void termination_message();
void exit_message();

int main(int argc, char* argv[]) {
    srand((unsigned int)time(NULL));

    if (argc > 1) {
        status.deck_num = std::stoi(argv[1]);
    }
    Deck game(status);

    save_screen();
    clear_screen();
    welcome_message();

    while (!status.complete && !status.exit) {
        if (status.input == "s" || status.input == "h") {
            status.complete = true;
        }
        while (!status.valid && !status.exit) {
            input_prompt();
            getline(std::cin, status.input);
            if (status.input != "s" && status.input != "h") {
                if (status.input == "0") {
                    status.exit = true;
                } else {
                    invalid_user_input();
                }
            } else {
                status.valid = true;
            }
        }
    }
    
    status.complete ? completion_message() : termination_message();
    exit_message();
    getline(std::cin, status.input);
    restore_screen();

    return 0;
}

void welcome_message() {
    std::cout << "Welcome to Blackjack\n";
    std::cout << "--------------------\n";
    std::cout << "Enter '0' at any time to exit command line execution\n";
    std::cout << "----------------------------------------------------\n";
}

void input_prompt() {
    std::cout << "\t[ s ] Stand\t[ h ] Hit\n\n";
    std::cout << "Would you like to hit or stand? ";
}

void invalid_user_input() {
    clear_lines(3);
    std::cout << "Please enter valid input.\n";
    move_cursor(4);
}

void completion_message() {
    std::cout << "Program execution complete.\n";
}

void termination_message() {
    std::cout << "Termination by user input.\n";
}

void exit_message() {
    std::cout << "Thank you for playing!\n\t";
    std::cout << "-Press enter to return. ";
}

