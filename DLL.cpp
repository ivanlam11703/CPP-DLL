#include <iostream>
#include "DLL.h"
using namespace std;

   DLL::DLL() {
      head = tail = pointer = nullptr;
   }

   DLL::~DLL() {
      deleteAllNodes();
   }

   void DLL::deleteAllNodes() {
      DLLNode * current = head, *temp;

      while(current!=nullptr) {
         temp = current->next;
         delete current;
         current = temp;
      }
   }

   bool DLL::prepend(int data) {
      if (data <= 0) {
         return false;
      }
      DLLNode *temp = new DLLNode(data);
      if (head == nullptr) {
         head = tail = temp;
         return true;
      }
      temp->next = head;
      head->prev = temp;
      head = temp;
      return true;
   }

   bool DLL::append(int data) {
      if (data <= 0) {
         return false;
      }
      DLLNode *temp = new DLLNode(data);
      if (tail == nullptr) {
         head = tail = temp;
         return true;
      }
      temp->prev = tail;
      tail->next = temp;
      tail = temp;
      return true;
   }

   bool DLL::merge(DLL &other) {
      if (this == &other) {
         return true;
      }
      tail->next = other.head;
      other.head->prev = tail;
      other.head = other.tail = nullptr;
      return true;
   }

   DLL&  DLL::operator+=(const DLL &other) {
      if (this == &other) {
         return *this;
      }
      DLLNode * current = other.head;
      while (current != nullptr) {
         append(current->data);
         current = current->next;
      }
      return *this;
   }

   DLL& DLL::operator-=(const DLL &other) {
      if (this == & other) {
         return *this;
      }
      DLLNode * current = other.head;
      while (current != nullptr) {
         DLLNode* temp = head;
         while (temp != nullptr) {
            if (temp->data == current->data) {
               if (temp->prev != nullptr && temp->next != nullptr) {
                  DLLNode* temp2 = temp->next;
                  temp->prev->next = temp->next;
                  temp->next->prev = temp->prev;
                  delete temp;
                  temp = temp2;
                  continue;
               }
               if (temp == head) {
                  DLLNode* temp2 = temp->next;
                  head = temp->next;
                  temp->next->prev = nullptr;
                  delete temp;
                  temp = temp2;
                  continue;
               }
               if (temp == tail) {
                  DLLNode* temp2 = temp->next;
                  tail = temp->prev;
                  temp->prev->next = nullptr;
                  delete temp;
                  temp = temp2;
                  continue;
               }
            }
            temp = temp->next;
         }
         current = current->next;
      }
      return *this;
   }

   int DLL::getMax() {
      if (head == nullptr) {
         return 0;
      }
      DLLNode * current = head;
      int max = head->data;
      while (current != nullptr) {
         if (current->data > max) {
            max = current->data;
         }
         current = current->next;
      }
      return max;
   }

   int DLL::extractMax() {
      if (head == nullptr) {
         return 0;
      }
      int max = getMax();
      DLLNode * current = head;
      while (current->data != max) {
         current = current->next;
      }
      if (pointer == current) {
         pointer = current->next;
      }
      if (current != head && current != tail) {
         current->prev->next = current->next;
         current->next->prev = current->prev;
         delete current;
      } else if (current == head) {
         current->next->prev = nullptr;
         head = current->next;
         delete current;
      } else {
         current->prev->next = nullptr;
         tail = current->prev;
         delete current;
      }
      return max;
   }

   DLL DLL::extractOdds() {
      DLL tempDLL;
      if (head == nullptr) {
         return tempDLL;
      }
      DLLNode* temp = head;
      while (temp != nullptr) {
         if (temp->data % 2 == 1) {
            tempDLL.append(temp->data);
            if (temp != head && temp != tail) {
                  DLLNode* temp2 = temp->next;
                  temp->prev->next = temp->next;
                  temp->next->prev = temp->prev;
                  if (pointer == temp) {
                     pointer = temp2;
                  }
                  delete temp;
                  temp = temp2;
                  continue;
               }
            if (temp == head) {
               DLLNode* temp2 = temp->next;
               head = temp->next;
               temp->next->prev = nullptr;
               if (pointer == temp) {
                  pointer = temp2;
               }
               delete temp;
               temp = temp2;
               continue;
            }
            if (temp == tail) {
               DLLNode* temp2 = temp->next;
               tail = temp->prev;
               temp->prev->next = nullptr;
               if (pointer == temp) {
                  pointer = temp2;
               }
               delete temp;
               temp = temp2;
               continue;
            }
         }
         temp = temp->next;
      }
      return tempDLL;
   }

   DLL DLL::extractEvens() {
      DLL tempDLL;
      if (head == nullptr) {
         return tempDLL;
      }
      DLLNode* temp = head;
      while (temp != nullptr) {
         if (temp->data % 2 == 0) {
            tempDLL.append(temp->data);
            if (temp != head && temp != tail) {
                  DLLNode* temp2 = temp->next;
                  temp->prev->next = temp->next;
                  temp->next->prev = temp->prev;
                  if (pointer == temp) {
                     pointer = temp2;
                  }
                  delete temp;
                  temp = temp2;
                  continue;
               }
            if (temp == head) {
               DLLNode* temp2 = temp->next;
               head = temp->next;
               temp->next->prev = nullptr;
               if (pointer == temp) {
                  pointer = temp2;
               }
               delete temp;
               temp = temp2;
               continue;
            }
            if (temp == tail) {
               DLLNode* temp2 = temp->next;
               tail = temp->prev;
               temp->prev->next = nullptr;
               if (pointer == temp) {
                  pointer = temp2;
               }
               delete temp;
               temp = temp2;
               continue;
            }
         }
         temp = temp->next;
      }
      return tempDLL;
   }

   void DLL::show() {
      for (DLLNode *temp = head; temp != nullptr; temp = temp->next) {
         cout << "[" << temp->data << "]";
      }
      cout << endl;
   }

   bool DLL::reset() {
      if (head != nullptr) {
         pointer = head;
         return true;
      }
      return false;
   }

   int DLL::getNext() {
      if (pointer == nullptr) {
         return 0;
      }
      int val = pointer->data;
      pointer = pointer->next;
      return val;
   }