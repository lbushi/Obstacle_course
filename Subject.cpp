#include "Subject.h"

void Subject::attach_Observer(Observer* ob)
{
	observers.emplace_back(ob);
}

void Subject::notify_Observers()
{
	for (auto ob : observers) {
		ob->on_notify(*this);
	}
}
