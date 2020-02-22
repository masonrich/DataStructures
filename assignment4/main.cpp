//Copyright 2019, Bradley Peterson, Weber State University, All rights reserved. (Feb 2019)

#include <iostream>
#include <map>
#include <algorithm>
#include <list>
#include <vector>

#include <sstream>

template <typename T> class DoublyLinkedList;

using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;
using std::stringstream;
using std::iter_swap;

//******************
//The node class
//******************
template <typename T>
struct Node {
    T data{};
    Node<T>* forward{ nullptr };
    Node<T>* backward{ nullptr };
};

//******************
//The Iterator class
//******************
template <typename T>
class Iterator : public std::iterator<std::bidirectional_iterator_tag, T> {
    friend class DoublyLinkedList<T>;
public:
    T& operator*() const;
    bool operator!=(const Iterator<T>& rhs) const;
    bool operator==(const Iterator<T>& rhs) const;
    Iterator<T> operator++(); //prefix
    Iterator<T> operator++(int); //postfix
    Iterator<T> operator--(); //decrement
private:
    //TODO: supply two data members
    Node<T>* current{nullptr};
    bool atRightEnd = false;
};

//***********************************
//The Iterator class methods
//***********************************

//TODO, code the definitions for all the iterator methods.
template <typename T>
T& Iterator<T>::operator*() const {
    return current->data;
}

template <typename T>
bool Iterator<T>::operator!=(const Iterator<T>& rhs) const{
    return (current != rhs.current || atRightEnd != rhs.atRightEnd);
}

template <typename T>
bool Iterator<T>::operator==(const Iterator<T>& rhs) const{
    return (current == rhs.current && atRightEnd == rhs.atRightEnd);
}

template <typename T>
Iterator<T> Iterator<T>::operator++(){
    if(current->forward == nullptr){
        atRightEnd = true;
    }
    else{
        current = current->forward;
    }
    return *this;
}

template <typename T>
Iterator<T> Iterator<T>::operator++(int){
    Iterator<T> temp = *this;
    ++*this;

    return temp;
}
template <typename T>
Iterator<T> Iterator<T>::operator--(){
    if(!(this->current->forward)&&(this->atRightEnd == true)){
        this->atRightEnd = false;
    }
    else{
        this->current = this->current->backward;
        //atRightEnd = true;
    }
    return *this;
}

//****************************
//The DoublyLinkedList class
//****************************
template <typename T>
class DoublyLinkedList {
public:
    //public members of the DoublyLinkedList class
    DoublyLinkedList();
    ~DoublyLinkedList();
    string getStringFromList();
    void insertFirst(const T&);
    void insertLast(const T&);
    Iterator<T> begin();
    Iterator<T> end();
    //TODO: Implement a begin() and end() method
protected:
    Node<T>* first{ nullptr };
    Node<T>* last{ nullptr };
    unsigned int count;
};

template <typename T>
DoublyLinkedList<T>::DoublyLinkedList() {
    count = 0;
    first = nullptr;
    last = nullptr;
}

template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList() {
    if (first) {
        while (first->forward) {
            first = first->forward;
            delete first->backward;
            first->backward = nullptr;
        }
        delete first;
    }
}

template <typename T>
void DoublyLinkedList<T>::insertFirst(const T& item) {
    Node<T>* temp = new Node<T>();

    temp->data = item;
    if (!first) {
        // Scenario: List is empty
        first = temp;
    }
    else {
        first->backward = temp;
        temp->forward = first;
    }
    first = temp;
    count++;
}

template <typename T>
void DoublyLinkedList<T>::insertLast(const T& item) {
    Node<T>* temp = new Node<T>();

    temp->data = item;
    if (!first) {
        // Scenario: List is empty
        first = temp;
    }
    else {
        last->forward = temp;
        temp->backward = last;
    }
    last = temp;
    count++;
}

//This method helps return a string representation of all nodes in the linked list
template <typename T>
string DoublyLinkedList<T>::getStringFromList() {
    stringstream ss;
    if (first == nullptr) {
        ss << "The list is empty.";
    }
    else {

        Node<T> * currentNode{ first };
        ss << currentNode->data;
        currentNode = currentNode->forward;

        while (currentNode != nullptr) {
            ss << " " << currentNode->data;
            currentNode = currentNode->forward;
        }
    }
    return ss.str();
}

//***********************************
//The DoublyLinkedList class methods
//***********************************
//TODO, implement the  the definitions for the begin() and end() methods

template <typename T>
Iterator<T> DoublyLinkedList<T>::begin()
{
    Iterator<T> tempIter;

    if(!this->first){
        tempIter.atRightEnd = true;
        //tempIter.current = this->first;
    }
    else{
        tempIter.current = this->first;
        tempIter.atRightEnd = false;
    }
    return tempIter;
}

template <typename T>
Iterator<T> DoublyLinkedList<T>::end()
{
    Iterator<T> tempIter;
    tempIter.atRightEnd = true;
    tempIter.current = this->last;
    return tempIter;
}

//***********************************
//TODO, complete the ourReverse function.
// Note that begin and end here are are iterators (The T is just saying it can be any kind of iterator).
// Our iterator tools are ***ONLY***
// ++, --, !=, *, ==.
//For example, these three lines do a swap:
///----
//auto temp = *end;
//*end = *begin;
//*begin = temp;
//--
//++begin;
//--end;
// To create a copy of iterators:
// T copyOfBeging = begin;
// To swap the data being pointed at by two iterators:
// iter_swap(begin, end);

template <typename T>
void ourReverse(T begin, T end) {
    while((begin != end)&&(begin != --end)){
        iter_swap(begin, end);
        ++begin;
    }
}

template <typename T, typename Functor>
void runFunctor(T begin, T end, Functor f) {
    while (begin != end) {
        f(*begin);
        ++begin;
    }
}

//----------------------------------------------------------------------------------------------------------------------------------------
//Copyright 2019, Bradley Peterson, Weber State University, All rights reserved. (Feb 2019)
//This helps with testing, do not modify.
bool checkTest(string testName, string whatItShouldBe, string whatItIs) {

    if (whatItShouldBe == whatItIs) {
        cout << "Passed " << testName << endl;
        return true;
    }
    else {
        cout << "****** Failed test " << testName << " ****** " << endl << "     Output was " << whatItIs << endl << "     Output should have been " << whatItShouldBe << endl;
        return false;
    }
}

//This helps with testing, do not modify.
bool checkTest(string testName, int whatItShouldBe, int whatItIs) {

    if (whatItShouldBe == whatItIs) {
        cout << "Passed " << testName << endl;
        return true;
    }
    else {
        cout << "****** Failed test " << testName << " ****** " << endl << "     Output was " << whatItIs << endl << "     Output should have been " << whatItShouldBe << endl;
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
        cout << "***Failed test " << testName << " *** " << endl << "  There are " << whatItIs << " bytes of memory yet to be reclaimed!" << endl;
        return false;
    }
}


//This helps with testing, do not modify.
void testIteratorFundamentals() {
    //cout << "|||### You need to comment in testIteratorIncrement() when it's ready and remove this ###|||" << endl;
    //cout << "|||### I'd strongly advise commenting in tests one at a time and testing those.  It's harder to try and do all tests at once.###|||" << endl;

    DoublyLinkedList<int> d;

    //Our test data should have all even numbers from 2 to 20
    for (int i = 2; i <= 20; i += 2) {
      d.insertLast(i);
    }

    //Get an iterator which points at the beginning of the list
    Iterator<int> iter = d.begin();

    //Test the operator* operator
    checkTest("testIteratorFundamentals #1", 2, *iter);

    //Test the ++ prefix increment opreator
    ++iter;
    checkTest("testIteratorFundamentals #2", 4, *iter);

    //Test the != operator
    //reset them back to the start
    iter = d.begin();
    Iterator<int> anotherIter = d.begin();
    if (iter != anotherIter) {
      cout << "****** Failed testIteratorFundamentals #3 ****** " << endl << "     The two iteraters held the same data." << endl;
    }
    else {
      cout << "Passed testIteratorFundamentals #3" << endl;
    }

    //Again test the != operator
    ++iter;
    if (iter != anotherIter) {
      cout << "Passed testIteratorFundamentals #4" << endl;
    }
    else {
      cout << "****** Failed testIteratorFundamentals #4 ****** " << endl << "     The two iteraters held different data." << endl;
    }

    //Test the ++postfix increment
    iter = d.begin(); //reset it back to the start
    anotherIter = iter++;  //anotherIter should be at the data 2

    checkTest("testIteratorFundamentals #5", 4, *iter);
    checkTest("testIteratorFundamentals #6", 2, *anotherIter);

    checkTest("testIteratorFundamentals #7", "2 4 6 8 10 12 14 16 18 20", d.getStringFromList());

}

//This helps with testing, do not modify.
void testIteratorIncrement() {
    //cout << "|||### You need to comment in testIteratorIncrement() when it's ready and remove this ###|||" << endl;
    DoublyLinkedList<int> *d = new DoublyLinkedList<int>;

    //Our test data should have all even numbers from 2 to 20
    for (int i = 2; i <= 20; i += 2) {
      d->insertLast(i);
    }

    //Get an iterator which points at the beginning of the list
    Iterator<int> iter = d->begin();

    //Test that it does point to the first
    checkTest("testIteratorsIncrement #1", 2, *iter);

    //Test that our Iterator can move forward;
    ++iter;	checkTest("testIteratorsIncrement #2", 4, *iter);


    //Test that our Iterator can move forward again;
    ++iter;
    checkTest("testIteratorsIncrement #3", 6, *iter);

    //move it some more
    for (int i = 0; i < 6; i++) {
      ++iter;
    }
    checkTest("testIteratorsIncrement #4", 18, *iter);

    //Hit the end
    ++iter;
    checkTest("testIteratorsIncrement #5", 20, *iter);

    //Verify we move the iterator past the end without crashing
    ++iter;
    checkTest("testIteratorsIncrement #6", "did not crash", "did not crash");


    delete d;
}

//This helps with testing, do not modify.
void testIteratorDecrement() {
    //cout << "|||### You need to comment in testIteratorDecrement() when it's ready and remove this###|||" << endl;

      DoublyLinkedList<int> *d = new DoublyLinkedList<int>;

      //Our test data should have all even numbers from 2 to 20
      for (int i = 2; i <= 20; i += 2) {
        d->insertLast(i);
      }

      //Get an Iterator which points at the end of the list
      Iterator<int> iter = d->end();
      --iter;  //We have to do a decrement otherwise it crashes

               //Test that it does point to the first
      checkTest("testIteratorsDecrement #1", 20, *iter);

      //Test that our Iterator can move forward;
      --iter;
      checkTest("testIteratorsDecrement #2", 18, *iter);

      //move it some more
      for (int i = 0; i < 7; i++) {
        --iter;
      }
      checkTest("testIteratorsDecrement #3", 4, *iter);

      //Hit the end
      --iter;
      checkTest("testIteratorsDecrement #4", 2, *iter);

      //Now go back forward
      ++iter;
      checkTest("testIteratorsDecrement #5", 4, *iter);

      delete d;
}

//This helps with testing, do not modify.
void testIterationTricky() {

    //cout << "|||### You need to comment in testIterationTricky() when it's ready and remove this###|||" << endl;

      DoublyLinkedList<int> myListOneNode;

      myListOneNode.insertLast(42);
      cout << "TestIterationTricky test #1, the next line should display 42" << endl;
      stringstream ss;
      //see if we can just iterator through one item.
      for (auto i : myListOneNode) {
        cout << i << " ";
        ss << i << " ";
      }
      cout << endl;
      checkTest("TestIterationTricky test #1", "42 ", ss.str());
      ss.str("");

      DoublyLinkedList<int> myListEmpty;
      cout << "TestIterationTricky test #2, the next line shouldn't display anything" << endl;
      //see if we can just iterator through one item.
      for (auto i : myListEmpty) {
        cout << i << " ";
        ss << i << " ";
      }
      cout << endl;
      checkTest("TestIterationTricky test #2", "", ss.str());
      ss.str("");
}



//This helps with testing, do not modify.
void testAlgorithms() {
    //cout << "|||### You need to comment in testAlgorithms() when it's ready and remove this###|||" << endl;
    DoublyLinkedList<int> myList;

    //Our test data should have all even numbers from 2 to 20
    for (int i = 2; i <= 6; i += 2) {
    myList.insertLast(i);
    }
    myList.insertLast(100);
    for (int i = 8; i <= 12; i += 2) {
    myList.insertLast(i);
    }
    myList.insertLast(100);
    for (int i = 14; i <= 20; i += 2) {
    myList.insertLast(i);
    }
    stringstream ss;
    cout << "testAlgorithms test #1, this should display 2 4 6 100 8 10 12 100 14 16 18 20." << endl;
    for (auto i : myList) {
    cout << i << " ";
    ss << i << " ";
    }
    cout << endl;
    checkTest("testAlgorithms test #1", "2 4 6 100 8 10 12 100 14 16 18 20 ", ss.str());
    ss.str("");

    //Test the STL reverse algorithm on our iterator
    cout << "testAlgorithms test #2, this should display 20 18 16 14 100 12 10 8 100 6 4 2." << endl;
    reverse(myList.begin(), myList.end()); /////no
    for (auto i : myList) {
    cout << i << " ";
    ss << i << " ";
    }
    cout << endl;
    checkTest("testAlgorithms test #2", "20 18 16 14 100 12 10 8 100 6 4 2 ", ss.str());
    ss.str("");

    //Test our reverse algorithm
    cout << "testAlgorithms test #3, this should display 20 18 16 14 100 12 10 8 100 6 4 2." << endl;
    //Get it back in ascending order using the STL reverse algorithm
    reverse(myList.begin(), myList.end()); //////no
    //Now reverse it using our algorithm
    ourReverse(myList.begin(), myList.end());
    for (auto i : myList) {
    cout << i << " ";
    ss << i << " ";
    }
    cout << endl;
    checkTest("testAlgorithms test #3", "20 18 16 14 100 12 10 8 100 6 4 2 ", ss.str());
    ss.str("");

    //Test our reverse algorithm on an STL vector collection
    vector<int> v;
    for (int i = 2; i <= 20; i += 2) {
    v.push_back(i);
    }
    cout << "testAlgorithms test #4, this should display 20 18 16 14 12 10 8 6 4 2." << endl;
    ourReverse(v.begin(), v.end());
    for (auto i : v) {
    cout << i << " ";
    ss << i << " ";
    }
    cout << endl;
    checkTest("testAlgorithms test #4", "20 18 16 14 12 10 8 6 4 2 ", ss.str());
    ss.str("");

    //Now test an odd sized list
    DoublyLinkedList<int> oddList;
    for (int i = 2; i <= 6; i += 2) {
    oddList.insertLast(i);
    }
    oddList.insertLast(100);
    for (int i = 8; i <= 12; i += 2) {
    oddList.insertLast(i);
    }
    oddList.insertLast(100);
    for (int i = 14; i <= 18; i += 2) {
    oddList.insertLast(i);
    }
    cout << "testAlgorithms test #5, this should display 18 16 14 100 12 10 8 100 6 4 2." << endl;
    ourReverse(oddList.begin(), oddList.end());
    for (auto i : oddList) {
    cout << i << " ";
    ss << i << " ";
    }
    cout << endl;
    checkTest("testAlgorithms test #5", "18 16 14 100 12 10 8 100 6 4 2 ", ss.str());
    ss.str("");


    //Delete all of occurrence using an STL algorithm.
    cout << "testAlgorithms test #6, this should display 4 2 5 1 2." << endl;
    DoublyLinkedList<int> manyNines;
    manyNines.insertLast(9);
    manyNines.insertLast(9);
    manyNines.insertLast(4);
    manyNines.insertLast(2);
    manyNines.insertLast(9);
    manyNines.insertLast(9);
    manyNines.insertLast(5);
    manyNines.insertLast(1);
    manyNines.insertLast(9);
    manyNines.insertLast(2);
    manyNines.insertLast(9);
    manyNines.insertLast(9);
    auto beginIter = manyNines.begin();
    auto endIter = manyNines.end();
    endIter = remove(beginIter, endIter, 9);

    while (beginIter != endIter) {
    cout << *beginIter << " ";
    ss << *beginIter << " ";
    ++beginIter;
    }
    cout << endl;
    checkTest("testAlgorithms test #6", "4 2 5 1 2 ", ss.str());
    ss.str("");
}

void pressAnyKeyToContinue() {
    cout << "Press enter to continue...";
    cin.get();
}

int main() {

//    cout << "This first test can run forever until you get operators *, != and ++ implemented." << endl;
//    pressAnyKeyToContinue();

    testIteratorFundamentals();
    pressAnyKeyToContinue();

    testIteratorIncrement();
    pressAnyKeyToContinue();

    testIteratorDecrement();
    pressAnyKeyToContinue();

    testIterationTricky();
    pressAnyKeyToContinue();

    testAlgorithms();
    pressAnyKeyToContinue();

    return 0;
}
