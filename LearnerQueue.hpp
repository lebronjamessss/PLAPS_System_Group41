#ifndef LEARNER_QUEUE_HPP
#define LEARNER_QUEUE_HPP

#include "Learner.hpp"

const int MAX_QUEUE = 100;
const int SESSION_CAPACITY = 5;

class LearnerQueue {

private:

    Learner queue[MAX_QUEUE];
    int front;
    int rear;

    Learner activeSession[SESSION_CAPACITY];
    int activeCount;

    int nextLearnerID;    

public:

    LearnerQueue();

    bool isEmpty();
    bool isFull();
    
    int generateLearnerID();

    void registerLearner(Learner learner);
    void startSession();
    void exitSession(int learnerID);

    void displayQueue();
    void displayActiveSession();

    bool learnerExists(int learnerID);

};

#endif