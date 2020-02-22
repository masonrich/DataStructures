//Copyright 2018, Bradley Peterson, Weber State University, All rights reserved.

#include <sstream>
#include <map>
#include <chrono>
#include <iostream>
#include <memory>


using std::cin;
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::stringstream;
using std::make_shared;
using std::shared_ptr;

//************************************************************************
//A class I designed to help keep track of how much memory you allocate
//Do not modify, this is not part of your assignment, it just helps test it.
//For this to work, a class needs to inherit off of this one.
//Then this does the rest of the work, since it
//overloads new, new[], delete, and delete[].
//************************************************************************
class ManageMemory {
public:

    static std::size_t getTotalSize() {
      std::size_t total = 0;
      std::map<void *, std::size_t>::iterator iter;
      for (iter = mapOfAllocations.begin(); iter != mapOfAllocations.end(); ++iter) {
        total += iter->second;
      }
      return total;
    }

    //I overloaded the new and delete keywords so I could manually track allocated memory.
    void* operator new(std::size_t x) {
      void *ptr = ::operator new(x);
      mapOfAllocations[ptr] = x;
      return ptr;
    }
    void* operator new[](std::size_t x) {
      void *ptr = ::operator new[](x);
      mapOfAllocations[ptr] = x;
      return ptr;
    }
    void operator delete(void* x) {
      mapOfAllocations.erase(x);
      ::operator delete(x);
    }
    void operator delete[](void* x) {
      mapOfAllocations.erase(x);
      ::operator delete[](x);
    }
private:
    static std::map<void *, std::size_t> mapOfAllocations;
};
std::map<void *, std::size_t> ManageMemory::mapOfAllocations;



//******************
//The node class
//******************
template <typename T>
class Node : public ManageMemory {
public:
    T data{};
    Node<T> * link;
};

//******************
// The linked list base class
//******************
template <typename T>
class LinkedListBase : public ManageMemory {
public:
    string getStringFromList();
    string getStringBackwardsFromList();
    T getFifthElement() const { cerr << "Error: You didn't override this base class method yet" << endl; T temp{}; return temp; }
    void insertNewFifthElement(const T& value) { cerr << "Error: You didn't override this base class method yet" << endl; }
    void deleteFifthElement() { cerr << "Error: You didn't override this base class method yet" << endl; }
    void swapFourthAndFifthElement() { cerr << "Error: You didn't override this base class method yet" << endl; }

protected:

    Node<T> *front{ nullptr };
    Node<T> *back{ nullptr };
    int count{ 0 };
};

//This method helps return a string representation of all nodes in the linked list, do not modify.
template <typename T>
string LinkedListBase<T>::getStringFromList() {
  stringstream ss;
  if (!front) {
    ss << "The list is empty.";
  }
  else {

    Node<T> *currentNode = front;
    ss << currentNode->data;
    currentNode = currentNode->link;

    while (currentNode) {
      ss << " " << currentNode->data;
      currentNode = currentNode->link;
    };
  }
  return ss.str();
}


//******************
//The singly linked list base class
//******************
template <typename T>
class SinglyLinkedListBase : public LinkedListBase<T> {
public:
    //public members of the SinglyLinkedList class
    ~SinglyLinkedListBase();
    void insertFront(const T&);
    void insertBack(const T&);
};

template <typename T>// destructor
SinglyLinkedListBase<T>::~SinglyLinkedListBase() {
  if (this->front) {
    Node<T> * temp{ this->front->link };
    while (temp) {
      delete this->front;
      this->front = temp;
      temp = temp->link;
    }
    delete this->front;
  }
}

template <typename T>
void SinglyLinkedListBase<T>::insertFront(const T& value) {
  Node<T> * temp = new Node<T>();
  temp->data = value;

  if (!this->front) {
    // Specific scenario, list is empty
    this->back = temp;
  }
  else {
    // General scenario, at least one node
    temp->link = this->front;
  }
  this->front = temp;
  this->count++;
}

template <typename T>
void SinglyLinkedListBase<T>::insertBack(const T& value) {
  Node<T> * temp = new Node<T>();
  temp->data = value;
  if (!this->front) {
    // Specific scenario, list is empty
    this->front = temp;
  }
  else {
    // General scenario, at least one node
    this->back->link = temp;
  }
  this->back = temp;
  this->count++;
}

//**********************************
//Write your code below here
//**********************************


template <typename T>
class SinglyLinkedList : public SinglyLinkedListBase<T> {
public:
    //TODO: Declare your methods here.
    T getFifthElement() const;
    void insertNewFifthElement(const T& value);
    void deleteFifthElement();
    void swapFourthAndFifthElement();
};

//TODO: Define your methods here.

//get fifth element function
template <typename T>
T SinglyLinkedList<T>::getFifthElement() const {
    auto currentNode = this->front;
    int currentNodeNum = 1;
    while(currentNodeNum < 5){
        currentNode = currentNode->link;  //iterate through the linked list
        if(currentNode == nullptr){
            throw 1;
        }
        currentNodeNum++;
    }

    return currentNode->data;

}

//insert new fifth element function
template <typename T>
void SinglyLinkedList<T>::insertNewFifthElement(const T &value) {
    auto currentNode = this->front;
    int currentNodeNum = 1;
    while(currentNodeNum < 4){
        currentNode = currentNode->link;
        if(currentNode == nullptr){
            throw 1;
        }
        currentNodeNum++;
    }

    Node<T> * temp = new Node<T>();   //creating a pointer to the node, creating a node.
    temp->data = value;    //give the new node the data being passed in
    temp->link = currentNode->link;
    currentNode->link = temp;  //set current nodes link equal to the new node

}

//delete 5th element
template <typename T>
void SinglyLinkedList<T>::deleteFifthElement() {
    auto currentNode = this->front;
    int currentNodeNum = 1;
    while(currentNodeNum < 4){
        currentNode = currentNode->link;  //iterate through the linked list
        if(currentNode == nullptr){
            throw 1;
        }
        currentNodeNum++;
    }

    auto tempNode = currentNode->link;
    currentNode->link = tempNode->link;
    if(this->back == tempNode){
        this->back = currentNode;    //if its the last element that is deleted, set "back" equal to last node
    }
    delete tempNode;
}

//swap 4th and 5th element
template <typename T>
void SinglyLinkedList<T>::swapFourthAndFifthElement() {
    auto currentNode = this->front;
    int currentNodeNum = 1;
    while(currentNodeNum < 3){
        currentNode = currentNode->link;  //iterate through the linked list
        if(currentNode == nullptr){
            throw 1;
        }
        currentNodeNum++;
    }

    auto tempNode = currentNode->link; //set tempNode equal to the 4th element
    auto tempNode2 = tempNode->link->link; //set tempNode2 equal to the 6th element
    currentNode->link = tempNode->link; //set 3rd link equal to the 5th element
    currentNode = currentNode->link; //move currentNode to 5th element
    currentNode->link = tempNode->link; //set 5th link equal to the 4th element
    tempNode->link = tempNode2; // set 4th link equal to the 6th element

}

//**********************************
//Write your code above here
//**********************************


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
    cout << "***Failed test " << testName << " *** " << endl << "  You lost track of " << whatItIs << " bytes in memory!" << endl;
    return false;
  }
}

//This helps with testing, do not modify.
void testGetFifthElement() {
  SinglyLinkedList<int> *si = new SinglyLinkedList<int>;
  for (int i = 10; i < 20; i++) {
    si->insertBack(i);
  }

  //Test just to make sure the data went in the list.
  checkTest("testGetFifthElement #1", "10 11 12 13 14 15 16 17 18 19", si->getStringFromList());

  //Test retrieving item.
  int item = si->getFifthElement();
  checkTest("testGetFifthElement #2", 14, item);
  delete si;

  si = new SinglyLinkedList<int>;
  for (int i = 10; i < 15; i++) {
    si->insertBack(i);
  }
  //Test just to make sure the data went in the list.
  checkTest("testGetFifthElement #3", "10 11 12 13 14", si->getStringFromList());

  //Test retrieving item.
  item = si->getFifthElement();
  checkTest("testGetFifthElement #4", 14, item);
  delete si;


  si = new SinglyLinkedList<int>;
  for (int i = 10; i < 14; i++) {
    si->insertBack(i);
  }
  //Test just to make sure the data went in the list.
  checkTest("testGetFifthElement #5", "10 11 12 13", si->getStringFromList());

  //Try to access out of bounds.
  string caughtError = "";
  try {
    item = si->getFifthElement();
  }
  catch (int) {
    caughtError = "caught";
  }
  checkTest("testGetFifthElement #6", "caught", caughtError);
  delete si;

  SinglyLinkedList<string> *ss = new SinglyLinkedList<string>;
  ss->insertBack("Multi Pass");
  ss->insertBack("Lelu Dallas");
  ss->insertBack("BIG BADA BOOM");
  ss->insertBack("Bruce Willis");
  ss->insertBack("Fried Chicken");
  ss->insertBack("EEEAAAAAAAeeeaaaaaEEeeAAAEEaaaaAA");
  checkTest("testGetFifthElement #7", "Fried Chicken", ss->getFifthElement());
  delete ss;


}

//This helps with testing, do not modify.
void testInsertNewFifthElement() {

  SinglyLinkedList<int> *si = new SinglyLinkedList<int>;
  for (int i = 10; i < 20; i++) {
    si->insertBack(i);
  }

  //Test just to make sure the data went in the list.
  checkTest("testInsertNewFifthElement #1", "10 11 12 13 14 15 16 17 18 19", si->getStringFromList());

  //Test inserting an item
  si->insertNewFifthElement(97);
  checkTest("testInsertNewFifthElement #2", "10 11 12 13 97 14 15 16 17 18 19", si->getStringFromList());
  delete si;

  si = new SinglyLinkedList<int>;
  for (int i = 10; i < 15; i++) {
    si->insertBack(i);
  }
  //Test just to make sure the data went in the list.
  checkTest("testInsertNewFifthElement #3", "10 11 12 13 14", si->getStringFromList());

  //Test inserting an item
  si->insertNewFifthElement(97);
  checkTest("testInsertNewFifthElement #4", "10 11 12 13 97 14", si->getStringFromList());
  delete si;

  si = new SinglyLinkedList<int>;
  for (int i = 10; i < 14; i++) {
    si->insertBack(i);
  }
  //Test just to make sure the data went in the list.
  checkTest("testInsertNewFifthElement #5", "10 11 12 13", si->getStringFromList());

  //Test inserting an item
  si->insertNewFifthElement(97);
  checkTest("testInsertNewFifthElement #6", "10 11 12 13 97", si->getStringFromList());
  delete si;


}


//This helps with testing, do not modify.
void testDeleteFifthElement() {
  // Note from the instructor: Please do not delete the actual movie.  It's very good and shouldn't be removed.

  SinglyLinkedList<int> *si = new SinglyLinkedList<int>;
  for (int i = 10; i < 20; i++) {
    si->insertBack(i);
  }

  //Test just to make sure the data went in the list.
  checkTest("testDeleteFifthElement #1", "10 11 12 13 14 15 16 17 18 19", si->getStringFromList());

  //Test deleting an item
  si->deleteFifthElement();
  checkTest("testDeleteFifthElement #2", "10 11 12 13 15 16 17 18 19", si->getStringFromList());
  delete si;

  si = new SinglyLinkedList<int>;
  for (int i = 10; i < 16; i++) {
    si->insertBack(i);
  }
  //Test just to make sure the data went in the list.
  checkTest("testDeleteFifthElement #3", "10 11 12 13 14 15", si->getStringFromList());

  //Test deleting an item
  si->deleteFifthElement();
  checkTest("testDeleteFifthElement #4", "10 11 12 13 15", si->getStringFromList());
  delete si;

  si = new SinglyLinkedList<int>;
  for (int i = 10; i < 15; i++) {
    si->insertBack(i);
  }
  //Test just to make sure the data went in the list.
  checkTest("testDeleteFifthElement #5", "10 11 12 13 14", si->getStringFromList());

  //Test deleting an item
  si->deleteFifthElement();
  checkTest("testDeleteFifthElement #6", "10 11 12 13", si->getStringFromList());
  delete si;

}



//This helps with testing, do not modify.
void testSwapFourthAndFifthElement() {
  // Note from the instructor: Please do not delete the actual movie.  It's very good and shouldn't be removed.

  SinglyLinkedList<int> *si = new SinglyLinkedList<int>;
  for (int i = 10; i < 20; i++) {
    si->insertBack(i);
  }

  //Test just to make sure the data went in the list.
  checkTest("testSwapFourthAndFifthElement #1", "10 11 12 13 14 15 16 17 18 19", si->getStringFromList());

  //Test swapping an item
  si->swapFourthAndFifthElement();
  checkTest("testSwapFourthAndFifthElement #2", "10 11 12 14 13 15 16 17 18 19", si->getStringFromList());

}


void pressAnyKeyToContinue() {
  cout << "Press enter to continue...";

  //Linux and Mac users with g++ don't need this
  //But everyone else will see this message.
  cin.get();

}


int main() {


  //Each of these checks how many bytes you have used.
  checkTestMemory("Memory Leak/Allocation Test #1", 0, ManageMemory::getTotalSize());

  //For your assignment, write the code to make these three methods work
  //You should not modify the code here in main.
  testGetFifthElement();

  checkTestMemory("Memory Leak/Allocation Test #2", 0, ManageMemory::getTotalSize());

  testInsertNewFifthElement();

  checkTestMemory("Memory Leak/Allocation Test #3", 0, ManageMemory::getTotalSize());

  testDeleteFifthElement();

  checkTestMemory("Memory Leak/Allocation Test #4", 0, ManageMemory::getTotalSize());

  testSwapFourthAndFifthElement();

  checkTestMemory("Memory Leak/Allocation Test #5", 0, ManageMemory::getTotalSize());

  pressAnyKeyToContinue();


  return 0;
}
