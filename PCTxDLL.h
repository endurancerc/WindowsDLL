#ifndef _PCTXDLL_H_
#define _PCTXDLL_H_
#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include <iostream>

#if defined DLL_EXPORT
#define DECLDIR __declspec(dllexport)
#else
#define DECLDIR __declspec(dllimport)
#endif

extern "C" {
	#include "hidsdi.h"
	#include <setupapi.h>

	bool connected;
	DECLDIR bool Send(int delay1,int delay2,int delay3,int delay4,int delay5,int delay6,int delay7,int delay8,
					  int delay9,int delay10,int delay11,int delay12,int delay13,int delay14,int delay15,int delay16,
					  int delay17,int delay18,int delay19,int delay20,int delay21,int delay22,int delay23,int delay24,
					  int delay25);
	DECLDIR bool Connect(void);

	HANDLE								DeviceHandle;
	HIDP_CAPS							Capabilities;
	BOOL								result;

	CHAR								OutputReport[26]; //buffer out to pctx or servo controller

	DWORD								BytesWritten;
	DWORD								BytesRead;

}

#endif