#pragma once

#include <iostream>

/*

Notes from : Templates and Metaprogramming

www.youtube.com/watch?v=dyHWVQE3Oo4

*/


//---------------------------------------//
//    CRTP                             //
// Curiously Recuren Template Pattern //
//------------------------------------//



namespace CRTP1
{

	// static polymorphism
	// more optimized than virtual

	template <typename Derived>
	struct Base
	{
		void interface(void)
		{
			((Derived *)this)->anotherFunction();
		}
	};

	struct MyStruct : public Base<MyStruct>
	{
		void anotherFunction()
		{
			std::cout << "lolilol" << std::endl;
		}
	};	
};



namespace MetaProg
{

void Test()
{
   	CRTP1::MyStruct test;

	test.anotherFunction();
}

};