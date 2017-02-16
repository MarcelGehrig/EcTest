#include <string>
#include <iostream>
#include <thread>

#include <DCDemoMain.hpp>
//-f eni_1MAXON.xml -i8254x 1 1 -perf
void task1(std::string msg1, std::string msg2)
{
    std::cout << "task1 says: " << msg1 << msg2 << std::endl;
}

int main(int argc, char **argv) {
// 	std::cout << argv[0] << std::endl;
// 	std::cout << argv[1] << std::endl;
// 	std::cout << argv[2] << std::endl;
// 	std::cout << argv[3] << std::endl;
// 	std::cout << sayHello("Bob") << std::endl;
	
	
	std::thread t1(mainEtherCAT, argc, argv);
	
	
	std::cout << "hallo" << std::endl;
	t1.join();
	
    return 0;
}
