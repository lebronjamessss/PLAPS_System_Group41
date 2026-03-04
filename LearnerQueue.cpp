#include <iostream>
#include "LearnerQueue.hpp"

using namespace std;

LearnerQueue::LearnerQueue() {
    front = -1;
    rear = -1;
    activeCount = 0;
}

bool LearnerQueue::isEmpty() {
    return front == -1;
}

bool LearnerQueue::isFull() {
    return rear == MAX_QUEUE - 1;
}

void LearnerQueue::registerLearner(Learner learner) {

    if (isFull()) {
        cout << "Registration queue is full.\n";
        return;
    }

    if (isEmpty()) {
        front = 0;
    }

    rear++;
    queue[rear] = learner;

    cout << "Learner registered successfully.\n";
}

void LearnerQueue::startSession() {

    if (isEmpty()) {
        cout << "No learners waiting.\n";
        return;
    }

    if (activeCount >= SESSION_CAPACITY) {
        cout << "Session is full.\n";
        return;
    }

    Learner learner = queue[front];

    front++;

    if (front > rear) {
        front = rear = -1;
    }

    activeSession[activeCount] = learner;
    activeCount++;

    cout << learner.name << " entered the session.\n";
}

void LearnerQueue::exitSession(int learnerID) {

    for (int i = 0; i < activeCount; i++) {

        if (activeSession[i].learnerID == learnerID) {

            for (int j = i; j < activeCount - 1; j++) {
                activeSession[j] = activeSession[j + 1];
            }

            activeCount--;

            cout << "Learner exited session.\n";
            return;
        }
    }

    cout << "Learner not found in session.\n";
}

void LearnerQueue::displayQueue() {

    if (isEmpty()) {
        cout << "Registration queue empty.\n";
        return;
    }

    cout << "\nRegistration Queue:\n";

    for (int i = front; i <= rear; i++) {
        cout << queue[i].learnerID << " - "
             << queue[i].name << endl;
    }
}

void LearnerQueue::displayActiveSession() {

    if (activeCount == 0) {
        cout << "No active learners.\n";
        return;
    }

    cout << "\nActive Session:\n";

    for (int i = 0; i < activeCount; i++) {
        cout << activeSession[i].learnerID << " - "
             << activeSession[i].name << endl;
    }
}