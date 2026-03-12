#include "RiskPriorityQueue.hpp"
#include <iostream>
#include <stdexcept>
#include <fstream>

using namespace std;

RiskPriorityQueue::RiskPriorityQueue(int initial_capacity) {

    capacity = initial_capacity;
    currentSize = 0;
    heap = new LearnerRisk[capacity];
    nextRiskID = 1;

}

RiskPriorityQueue::~RiskPriorityQueue() { 

    delete[] heap; 

}

LearnerRisk RiskPriorityQueue::top() const {

    if (currentSize == 0) throw runtime_error("Priority queue is empty!");
    return heap[0];
}

bool RiskPriorityQueue::empty() const { 

    return currentSize == 0; 
    
}

int RiskPriorityQueue::size() const { 

    return currentSize; 

}

RiskPriorityQueue::RiskPriorityQueue(const RiskPriorityQueue& other) {
    
    capacity = other.capacity;
    currentSize = other.currentSize;
    heap = new LearnerRisk[capacity];

    for (int i = 0; i < currentSize; i++) {
        heap[i] = other.heap[i];
    }

}

RiskPriorityQueue& RiskPriorityQueue::operator=(const RiskPriorityQueue& other) {

    if (this == &other) {
        return *this;
    }
    
    delete[] heap;
    
    capacity = other.capacity;
    currentSize = other.currentSize;
    heap = new LearnerRisk[capacity];

    for (int i = 0; i < currentSize; i++) {
        heap[i] = other.heap[i];
    }

    return *this;

}

void RiskPriorityQueue::resize() {

    capacity *= 2;
    LearnerRisk* newHeap = new LearnerRisk[capacity];

    for (int i = 0; i < currentSize; ++i) {
        newHeap[i] = heap[i];
    }

    delete[] heap;
    heap = newHeap;

}

void RiskPriorityQueue::heapifyUp(int index) {

    int parent = (index - 1) / 2;
    
    while (index > 0 && heap[index] > heap[parent]) {
        LearnerRisk temp = heap[index];
        heap[index] = heap[parent];
        heap[parent] = temp;
        index = parent;
        parent = (index - 1) / 2;
    }

}

void RiskPriorityQueue::heapifyDown(int index) {

    while (true) {
        int largest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < currentSize && heap[left] > heap[largest]) {
            largest = left;
        }

        if (right < currentSize && heap[right] > heap[largest]) {
            largest = right;
        }

        if (largest != index) {
            LearnerRisk temp = heap[index];
            heap[index] = heap[largest];
            heap[largest] = temp;
            index = largest;

        } else {
            break;
        }
    }

}

void RiskPriorityQueue::push(const LearnerRisk& value) {

    if (currentSize == capacity) {
        resize();
    }

    heap[currentSize] = value;
    heapifyUp(currentSize);
    currentSize++;

}

void RiskPriorityQueue::pop() {

    if (currentSize == 0) {
        return;
    }

    heap[0] = heap[currentSize - 1];
    currentSize--;

    if (currentSize > 0) {
        heapifyDown(0);
    }

}


void RiskPriorityQueue::evaluateAndPushLearner(int learnerID, ActivityLogCircularQueue& logQueue) {

    int activityCount = 0, totalScore = 0, failedAttempts = 0;
    
    logQueue.getLearnerPerformanceMetrics(learnerID, activityCount, totalScore, failedAttempts);
    
    if (activityCount == 0) return;

    int averageScore = totalScore / activityCount;
    int riskScore = 100 - averageScore; 
    riskScore += (failedAttempts * 10); 
    if (riskScore > 100) {
        riskScore = 100;
    }

    LearnerRisk newRisk;
    newRisk.riskID = this->nextRiskID++;
    newRisk.learnerID = learnerID;
    newRisk.riskScore = riskScore;
    
    if (newRisk.riskScore >= HIGH_PRIORITY_THRESHOLD) newRisk.recommendedAction = "High Priority: May Require a 1-on-1 Tutor Session";
    else if (newRisk.riskScore >= MODERATE_PRIORITY_THRESHOLD) newRisk.recommendedAction = "Moderate Priority: Repeat Topics at Lecturer's Discretion";
    else if (newRisk.riskScore >= LOW_PRIORITY_THRESHOLD) newRisk.recommendedAction = "Low Priority: Return to a Lower Difficulty Level";
    else newRisk.recommendedAction = "Minimal Priority: Student not at Risk";
    
    push(newRisk);
    
}

void RiskPriorityQueue::exportRiskCSV(string filename, RiskPriorityQueue tempQueue, int riskThreshold) {
    int minScore = 0;
    int maxScore = 101; 

    switch (riskThreshold) {
        case 1:
            minScore = 0;
            break;
            
        case 2:
            minScore = HIGH_PRIORITY_THRESHOLD;
            break;

        case 3:
            minScore = MODERATE_PRIORITY_THRESHOLD;
            maxScore = HIGH_PRIORITY_THRESHOLD; 
            break;

        case 4:
            minScore = LOW_PRIORITY_THRESHOLD;
            maxScore = MODERATE_PRIORITY_THRESHOLD;
            break;

        case 5:
            minScore = 0;
            maxScore = LOW_PRIORITY_THRESHOLD;
            
        default:
            minScore = 0;
            break;
    }

    ofstream file(filename);

    if (!file) {
        cout << "Error creating file.\n";
        return;
    }

    file << "Rank,LearnerID,RiskScore,RecommendedAction\n";

    int rank = 1;
    
    while (!tempQueue.empty()) {

        LearnerRisk lrisk = tempQueue.top();
        tempQueue.pop();

        if (lrisk.riskScore >= minScore && lrisk.riskScore < maxScore) {

            file << rank++ << "," << lrisk.learnerID << "," 
                 << lrisk.riskScore << "," << lrisk.recommendedAction << "\n";
                 
        }
    }

    file.close();
    cout << "\nSuccessfully exported at-risk learners to " << filename << endl;

}

void RiskPriorityQueue::printAtRiskLearners (RiskPriorityQueue tempQueue, int limit, int riskThreshold){
    int rankCounter = 1;
    bool foundAny = false;
    string riskTitle = " ";
    int minScore = 0;
    int maxScore = 101;

    switch (riskThreshold){
        case 1:
            minScore = 0;
            riskTitle = "\n=-=-=-=-=Learners and Recommendations (Top 5) =-=-=-=-=\n";
            break;

        case 2:
            minScore = HIGH_PRIORITY_THRESHOLD;
            riskTitle = "\n=-=-=-=-= High Priority Learners and Recommendations (Top 5) =-=-=-=-=\n";
            break;

        case 3:
            minScore = MODERATE_PRIORITY_THRESHOLD;
            maxScore = HIGH_PRIORITY_THRESHOLD;
            riskTitle = "\n=-=-=-=-= Moderate Priority Learners and Recommendations (Top 5) =-=-=-=-=\n";
            break;

        case 4:
            minScore = LOW_PRIORITY_THRESHOLD;
            maxScore = MODERATE_PRIORITY_THRESHOLD;
            riskTitle = "\n=-=-=-=-= Low Priority Learners and Recommendations (Top 5) =-=-=-=-=\n";
            break;

        case 5:
            minScore = 0;
            maxScore = LOW_PRIORITY_THRESHOLD;
            riskTitle = "\n=-=-=-=-= Minimal Priority Learners and Recommendations (Top 5) =-=-=-=-=\n";

        case -1:
            minScore = 0;
            riskTitle = "\n=-=-=-=-=-= Current Risk Score Rankings =-=-=-=-=-=\n";

        default:
            break;
    }

    cout << riskTitle;

    while (!tempQueue.empty() && (limit == -1 || rankCounter <= limit)) {

        LearnerRisk lrisk = tempQueue.top();
        tempQueue.pop();
        
        if (lrisk.riskScore >= minScore && lrisk.riskScore < maxScore) {

            foundAny = true;
            cout << "[ " << rankCounter << " ]" << endl;
            cout << "Learner ID: " << lrisk.learnerID << endl;
            cout << "Risk Score: " << lrisk.riskScore << endl;
            cout << "Rec. Action: " << lrisk.recommendedAction << endl;
            cout << "---------------------------------------------------------" << endl;

            rankCounter++;
        }
    }

    cout << "=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n";

    if (!foundAny) {

        if (riskThreshold > 0) {

            cout << "No learners are currently in the high-risk category.\n";

        } else {

            cout << "There are no evaluated learners to display.\n";

        }
    }
}