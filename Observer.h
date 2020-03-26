#pragma once
class Subject;
class Observer {
public:
	virtual void on_notify(Subject& whonotified) = 0;
	virtual ~Observer() {}
};
