#ifndef BACKSPACE_HPP
#define BACKSPACE_HPP

#include "Command.hpp"


class backSpace: public Command
{
public:

    void execute(EditorModel& model) override;

    void undo(EditorModel& model) override;

    //reset originCursorCol
    void setCol(int col);

    //reset originCursorLine
    void setLine(int line);

    //reset originChar
    void setChar(char c);

private:
    char originChar = '\0';
    int originCursorCol = 1;
    int originCursorLine = 1;
};



#endif