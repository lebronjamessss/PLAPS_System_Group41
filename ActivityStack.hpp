#ifndef ACTIVITY_STACK_HPP
#define ACTIVITY_STACK_HPP

#include <string>

const int MAX_STACK = 100;

struct Activity {
    int learnerID;
    int activityID;
    std::string topic;
    int difficulty;
    int score;
};

class ActivityStack {

private:

    Activity stack[MAX_STACK];
    int top;

public:

    ActivityStack();

    bool isEmpty();
    bool isFull();

    void push(Activity activity);
    void pop();

    Activity peek();

    void display();

};

#endif