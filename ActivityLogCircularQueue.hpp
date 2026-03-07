#ifndef ACTIVITY_LOG_CIRCULAR_QUEUE_HPP
#define ACTIVITY_LOG_CIRCULAR_QUEUE_HPP

#include "ActivityStack.hpp"
#include <string>

const int MAX_LOG = 10;

class ActivityLogCircularQueue {

private:

    Activity logs[MAX_LOG];

    int front;
    int rear;
    int count;

public:

    ActivityLogCircularQueue();

    bool isEmpty();
    bool isFull();

    void addLog(Activity activity);

    void displayLogs();

    void filterByLearner(int learnerID);

    void exportCSV(std::string filename);

};

#endif