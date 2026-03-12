#include <iostream>
#include <fstream>
#include "ActivityLogCircularQueue.hpp"

using namespace std;

ActivityLogCircularQueue::ActivityLogCircularQueue() {
    front = 0;
    rear = -1;
    count = 0;
}

bool ActivityLogCircularQueue::isEmpty() {
    return count == 0;
}

bool ActivityLogCircularQueue::isFull() {
    return count == MAX_LOG;
}

void ActivityLogCircularQueue::addLog(Activity activity) {

    // If full → overwrite oldest record
    if (isFull()) {
        front = (front + 1) % MAX_LOG;
        count--;
    }

    rear = (rear + 1) % MAX_LOG;

    logs[rear] = activity;

    count++;
}

void ActivityLogCircularQueue::displayLogs() {

    if (isEmpty()) {
        cout << "\nNo activity logs available.\n";
        return;
    }

    cout << "\n===== Activity Logs =====\n";

    int index = front;

    for (int i = 0; i < count; i++) {

        Activity a = logs[index];

        cout << "Learner ID: " << a.learnerID << endl;
        cout << "Activity ID: " << a.activityID << endl;
        cout << "Topic: " << a.topic << endl;
        cout << "Difficulty: " << a.difficulty << endl;
        cout << "Score: " << a.score << endl;
        cout << "--------------------------\n";

        index = (index + 1) % MAX_LOG;
    }
}

void ActivityLogCircularQueue::filterByLearner(int learnerID) {

    if (isEmpty()) {
        cout << "\nNo activity logs available.\n";
        return;
    }

    bool found = false;

    int index = front;

    cout << "\n===== Logs for Learner ID: " << learnerID << " =====\n";

    for (int i = 0; i < count; i++) {

        Activity a = logs[index];

        if (a.learnerID == learnerID) {

            found = true;

            cout << "Activity ID: " << a.activityID << endl;
            cout << "Topic: " << a.topic << endl;
            cout << "Difficulty: " << a.difficulty << endl;
            cout << "Score: " << a.score << endl;
            cout << "--------------------------\n";
        }

        index = (index + 1) % MAX_LOG;
    }

    if (!found) {
        cout << "No records found for this learner.\n";
    }
}

void ActivityLogCircularQueue::exportCSV(string filename) {

    if (isEmpty()) {
        cout << "\nNo logs to export.\n";
        return;
    }

    ofstream file(filename);

    if (!file) {
        cout << "Error creating file.\n";
        return;
    }

    file << "LearnerID,ActivityID,Topic,Difficulty,Score\n";

    int index = front;

    for (int i = 0; i < count; i++) {

        Activity a = logs[index];

        file << a.learnerID << ","
             << a.activityID << ","
             << a.topic << ","
             << a.difficulty << ","
             << a.score << "\n";

        index = (index + 1) % MAX_LOG;
    }

    file.close();

    cout << "\nLogs exported to " << filename << endl;
}

// used for recent performance calcs (riskpriorityqueue) // addded by Sean
void ActivityLogCircularQueue::getLearnerPerformanceMetrics(int learnerID, int &activityCount, int &totalScore, int &failedAttempts){
    activityCount = 0;
    totalScore = 0;
    failedAttempts = 0;

    if (isEmpty()){
        return;
    }

    int index = front;
    for (int i = 0; i < count ; i++){
        Activity activity = logs[index];
        
        if (activity.learnerID == learnerID){
            activityCount ++;
            totalScore += activity.score;

            if(activity.score < 40){ 
                failedAttempts++;
            }
        }
        index = (index + 1) % MAX_LOG;
    }
}