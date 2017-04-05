#include "test.h"

Test::Test()
{

}

void Test::testDirectory()
{
	using namespace EXTERN;

	Timer timer = Timer();

	if(Directory::fileExists("./Neverdo/file.txt"))
	{
		std::cout << "pass" << std::endl;
	}
	if(Directory::fileExists("./source/main.cpp"))
	{
		std::cout << "pass" << std::endl;
	}

	std::cout << timer.stop() << std::endl;
}