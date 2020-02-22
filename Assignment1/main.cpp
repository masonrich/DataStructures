//Copyright 2019, Bradley Peterson, Weber State University, All rights reserved.
#include <iostream>
#include <string>
#include <cstdio>
#include <memory>

//To prevent those using g++ from trying to use a library
//they don't have
#ifndef __GNUC__
#include <conio.h>
#endif

using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::make_unique;
using std::unique_ptr;


//These two base classes help the assignment compile and run without any changes.
//Dot not modify these.  You will instead override the methods in the derived classes below.
template <typename T>
class BaseStackQueue {
public:
    BaseStackQueue() {}
    BaseStackQueue(const unsigned int size) {}                       //These methods just contain filler code to help the code compile on the initial run.
    void push(const T& item) {}                                  //In the derived classes below, you will be overriding these with your own versions.
    T top() { T temp{}; return temp; }
    void pop() { }
    const unsigned int size() const { return 0; }
protected:
    T * arr;
    //unsigned int currentSize;
    //unsigned int capacity;
};

//**********************************
//Write your code below here
//**********************************

//StackForCS2420 class
template <typename T>
class StackForCS2420 : public BaseStackQueue<T> {
public:
    StackForCS2420(const unsigned int size);
    ~StackForCS2420(); //destructor
    void push(const T& item);
    void pop();
    T top();
    unsigned int size();
private:
    unsigned int currentSize;
    unsigned int capacity;
    T * arr;
};

//constructor w/ values
template <typename T>
StackForCS2420<T>::StackForCS2420(const unsigned int size) {
    arr = new T[size];
    this->currentSize = 0;
    this->capacity = size;
}

//desctructor for stack, deallocating memory on the heap
template <typename T>
StackForCS2420<T>::~StackForCS2420() {
    //delete[]this-> arr;
    delete[] arr;
}

//push function for stack
template <typename T>
void StackForCS2420<T>::push(const T& item) {
    if (currentSize == capacity) {
        cout << "Error: Full" << endl;
        return;
    }
    arr[currentSize] = item;
    currentSize++;
}

//pop function for stack
template <typename T>
void StackForCS2420<T>::pop() {
    this->currentSize--;
}

//top function for stack
template <typename T>
T StackForCS2420<T>::top() {
    if (currentSize == 0) {
        throw 1;
    }
    return arr[currentSize-1];
}

//size function for the stack
template <typename T>
unsigned int StackForCS2420<T>::size() {
    return currentSize;
}

//QueueForCS2420 class
template <typename T>
class QueueForCS2420 : public BaseStackQueue<T> {
public:
    QueueForCS2420(const unsigned int size); //constructor with values in the parameter
    ~QueueForCS2420(); //destructor
    void push(const T& item);
    void pop();
    T top();
    unsigned int size();
private:
    T * arr;
    unsigned int currentSize;
    unsigned int capacity;
    unsigned int front;
    unsigned int back;
};

//constructor for Queue
template <typename T>
QueueForCS2420<T>::QueueForCS2420(const unsigned int size){
    arr = new T[size];
    this->currentSize = 0;
    this->capacity = size;
    this->front = currentSize;
    this->back = currentSize;
}

//destructor, deallocating memory on the heap
template <typename T>
QueueForCS2420<T>::~QueueForCS2420() {
    delete[] arr;
}

//pop function for queue
template <typename T>
void QueueForCS2420<T>::pop(){
    currentSize--;
    front++;
}

//top function for queue
template <typename T>
T QueueForCS2420<T>::top(){
    //front++;
    if(front == capacity)
    {
        front = 0;
    }
    if(currentSize == 0) {
        throw 1;
    }

    return arr[front];
}

//push function for queue
template <typename T>
void QueueForCS2420<T>::push(const T& item) {
    //back++;
    if(currentSize == capacity){
        cout << "Error: full" << endl;
        return;
    }
    if (back == capacity){
        back = 0;
    }
    arr[back] = item;
    back++;
    currentSize++;
}

//queue size function
template <typename T>
unsigned int QueueForCS2420<T>::size(){
    return currentSize;
}

//**********************************
//Write your code above here
//**********************************

//This helps with testing, do not modify.
bool checkTest(string testName, int whatItShouldBe, int whatItIs) {

    if (whatItShouldBe == whatItIs) {
        cout << "Passed " << testName << endl;
        return true;
    }
    else {
        cout << "***Failed test " << testName << " *** " << endl << "   Output was " << whatItIs << endl << "   Output should have been " << whatItShouldBe << endl;
        return false;
    }
}


//This helps with testing, comment it in when ready, but do not modify the code.
bool checkTest(string testName, string whatItShouldBe, string whatItIs) {

    if (whatItShouldBe == whatItIs) {
        cout << "Passed " << testName << endl;
        return true;
    }
    else {
        if (whatItShouldBe == "") {
            cout << "***Failed test " << testName << " *** " << endl << "   Output was " << whatItIs << endl << "   Output should have been blank. " << endl;
        }
        else {
            cout << "***Failed test " << testName << " *** " << endl << "   Output was " << whatItIs << endl << "   Output should have been " << whatItShouldBe << endl;
        }
        return false;
    }
}

//This helps with testing, do not modify.
bool checkTestMemory(string testName, int whatItShouldBe, int whatItIs) {

    if (whatItShouldBe == whatItIs) {
        cout << "Passed " << testName << endl;
        return true;
    }
    else {
        cout << "***Failed test " << testName << " *** " << endl << ".  ";
        cout << "You are manually managing " << whatItIs << " bytes in memory, but it should be " << whatItShouldBe << " bytes." << endl;
        return false;
    }
}



//This helps with testing, do not modify.
void testStackForCS2420() {

    // Last in, first out data structure (LIFO)

    string result;
    string caughtError;
    {
        auto stack = make_unique< StackForCS2420<int> >(5);

        stack->push(1);

        int data = stack->top();
        stack->pop();
        checkTest("testStackForCS2420 #1", 1, data);

        stack->push(1);
        stack->push(2);
        stack->push(3);
        stack->push(4);
        stack->push(5);
        checkTest("testStackForCS2420 #2", 5, stack->top());
        stack->pop();
        checkTest("testStackForCS2420 #3", 4, stack->top());
        stack->pop();
        checkTest("testStackForCS2420 #4", 3, stack->top());
        stack->pop();
        checkTest("testStackForCS2420 #5", 2, stack->top());
        stack->pop();
        checkTest("testStackForCS2420 #6", 1, stack->top());
        stack->pop();
        // Now cover error handling
        try {
            result = stack->top();
        }
        catch (int e) {
            caughtError = "caught";
        }
        checkTest("testStackForCS2420 #7", "caught", caughtError);

        // Check currentSize
        checkTest("testStackForCS2420 #8", 0, stack->size());
        stack->push(12);
        stack->push(32);
        checkTest("testStackForCS2420 #9", 2, stack->size());

        // Now test filling it up
        stack->push(14);
        stack->push(53);
        stack->push(47);
        checkTest("testStackForCS2420 #10", 5, stack->size());

        // This should simply not let the 20 go in, as it is out of room.
        stack->push(20);

        // Peek at what is at the top
        checkTest("testStackForCS2420 #11", 47, stack->top());

        // Grab all the items again.
        checkTest("testStackForCS2420 #12", 47, stack->top());
        stack->pop();
        checkTest("testStackForCS2420 #13", 53, stack->top());
        stack->pop();
        checkTest("testStackForCS2420 #14", 14, stack->top());
        stack->pop();
        checkTest("testStackForCS2420 #15", 32, stack->top());
        stack->pop();
        checkTest("testStackForCS2420 #16", 12, stack->top());
        stack->pop();

        // Now do error handling again
        try {
            result = stack->top();
        }
        catch (int e) {
            caughtError = "caught";
        }
        checkTest("testStackForCS2420 #17", "caught", caughtError);
    }
    {
        // Test some strings
        auto sstack = make_unique < StackForCS2420<string> >(10);

        sstack->push("pencil");
        sstack->push("pen");
        sstack->push("marker");

        checkTest("testStackForCS2420 #18", 3, sstack->size());

        // Remove pen from the stack.
        string temp = sstack->top(); // Get marker
        sstack->pop();               // Remove marker
        sstack->pop();               // Remove pen
        sstack->push(temp);          // Push marker back in

        // See if it worked
        checkTest("testStackForCS2420 #19", "marker", sstack->top());
        sstack->pop();
        checkTest("testStackForCS2420 #20", "pencil", sstack->top());
        sstack->pop();

        checkTest("testStackForCS2420 #21", 0, sstack->size());
    }

}

void testQueueForCS2420() {

    string result;
    string caughtError;
    auto pQueue = make_unique< QueueForCS2420<string> >(5);

    // Tests push
    pQueue->push("penny");
    pQueue->push("nickel");
    pQueue->push("dime");
    pQueue->push("quarter");

    checkTest("testQueueForCS2420 #1", 4, pQueue->size());

    checkTest("testQueueForCS2420 #2", "penny", pQueue->top());
    pQueue->pop();
    checkTest("testQueueForCS2420 #3", 3, pQueue->size());

    checkTest("testQueueForCS2420 #4", "nickel", pQueue->top());
    pQueue->pop();
    checkTest("testQueueForCS2420 #5", "dime", pQueue->top());
    pQueue->pop();
    checkTest("testQueueForCS2420 #6", "quarter", pQueue->top());
    pQueue->pop();
    checkTest("testQueueForCS2420 #7", 0, pQueue->size());

    caughtError = "not caught";
    try {
        result = pQueue->top();
    }
    catch (int e) {
        caughtError = "caught";
    }
    checkTest("testQueueForCS2420 #8", "caught", caughtError);
    checkTest("testQueueForCS2420 #9", 0, pQueue->size());

    // Try it again.  This should make it wrap around, and fill up.
    pQueue->push("penny");
    pQueue->push("nickel");
    pQueue->push("dime");
    pQueue->push("quarter");

    checkTest("testQueueForCS2420 #10", "penny", pQueue->top());
    pQueue->pop();
    pQueue->push("half dollar");
    pQueue->push("silver dollar");

    // It should be full, no more room to add more.
    pQueue->push("million dollar bill");

    // Take a look at what is coming next.
    checkTest("testQueueForCS2420 #11", "nickel", pQueue->top());
    pQueue->pop();
    checkTest("testQueueForCS2420 #12", "dime", pQueue->top());
    pQueue->pop();
    checkTest("testQueueForCS2420 #13", "quarter", pQueue->top());
    pQueue->pop();
    checkTest("testQueueForCS2420 #14", "half dollar", pQueue->top());
    pQueue->pop();
    checkTest("testQueueForCS2420 #15", "silver dollar", pQueue->top());
    pQueue->pop();
    caughtError = "not caught";
    try {
        result = pQueue->top();
    }
    catch (int e) {
        caughtError = "caught";
    }
    checkTest("testQueueForCS2420 #16", "caught", caughtError);

    // Test adding and removing back and forth
    pQueue->push("penny");
    checkTest("testQueueForCS2420 #17", "penny", pQueue->top());
    pQueue->pop();
    pQueue->push("nickel");
    checkTest("testQueueForCS2420 #18", "nickel", pQueue->top());
    pQueue->pop();
    pQueue->push("dime");
    checkTest("testQueueForCS2420 #19", "dime", pQueue->top());
    pQueue->pop();
    pQueue->push("quarter");
    checkTest("testQueueForCS2420 #20", "quarter", pQueue->top());
    pQueue->pop();
    pQueue->push("half dollar");
    checkTest("testQueueForCS2420 #21", "half dollar", pQueue->top());
    pQueue->pop();
    pQueue->push("silver dollar");
    checkTest("testQueueForCS2420 #22", 1, pQueue->size());

    checkTest("testQueueForCS2420 #23", "silver dollar", pQueue->top());
    pQueue->pop();
    caughtError = "not caught";
    try {
        result = pQueue->top();
    }
    catch (int e) {
        caughtError = "caught";
    }
    checkTest("testQueueForCS2420 #24", "caught", caughtError);

}

void pressAnyKeyToContinue() {
    cout << "Press any key to continue...";

    //Linux and Mac users with g++ don't need this
    //But everyone else will see this message.
#ifndef __GNUC__
    _getch();

#else
    int c;
    fflush(stdout);
    do c = getchar(); while ((c != '\n') && (c != EOF));
#endif
    cout << endl;
}


int main() {

    {
        testStackForCS2420();
        pressAnyKeyToContinue();

        testQueueForCS2420();
        pressAnyKeyToContinue();
    }
    cout << "Shutting down the program" << endl;
    return 0;
}