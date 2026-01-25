#ifndef ROLLBACKMANAGER_H
#define ROLLBACKMANAGER_H

#include <vector>
#include <functional>
using namespace std;

class RollbackManager {
private:
    vector<function<void()>> actions;

public:
    void recordAction(function<void()> undoAction);
    void rollback(int k = 1);
};

#endif
