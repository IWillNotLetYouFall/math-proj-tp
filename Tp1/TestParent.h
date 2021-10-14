#pragma once
#include <stdlib.h>
#include <string>
#include <iostream>

class TestParent
{
protected:
	std::string message;
public:
	TestParent(int i);
	virtual void PrintMess();
};

