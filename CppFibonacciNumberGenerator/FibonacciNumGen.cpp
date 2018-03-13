#include<vector>
#include<iostream>
#include<ctime>

const unsigned int MAXVALUE = 42;

namespace FibonacciNumberGenerator
{
	// Method for run-time number evaluation
	constexpr unsigned int Fibonacci_RunTime(unsigned int Num) {
		return (!!Num ? (Num > 1 ? Fibonacci_RunTime(Num - 2) + Fibonacci_RunTime(Num - 1) : 1) : 0);
	}

	// Method for compile-time number evaluation
	template<unsigned long N>
	class Fibonacci_CompileTime {
	public:
		enum {
			Value = Fibonacci_CompileTime<N - 2>::Value + Fibonacci_CompileTime<N - 1>::Value
		};
	};

	template<>
	class Fibonacci_CompileTime<1> {
	public:
		enum {
			Value = 1
		};
	};

	template<>
	class Fibonacci_CompileTime<0> {
	public:
		enum {
			Value = 0
		};
	};
}

int main() {

	clock_t
		Clk_Begin,
		Clk_End;

	unsigned int FibonacciNumber = 0;
	double FibGen_ElapsedTime = 0.f;


	// Compile-Time Method
	{
		Clk_Begin = clock();

		FibonacciNumber = FibonacciNumberGenerator::Fibonacci_CompileTime<MAXVALUE>::Value;

		Clk_End = clock();
	}

	FibGen_ElapsedTime = (Clk_End - Clk_Begin) / CLOCKS_PER_SEC;
	std::cout << "Compile time fibonacci Generator for number " << MAXVALUE << " is " << FibonacciNumber << "\n Time: " << FibGen_ElapsedTime << " seconds" << "\n";

	// Run-Time Method
	{
		Clk_Begin = clock();

		FibonacciNumber = FibonacciNumberGenerator::Fibonacci_RunTime(MAXVALUE);

		Clk_End = clock();
	}

	FibGen_ElapsedTime = (Clk_End - Clk_Begin) / CLOCKS_PER_SEC;
	std::cout << "Run-time fibonacci Generator for number " << MAXVALUE << " is " << FibonacciNumber << "\n Time: " << FibGen_ElapsedTime << " seconds" << "\n";

	getchar();
	return 0;
}