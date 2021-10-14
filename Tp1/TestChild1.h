#pragma once
#include "TestParent.h"

class TestChild1 : TestParent
{
public:
	TestChild1(int i);
	void PrintMess() override;
};

