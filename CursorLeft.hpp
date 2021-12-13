#ifndef CURSORLEFT_HPP
#define CURSORLEFT_HPP

#include "Command.hpp"
#include "EditorException.hpp"

class cursorLeft: public Command
{
public:

    void execute(EditorModel& model) override
    {
        if (model.cursorLine() == 1 && 
            model.cursorColumn() == 1)
        {
            throw EditorException("Already at beginning");
        }
        model.cursorLeft();
    }

    void undo(EditorModel& model) override
    {
        model.cursorRight();
    }
};




#endif