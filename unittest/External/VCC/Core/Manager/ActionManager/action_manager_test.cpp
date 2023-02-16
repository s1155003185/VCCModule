#include <gtest/gtest.h>

#include <string>

#include "i_action.hpp"
#include "base_action.hpp"
#include "action_manager.hpp"

using namespace vcc;

class ActionManagerTestClass : public BaseAction
{
    private:
        int uuid = 0;
    
    protected:
        virtual void DoRedo() override {}
        virtual void DoUndo() override {}

        virtual wstring GetRedoMessage() override { return L""; }
        virtual wstring GetUndoMessage() override { return L""; }

        virtual void LogRedo() override {}
        virtual void LogUndo() override {}
    public:
        virtual wstring GetMessage() override { return std::to_wstring(uuid); }
 
        ActionManagerTestClass(int uuid) : BaseAction(ActionType::NA)
        {
            this->uuid = uuid;
        }
};

class ActionManagerTest : public testing::Test 
{
    private:
        ActionManager _Manager;

    public:
        ActionManager * GetManager()
        {
            return &this->_Manager;
        }

        shared_ptr<IAction> CreateAction(int index)
        {
            shared_ptr<ActionManagerTestClass> action = make_shared<ActionManagerTestClass>(index);
            return action;
        }

        void ResetWithFiveActions()
        {
            this->_Manager.Clear();
            this->_Manager.Redo(this->CreateAction(0));
            this->_Manager.Redo(this->CreateAction(1));
            this->_Manager.Redo(this->CreateAction(2));
            this->_Manager.Redo(this->CreateAction(3));
            this->_Manager.Redo(this->CreateAction(4));
        }

        void SetUp() override
        {
            this->_Manager.SetMaxActionListSize(10);
        }

        void TearDown() override
        {

        }
};

TEST_F(ActionManagerTest, EmptyTest) 
{
    ActionManager *manager = this->GetManager();
    // Redo
    EXPECT_EQ(manager->Redo(), -1);
    EXPECT_EQ(manager->Redo(1), -1);
    EXPECT_EQ(manager->RedoToActionIndex(2), -1);
    // Undo
    EXPECT_EQ(manager->Undo(), -1);
    EXPECT_EQ(manager->Undo(1), -1);
    EXPECT_EQ(manager->UndoToActionIndex(2), -1);
    // Chop
    EXPECT_EQ(manager->ChopActionListWithSize(1), -1);
    EXPECT_EQ(manager->ChopActionListFromIndex(1), -1);
    EXPECT_EQ(manager->ChopActionListFromBeginning(1), -1);
    EXPECT_EQ(manager->ChopActionListFromEnding(1), -1);
}

TEST_F(ActionManagerTest, NegativeTest) 
{
    ActionManager *manager = this->GetManager();
    this->ResetWithFiveActions();
    // Redo
    EXPECT_EQ(manager->Redo(-1), 4);
    EXPECT_EQ(manager->RedoToActionIndex(-1), 4);
    // Undo
    EXPECT_EQ(manager->Undo(-1), 4);
    EXPECT_EQ(manager->UndoToActionIndex(-1), -1);
    // Chop
    this->ResetWithFiveActions();
    EXPECT_EQ(manager->ChopActionListWithSize(-1), 4);
    this->ResetWithFiveActions();
    EXPECT_EQ(manager->ChopActionListFromIndex(-1), -1);
    this->ResetWithFiveActions();
    EXPECT_EQ(manager->ChopActionListFromBeginning(-1), 4);
    this->ResetWithFiveActions();
    EXPECT_EQ(manager->ChopActionListFromEnding(-1), 4);
}

TEST_F(ActionManagerTest, ExceedTest) 
{
    ActionManager *manager = this->GetManager();
    // Redo
    this->ResetWithFiveActions();
    EXPECT_EQ(manager->Redo(100), 4);
    this->ResetWithFiveActions();
    EXPECT_EQ(manager->RedoToActionIndex(100), 4);
    // Undo
    this->ResetWithFiveActions();
    EXPECT_EQ(manager->Undo(100), -1);
    this->ResetWithFiveActions();
    EXPECT_EQ(manager->UndoToActionIndex(100), 4);
    // Chop
    this->ResetWithFiveActions();
    EXPECT_EQ(manager->ChopActionListWithSize(100), 4);
    this->ResetWithFiveActions();
    EXPECT_EQ(manager->ChopActionListFromIndex(100), 4);
    this->ResetWithFiveActions();
    EXPECT_EQ(manager->ChopActionListFromBeginning(100), 4);
    this->ResetWithFiveActions();
    EXPECT_EQ(manager->ChopActionListFromEnding(100), -1);
}

TEST_F(ActionManagerTest, RedoUndoTest) 
{
    ActionManager *manager = this->GetManager();
    // Add
    this->ResetWithFiveActions();
    EXPECT_EQ(manager->Redo(this->CreateAction(10)), 5);
    EXPECT_EQ(manager->GetActions()->size(), 6);
    EXPECT_EQ(manager->GetActions()->at(0)->GetMessage(), L"0");
    EXPECT_EQ(manager->GetActions()->at(1)->GetMessage(), L"1");
    EXPECT_EQ(manager->GetActions()->at(2)->GetMessage(), L"2");
    EXPECT_EQ(manager->GetActions()->at(3)->GetMessage(), L"3");
    EXPECT_EQ(manager->GetActions()->at(4)->GetMessage(), L"4");
    EXPECT_EQ(manager->GetActions()->at(5)->GetMessage(), L"10");

    // Redo Undo
    EXPECT_EQ(manager->Undo(), 4);
    EXPECT_EQ(manager->Undo(2), 2);
    EXPECT_EQ(manager->Undo(), 1);
    EXPECT_EQ(manager->Redo(), 2);
    EXPECT_EQ(manager->Redo(3), 5);
    EXPECT_EQ(manager->GetActions()->size(), 6);

    // Redo Chop
    this->ResetWithFiveActions();
    EXPECT_EQ(manager->Undo(2), 2);
    EXPECT_EQ(manager->Redo(this->CreateAction(20)), 3);
    EXPECT_EQ(manager->GetActions()->size(), 4);
    EXPECT_EQ(manager->GetActions()->at(0)->GetMessage(), L"0");
    EXPECT_EQ(manager->GetActions()->at(1)->GetMessage(), L"1");
    EXPECT_EQ(manager->GetActions()->at(2)->GetMessage(), L"2");
    EXPECT_EQ(manager->GetActions()->at(3)->GetMessage(), L"20");
}

TEST_F(ActionManagerTest, ChopTest) 
{
    ActionManager *manager = this->GetManager();
    // ChopWithSize
    this->ResetWithFiveActions();
    EXPECT_EQ(manager->ChopActionListWithSize(2), 1);
    EXPECT_EQ(manager->GetActions()->size(), 2);
    EXPECT_EQ(manager->GetActions()->at(0)->GetMessage(), L"3");
    EXPECT_EQ(manager->GetActions()->at(1)->GetMessage(), L"4");

    this->ResetWithFiveActions();
    EXPECT_EQ(manager->ChopActionListWithSize(4), 3);
    EXPECT_EQ(manager->GetActions()->size(), 4);
    EXPECT_EQ(manager->GetActions()->at(0)->GetMessage(), L"1");
    EXPECT_EQ(manager->GetActions()->at(1)->GetMessage(), L"2");
    EXPECT_EQ(manager->GetActions()->at(2)->GetMessage(), L"3");
    EXPECT_EQ(manager->GetActions()->at(3)->GetMessage(), L"4");

    // ChopActionListFromIndex
    this->ResetWithFiveActions();
    EXPECT_EQ(manager->ChopActionListFromIndex(2), 1);
    EXPECT_EQ(manager->GetActions()->size(), 2);
    EXPECT_EQ(manager->GetActions()->at(0)->GetMessage(), L"0");
    EXPECT_EQ(manager->GetActions()->at(1)->GetMessage(), L"1");
    
    this->ResetWithFiveActions();
    EXPECT_EQ(manager->ChopActionListFromIndex(4), 3);
    EXPECT_EQ(manager->GetActions()->size(), 4);
    EXPECT_EQ(manager->GetActions()->at(0)->GetMessage(), L"0");
    EXPECT_EQ(manager->GetActions()->at(1)->GetMessage(), L"1");
    EXPECT_EQ(manager->GetActions()->at(2)->GetMessage(), L"2");
    EXPECT_EQ(manager->GetActions()->at(3)->GetMessage(), L"3");

    // ChopActionListFromBeginning
    this->ResetWithFiveActions();
    EXPECT_EQ(manager->ChopActionListFromBeginning(2), 2);
    EXPECT_EQ(manager->GetActions()->size(), 3);
    EXPECT_EQ(manager->GetActions()->at(0)->GetMessage(), L"2");
    EXPECT_EQ(manager->GetActions()->at(1)->GetMessage(), L"3");
    EXPECT_EQ(manager->GetActions()->at(2)->GetMessage(), L"4");

    this->ResetWithFiveActions();
    EXPECT_EQ(manager->ChopActionListFromBeginning(4), 0);
    EXPECT_EQ(manager->GetActions()->size(), 1);
    EXPECT_EQ(manager->GetActions()->at(0)->GetMessage(), L"4");
    
    // ChopActionListFromEnding
    this->ResetWithFiveActions();
    EXPECT_EQ(manager->ChopActionListFromEnding(2), 2);
    EXPECT_EQ(manager->GetActions()->size(), 3);
    EXPECT_EQ(manager->GetActions()->at(0)->GetMessage(), L"0");
    EXPECT_EQ(manager->GetActions()->at(1)->GetMessage(), L"1");
    EXPECT_EQ(manager->GetActions()->at(2)->GetMessage(), L"2");

    this->ResetWithFiveActions();
    EXPECT_EQ(manager->ChopActionListFromEnding(4), 0);
    EXPECT_EQ(manager->GetActions()->size(), 1);
    EXPECT_EQ(manager->GetActions()->at(0)->GetMessage(), L"0");
}