#include <string>
#include <iostream>
#include <sstream>
#include <signal.h>
#include <thread>

#include <EtherCATMain.hpp>
//-f eni_1MAXON.xml -i8254x 1 1 -perf

using namespace ethercat;

int32_t encoder;
EC_T_BYTE* pbyPDIn;


std::string getStatus() 
{
	std::stringstream stream;
	stream << std::hex << EC_GET_FRM_WORD( pbyPDIn + 0 );
	return stream.str();
}

std::string getModeOfOp() 
{
	std::stringstream stream;
	stream << std::hex << (int)*(pbyPDIn + 2);
	return stream.str();
}

std::string getPosActValue() 
{
	return std::to_string( EC_GET_FRM_DWORD( pbyPDIn + 4 ) );
}

std::string getPosDemadValue() 
{
	return std::to_string( EC_GET_FRM_DWORD( pbyPDIn + 8 ) );
}






void callbackFct(EC_T_BYTE* pbyPDInPtr, EC_T_BYTE* pbyPDOut)
{
	pbyPDIn = pbyPDInPtr;
	// 	encoder = EC_GET_FRM_DWORD( pbyPDIn + 0 );
	
	// lese position von pointer und schreibe in globale variable von main
}



int main(int argc, char **argv) {

	EtherCATMain etherCATStack(argc, argv, &callbackFct);


	while ( !pbyPDIn ) sleep (1);
	while ( EC_GET_FRM_WORD( pbyPDIn + 0 )==0 ) sleep(1);
	
	while ( etherCATStack.isRunning() ) {
		std::cout << "Status:        " << getStatus() << std::endl;
		std::cout << "ModeOfOp:      " << getModeOfOp() << std::endl;
		std::cout << "PosDemadValue: " << getPosDemadValue() << std::endl;
		std::cout << "PosActValue:   " << getPosActValue() << std::endl;

		sleep(1);
	}

	etherCATStack.join();

	return 0;
}
