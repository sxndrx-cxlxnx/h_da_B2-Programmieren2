#ifndef LIST_H
#define LIST_H
#include <iostream>
#include "level.h"
#include <stdexcept>

class List{
private:
    struct Element{
        Level* data = nullptr;
        Element* next = nullptr;
        Element* back = nullptr;
    };

    struct iterator{
        Element* pointer = new Element();
        iterator& operator++(){
            if( pointer->next != nullptr ){
                pointer = pointer->next;
                return *this;
            }else{
                throw std::runtime_error("no next element");
            }
        };
        iterator& operator--(){
            if( pointer->back != nullptr ){
                pointer = pointer->back;
                return *this;
            }else{
                throw std::runtime_error("already first element");
            }

        };
        Level& operator*() const {
            if(pointer->data == nullptr){
                throw std::runtime_error("nullpointer");
            }else{
                return *pointer->data;}
        };
        bool operator==(const iterator& theOther){ return this->pointer->data == theOther.pointer->data; };
        bool operator!=(const iterator& theOther){ return !(*this == theOther); };
    };
    iterator first;
    iterator last;

public:
    List();
    void push_front(Level* level);
    void push_back(Level* level);
    void pop_back();
    void pop_front();
    bool empty();
    std::size_t size();
    Element* searchElement(Level* level);
    void remove(Level* level);
    iterator begin();
    iterator end();

};

#endif // LIST_H
