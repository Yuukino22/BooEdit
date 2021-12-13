#ifndef CURSOREND_HPP
#define CURSOREND_HPP

#include "Command.hpp"

class cursorEnd: public Command
{
public:

    void execute(EditorModel& model) override
    {
        setCol(model.cursorColumn());
        model.cursorEnd();
    }

    void undo(EditorModel& model) override
    {
        model.undoEnd(originCursorCol);
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