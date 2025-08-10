//A simple application demonstrating how to use the PCTxDLL to connect to the PCTx or 25 Servo Controller

#include <stdafx.h>
#include <iostream>
#include <windows.h>

typedef bool (*Connect)();
typedef bool (*Send)(int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int,int);

int main()
{
   Connect _Connect;
   Send _Send;
   int x = 0;
   HINSTANCE hInstLibrary = LoadLibrary("PCTx.dll");

   if (hInstLibrary == NULL) {
	   FreeLibrary(hInstLibrary);
   }

   _Connect = (Connect)GetProcAddress(hInstLibrary, "Connect");
   _Send = (Send)GetProcAddress(hInstLibrary, "Send");

   if ((_Connect == NULL) || (_Send == NULL)) {
      FreeLibrary(hInstLibrary);
   }

   std::cout << "Attempting to connect..." << std::endl;
   if(_Connect()){
		std::cout << "Connected!" << std::endl;
   }
   else {
	   std::cout << "Not Connected!" << std::endl;
   }

   int ch1 = 100;
   int ch2 = 200;

   while(x<10){
	   std::cout << "Attempting to send..." << std::endl;

	   if(_Send(ch1,ch2,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150,150)){
			std::cout << "Sent!" << std::endl;
	   }
	   else {
		   std::cout << "Not Sent!" << std::endl;
	   }

	   _sleep(1000);

	   if(ch1 == 100){
		   ch1 = 200;
		   ch2 = 100;
	   }
	   else {
		   ch1 = 100;
		   ch2 = 200;
	   }

	   x++;
   }

   FreeLibrary(hInstLibrary);

   return(0);
}