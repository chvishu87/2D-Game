#ifndef MAINMANAGER__H
#define MAINMANAGER__H

#include "compositeManager.h"
#include "manager.h"
#include "menuManager.h"

class MainManager:public CompositeManager {
public:
	MainManager();
	virtual MODE play();

	CompositeManager* managers[2]; //need to delete the created managers in the destructor.

	virtual ~MainManager() {
		delete managers[0];
		delete managers[1];
	}

private:
	MainManager(const MainManager&);
	MainManager& operator=(const MainManager&);

};

#endif
