Coolest LinkedList. (maybe)
Matric number: 40280334
Author name: Darwon Rashid

(Okay, it is not the coolest LinkedList, it is okay at best.)

Summary:
Basically we create a LinkedList, A LinkedList has a head and tail node that first point to a nullptr. And the node comes from a struct called Node, each node has an int value, and another Node that
points to the next node. We had to code the given Constructors, methods, and Operator overloaders for the LinkedList Class.

Example:
LinkedList::LinkedList(const LinkedList& rhs) - performs a deep copy constructor.
void LinkedList::push(int value) - adds a value to the head of our list.
bool LinkedList::operator !=(const LinkedList& other) const - checks if two lists are not equal in state.
void LinkedList::reverse() - reverses the LinkedList.

Compiler and Version:

Microsoft (R) C/C++ Optimizing Compiler Version 19.10.24930 for x86
Copyright (C) Microsoft Corporation.  All rights reserved.

To build the program from the command line:

          cl /c LinkedList.cpp
          lib /OUT:LinkedList.lib LinkedList.obj
          cl /c test.cpp
          link test.obj LinkedList.lib

1) To build the program and run it from the makefile, you type nmake run.
2) To build the LinkedList library from the makefile, you type nmake library.
3) To clean from the makefile, you type nmake clean.
