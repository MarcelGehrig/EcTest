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
EC_T_BYTE* pbyPDOut;
EtherCATMain* etherCATStack;


static void SignalHandler( int nSignal )
{
    etherCATStack->stop();
}


// get functions
// /////////////
uint16_t getStatus() 
{
// 	std::stringstream stream;
// 	stream << std::hex << EC_GET_FRM_WORD( pbyPDIn + 0 );
// 	return stream.str();
	return EC_GET_FRM_WORD( pbyPDIn + 0 );
}

std::string getModeOfOp() 
{
	std::stringstream stream;
	stream << std::hex << (int)*(pbyPDIn + 2);
	return stream.str();
}

std::string getPosActValue() 
{
	return std::to_string( (int)EC_GET_FRM_DWORD( pbyPDIn + 4 ) );
}

std::string getPosDemadValue() 
{
	return std::to_string( (int)EC_GET_FRM_DWORD( pbyPDIn + 8 ) );
}


// set functions
// /////////////
void setOutputControlWord( uint16_t word )
{
// 	std::cout << "setOutputControlWord( 0x" << std::hex << (uint16_t)word << " )" << std::endl;
	EC_SETWORD(pbyPDOut+0, word);
}

void setModeOfeOperation( uint8_t mode )
{
	*(pbyPDOut + 2) = mode;
}

void setTargetPosition ( int32_t targetPos )
{
	EC_SETDWORD(pbyPDOut+4, targetPos);
}

void setProfileVelocity( uint32_t profileVelocity )
{
	EC_SETDWORD(pbyPDOut+8, profileVelocity);
}

void setProfileAcceleration( uint32_t profileAcceleration )
{
	EC_SETDWORD(pbyPDOut+12, profileAcceleration);
}

void setProfileDeceleration( uint32_t profileDeceleration )
{
	EC_SETDWORD(pbyPDOut+16, profileDeceleration);
}





void callbackFct(EC_T_BYTE* pbyPDInPtr, EC_T_BYTE* pbyPDOutPtr)
{
	pbyPDIn = pbyPDInPtr;
	pbyPDOut = pbyPDOutPtr;
	// 	encoder = EC_GET_FRM_DWORD( pbyPDIn + 0 );
	
	// lese position von pointer und schreibe in globale variable von main
}



int main(int argc, char **argv) {

	EtherCATMain eCATStack(argc, argv, &callbackFct);
	etherCATStack = &eCATStack;

	
	while ( !pbyPDIn ) sleep (1);
	while ( EC_GET_FRM_WORD( pbyPDIn + 0 )==0 ) sleep(1);	//wait for valid data
	
	
	std::cout << "Status1:         0x" << std::hex << getStatus() << std::endl;
	setOutputControlWord(0xf);					//reset fault
	setOutputControlWord(0x80);					//reset fault
	sleep(0.1);
	setOutputControlWord(0x0);
	sleep(0.1);
	
	setModeOfeOperation(1);
	setOutputControlWord(0x6);					//shutdown command
	while ( getStatus()!=0x231 ) sleep(0.1);	//wait for "ready to switch on"
	setProfileAcceleration(10000);
	setProfileDeceleration(10000);
	setProfileVelocity(10000);
	setTargetPosition(10000);
	
	setOutputControlWord(0x7);					//switch ON commad
	std::cout << "switch ON commad sent" << std::endl;
	while ( getStatus()!=0x233 ) sleep(0.1);	//wait for "switched on"
	setOutputControlWord(0x3f);					//enable operation commad
	
	while ( etherCATStack->isRunning() ) {
		std::cout << "Status:         0x" << std::hex << getStatus() << std::endl;
		std::cout << "ModeOfOp:         " << getModeOfOp() << std::endl;
		std::cout << "PosDemadValue:    " << getPosDemadValue() << std::endl;
		std::cout << "PosActValue:      " << getPosActValue() << std::endl;
		std::cout << std::endl;

		sleep(1);
	}

	etherCATStack->join();

	return 0;
}
