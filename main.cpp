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
        cin >> choice;

        if (choice == 1) {

            int option;

            do {

                showLearnerMenu();
                cin >> option;

                if (option == 1) {

                    Learner learner;

                    cout << "Enter Learner ID: ";
                    cin >> learner.learnerID;

                    cout << "Enter Name: ";
                    cin >> learner.name;

                    learnerQueue.registerLearner(learner);
                }

                else if (option == 2) {
                    learnerQueue.startSession();
                }

                else if (option == 3) {

                    int id;

                    cout << "Enter learner ID to exit session: ";
                    cin >> id;

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