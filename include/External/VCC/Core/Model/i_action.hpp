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

        virtual void _DoRedo() = 0;
        virtual void _DoUndo() = 0;

        virtual wstring _GetRedoMessage() = 0;
        virtual wstring _GetUndoMessage() = 0;

    public:
        virtual void SetSeqNo(size_t seqNo) = 0;
        virtual size_t GetSeqNo() = 0;
        virtual wstring GetMessage() = 0;
        
        virtual void Redo() = 0;
        virtual void Undo() = 0;
    };
}
