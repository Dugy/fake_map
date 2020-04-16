#include "fake_map.hpp"
#include <iostream>
#include <string>

int main() {
	FakeMap<std::string, int> a = {};
	a["thirteen"] = 13;
	a["fourteen"] = 14;
	if (a.count("sixteen") == 0)
		a["seventeen"] = 16;
	a.at("seventeen") = 17;
	for (auto it : a)
		std::cout << it.first << " " << it.second << std::endl;
	a.erase("sixteen");
	a.erase("seventeen");
	std::cout << std::endl;
	for (auto it : a)
		std::cout << it.first << " " << it.second << std::endl;
}
