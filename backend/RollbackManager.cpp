#include "RollbackManager.h"
#include <iostream>

void RollbackManager::recordAction(function<void()> undoAction) {
    actions.push_back(undoAction);
}

void RollbackManager::rollback(int k) {
    if (actions.empty()) {
        cout << "Nothing to rollback\n";
        return;
    }

    for (int i = 0; i < k && !actions.empty(); i++) {
        auto lastAction = actions.back();
        lastAction(); // undo
        actions.pop_back();
    }
}
