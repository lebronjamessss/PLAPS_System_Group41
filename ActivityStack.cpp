#include <iostream>
#include "ActivityStack.hpp"

using namespace std;

ActivityStack::ActivityStack() {
    top = -1;
    nextActivityID = 1;
}

bool ActivityStack::isEmpty() {
    return top == -1;
}

bool ActivityStack::isFull() {
    return top == MAX_STACK - 1;
}

void ActivityStack::push(Activity activity) {

    if (isFull()) {
        cout << "Stack overflow. Cannot add more activities.\n";
        return;
    }

    top++;
    stack[top] = activity;
    
}

void ActivityStack::pop() {

    if (isEmpty()) {
        cout << "No activity to undo.\n";
        return;
    }

    cout << "Undoing activity: " << stack[top].topic << endl;

    top--;
}

Activity ActivityStack::peek() {

    if (isEmpty()) {
        cout << "No current activity.\n";
        return Activity();
    }

    return stack[top];
}

void ActivityStack::display() {

    if (isEmpty()) {
        cout << "No activities completed yet.\n";
        return;
    }

    cout << "\n===== Activity History (Stack) =====\n";

    for (int i = top; i >= 0; i--) {

        cout << "Learner ID: " << stack[i].learnerID << endl;
        cout << "Activity ID: " << stack[i].activityID << endl;
        cout << "Topic: " << stack[i].topic << endl;
        cout << "Difficulty: " << stack[i].difficulty << endl;
        cout << "Score: " << stack[i].score << endl;
        cout << "-----------------------------\n";
    }
}

int ActivityStack::generateActivityID() {
    return nextActivityID++;
}