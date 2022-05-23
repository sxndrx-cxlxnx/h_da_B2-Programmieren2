#include "active.h"
#include "passive.h"

// ************************ constructor ***********************************************
Active::Active(){

}

// ************************ other methods *********************************************
void Active::attach(Passive *passiveTile){

    bool alreadyIncluded = false;
    for(int i = 0; i < static_cast<int>( observers.size() ); i++){          // look if "passive Tile" already in vector "observers"
        if(observers[i] == passiveTile){
            alreadyIncluded = true;
            break;
        }
    }                                                                        // if not:
    if(!alreadyIncluded){                                                    // attach "passive Tile" to vector "observers"
        observers.push_back(passiveTile);
    }
}

void Active::detach(Passive *passiveTile){
    for(int i = 0; i < static_cast<int>( observers.size() ); i++){          // search for "passive Tile" in vector "observers"
        if(observers[i] == passiveTile){
            delete observers[i];                                            // delete
            observers.erase(observers.begin() +i);                          // detach
            break;
        }
    }
}
