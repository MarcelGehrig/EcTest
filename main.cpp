#include <string>
#include <iostream>
#include <sstream>
#include <signal.h>
#include <thread>

#include <EtherCATMain.hpp>
//-f eni_1MAXON.xml -i8254x 1 1 -perf

using namespace ethercat;


bool manualMode = false;

bool threadFinishd = false;
int32_t encoder;
EC_T_BYTE* pbyPDIn;
EC_T_BYTE* pbyPDOut;
EtherCATMain* etherCATStack;


void setOutputControlWord( uint16_t word );

static void SignalHandler( int nSignal )
{
	setOutputControlWord(0x0);
	sleep(0.1);
    etherCATStack->stop();
	sleep(2);
	if ( !threadFinishd ) {
		std::cout << "std::terminate()" << std::endl;
		std::terminate();
	}
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

	
	//timekeeping stuff
	typedef std::chrono::steady_clock clock;	
	
	
	while ( !pbyPDIn ) sleep (1);
	while ( EC_GET_FRM_WORD( pbyPDIn + 0 )==0 ) sleep(1);	//wait for valid data
	
	if ( !manualMode ) {
		std::cout << "Status1:         0x" << std::hex << getStatus() << std::endl;
		setOutputControlWord(0x80);					//reset fault
		sleep(1.0);
		std::cout << "Status2:         0x" << std::hex << getStatus() << std::endl;
		sleep(0.1);
		setOutputControlWord(0x0);
		sleep(1.0);
		std::cout << "Status3:         0x" << std::hex << getStatus() << std::endl;
		sleep(0.1);
		
		setModeOfeOperation(1);
		setOutputControlWord(0x6);					//shutdown command
		while ( getStatus()!=0x231 ) sleep(0.1);	//wait for "ready to switch on"
		setProfileAcceleration(50000);
		setProfileDeceleration(50000);
		setProfileVelocity(50000);
// 		setTargetPosition(10000);
		
		setOutputControlWord(0x7);					//switch ON commad
		std::cout << "switch ON commad sent" << std::endl;
		while ( getStatus()!=0x233 ) sleep(0.1);	//wait for "switched on"
// 		setOutputControlWord(0x3f);					//enable operation commad
		
		int loopCounter = 0;
		while ( etherCATStack->isRunning() ) {
			std::cout << "Status:         0x" << std::hex << getStatus() << std::endl;
			std::cout << "ModeOfOp:         " << getModeOfOp() << std::endl;
			std::cout << "PosDemadValue:    " << getPosDemadValue() << std::endl;
			std::cout << "PosActValue:      " << getPosActValue() << std::endl;
			std::cout << std::endl;

			if ( loopCounter%4 == 1 ) {
				std::cout << std::endl << "setPosition to 5000" << std::endl << std::endl;
			std::cout << "Status1:                             0x" << std::hex << getStatus() << std::endl;
				if (loopCounter != 1) while ( getStatus() != 0x0637 ) sleep(0.01);
			std::cout << "Status2: getStatus() != 0x0637       0x" << std::hex << getStatus() << std::endl;
				setTargetPosition(5000);		//1.) send new data
			std::cout << "Status3: setTargetPosition(5000)     0x" << std::hex << getStatus() << std::endl;
				setOutputControlWord(0x3f);		//1.) new set point, set immediately
			std::cout << "Status4: setOutputControlWord(0x3f)  0x" << std::hex << getStatus() << std::endl;
				while ( getStatus() != 0x1637 ) sleep(0.01);	//2.) waits till drive set-point acknowledge
			std::cout << "Status5: getStatus() != 0x1637 0x" << std::hex << getStatus() << std::endl;
				setOutputControlWord(0x2f);		//3.) start motion by reset "new set point"
			std::cout << "Status6: setOutputControlWord(0x2f)  0x" << std::hex << getStatus() << std::endl;
			}

			if ( loopCounter%4 == 3 ) {
				std::cout << std::endl << "setPosition to -5000" << std::endl << std::endl;
				while ( getStatus() != 0x0637 ) sleep(0.01);
// 				std::this_thread::sleep_for(std::chrono::milliseconds(4000));
				setTargetPosition(-5000);		//1.) send new data
				setOutputControlWord(0x3f);		//1.) new set point, set immediately
				
				auto start = clock::now();
// 				while ( getStatus() != 0x1637 ) sleep(0.01);	//2.) waits till drive set-point acknowledge
				while ( getStatus() != 0x1637 ) std::this_thread::sleep_for(std::chrono::nanoseconds(1));	//2.) waits till drive set-point acknowledge
				auto stop = clock::now();
// 				std::chrono::duration<double, std::nano> durationCasted = stop - start;
				std::chrono::duration<double, std::milli> durationCasted = stop - start;
				std::cout << "Duration: 'setOutputControlWord(0x3f);	'" << durationCasted.count() << " millisec" << std::endl;
				
				setOutputControlWord(0x2f);		//3.) start motion by reset "new set point"
			}
			
			sleep(1);
			loopCounter++;
		}
	}
	else {		//manual mode
		
		
	}
	
	
	

	etherCATStack->join();
	threadFinishd = true;
	
	return 0;
}
