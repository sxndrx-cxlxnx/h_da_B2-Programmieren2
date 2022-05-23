#include "terminalui.h"
#include "level.h"

// ************************ constructor ***********************************************
TerminalUI::TerminalUI(){

}

// ************************ other methods *********************************************
void TerminalUI::draw(Level* level){
    system("clear");

    // explain control
    std::cout << "Steuerung:" << std::endl << std::endl;
    std::cout << " 7 8 9           \\  |  up  |   / "   << std::endl;
    std::cout << " 4 5 6         left | stay | right" << std::endl;
    std::cout << " 1 2 3           /  | down |   \\ "   << std::endl;
    std::cout << std::endl;
    std::cout << "   0                 Abbruch " << std::endl;
    std::cout << std::endl << "      - Eingabe ohne Enter -" << std::endl;
    std::cout << "___________________________________" << std::endl;

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
