#include <iostream>
#include "LearnerQueue.hpp"

using namespace std;

LearnerQueue::LearnerQueue() {
    front = -1;
    rear = -1;
    activeCount = 0;
    nextLearnerID = 1001;
}

bool LearnerQueue::isEmpty() {
    return front == -1;
}

bool LearnerQueue::isFull() {
    return rear == MAX_QUEUE - 1;
}

int LearnerQueue::generateLearnerID() {
    return nextLearnerID++;
}

void LearnerQueue::registerLearner(Learner learner) {

    if (isFull()) {
        cout << "\nRegistration queue is full. Cannot register more learners.\n";
        return;
    }

    if (learner.name.empty()) {
        cout << "\nInvalid name. Registration failed.\n";
        return;
    }

    if (isEmpty()) {
        front = 0;
    }

    rear++;
    queue[rear] = learner;

    int position = rear - front + 1;

    cout << "\nLearner registered successfully.\n";
    cout << "Learner ID: " << learner.learnerID << endl;
    cout << "Queue position: " << position << endl;
}

void LearnerQueue::startSession() {

    if (isEmpty()) {
        cout << "\nNo learners waiting in the queue.\n";
        return;
    }

    if (activeCount >= SESSION_CAPACITY) {
        cout << "\nSession is full. Cannot add more learners.\n";
        return;
    }

    Learner learner = queue[front];

    front++;

    if (front > rear) {
        front = rear = -1;
    }

    activeSession[activeCount] = learner;
    activeCount++;

    cout << "\nLearner entered session successfully.\n";
    cout << learner.learnerID << " - " << learner.name << endl;
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
        cout << "\n===== Registration Queue =====\n";
        cout << "No learners waiting.\n";
        return;
    }

    cout << "\n===== Registration Queue =====\n";

    int position = 1;

    for (int i = front; i <= rear; i++) {
        cout << position << ". "
             << queue[i].learnerID << " - "
             << queue[i].name << endl;
        position++;
    }
}

void LearnerQueue::displayActiveSession() {

    cout << "\n===== Active Session =====\n";
    cout << "Capacity: " << activeCount << " / " << SESSION_CAPACITY << endl;

    if (activeCount == 0) {
        cout << "No learners currently in session.\n";
        return;
    }

    for (int i = 0; i < activeCount; i++) {
        cout << i + 1 << ". "
             << activeSession[i].learnerID << " - "
             << activeSession[i].name << endl;
    }
}

bool LearnerQueue::learnerExists(int learnerID) {

    // Check queue
    for (int i = front; i <= rear; i++) {
        if (queue[i].learnerID == learnerID)
            return true;
    }

    // Check active session
    for (int i = 0; i < activeCount; i++) {
        if (activeSession[i].learnerID == learnerID)
            return true;
    }

    return false;
}