#include "CursorDown.hpp"
#include "EditorException.hpp"

void cursorDown::execute(EditorModel& model)
{
    if (model.cursorLine() == model.lineCount())
    {
        throw EditorException("Already at bottom");
    }
    setCol(model.cursorColumn());        
    setLine(model.cursorLine());
    model.cursorDown();
}

void cursorDown::undo(EditorModel& model)
{
    model.undoDown(originCursorCol, originCursorLine);
}

void cursorDown::setCol(int col)
{
    originCursorCol = col;
}

void cursorDown::setLine(int line)
{
    originCursorLine = line;
}