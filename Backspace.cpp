#include "Backspace.hpp"
#include "EditorException.hpp"

void backSpace::execute(EditorModel& model)
{
    if (model.cursorColumn() == 1 && model.cursorLine() == 1)
    {
        throw EditorException("Already at beginning");
    }

    setCol(model.cursorColumn());
    setLine(model.cursorLine());

    if (model.cursorColumn() >= 2)
    {
        setChar(model.line(model.cursorLine()).at(model.cursorColumn() - 2));
    }   

    model.backSpace();
}

void backSpace::undo(EditorModel& model)
{
    model.undoBackSpace(originChar, originCursorCol, originCursorLine);
}

void backSpace::setCol(int col)
{
    originCursorCol = col;
}

void backSpace::setLine(int line)
{
    originCursorLine = line;
}

void backSpace::setChar(char c)
{
    originChar = c;
}