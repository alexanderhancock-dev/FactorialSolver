#include <iostream>
#include <string>
#include <vector>

class Factorial
{
public:
	unsigned int deg;
	Factorial(unsigned int degree)
	{
		deg = degree;
	}
	unsigned long long int Calculate(int offset = 0) const
	{
		unsigned long long int res = 1;
		for (int i = offset + 1; i <= deg; i++)
		{
			res *= i;
		}
		return res;
	};
	inline unsigned long long int operator-(Factorial const& rhs)
	{
		return Calculate(rhs.deg);
	}
};

static void PrintPrev(std::vector<std::string>& prevCalcs)
{
	for (auto iter = prevCalcs.begin(); iter != prevCalcs.end(); iter++)
	{
		std::cout << *iter;
	}
}

int main()
{
	std::string restart;
	std::vector<std::string> prevCalcs;

	do
	{
		// Get the number of values in the set
		std::string setNum;
		do
		{
			std::cout << "\033c";
			PrintPrev(prevCalcs);
			std::cout << "Number of values in set: ";
			std::cin >> setNum;
		} while (strspn(setNum.c_str(), "0123456789") != setNum.size());

		// Get the number of unique values to pick
		std::string pickedNum;
		do
		{
			do
			{
				std::cout << "\033c";
				PrintPrev(prevCalcs);
				std::cout << "Number of values in set: " << setNum << '\n';
				std::cout << setNum << " pick ";
				std::cin >> pickedNum;
			} while (strspn(pickedNum.c_str(), "0123456789") != pickedNum.size());
		} while (std::stoi(pickedNum) > std::stoi(setNum));

		// Get whether permutation or combination
		std::string factorialType;
		do
		{
			std::cout << "\033c";
			PrintPrev(prevCalcs);
			std::cout << "Number of values in set: " << setNum << '\n' << setNum << " pick " << pickedNum << '\n';
			std::cout << "Permutation or Combination? (P/C) ";
			std::cin >> factorialType;
		} while (!(strspn(factorialType.c_str(), "pPcC") == factorialType.size() && factorialType.size() == 1));

		Factorial set(std::stoi(setNum));
		Factorial chosen(std::stoi(setNum) - std::stoi(pickedNum));
		unsigned long long int result = 0;
		if (strspn(factorialType.c_str(), "pP") == factorialType.size())
		{
			// Permutation
			result = set - chosen;
		}
		else
		{
			// Combination
			result = set - chosen;
			result /= Factorial(std::stoi(pickedNum)).Calculate();
		}

		std::cout << "Result: " << result << '\n';


		std::cout << "Go again? (Q to quit, R to restart) ";
		std::cin >> restart;

		if (strspn(factorialType.c_str(), "pP") == factorialType.size())
		{
			std::string calcStr = setNum + " permute " + pickedNum + " equals " + std::to_string(result) + '\n';
			prevCalcs.push_back(calcStr);
		}
		else
		{
			std::string calcStr = setNum + " choose " + pickedNum + " equals " + std::to_string(result) + '\n';
			prevCalcs.push_back(calcStr);
		}

	} while (strspn(restart.c_str(), "Qq") == 0);

	return 0;
}
