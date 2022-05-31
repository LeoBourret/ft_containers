#include <utility>      // std::pair, std::get
#include <iostream>     // std::cout
#include "pair.hpp"
#include <map>

int main ()
{

	std::map<int, int> mp;

	mp[0] = 2;
	mp[1] = 12;
	mp[2] = 22;
	mp[3] = 32;
	mp[4] = 42;

	std::map<int, int>::iterator ite = mp.end();

	std::cout << ite->second << std::endl;
	ite--;
	std::cout << ite->second << std::endl;
	ite++;
	std::cout << ite->second << std::endl;
	ite++;
	std::cout << ite->second << std::endl;


	return 0;
}
