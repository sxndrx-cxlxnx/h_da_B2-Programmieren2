#include "terminalui.h"
#include "level.h"

// ************************ constructor ***********************************************
TerminalUI::TerminalUI(){

}

// ************************ other methods *********************************************
void TerminalUI::draw(Level* level){
    system("clear");
    for(int r = 0; r < level->getLength(); r++){                            // Row
        std::cout << std::endl;
        for(int c = 0; c < level->getWidth(); c++){                         // Column

            bool b = level->getTile(r,c)->hasCharacter();                   // if a character is standing on it
            if( b ){
                std::cout << level->getCharacters()[0]->getTexture();       // -> Output Character
            }else{
                std::cout << level->getTile(r,c)->getTexture();             // Else Output Tile

            }
        }
    }
    std::cout << std::endl;
}
