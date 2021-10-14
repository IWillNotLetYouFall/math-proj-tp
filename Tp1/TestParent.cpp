#include "TestParent.h"

TestParent::TestParent(int i)
{
	message = "Parent avec id " + std::to_string(i);
}

void TestParent::PrintMess()
{
	std::cout << "Print ParentTest avec message : " + message + " - fin message \n";
}
