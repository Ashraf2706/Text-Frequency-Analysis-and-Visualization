#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

//DO NOT ADD ANY CONSTANTS OR FUNCTIONS TO ANY CLASS

// Templated Node class
// Normal node except that each node can hold a pair <T,int>
// where the first value is templated and the second value is the frequency
// (or quantity) of the first
// For example, if T was a string then it would hold string,int
template <class T>
class Node {
public:
  Node( const T& data ); //Node Constructor - Assume each quan
  pair<T,int>& GetData(); //Node Data Getter
  void SetData( const pair<T,int>& ); //Node Data Setter
  Node<T>* GetNext(); //Node m_next getter
  void SetNext( Node<T>* next ); //Node m_next setter
private:
  pair <T,int> m_data; //Holds templated data
  Node<T>* m_next; //Pointer to next node
};

template <class T>
Node<T>::Node( const T& data ) {
  m_data = make_pair(data,1);
  m_next = nullptr;
}

template <class T>
pair<T,int>& Node<T>::GetData() {
   return m_data;
}

template <class T>
void Node<T>::SetData( const pair<T,int>& data ) {
   m_data = data;
}

template <class T>
Node<T>* Node<T>::GetNext() {
   return m_next;
}

template <class T>
void Node<T>::SetNext( Node<T>* next ) {
   m_next = next;
}

//Templated Linked List class
template <class T>
class LL {
 public:
  // Name: LL() (Linked List) - Default Constructor
  // Desc: Used to build a new linked list
  // Preconditions: None
  // Postconditions: Creates a new linked list where m_head points to nullptr
  LL();
  // Name: ~LL() - Destructor
  // Desc: Used to destruct a LL
  // Preconditions: There is an existing LL with at least one node
  // Postconditions: A LL is deallocated (including dynamically allocated nodes)
  //                 to have no memory leaks!
 ~LL();
  // Name: LL (Copy Constructor)
  // Desc: Creates a copy of existing LL
  //       Requires a LL - REQUIRED to be implemented even if not used
  // Preconditions: Source LL exists
  // Postconditions: Copy of source LL
  LL(const LL&);
  // Name: operator= (Overloaded Assignment Operator)
  // Desc: Makes two LL of the same type have identical number of nodes and values
  // Preconditions: Requires two linked lists of the same templated type
  //                REQUIRED to be implemented even if not used
  // Postconditions: Two idenetical LL
  LL<T>& operator= (const LL&);
  // Name: Find
  // Desc: Iterates through LL and returns node if data found
  // Preconditions: LL Populated
  // Postconditions: Returns nullptr if not found OR Node pointer if found
  Node<T>* Find(const T& data);
  // Name: Insert
  // Desc: Either inserts a node to the linked list OR increments frequency of first
  //       Takes in data. If "first" (of pair) NOT in list, adds node
  //       If "first" (of pair) is already in list, increments quantity
  //       Inserts "first" in order with no duplicates
  // Preconditions: Requires a LL.
  // Postconditions: Node inserted in LL based on first value (or quantity incremented)
  void Insert(const T&);
  // Name: RemoveAt
  // Desc: Removes a node at a particular position based on data passed (matches first)
  // Preconditions: LL with at least one node. 
  // Postconditions: Removes first node with passed value (in first)
  void RemoveAt(const T&);
  // Name: Display
  // Desc: Display all nodes in linked list
  // Preconditions: Outputs the LL
  // Postconditions: Displays the pair in each node of LL 
  void Display();
  // Name: GetSize
  // Desc: Returns the size of the LL
  // Preconditions: Requires a LL
  // Postconditions: Returns m_size
  int GetSize();
  // Name: operator<< (Overloaded << operator)
  // Desc: Returns the ostream of the data in each node
  // Preconditions: Requires a LL
  // Postconditions: Returns an ostream with the data from each node on different line
  template <class U>
  friend ostream& operator<<(ostream& output, const LL<U>&);
  // Name: Overloaded [] operator
  // Desc: When passed an integer, returns the data at that location
  // Precondition: Existing LL
  // Postcondition: Returns pair from LL using []
  pair<T,int>& operator[] (int x);//Overloaded [] operator to pull data from LL
private:
  Node <T> *m_head; //Node pointer for the head
  int m_size; //Number of nodes in queue
};
//*****************************************************************
//Implement LL here

//LL Default Constructor
template <class T>
LL<T>::LL(){
  //Initializes the head of the linked list to null and sets its size to zero
  m_head = nullptr;
  m_size = 0;
}

//LL Destructor
template <class T>
LL<T>::~LL(){
  //Loop through the linked list and delete all nodes
  while(m_head != nullptr){
    //Set temp to the current head node and set the head to next node
    //then delete current headd node
    Node<T>* temp = m_head;
    m_head = m_head->GetNext();
    delete temp;
  }
  m_size = 0; //set size to zero
}

//LL Copy Constructor
template <class T>
LL<T>::LL(const LL<T>&toCopy){
  m_head = nullptr;
  m_size = 0;
  Node<T>* current = toCopy.m_head;
  while(current != nullptr){
    //Create a new node with the same data as the current node in the 
    //linked list to be copied
    Node<T>* newNode = new Node<T>(current->GetData().first);
    // Set the second value of the new node to be the same as the second 
    //value of the current node in the linked list to be copied
    newNode->GetData().second = current->GetData().second;
    //If the head node of the new linked list is null, set it to the new node
    //Otherwise, add the new node to the end of the linked list
    if(m_head == nullptr){
      m_head = newNode;
    }else{
      Node<T>* last = m_head;//Set last to the head node of the new linked list
      while(last->GetNext() != nullptr){
        last = last->GetNext();
      }
      //Add the new node to the end of the linked list
      last->SetNext(newNode);
    }
    m_size++;
    current = current->GetNext();
  } 
}

//LL Overloaded Assignment Operator
template <class T>
LL<T>& LL<T>::operator= (const LL& other){
  if(this != &other){//check if this and other are the same object
    this->~LL();

    Node<T>* otherNode = other.m_head; //set otherNode to the head of the other list
    //Iterate through other list and get value of current node
    //and insert value into this list
    while(otherNode != nullptr){
      T value = otherNode->GetData().first;
      this->Insert(value);
      //Set frequency of value in this list to frequency of other list
      this->Find(value)->GetData().second = otherNode->GetData().second;
      otherNode = otherNode->GetNext();
    }
  }
  return *this;
}

//LL Find function
template <class T>
Node<T>* LL<T>::Find(const T& data){
  Node<T>*current = m_head;
  while(current != nullptr){
    //if the current node contains the data then return current node
    if(current->GetData().first == data){
      return current;
    }
    current = current->GetNext();
  }
  return nullptr;
}

//LL Insert function
template <class T>
void LL<T>::Insert(const T& data){
  Node<T>* current = m_head;
  Node<T>* prev = nullptr;
  //iterate through the list to find the position to insert the new node
  while(current != nullptr && current->GetData().first < data){
    prev = current;
    current = current->GetNext();
  }
  if((current == nullptr)||(current->GetData().first != data)){
    Node<T>* newNode = new Node<T>(data);
    if(prev == nullptr){//if list is empty or data is to be inserted at the beginning of the list
      m_head = newNode;
    }
    else{
      prev->SetNext(newNode);
    }
    newNode->SetNext(current);
    m_size++;
  }
  else{
    current->GetData().second++;
  }
}

//LL RemoveAt function
template <class T>
void LL<T>::RemoveAt(const T& data){
  Node<T>* current = m_head;
  Node<T>* prev = nullptr;
  while((current != nullptr) and (current->GetData().first != data)){
    prev = current;
    current = current->GetNext();
  }
  if(current != nullptr){
    if(current->GetData().second > 1){//if the value of data is grater than 1
      current->GetData().second--;
    }
    else{
      if(prev == nullptr){
        m_head = current->GetNext();
      }
      else{
        prev->SetNext(current->GetNext());
      }
      delete current;
      m_size--; //Decrement the size
    }
  }
}

//Display function
template <class T>
void LL<T>::Display(){
  Node<T>* current = m_head;
  while(current != nullptr){
    cout << current->GetData().first << " " << current->GetData().second << endl;
    current = current->GetNext(); 
  }
}

//LL GetSize function
template <class T>
int LL<T>::GetSize(){
  return m_size;
}

//LL Overloaded << operator
template <class U>
ostream& operator<<(ostream& output, const LL<U>&list){
  Node<U>* current = list.m_head;
  while(current != nullptr){
    output << current->GetData().first << " " << current->GetData().second << endl;
    current = current->GetNext();
  }
  return output;
}

//LL pair overloaded operator
template <class T>
pair<T, int>& LL<T>::operator[] (int x){
  if(x < 0 or x >= m_size){
    throw out_of_range("Index out of range");
  }
  Node<T>* curr = m_head;
  for(int i = 0; i < x; i++){
    curr = curr->GetNext();
  }
  return curr->GetData();
}
