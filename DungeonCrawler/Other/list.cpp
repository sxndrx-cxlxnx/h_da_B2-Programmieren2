#include "list.h"

// ************************ constructor ***********************************************
List::List(){
    first.pointer->next = last.pointer;
    last.pointer->next = NULL;
    last.pointer->back = first.pointer;
    first.pointer->back = nullptr;
}

// ************************ destructor ************************************************
List::~List(){
    while(!empty()){
        pop_back();
    }
}

// ************************ methods ***************************************************
void List::push_front(Level *level){
    Element* element = new Element();
    element->data = level;

    element->next = first.pointer->next;
    first.pointer->next->back = element;
    first.pointer->next = element;
    element->back = first.pointer;
}

void List::push_back(Level *level){
    Element* element = new Element();
    element->data = level;

    element->next = last.pointer;
    element->back = last.pointer->back;
    last.pointer->back->next = element;
    last.pointer->back = element;
}

void List::pop_back(){
    Element* runner = last.pointer->back;

    last.pointer->back->back->next = last.pointer;
    last.pointer->back = runner->back;
    delete runner;
}

void List::pop_front(){
    Element* runner = first.pointer->next;

    first.pointer->next->next->back = first.pointer;
    first.pointer->next = runner->next;
    delete runner;
}

bool List::empty(){
    if(first.pointer->next == last.pointer){
        return true;
    } else{
        return false;
    }
}

std::size_t List::size(){
    Element* runner = first.pointer;
    size_t counter = 0;
    if(empty()){
        return 0;
    } else{
        while(runner->next != last.pointer){
            counter ++;
            runner = runner->next;
        }
        return counter;
    }
}

List::Element *List::searchElement(Level *level){
    Element *runner = first.pointer->next;

    for(size_t i = 0; i <= size(); i++){
        if(runner->data != level){
            runner = runner->next;
        } else if(runner == last.pointer){
            // cannot remove sth not included
            runner = nullptr;
        }
    }
    return runner;
}

void List::remove(Level *level){
    Element *runner = searchElement(level);

    runner->next->back = runner->back;
    runner->back->next = runner->next;
    delete runner;
}

List::iterator List::begin(){
    return first;
}

List::iterator List::end(){
    return last;
}
