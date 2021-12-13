#include "DeleteLine.hpp"
#include "EditorException.hpp"

void deleteLine::execute(EditorModel& model)
{
    if (model.cursorLine() == 1 && model.lineCount() == 1 && model.line(1).length() == 0)
    {
        throw EditorException("Already empty");
    }
    setCol(model.cursorColumn());
    setLine(model.cursorLine());
    setLineCount(model.lineCount());
    setString(model.line(model.cursorLine()));
    model.deleteLine();
}

void deleteLine::undo(EditorModel& model)
{
    model.undoDeleteLine(originString, originCursorCol, originCursorLine, originLineCount);
}

void deleteLine::setCol(int col)
{
    originCursorCol = col;
}

void deleteLine::setLine(int line)
{
    originCursorLine = line;
}

void deleteLine::setString(std::string c)
{
    originString = c;
}

void deleteLine::setLineCount(int linecount)
{
    originLineCount = linecount;
}