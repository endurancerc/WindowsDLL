#define DLL_EXPORT
#include "PCTxDLL.h"

using namespace std;

const unsigned int VendorID =	0x0925;
const unsigned int ProductID =	0x1299;

extern "C"
{
	DECLDIR bool Connect(void){
		connected = false;

		GUID								HidGuid;
		HANDLE								hDevInfo;
		SP_DEVICE_INTERFACE_DATA			devInfoData;
		int									MemberIndex = 0;
		bool								MyDeviceDetected = FALSE;
		bool								LastDevice = FALSE;
		ULONG								Length;
		PSP_DEVICE_INTERFACE_DETAIL_DATA	detailData;
		ULONG								Required;
		HIDD_ATTRIBUTES						Attributes;
		PHIDP_PREPARSED_DATA				PreparsedData;

		// Get the GUID for all system HIDs
		HidD_GetHidGuid(&HidGuid);

		// Get handle to device information set for all installed devices
		hDevInfo = SetupDiGetClassDevs(&HidGuid, NULL, NULL, DIGCF_PRESENT | DIGCF_INTERFACEDEVICE);

		// Set struct size before calling SetupDiEnumDeviceInterfaces
		devInfoData.cbSize = sizeof(devInfoData);

		do {
			MyDeviceDetected=FALSE;

			// Get handle to a SP_DEVICE_INTERFACE_DATA structure for a detected device
			result = SetupDiEnumDeviceInterfaces(hDevInfo, 0, &HidGuid, MemberIndex, &devInfoData);

			if (result) {
				result = SetupDiGetDeviceInterfaceDetail(hDevInfo, &devInfoData, NULL, 0, &Length, NULL);

				//Allocate memory for the hDevInfo structure, using the returned Length.
				detailData = (PSP_DEVICE_INTERFACE_DETAIL_DATA) malloc(Length);

				//Set cbSize in the detailData structure.
				detailData->cbSize = sizeof(SP_DEVICE_INTERFACE_DETAIL_DATA);

				//Call the function again, this time passing it the returned buffer size.
				result = SetupDiGetDeviceInterfaceDetail(hDevInfo, &devInfoData, detailData, Length, &Required, NULL);

				DeviceHandle = CreateFile 
					(detailData->DevicePath, 
					GENERIC_READ | GENERIC_WRITE, 
					FILE_SHARE_READ | FILE_SHARE_WRITE, 
					(LPSECURITY_ATTRIBUTES) NULL,
					OPEN_EXISTING, 
					0, 
					NULL);
				
				Attributes.Size = sizeof(Attributes);

				result = HidD_GetAttributes(DeviceHandle, &Attributes);

				if (Attributes.VendorID == VendorID) {
					if (Attributes.ProductID == ProductID) {
						//Both the Product and Vendor IDs match.
						MyDeviceDetected = TRUE;
					}
					else {
						CloseHandle(DeviceHandle);
					}
				} 
				else {
					CloseHandle(DeviceHandle);
				}
				//Free the memory used by the detailData structure (no longer needed).
				free(detailData);
			}
			else {
				//SetupDiEnumDeviceInterfaces returned 0, so there are no more devices to check.
				LastDevice=TRUE;
			}
			//If we haven't found the device yet, and haven't tried every available device,
			//try the next one.
			MemberIndex++;
		} while ((LastDevice == FALSE) && (MyDeviceDetected == FALSE));

		if (MyDeviceDetected == FALSE) {
			connected = false;
			return false;
		}

		//Free the memory reserved for hDevInfo by SetupDiClassDevs.
		SetupDiDestroyDeviceInfoList(hDevInfo);
		
		HidD_GetPreparsedData(DeviceHandle, &PreparsedData);
		HidP_GetCaps(PreparsedData, &Capabilities);

		HidD_FreePreparsedData(PreparsedData);
		connected = true;
		return true;
	}


	bool Send(int delay1,int delay2,int delay3,int delay4,int delay5,int delay6,int delay7,int delay8,
						int delay9,int delay10,int delay11,int delay12,int delay13,int delay14,int delay15,int delay16,
						int delay17,int delay18,int delay19,int delay20,int delay21,int delay22,int delay23,int delay24,
						int delay25){

		OutputReport[0] = 0;  //do not remove

		OutputReport[1] = delay1; //ch1
		OutputReport[2] = delay2; //ch2
		OutputReport[3] = delay3; //ch3
		OutputReport[4] = delay4; //ch4
		OutputReport[5] = delay5; //ch5
		OutputReport[6] = delay6; //ch6
		OutputReport[7] = delay7; //ch7
		OutputReport[8] = delay8; //ch8

		OutputReport[9] = delay9; //ch9
		OutputReport[10] = delay10; //ch10
		OutputReport[11] = delay11; //ch11
		OutputReport[12] = delay12; //ch12
		OutputReport[13] = delay13; //ch13
		OutputReport[14] = delay14; //ch14
		OutputReport[15] = delay15; //ch15
		OutputReport[16] = delay16; //ch16

		OutputReport[17] = delay17; //ch17
		OutputReport[18] = delay18; //ch18
		OutputReport[19] = delay19; //ch19
		OutputReport[20] = delay20; //ch20
		OutputReport[21] = delay21; //ch21
		OutputReport[22] = delay22; //ch22
		OutputReport[23] = delay23; //ch23
		OutputReport[24] = delay24; //ch24
		OutputReport[25] = delay25; //ch25

		if(!WriteFile(DeviceHandle, OutputReport, Capabilities.OutputReportByteLength, &BytesWritten, NULL)) {
			//CloseHandle(DeviceHandle);
			connected = false;
			return false;
		}

		return true;
	}
}