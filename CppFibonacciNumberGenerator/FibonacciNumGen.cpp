#include<vector>
#include<iostream>
#include<ctime>
#include<functional>

const unsigned int MAXVALUE = 42;

namespace FibonacciNumberGenerator
{
	// Method A for run-time number generation
	constexpr unsigned long int Fibonacci_RunTime_Recursive(unsigned long int Num) {
		return (!!Num ? (Num > 1 ? Fibonacci_RunTime_Recursive(Num - 2) + Fibonacci_RunTime_Recursive(Num - 1) : 1) : 0);
	}

	// Method B for run-time number generation
	unsigned long int Fibonacci_RunTime_Non_Recursive(unsigned long int Num) {
		
		auto FibonacciLambda = [](unsigned long int Num)->unsigned long int {
			
			unsigned long int 
				CurrNum = 1,
				PrevNum = 0,
				TempNum = 0;

			for (unsigned long int FibNum = 0; FibNum < Num - 1; ++FibNum) {
				TempNum = CurrNum + PrevNum;
				PrevNum = CurrNum;
				CurrNum = TempNum;
			}
			
			return CurrNum;
		};

		return  Num > 1 ? FibonacciLambda(Num) : Num;
	}

	// Method A for compile-time number generation
	template<unsigned long int N>
	struct Fibonacci_CompileTime_Recursive_A { 
		enum { Value = Fibonacci_CompileTime_Recursive_A<N - 2>::Value + Fibonacci_CompileTime_Recursive_A<N - 1>::Value };
	};

	template<>
	struct Fibonacci_CompileTime_Recursive_A<1> {
		enum { Value = 1 };
	};

	template<>
	struct Fibonacci_CompileTime_Recursive_A<0> {
		enum { Value = 0 };
	};

	// Method B for compile-time number generation
	template<unsigned long N>
	struct Fibonacci_CompileTime_Recursive_B: std::integral_constant<unsigned long int, (Fibonacci_CompileTime_Recursive_B<N - 1>{} + Fibonacci_CompileTime_Recursive_B<N - 2>{})> {};
	
	template<> 
	struct Fibonacci_CompileTime_Recursive_B<1>: std::integral_constant<unsigned long  int, 1> {};
	template<> 
	struct Fibonacci_CompileTime_Recursive_B<0>: std::integral_constant<unsigned long int, 0> {};
}

int main() {

	clock_t
		Clk_Begin,
		Clk_End;

	unsigned long int FibonacciNumber = 0;
	double FibGen_ElapsedTime = 0.f;


	// Compile-Time Method A
	{
		Clk_Begin = clock();

		FibonacciNumber = FibonacciNumberGenerator::Fibonacci_CompileTime_Recursive_A<MAXVALUE>::Value;

		Clk_End = clock();
	}

	FibGen_ElapsedTime = (Clk_End - Clk_Begin) / CLOCKS_PER_SEC;
	std::cout << "Compile time recursive fibonacci generator A for number " << MAXVALUE << " is " << FibonacciNumber << "\n Time: " << FibGen_ElapsedTime << " seconds" << "\n";

	// Compile-Time Method B
	{
		Clk_Begin = clock();

		FibonacciNumber = FibonacciNumberGenerator::Fibonacci_CompileTime_Recursive_B<MAXVALUE>();

		Clk_End = clock();
	}

	FibGen_ElapsedTime = (Clk_End - Clk_Begin) / CLOCKS_PER_SEC;
	std::cout << "Compile time recursive fibonacci generator B for number " << MAXVALUE << " is " << FibonacciNumber << "\n Time: " << FibGen_ElapsedTime << " seconds" << "\n";

	// Run-Time Non-Recursive Method
	{
		Clk_Begin = clock();

		FibonacciNumber = FibonacciNumberGenerator::Fibonacci_RunTime_Non_Recursive(MAXVALUE);

		Clk_End = clock();
	}

	FibGen_ElapsedTime = (Clk_End - Clk_Begin) / CLOCKS_PER_SEC;
	std::cout << "Run-time non-recursive fibonacci generator for number " << MAXVALUE << " is " << FibonacciNumber << "\n Time: " << FibGen_ElapsedTime << " seconds" << "\n";

	// Run-Time Recursive Method
	{
		Clk_Begin = clock();

		FibonacciNumber = FibonacciNumberGenerator::Fibonacci_RunTime_Recursive(MAXVALUE);

		Clk_End = clock();
	}

	FibGen_ElapsedTime = (Clk_End - Clk_Begin) / CLOCKS_PER_SEC;
	std::cout << "Run-time recursive fibonacci generator for number " << MAXVALUE << " is " << FibonacciNumber << "\n Time: " << FibGen_ElapsedTime << " seconds" << "\n";

	getchar();
	return 0;
}