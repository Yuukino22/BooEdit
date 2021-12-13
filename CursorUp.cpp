#include "CursorUp.hpp"
#include "EditorException.hpp"


void cursorUp::execute(EditorModel& model)
{
    if (model.cursorLine() == 1)
    {
        throw EditorException("Already at top");
    }
    setCol(model.cursorColumn());
    setLine(model.cursorLine());
    model.cursorUp();
}

void cursorUp::undo(EditorModel& model)
{
    model.undoUp(originCursorCol, originCursorLine);
}

void cursorUp::setCol(int col)
{
    originCursorCol = col;
}

void cursorUp::setLine(int line)
{
    originCursorLine = line;
}