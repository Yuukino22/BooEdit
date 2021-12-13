// EditorModel.cpp
//
// ICS 45C Fall 2020
// Project #4: People Just Love to Play with Words
//
// Implementation of the EditorModel class

#include "EditorModel.hpp"
#include "EditorException.hpp"
#include <iostream>


EditorModel::EditorModel()
{
}


int EditorModel::cursorLine() const
{
    return cursorline;
}


int EditorModel::cursorColumn() const
{
    return cursorcol;
}


int EditorModel::lineCount() const
{
    return linecount;
}

std::vector<std::string*> EditorModel::Content()
{
    return content;
}


const std::string& EditorModel::line(int lineNumber) const
{
    return *content.at(lineNumber - 1);
}


const std::string& EditorModel::currentErrorMessage() const
{
    return errorMessage;
}


void EditorModel::setErrorMessage(const std::string& errorMessage)
{
    this->errorMessage = errorMessage;
}


void EditorModel::clearErrorMessage()
{
    errorMessage = "";
}

void EditorModel::cursorRight()
{
    if (cursorcol == (line(cursorline).length() + 1))
    {
        cursorcol = 1;
        cursorline += 1;
    }
    else
    {
        cursorcol += 1;
    } 
}

void EditorModel::cursorLeft()
{
    if (cursorcol == 1)
    {
        cursorline -= 1;
        cursorcol = line(cursorline).length() + 1;
    }
    else
    {
        cursorcol -= 1;
    }
}

void EditorModel::insertCharacter(char c)
{
    if (content.size() < cursorline)
    {
        content.push_back(new std::string(""));
    }
    if (content.at(cursorline - 1)->length() == (cursorcol - 1))
    {
        *(content.at(cursorline - 1)) += c;
        cursorcol += 1;
    }
    else if (content.at(cursorline - 1)->length() > (cursorcol - 1))
    {
        *(content.at(cursorline - 1)) = (content.at(cursorline - 1))->insert(cursorcol - 1, std::string(1,c));
        cursorcol += 1;
    }
}

void EditorModel::deleteCharacter()
{
    if (content.at(cursorline - 1)->length() >= (cursorcol - 1))
    {
        content.at(cursorline - 1)->erase(cursorcol - 2, 1);
        cursorcol -= 1;
    }
}

void EditorModel::newLine()
{
    if (content.at(cursorline - 1)->length() == (cursorcol - 1))
    {
        content.insert(content.begin() + cursorline, new std::string(""));
        cursorcol = 1;
        cursorline += 1;
        linecount += 1;
    }
    else if (content.at(cursorline - 1)->length() > (cursorcol - 1))
    {
        content.insert(content.begin() + cursorline, new std::string(""));
        *(content.at(cursorline)) += (content.at(cursorline - 1)->substr(cursorcol - 1));
        content.at(cursorline - 1)->erase(cursorcol - 1);
        cursorcol = 1;
        cursorline += 1;
        linecount += 1;
    }
}

void EditorModel::undoNewLine()
{
    if (content.at(cursorline - 1)->length() == 0)
    {
        delete content.at(cursorline - 1);
        content.erase(content.begin() + cursorline - 1);
        cursorcol = content.at(cursorline - 2)->length() + 1;
        cursorline -= 1;
        linecount -= 1;
    }
    else
    {
        cursorcol = content.at(cursorline - 2)->length() + 1;
        *(content.at(cursorline - 2)) += *(content.at(cursorline - 1));
        delete content.at(cursorline - 1);
        content.erase(content.begin() + cursorline - 1);
        cursorline -= 1;
        linecount -= 1;
    }
    
}

void EditorModel::cursorUp()
{
    if (content.at(cursorline -2)->length() >= cursorcol)
    {
        cursorline -= 1;
    }
    else
    {
        cursorline -= 1;
        cursorcol = content.at(cursorline - 1)->length() + 1;
    }
}


void EditorModel::undoUp(int col, int line)
{
    cursorcol = col;
    cursorline = line;
}

void EditorModel::cursorDown()
{
    if (content.at(cursorline)->length() >= cursorcol)
    {
        cursorline += 1;
    }
    else
    {
        cursorline += 1;
        cursorcol = content.at(cursorline - 1)->length() + 1;
    }
}


void EditorModel::undoDown(int col, int line)
{
    cursorcol = col;
    cursorline = line;
}

void EditorModel::cursorHome()
{
    cursorcol = 1;
}

void EditorModel::undoHome(int col)
{
    cursorcol = col;
}

void EditorModel::cursorEnd()
{
    cursorcol = content.at(cursorline - 1)->length() + 1;
}

void EditorModel::undoEnd(int col)
{
    cursorcol = col;
}


void EditorModel::backSpace()
{
    if (cursorcol == 1)
    {
        undoNewLine();
    }
    else if (cursorcol <= (content.at(cursorline - 1)->length() + 1))
    {
        content.at(cursorline - 1)->erase(cursorcol - 2, 1);
        cursorcol -= 1;
    } 
}

void EditorModel::undoBackSpace(char c, int col, int line)
{
    if (col != 1)
    {
        content.at(cursorline - 1)->insert(cursorcol - 1, std::string(1,c));
        cursorcol = col;
        cursorline = line;
    }
    else
    {
        newLine();
    }
}

void EditorModel::deleteLine()
{
    if (cursorline == 1 && linecount == 1)
    {
        *(content.at(0)) = "";
        cursorcol = 1;
        cursorline = 1;
    }
    else if (cursorline == linecount)
    {
        delete content.at(cursorline - 1);
        content.erase(content.begin() + cursorline - 1);
        cursorline -= 1;
        linecount -= 1;
        if (content.at(cursorline - 1)->length() <= (cursorcol - 1))
        {
            cursorcol = content.at(cursorline - 1)->length() + 1;
        }
    }
    else
    {
        delete content.at(cursorline - 1);
        content.erase(content.begin() + cursorline - 1);
        linecount -= 1;
        if (content.at(cursorline - 1)->length() <= (cursorcol - 1))
        {
            cursorcol = content.at(cursorline - 1)->length() + 1;
        }
    }
}

void EditorModel::undoDeleteLine(std::string s, int col, int line, int linec)
{
    if (linec == 1)
    {
        *(content.at(0)) = s;
        cursorcol = col;
        cursorline = line;
    }
    else if (linec == line)
    {
        linecount += 1;
        content.push_back(new std::string(""));
        *(content.at(linecount - 1)) = s;
        cursorcol = col;
        cursorline = line;
    }
    else
    {
        linecount += 1;
        content.insert(content.begin() + line - 1, new std::string(""));
        *(content.at(cursorline - 1)) = s;
        cursorcol = col;
    }
    
}

void EditorModel::clearContent()
{
    while (!content.empty())
    {
        delete content.back();
        content.pop_back();
    }
}