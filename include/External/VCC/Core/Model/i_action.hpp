#pragma once
#include <string>

using namespace std;

namespace vcc
{
    class IAction
    {
    protected:
        IAction() {}
        ~IAction() {}

        virtual void DoRedo() = 0;
        virtual void DoUndo() = 0;

        virtual wstring GetRedoMessage() = 0;
        virtual wstring GetUndoMessage() = 0;

        virtual void LogRedo() = 0;
        virtual void LogUndo() = 0;
            
    public:
        virtual wstring GetMessage() = 0;
        
        virtual void Redo() = 0;
        virtual void Undo() = 0;
    };
}
