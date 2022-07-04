#include "terminalui.h"
#include "../Other/level.h"
#include <unistd.h>
#include <termios.h>

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

            bool tileHasCharacter = level->getTile(r,c)->hasCharacter();    // if a character is standing on it
            if( tileHasCharacter ){
                std::cout << level->getCharacters()[0]->getTexture();       // -> Output Character
            } else{
                std::cout << level->getTile(r,c)->getTexture();             // Else Output Tile
            }
        }
    }
    std::cout << std::endl;
}

// ***** move without enter *****
char getch2(void){
    char buf = 0;
    struct termios old = {0};
    fflush(stdout);
    if(tcgetattr(0, &old) < 0)
        perror("tcsetattr()");
    old.c_lflag &= ~ICANON;
    old.c_lflag &= ~ECHO;
    old.c_cc[VMIN] = 1;
    old.c_cc[VTIME] = 0;
    if(tcsetattr(0, TCSANOW, &old) < 0)
        perror("tcsetattr ICANON");
    if(read(0, &buf, 1) < 0)
        perror("read()");
    old.c_lflag |= ICANON;
    old.c_lflag |= ECHO;
    if(tcsetattr(0, TCSADRAIN, &old) < 0)
        perror("tcsetattr ~ICANON");
    printf("%c\n", buf);
    return buf;
};
// ***** move without enter *****

int TerminalUI::move(){
    char direction;
    int directionInt;

    while(true){
        direction = getch2();               // input without enter

        directionInt = direction - '0';     // convert char to int

        bool digit = isdigit( direction );

        if(0 <= directionInt && directionInt <= 9 && digit){        // react only to right input (number between 0 and 9)
            return directionInt;
        }
    }
}
