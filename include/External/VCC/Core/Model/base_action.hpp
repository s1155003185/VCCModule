#pragma once
#include "i_action.hpp"
#include "class_macro.hpp"

#include "action_type.hpp"
#include "log_service.hpp"

namespace vcc
{
    class BaseAction : public IAction
    {
        THREAD_SAFE
        GET(ActionType, Type, ActionType::NA)

        protected:
            BaseAction() : BaseAction(ActionType::NA) {}
            BaseAction(ActionType type) : IAction() { this->_Type = type; }
            ~BaseAction() {}

            virtual void LogRedo() override
            {
                LogService::LogInfo(this->GetRedoMessage());
            }

            virtual void LogUndo() override
            {
                LogService::LogInfo(this->GetUndoMessage());
            }

            virtual void Redo() override
            {
                this->DoRedo();
                this->LogRedo();
            }

            virtual void Undo() override
            {
                this->DoUndo();
                this->LogUndo();
            }
    };
}
