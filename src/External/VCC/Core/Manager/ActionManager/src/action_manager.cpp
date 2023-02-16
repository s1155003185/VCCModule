#include "action_manager.hpp"

#include <math.h>

#include "i_action.hpp"

namespace vcc
{
    int64_t ActionManager::Redo(std::shared_ptr<IAction> action)
    {
        // 1. Remove the action after index
        // 2. Append action
        // 3. Do Action
        // 4. Current Index + 1
        this->ChopActionListFromIndex(this->_CurrentActionIndex + 1);
        this->_Actions.push_back(action);
        action->Redo();
        this->_CurrentActionIndex = this->_Actions.size() - 1;

        return this->ChopActionListWithSize(this->_MaxActionListSize);
    }

    int64_t ActionManager::Redo()
    {
        if (this->_CurrentActionIndex < static_cast<int64_t>(this->_Actions.size()) - 1) {
            this->_CurrentActionIndex++;
            this->_Actions.at(this->_CurrentActionIndex)->Redo();
        }
        return this->_CurrentActionIndex;
    }

    int64_t ActionManager::Redo(int64_t noOfStep)
    {
        for (int64_t i = 0; i < noOfStep; i++)
            this->Redo();
        return this->_CurrentActionIndex;
    }

    int64_t ActionManager::RedoToActionIndex(int64_t actionIndex)
    {
        if (actionIndex <= this->_CurrentActionIndex)
            return this->_CurrentActionIndex;

        actionIndex = min(actionIndex, static_cast<int64_t>(this->_Actions.size() - 1));
        while (actionIndex > this->_CurrentActionIndex && this->_CurrentActionIndex < static_cast<int64_t>(this->_Actions.size()))
            this->Redo();
        return this->_CurrentActionIndex;
    }

    int64_t ActionManager::Undo()
    {
        if (this->_CurrentActionIndex > -1) {
            this->_Actions[this->_CurrentActionIndex]->Undo();
            this->_CurrentActionIndex--;
        }
        return this->_CurrentActionIndex;
    }

    int64_t ActionManager::Undo(int64_t noOfStep)
    {
        for (int64_t i = 0; i < noOfStep; i++)
            this->Undo();
        return this->_CurrentActionIndex;
    }

    int64_t ActionManager::UndoToActionIndex(int64_t actionIndex)
    {
        // undo all
        if (actionIndex < 0) {
            while (this->_CurrentActionIndex >= 0)
                this->Undo();
        } else {
            actionIndex = min(actionIndex, static_cast<int64_t>(this->_Actions.size()) - 1);
            while (actionIndex < this->_CurrentActionIndex && this->_CurrentActionIndex >= 0 )
                this->Undo();
        }
        return this->_CurrentActionIndex;
    }

    int64_t ActionManager::ChopActionListWithSize(int64_t size)
    {
        if (size < 0)
            return this->_CurrentActionIndex;
        else if (size == 0)
            return this->Clear();

        while (static_cast<int64_t>(this->_Actions.size()) > size) {
            this->_Actions.erase(this->_Actions.begin());
            this->_CurrentActionIndex--;
        }
        return this->_CurrentActionIndex;
    }

    int64_t ActionManager::ChopActionListFromIndex(int64_t index)
    {
        if (index <= 0)
            return this->Clear();
        else if (index > static_cast<int64_t>(this->_Actions.size()) - 1)
            return this->_CurrentActionIndex;
        
        int64_t size = static_cast<int64_t>(this->_Actions.size());
        for (int64_t i = 0; i < size - index; i++) {
            this->_Actions.pop_back();
        }
        this->_CurrentActionIndex = min(this->_CurrentActionIndex, index - 1);
        return this->_CurrentActionIndex;
    }

    int64_t ActionManager::ChopActionListFromBeginning(int64_t count)
    {
        return this->ChopActionListWithSize(this->_Actions.size() - count);
    }

    int64_t ActionManager::ChopActionListFromEnding(int64_t count)
    {
        return this->ChopActionListFromIndex(this->_Actions.size() - count);
    }

    int64_t ActionManager::Clear()
    {
        this->_Actions.clear();
        this->_CurrentActionIndex = -1;
        return this->_CurrentActionIndex;
    }
}
