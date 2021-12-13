#ifndef CURSORRIGHT_HPP
#define CURSORRIGHT_HPP

#include "Command.hpp"
#include "EditorException.hpp"
#include <iostream>

class cursorRight: public Command
{
public:

    void execute(EditorModel& model) override
    {
        if (model.cursorLine() == model.lineCount() && 
            model.cursorColumn() == (model.line(model.cursorLine()).length() + 1))
        {
            throw EditorException("Already at end");
        }
        model.cursorRight();
    }

    void undo(EditorModel& model) override
    {
        model.cursorLeft();
    }
};




#endif