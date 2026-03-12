#ifndef RISK_PRIORITY_QUEUE_HPP
#define RISK_PRIORITY_QUEUE_HPP

#include "Learner.hpp"
#include "ActivityLogCircularQueue.hpp"
#include <string>

struct LearnerRisk{
    int riskID;
    int learnerID; 
    int leanerName;
    int riskScore;
    int riskRank;
    std::string recommendedAction;

    bool operator>(const LearnerRisk& other) const {
        return this->riskScore > other.riskScore;
    }

    LearnerRisk() : riskID(0), learnerID(0), riskScore(0), riskRank(0), recommendedAction("") {
        riskID = 0;
        learnerID = 0;
        riskScore = 0;
        riskRank = 0;
        recommendedAction = "";
    }

    LearnerRisk(int riskid, int lID, int riskscore, int riskrank, std::string recaction) {
        riskID = riskid;
        learnerID = lID;
        riskScore = riskscore;
        riskRank = riskscore;
        recommendedAction = recaction;
    }
};

class RiskPriorityQueue {
private:
    LearnerRisk* heap;
    int capacity;
    int currentSize;
    int nextRiskID;

    void resize();
    void heapifyUp(int index);
    void heapifyDown(int index);

public:
    static const int HIGH_PRIORITY_THRESHOLD = 80;
    static const int MODERATE_PRIORITY_THRESHOLD = 50;
    static const int LOW_PRIORITY_THRESHOLD = 30;

    RiskPriorityQueue(int initial_capacity = 10);
    ~RiskPriorityQueue();

    RiskPriorityQueue(const RiskPriorityQueue& other);
    RiskPriorityQueue& operator=(const RiskPriorityQueue& other);

    void push(const LearnerRisk& value);
    void pop();
    LearnerRisk top() const;
    bool empty() const;
    int size() const;

    void evaluateAndPushLearner(int learnerID, ActivityLogCircularQueue& logQueue);
    void exportRiskCSV(std::string filename, RiskPriorityQueue tempQueue, int riskThreshold);
    void printAtRiskLearners (RiskPriorityQueue tempQueue, int limit = -1, int riskThreshold = -1);
};



#endif