#include <iostream>

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

int main() {

    int choice;

    do {

        showMainMenu();
        cin >> choice;

        if (choice == 1) {
            cout << "\n[Task 1 - Queue Module]\n";
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