#pragma once
#include "Observer.h"
#include <vector>
class Subject {
private:
	std::vector<Observer*> observers;
public:
	void attach_Observer(Observer* ob);
	void notify_Observers();
	virtual ~Subject() {}
};