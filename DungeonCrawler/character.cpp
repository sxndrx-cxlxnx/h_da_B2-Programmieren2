#include "character.h"
// #include <conio.h>                       // just in Windows
#include <unistd.h>
#include <termios.h>

// ************************ setter - methods *****************************************
void Character::setTile(Tile *newTile){
    tile = newTile;
}

// ************************ getter - methods *****************************************
const std::string &Character::getTexture() const{
    return texture;
}

Tile *Character::getTile() const{
    return tile;
}

// ************************ other functions ******************************************
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

int Character::move(){
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



