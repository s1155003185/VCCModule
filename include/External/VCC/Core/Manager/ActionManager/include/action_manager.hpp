#pragma once
#include "base_manager.hpp"
#include "i_action.hpp"

#include <memory>
#include <stdint.h>

using namespace std;

namespace vcc
{
    class ActionManager : public BaseManager
    {
        GETSET(int64_t, MaxActionListSize, 100)
        VECTOR(shared_ptr<IAction>, Actions)
        GET(int64_t, CurrentActionIndex, -1)

    public:
        ActionManager() : BaseManager(ManagerType::Action) {}
        ~ActionManager() {}

        int64_t Redo(shared_ptr<IAction> action);
        int64_t Redo();
        int64_t Redo(int64_t noOfStep);
        int64_t RedoToActionIndex(int64_t actionIndex);

        int64_t Undo();
        int64_t Undo(int64_t noOfStep);
        int64_t UndoToActionIndex(int64_t actionIndex);
        
        int64_t ChopActionListWithSize(int64_t size);
        int64_t ChopActionListFromIndex(int64_t index);
        int64_t ChopActionListFromBeginning(int64_t count);
        int64_t ChopActionListFromEnding(int64_t count);
        
        int64_t Clear();
    };
}
