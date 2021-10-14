#include "TestChild1.h"

TestChild1::TestChild1(int i) : TestParent(i)
{
	message = "Child avec id " + std::to_string(i) + " :)";
	TestParent::PrintMess();
}

void TestChild1::PrintMess()
{
	TestParent::PrintMess();
	std::cout << "Print ChildTest1 avec child message : " + message + " - fin message \n";
}
