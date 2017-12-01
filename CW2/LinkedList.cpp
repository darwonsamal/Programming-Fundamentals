/*
   File:   LinkedList.cpp
   Author: Darwon Rashid
   Matric Number: 40280334

   Last modified 02/04/2017

   Constructors/Functions/Operator Overload implementation
   for the Linked list class.

  This is where the code is written.
 */



#include <string>
#include <cassert>
#include <iostream>
#include <sstream>
#include "linked_list.h"
using namespace std;


//creates an empty list
LinkedList::LinkedList()
{
 // Do absolutely nothing.
}

//creates a list with an initial value to store
LinkedList::LinkedList(int value)
{
  // we make a new head node
  head = new Node;
  // assign value to the head node
  head->data = value;
  // connect tail to the head
  tail = head;
}

//copy constructor (performs a deep copy)
LinkedList::LinkedList(const LinkedList& rhs)
{
  // Make a temporary node that starts off as the head of the
  // List in which we are copying.

  // A note on auto, try your best not to use it for it is hard to read.
  auto temp = rhs.head;
  // Iteriate though each node till the end of the list.
  while(temp != nullptr)
  {
    // We append each node to our list.
    append(temp->data);
    temp = temp->next;
  }
}


//destroys (cleans up) the list
LinkedList::~LinkedList()
{

 auto temp = head;
 Node* prev;
 while(temp != nullptr)
 {
   // Make prev temp to delete prev later on.
   prev = temp;
   temp = temp->next;
   // See ya later node
   delete prev;
 }
  //Once the nodes are deleted, we assign the null pointers to to the head and tail.
  head = nullptr;
  tail = nullptr;
}

//adds a value to the head of the list
void LinkedList::push(int value)
{
  // If LinkedList is empty make new one
  if (head == nullptr)
  {
    head = new Node;
    head->data = value;
    tail = head;
  }
  else
  {
    // Make a new node and make it the head
    Node *node = new Node;
    node->data = value;
    node->next = head;
    head = node;
  }

}

//gets the last element from the list, without removing it
//requires: list not empty
int LinkedList::peekTail()
{

     assert(head != nullptr);
     return tail->data;

}

//prints the list in order from head to tail
string LinkedList::toString() const
{
  // Set temp to head.
  auto temp = head;
  string str;
  // If LinkedList is empty, return nothing.
  if(head == nullptr)
  {
    return "";
  }
  else
  {
    // While LinkedList is not empty, append each value to a string.
    while(temp != nullptr)
    {
      str.append(to_string(temp->data));
      temp = temp->next;
      // Append a space between each value in each node.
      if(temp != nullptr)
      {
        str.append(" ");
      }
    }
  }

  return str;
}

//removes and returns the value at the head of the list
//requires: list not empty
int LinkedList::pop()
{
  assert(head != nullptr);
  Node* temp;
  int value = 0;


  // Assign temp to head.
  temp = head;
  // Assign value inside head into a variable also called value.....
  value = head->data;
  // Head is changed, why oh why.
  head = head->next;
  // RIP temp.
  delete temp;

  // Returns value, not that you needed me to comment it.
  return value;
}

//adds a value to the end of the list
void LinkedList::append(int value)
{
  // Make new node and assign the value
  auto temp = new Node;
  temp->data = value;
  // Points to nullptr for it will be the tail later on.
  temp->next = nullptr;

  // If LinkedList is empty, make new one.
  if(head == nullptr)
  {
    head = temp;
    tail = head;
  }
  else
  {
    // Points tail to temp.
    tail->next = temp;
    //Then assign temp to tail.
    tail = temp;
  }
}

//appends the deep copies of the nodes of rhs on to the end of this list
void LinkedList::appendList(const LinkedList& rhs)
{
  // Assigns temp to head from rhs.
   auto temp = rhs.head;

   while(temp != nullptr)
   {
     // Appends nodes from the second LinkedList into ours
     append(temp->data);
     temp = temp->next;
   }

}

//inserts a value immediately after the first occurrence of afterValue,
//if afterValue is not in the list then inserts at the tail
void LinkedList::insertAfter(int value, int afterValue)
{
  auto flag = true;
  auto current = head;

  if(head == nullptr)
  {
    cout << "The list is empty mate";
  }

  else
  {

    while(flag)
    {
      // if our current node equals the aftervalue, we make a new node and add it after our current node.
      if(current->data == afterValue)
      {
        auto temp = new Node;
        temp->data = value;
        // We make it point to the next node from current's view.
        temp->next = current->next;

        // if our aftervalue is the last node in the linked list, we make the new node the tail.
        if(current->next == nullptr)
        {
          tail = temp;
        }
        //Change our current's pointer to the new node.
        current->next = temp;
        //Exit the loop.
        flag = false;
      }

      // If we go through the LinkedList and and not find the aftervalue, we append the value.
      if(current->next == nullptr)
      {
        append(value);
        flag = false;
      }

      else
      {
        // Iteriate
        current = current->next;
      }
    }
  }
}

//removes all occurrences of value from the list
void LinkedList::removeAllOccurences(int value)
{
  auto current = head;
  Node* prev;
  if(head == nullptr)
  {
    cout <<"List is empty mate" << endl;
  }

  else
  {
    // This is for the case if our value is the head.
    while(current && current->data == value)
    {
      prev = current;
      current = current->next;
      head = current;
      delete prev;
    }

    // This is for the case if our value is not the head.
    while(current)
    {

      if(current->data == value)
      {
        // We make prev point to what our current is pointing to
        prev->next = current->next;
        // We delete current
        delete current;
        // And then assign current to what prev is pointing to.
        current = prev->next;
      }

      else
      {
        // Iteriate
        prev = current;
        current = current->next;
      }
    }
  }
}

//reverses the list
void LinkedList::reverse()
{
  Node* prev = nullptr;
  auto current = head;
  Node* next;

  while(current != nullptr)
  {
    // We make next point to what our current node is pointing to.
    next = current->next;
    // We then make current point to our previous node.
    current->next = prev;
    // Make prev current.
    prev = current;
    // make current next.
    current = next;
  }
  // Assign
  tail = head;
  head = prev;
}

//checks if two lists are equal in state (contain the same values in the same order)
bool LinkedList::operator ==(const LinkedList& other) const
{
  // If their toStrings are equal, it means that the two lists are equal.
   if(this->toString() == other.toString())
   {
     return true;
   }
   // Else return false
   return false;
}

//checks if two lists are not equal in state
bool LinkedList::operator !=(const LinkedList& other) const
{
  // If their toStrings are equal, it means that they are equal.
  if(this->toString() == other.toString())
  {
    return false;
  }
  else
  {
    // Else return true
    return true;
  }
}

//pushes a new value onto the head of the list
LinkedList& LinkedList::operator +(int value)
{
    push(value);
    return *this;
}

//copy assignment operator (performs a deep copy)
LinkedList& LinkedList::operator =(const LinkedList& rhs)
{
    auto second_list_temp = rhs.head;


    // For the future, toStrings arent suggested.
    // If our list is equal to the list we wanna have as ours, then return our list back.
    if(this->toString() == rhs.toString())
    {
      return *this;
    }

    else
    {
        // Implement delete helper function
        // Delete our list.
      this->~LinkedList();

      // And then add the values from the second LinkedList to ours.
      while(second_list_temp != nullptr)
      {
         append(second_list_temp->data);

         second_list_temp = second_list_temp->next;
      }

    }

    return *this;
}

//pushes values from an input stream onto the front of the list
std::istream& operator>>(std::istream &in, LinkedList &value)
{
     int input_value;
     char ch;

     // While our input stream isn't empty.
     while(!in.eof())
     {
       // we get each character.
       in.get(ch);
       //If it is a new line, we break the loop.
       if(ch == '\n')
       {
         break;
       }
       // take in the input stream as an int.
     in >> input_value;

     // Add it to the LinkedList.
     value.push(input_value);
     }

   return in;
}

//writes the values, in order, to an output stream
std::ostream& operator<<(std::ostream &out, const LinkedList &value)
{
    // output the toString method for the LinkedList.
    out << value.toString();
    return out;
}
