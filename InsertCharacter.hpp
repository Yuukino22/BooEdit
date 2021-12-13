#ifndef INSERTCHARACTER_HPP
#define INSERTCHARACTER_HPP

#include "Command.hpp"
#include <string>

class InsertCharacter: public Command
{
public:
    InsertCharacter(char c)
        :c{c}
    {
    }

    void execute(EditorModel& model) override
    {
        model.insertCharacter(this->c);
    }

    void undo(EditorModel& model) override
    {
        model.deleteCharacter();
    }

private:
    char c;
};

#endif