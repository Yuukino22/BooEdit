// KeypressInteractionReader.cpp
//
// ICS 45C Fall 2020
// Project #4: People Just Want to Play with Words
//
// Implementation of the KeypressInteractionReader
//
// YOU WILL NEED TO IMPLEMENT SOME THINGS HERE

#include "KeypressInteractionReader.hpp"
#include "CursorRight.hpp"
#include "CursorLeft.hpp"
#include "InsertCharacter.hpp"
#include "NewLine.hpp"
#include "CursorUp.hpp"
#include "CursorDown.hpp"
#include "CursorHome.hpp"
#include "CursorEnd.hpp"
#include "Backspace.hpp"
#include "DeleteLine.hpp"
#include <iostream>

// You will need to update this member function to watch for the right
// keypresses and build the right kinds of Interactions as a result.
//
// The reason you'll need to implement things here is that you'll need
// to create Command objects, which you'll be declaring and defining
// yourself; they haven't been provided already.
//
// I've added handling for "quit" here, but you'll need to add the others.

Interaction KeypressInteractionReader::nextInteraction()
{
    while (true)
    {
        Keypress keypress = keypressReader.nextKeypress();

        if (keypress.ctrl())
        {
            // The user pressed a Ctrl key (e.g., Ctrl+X); react accordingly
            switch (keypress.code())
            {
            case 'X':
                return Interaction::quit();
            case 'O':
                return Interaction::command(new cursorRight);
            case 'U':
                return Interaction::command(new cursorLeft);
            case 'Z':
                return Interaction::undo();
            case 'A':
                return Interaction::redo();
            case 'J':
            case 'M':
                return Interaction::command(new newLine);
            case 'I':
                return Interaction::command(new cursorUp);
            case 'K':
                return Interaction::command(new cursorDown);
            case 'Y':
                return Interaction::command(new cursorHome);
            case 'P':
                return Interaction::command(new cursorEnd);
            case 'H':
                return Interaction::command(new backSpace);
            case 'D':
                return Interaction::command(new deleteLine);
            }
        }
        else
        {
            return Interaction::command(new InsertCharacter(keypress.code()));
            // The user pressed a normal key (e.g., 'h') without holding
            // down Ctrl; react accordingly
        }
    }
}

