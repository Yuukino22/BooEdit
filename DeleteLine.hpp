#ifndef DELETELINE_HPP
#define DELETELINE_HPP

#include "Command.hpp"



class deleteLine: public Command
{
public:

    void execute(EditorModel& model) override;


    void undo(EditorModel& model) override;

    //reset originCursorCol
    void setCol(int col);

    //reset originCursorLine
    void setLine(int line);

    //reset originString
    void setString(std::string c);

    //reset originLineCount
    void setLineCount(int linecount);


private:
    std::string originString = "";
    int originCursorCol = 1;
    int originCursorLine = 1;
    int originLineCount = 1;
};



#endif