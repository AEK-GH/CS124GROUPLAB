#include "Stack.hpp"

Stack::Stack()
{  
   first = nullptr;
   len = 0;
}

Stack::~Stack()
{
    while (first != nullptr) 
    {
        Node* temp = first;
        first = first->next;
        delete temp;
    }
}


void Stack::push(Waypoint* element)
{  
   Node* new_node = new Node;
   new_node->data = element;
   new_node->next = first;
   first = new_node;
   len++;
}

Waypoint* Stack::top() const
{
   return first->data;
}

void Stack::pop()
{
   Node* to_delete = first;
   first = first->next;
   delete to_delete;
   len--;
}

int Stack::size() const
{
   return len;
}
