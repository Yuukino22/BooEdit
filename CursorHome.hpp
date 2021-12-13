#ifndef CURSORHOME_HPP
#define CURSORHOME_HPP

#include "Command.hpp"

class cursorHome: public Command
{
public:

    void execute(EditorModel& model) override
    {
        setCol(model.cursorColumn());
        model.cursorHome();
    }

    void undo(EditorModel& model) override
    {
        model.undoHome(originCursorCol);
    }

    //reset originCursorCol
    void setCol(int col)
    {
        originCursorCol = col;
    }

private:
    int originCursorCol = 1;
};



#endif