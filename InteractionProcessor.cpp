// InteractionProcessor.cpp
//
// ICS 45C Fall 2020
// Project #4: People Just Love to Play with Words
//
// Implementation of the InteractionProcessor class

#include "InteractionProcessor.hpp"
#include "EditorException.hpp"
#include "Interaction.hpp"
#include "Command.hpp"
#include <stack>
#include <iostream>


// This function implements command execution, but does not handle "undo"
// and "redo"; you'll need to add that handling.

namespace
{
    std::stack<Command*> commandStack; //A stack stores all the command which has been executed.
    std::stack<Command*> undoStack;    //A stack stores all the command which has been undid.
}

void InteractionProcessor::run()
{
    view.refresh();

    while (true)
    {
        Interaction interaction = interactionReader.nextInteraction();

        if (interaction.type() == InteractionType::quit)
        {
            while(!commandStack.empty())
            {
                delete commandStack.top();
                commandStack.pop();
            }
            while(!undoStack.empty())
            {
                delete undoStack.top();
                undoStack.pop();
            }
            model.clearContent();
            break;
        }
        else if (interaction.type() == InteractionType::undo)
        {
            if (!commandStack.empty())
            {
                commandStack.top()->undo(model);
                undoStack.push(commandStack.top());
                commandStack.pop();
                model.clearErrorMessage();
                view.refresh();
            }
        }
        else if (interaction.type() == InteractionType::redo)
        {
            if (!undoStack.empty())
            {
                undoStack.top()->execute(model);
                commandStack.push(undoStack.top());
                undoStack.pop();
                model.clearErrorMessage();
                view.refresh();
            }
        }
        else if (interaction.type() == InteractionType::command)
        {
            Command* command = interaction.command();

            try
            {
                command->execute(model);
                commandStack.push(command);
                while(!undoStack.empty())
                {
                    delete undoStack.top();
                    undoStack.pop();
                }
                model.clearErrorMessage();
            }
            catch (EditorException& e)
            {
                model.setErrorMessage(e.getReason());
            }


            view.refresh();



            // Note that you'll want to be more careful about when you delete
            // commands once you implement undo and redo.  For now, since
            // neither is implemented, I've just deleted it immediately
            // after executing it.  You'll need to wait to delete it until
            // you don't need it anymore.
        }
    }
}

