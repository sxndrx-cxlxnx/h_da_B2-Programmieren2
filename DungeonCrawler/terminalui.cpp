#include "terminalui.h"
#include "level.h"
#include <unistd.h>
#include <termios.h>

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


int TerminalUI::move(){
    char direction;
    int directionInt;

    while(true){
        direction = getch2();

        directionInt = direction - '0';

        bool digit = isdigit( direction );

        if(0 <= directionInt && directionInt <= 9 && digit){
            return directionInt;
        }
    }
}
