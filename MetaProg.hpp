#pragma once

#include <iostream>

/*

Notes from : Templates and Metaprogramming

www.youtube.com/watch?v=dyHWVQE3Oo4

*/


//---------------------------------------//
//    CRTP                             //
// Curiously Recurent Template Pattern //
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

	struct NullStruct : public Base<NullStruct>
	{
		void anotherFunction() {}		
	};

	struct MyStruct : public Base<MyStruct>
	{
		void anotherFunction()
		{
			std::cout << "Struct 1" << std::endl;
		}
	};

	struct MyStruct2 : public Base<MyStruct2>
	{
		void anotherFunction()
		{
			std::cout << "Struct 2" << std::endl;
		}
	};
};


namespace CRTP2
{
	// Mixins

	// here we have a class who list every instances of inherited classes
	// here constness have been stripped from the example

	template <typename T>
	struct CtorLister
	{
		CtorLister()
		{
			next_ = Head();
			Head() = static_cast<T *>(this);
		}

		T *Next(void)
		{
			return next_;
		}

		static T *& Head()
		{
			static T *p = NULL;
			return p;
		}
	private:
		T *next_;
	};
	
	struct MyStruct : public CtorLister<MyStruct>
	{
		MyStruct(unsigned int v)
			: CtorLister<MyStruct>(),
			val_(v)
		{}
		unsigned int &getVal()
		{
			return val_;
		}
	private:
		unsigned int val_;
	};	

};

namespace Meta
{
	template <int i>
	struct IsEven
	{
		static const bool value = i  % 2 == 0; // static const bevause only static const integral data members
		// can be initialized within a class
	};

	template <unsigned int i>
	struct Factorial
	{
		enum { result = i * Factorial<i - 1>::result };
	};

	template <>
	struct Factorial<1>
	{
		enum { result = 1 };		
	};

};

namespace ExpressionTemplates
{
// stop at 29:59
};

namespace MetaProg
{
	void Test()
	{
		{
			std::cout <<"CRTP test -> static polymorphism " << std::endl;
			CRTP1::MyStruct test;
			CRTP1::MyStruct2 test2;
			test.anotherFunction();
			test2.anotherFunction();
		}
		
		{
			std::cout  << std::endl <<"CRTP test ->  Mixin" << std::endl;

			CRTP2::MyStruct s1(1), s2(2), s3(3), s4(4);

			for (CRTP2::MyStruct *i = CRTP2::MyStruct::Head(); i != NULL; i = i->Next())
				std::cout << i->getVal() << std::endl;
		}

		{
			std::cout  << std::endl <<"CRTP test ->  Metaprog" << std::endl;

			std::cout << "10 is even " << Meta::IsEven<10>::value << std::endl;
			std::cout << "11 is even " << Meta::IsEven<11>::value << std::endl;
			std::cout << "12 is even " << Meta::IsEven<12>::value << std::endl;

			std::cout << "Factorial of 16 is " << Meta::Factorial<12>::result << std::endl;

		}

	}

};