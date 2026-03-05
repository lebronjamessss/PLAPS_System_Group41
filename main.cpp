#include <iostream>
#include "LearnerQueue.hpp"
#include "Learner.hpp"

using namespace std;

void showMainMenu() {
    cout << "\n===== PLAPS SYSTEM =====\n";
    cout << "1. Learner Registration & Session Management (Queue)\n";
    cout << "2. Activity Navigation & Session Flow (Stack)\n";
    cout << "3. Recent Activity Logging (Circular Queue)\n";
    cout << "4. At-Risk Learner Priority (Priority Queue)\n";
    cout << "5. Exit\n";
    cout << "Choose option: ";
}

void showLearnerMenu() {
    cout << "\n===== Learner Registration & Session Management =====\n";
    cout << "1. Register Learner\n";
    cout << "2. Start Session (Move learner from queue)\n";
    cout << "3. Exit Session\n";
    cout << "4. Show Registration Queue\n";
    cout << "5. Show Active Session\n";
    cout << "6. Back\n";
    cout << "Choose option: ";
}

int main() {

    LearnerQueue learnerQueue;

    int choice;

    do {

        showMainMenu();
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        if (choice == 1) {

            int option;

            do {

                showLearnerMenu();
                if (!(cin >> option)) {
                    cin.clear();
                    cin.ignore(1000, '\n');
                    cout << "Invalid input. Please enter a number.\n";
                    continue;
                }

                if (option == 1) {

                    Learner learner;

                    cin.ignore(1000, '\n');

                    cout << "Enter Learner Name: ";
                    getline(cin, learner.name);

                    // validate name BEFORE generating ID
                    bool validName = false;

                    for (char c : learner.name) {
                        if (!isspace(c)) {
                            validName = true;
                            break;
                        }
                    }

                    if (!validName) {
                        cout << "\nInvalid name. Registration failed.\n";
                        continue;
                    }

                    learner.learnerID = learnerQueue.generateLearnerID();

                    learnerQueue.registerLearner(learner);
                }

                else if (option == 2) {
                    learnerQueue.startSession();
                }

                else if (option == 3) {

                    int id;

                    cout << "Enter learner ID to exit session: ";
                    if (!(cin >> id)) {
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cout << "Invalid learner ID.\n";
                        continue;
                    }

                    learnerQueue.exitSession(id);
                }

                else if (option == 4) {
                    learnerQueue.displayQueue();
                }

                else if (option == 5) {
                    learnerQueue.displayActiveSession();
                }

            } while (option != 6);
        }

        else if (choice == 2) {
            cout << "\n[Task 2 - Stack Module]\n";
        }

        else if (choice == 3) {
            cout << "\n[Task 3 - Circular Queue Module]\n";
        }

        else if (choice == 4) {
            cout << "\n[Task 4 - Priority Queue Module]\n";
        }

    } while (choice != 5);

    cout << "System exiting.\n";

    return 0;
}