#include "active.h"
#include "passive.h"

Active::Active(){

}

void Active::attach(Passive *passiveTile){

    bool alreadyIncluded = false;
    for(int i = 0; i < static_cast<int>( observers.size() ); i++){
        if(observers[i] == passiveTile){
            alreadyIncluded = true;
            break;
        }
    }
    if(!alreadyIncluded){
        observers.push_back(passiveTile);
    }
}

void Active::detach(Passive *passiveTile){

    for(int i = 0; i < static_cast<int>( observers.size() ); i++){
        if(observers[i] == passiveTile){
            delete observers[i];
            observers.erase(observers.begin() +i);
            break;
        }
    }
}

void Active::activate(){
    for(int i = 0; i < static_cast<int>( observers.size() ); i++){
        observers[i]->notify(this);
    }
}
