#ifndef PASSIVE_H
#define PASSIVE_H
class Active;

class Passive{
public:
    // constructor
    Passive();

    // destructor (inline)
    virtual ~Passive(){};

    // other methods
    virtual void notify(Active* source) = 0;
};

#endif // PASSIVE_H
