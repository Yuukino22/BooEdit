#ifndef CURSORDOWN_HPP
#define CURSORDOWN_HPP

#include "Command.hpp"


class cursorDown: public Command
{
public:

    void execute(EditorModel& model) override;

    void undo(EditorModel& model) override;

    //reset originCursorCol
    void setCol(int col);

    //reset originCursorLine
    void setLine(int line);

private:
    int originCursorCol = 1;
    int originCursorLine = 1;
};




#endif