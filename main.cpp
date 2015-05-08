#include <iostream>

#include "LibLocator.h"

int main()
{
	LibLocator ll;
	std::cout << "Boost filesystem library is at " << ll.GetLibPath("boost_filesystem") <<std::endl;
	std::cout << "Libc 6 is at " << ll.GetLibPath("c", "6") << std::endl;
	std::cout << "Boost system library is in the directory " << ll.GetLibDir("boost_system") <<std::endl;
	std::cout << "Boost filesystem library is at " << ll.GetPathRelativeToLibDir("..", "boost_filesystem") <<std::endl;
	return 0; 
}
