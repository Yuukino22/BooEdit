#ifndef NEWLINE_HPP
#define NEWLINE_HPP

#include "Command.hpp"

class newLine: public Command
{
public:

    void execute(EditorModel& model) override
    {
        model.newLine();
    }

    void undo(EditorModel& model) override
    {
        model.undoNewLine();
    }
};



#endif