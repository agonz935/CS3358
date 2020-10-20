// FILE: QueueCLL.cpp
// IMPLEMENTS: QueueCLL (see QueueCLL.h for documentation.)
//
// INVARIANT for the QueueCLL class:
//   1. The number of items in the QueueCLL is stored in the member
//      variable numItems.
//   2. The items themselves are stored in a circular linked list
//      of Nodes.
//      2.1 The member variable rear_ptr points to the rear of the
//          QueueCLL (tail node of the circular linked list).
//          heap[0] through heap[used - 1].
//      2.2 The rear_ptr is set to the null address if the circular
//          linked list (thus queue) is empty.

#include <iostream>
#include <cassert>  // provides assert
#include <cstdlib>  // provides size_t
using namespace std;

#include "QueueCLL.h"

QueueCLL::QueueCLL() : rear_ptr(0), numItems(0) { }

QueueCLL::QueueCLL(const QueueCLL& src) : rear_ptr(src.rear_ptr),
                                          numItems(src.numItems)
{
   if(!empty())
   {
      Node* cursor = src.rear_ptr->link;

      while(cursor != src.rear_ptr)
      {
         push(cursor->data);
         cursor = cursor->link;
      }

      push(cursor->data);
   }
}

QueueCLL::~QueueCLL()
{
   Node *cursor;
   cursor = rear_ptr;

   while (rear_ptr != 0)
   {
      rear_ptr = rear_ptr->link;
      delete cursor;
      cursor = rear_ptr;
      --numItems;

      if(numItems == 1)
      {
         rear_ptr = 0;
         --numItems;
      }
      else
         ;
   }
}

QueueCLL& QueueCLL::operator=(const QueueCLL& rhs)
{
   if(this != &rhs)
   {
      this->~QueueCLL();

      if(rhs.numItems > 0)
      {
         Node* nodePtr;
         nodePtr = rhs.rear_ptr->link;

         while(nodePtr != rhs.rear_ptr)
         {
            push(nodePtr->data);
            nodePtr = nodePtr->link;
         }

         push(nodePtr->data);
      }
   }

   return *this;
}

void QueueCLL::push(const value_type& entry)
{
   Node* temp = new Node;

   temp->data = entry;
   temp->link = 0;

   if(numItems == 0)
      rear_ptr = temp;

   else if(numItems == 1)
   {
      temp->link = rear_ptr;
      rear_ptr->link = temp;
      rear_ptr = rear_ptr->link;
   }

   else if(numItems > 1)
   {
      temp->link = rear_ptr->link;
      rear_ptr->link = temp;
      rear_ptr = temp;
   }

   ++numItems;
}

QueueCLL::value_type QueueCLL::front( ) const
{
   assert(size() > 0);

   if(numItems == 1)
      return rear_ptr->data;
   else
      return rear_ptr->link->data;
}

void QueueCLL::pop( )
{
   assert(size() > 0);

   Node* temp = new Node;

   if(numItems == 1)
   {
      temp = rear_ptr;
      rear_ptr->link = 0;
      delete temp;
   }
   else
   {
      temp = rear_ptr->link;
      rear_ptr->link = rear_ptr->link->link;
      delete temp;
   }

   --numItems;
}

QueueCLL::size_type QueueCLL::size() const
{
   return numItems;
}

bool QueueCLL::empty() const
{
   return(numItems == 0);
}

QueueCLL::value_type QueueCLL::peek(size_type n) const
{
   assert(size() > 0);

   Node* nodePtr = new Node;

   if(numItems == 1)
      return rear_ptr->data;

   else
   {
      nodePtr = rear_ptr->link;

      for(size_type i = 1; i < n; ++i)
         nodePtr = nodePtr->link;

      return nodePtr->data;
   }
}

