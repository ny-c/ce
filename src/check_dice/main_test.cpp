#include <iostream>
#include <sstream>
#include <chrono>
#include "main.h"

using namespace std;
using namespace std::chrono;

Random::RandomGen *rg;
int current_n;
		
inline bool check_dice()
{		
	return rg->nextInt(1, 6+1) == 6;
}

bool check()
{
	for(int i = 0; i < current_n; ++i)
		if(!check_dice()) return false;

	return true;
}

void performMainTest(const CheckdiceParameters& p, Random::RandomGen *r)
{
	rg = r;
	current_n = p.n;

	int count = 0;
	
	for(int i = 0; i < p.iterations; ++i) {

		count += check();
	}
		
	printResult(p, count);
}

void printResult(const CheckdiceParameters& p, int result)
{
	cout << "Number of tests among " << p.iterations << " tests\n"
		 << "where each of the " << p.n << " dices is 6: " << result << endl;
}