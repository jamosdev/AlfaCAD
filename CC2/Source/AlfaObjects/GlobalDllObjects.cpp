// GlobalDllObjects.cpp : Defines the initialization routines for the DLL.
//

#include "stdafx.h"
#include <new.h>
#include <WinUser.h>
#include <mmsystem.h>

#define GLOBALDLLOBJECTS_EXPORTS
#include "GlobalDllObjects.h"

//#define MAXPATH   260

// blokowanie dostêpu miêdzy procesami
HANDLE g_hMutex = ::CreateMutex(NULL, FALSE, "CTest");
/*
HANDLE g_hMutex1 = ::CreateMutex(NULL, FALSE, "CDeposit");
HANDLE g_hMutex2 = ::CreateMutex(NULL, FALSE, "CReturn");
HANDLE g_hMutex3 = ::CreateMutex(NULL, FALSE, "CReset");
HANDLE g_hMutex4 = ::CreateMutex(NULL, FALSE, "CSet");
HANDLE g_hMutex5 = ::CreateMutex(NULL, FALSE, "CCheck");
HANDLE g_hMutex6 = ::CreateMutex(NULL, FALSE, "CActive");
*/

/*
typedef struct
{
	unsigned char flag = 0;
	int x1, y1, x2, y2;
	char drawing_file[MAXPATH];
	char dump_file[MAXPATH];
} Client_Bitmap;
*/

#pragma data_seg(".SHARDAT")
static char lpszMemory[sizeof(CTest)];
CTest* g_pTest = NULL;
int g_nClients = 0;
int g_noClient = 0;
int g_noClient_ = 0;
////MMRESULT my_timer;
#define EMPTY "                                                                                                                                "
#define MAX_NUMBER_OF_CLIENTS 16
static Client_Bitmap client_bitmap[MAX_NUMBER_OF_CLIENTS] = { {0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},
									{0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},
/*
                                    {0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},
									{0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},
									{0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},
									{0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},
									{0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},
									{0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},{0,0,0,0,0,EMPTY,EMPTY},
 */
};
#pragma data_seg()


static void nooop(void)
{}

void(*AlfaRedrawPtr)(void) = NULL; // nooop;
int(*AlfaEditTextPtr)(char *mytext, int edit_params, int nCmdShow) = NULL;
int(*AlfatestCallPtr)(int) = NULL;

void(*FF)(void) = nooop;

//typedef void(*TEST_CALLBACK)(int val);

TEST_CALLBACK _theCallback = NULL;

//__declspec(dllexport) void SetCallback(TEST_CALLBACK callback)

void EXPORTED_DLL_FUNCTION SetCallback(TEST_CALLBACK callback)
{
	_theCallback = callback;
}


/*
#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif
*/

//
//	Note!
//
//		If this DLL is dynamically linked against the MFC
//		DLLs, any functions exported from this DLL which
//		call into MFC must have the AFX_MANAGE_STATE macro
//		added at the very beginning of the function.
//
//		For example:
//
//		extern "C" BOOL PASCAL EXPORT ExportedFunction()
//		{
//			AFX_MANAGE_STATE(AfxGetStaticModuleState());
//			// normal function body here
//		}
//
//		It is very important that this macro appear in each
//		function, prior to any calls into MFC.  This means that
//		it must appear as the first statement within the 
//		function, even before any object variable declarations
//		as their constructors may generate calls into the MFC
//		DLL.
//
//		Please see MFC Technical Notes 33 and 58 for additional
//		details.
//

/////////////////////////////////////////////////////////////////////////////
// CGlobalDllObjectsApp

BEGIN_MESSAGE_MAP(CGlobalDllObjectsApp, CWinApp)
	//{{AFX_MSG_MAP(CGlobalDllObjectsApp)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CGlobalDllObjectsApp construction

CGlobalDllObjectsApp::CGlobalDllObjectsApp()
{
	// TODO: add construction code here,
	// Place all significant initialization in InitInstance
}

/////////////////////////////////////////////////////////////////////////////
// The one and only CGlobalDllObjectsApp object

CGlobalDllObjectsApp theApp;

/*
void update_flags(void)
{
	BOOL ret;
	int i;
	//ret = PlaySound("MouseClick", NULL, SND_SYSTEM);
	for (i = 0; i < 64; i++)
	{
		if (client_bitmap[i].flag > 0)
		{
			if ((client_bitmap[i].flag == 1) || (client_bitmap[i].flag == 3)) client_bitmap[i].flag++;
			else
			{
				client_bitmap[i].flag = 0;
				//ret = PlaySound("MouseClick", NULL, SND_SYSTEM);
				////ret = PlaySound("clicked.wav", NULL, SND_FILENAME | SND_ASYNC);
			}
		}
	}
	return;
}
*/

BOOL CGlobalDllObjectsApp::InitInstance() 
{
 ::WaitForSingleObject(g_hMutex,INFINITE);

 if (!g_pTest)
 {

	/*
  ::MessageBox(NULL,
   "CGlobalDllObjectsApp::InitInstance - "
   "konstruowanie globalnego CTest", 
   "CTest.DLL", MB_OK);
  MessageBeep(MB_ABORTRETRYIGNORE);
  */
  //my_timer=timeSetEvent(5000, 500, (LPTIMECALLBACK)update_flags, NULL, TIME_PERIODIC);
  
  g_pTest = ::new (lpszMemory) CTest;
  ASSERT(g_pTest);

  ////my_timer = timeSetEvent(10000, 500, (LPTIMECALLBACK)update_flags, NULL, TIME_PERIODIC);
 }
 
 g_nClients++;
 g_noClient++;
 if (g_noClient <= MAX_NUMBER_OF_CLIENTS) g_noClient_ = g_noClient;
 else g_noClient_ = MAX_NUMBER_OF_CLIENTS;


 client_bitmap[g_noClient_ - 1].flag = 0;
 strcpy(client_bitmap[g_noClient_ - 1].dump_file, "");

 ::ReleaseMutex(g_hMutex);
	
 return CWinApp::InitInstance();
}

int CGlobalDllObjectsApp::ExitInstance() 
{
  MMRESULT ret_timer;

 ::WaitForSingleObject(g_hMutex,INFINITE);

 if (0 == --g_nClients)
 {

  MSG msg;

  ::PeekMessage(&msg, NULL, 
   WM_QUIT, WM_QUIT, PM_REMOVE);

  /*
  ::MessageBox(NULL,
   "CGlobalDllObjectsApp::ExitInstance - "
   "niszczenie globalnego obiektu CTest", 
   "CTest.DLL", MB_OK);
   */
  ////if (my_timer) ret_timer=timeKillEvent(my_timer);

  g_noClient=1;
  g_noClient_ = g_noClient;

  delete g_pTest;
  g_pTest = NULL;

 }

 ::ReleaseMutex(g_hMutex);
 ::CloseHandle(g_hMutex);
 
 //::ReleaseMutex(g_hMutex1);
 //::CloseHandle(g_hMutex1);

 //::ReleaseMutex(g_hMutex2);
 //::CloseHandle(g_hMutex2);

 //::ReleaseMutex(g_hMutex3);
 //::CloseHandle(g_hMutex3);

 //::ReleaseMutex(g_hMutex4);
 //::CloseHandle(g_hMutex4);

 //::ReleaseMutex(g_hMutex5);
 //::CloseHandle(g_hMutex5);

 //::ReleaseMutex(g_hMutex6);
 //::CloseHandle(g_hMutex6);
 
	
 return CWinApp::ExitInstance();
}

extern "C"
{

void EXPORTED_DLL_FUNCTION GetTestPtr(CTest*& rpTest)
{
 rpTest = g_pTest;
}

int EXPORTED_DLL_FUNCTION GetNbrOfClients()
{
 return g_nClients;
}

int EXPORTED_DLL_FUNCTION GetNoOfClient()
{
 return g_noClient;
}

int EXPORTED_DLL_FUNCTION RegRedraw(void(*ptr)(void))  //(char *ptr)
{
	AlfaRedrawPtr = ptr;
	return 1;
}

int EXPORTED_DLL_FUNCTION RegEditText(int(*ptr)(char *mytext, int edit_params, int nCmdShow))
{
	AlfaEditTextPtr = ptr;
	return 1;
}

int EXPORTED_DLL_FUNCTION RegtestCall(int(*ptr)(int))
{
	AlfatestCallPtr = ptr;
	return 1;
}


int EXPORTED_DLL_FUNCTION AlfaRedraw()
{
	if (AlfaRedrawPtr != NULL)
	{
		AlfaRedrawPtr();
		return 1;
	}
	else return 0;
}

int EXPORTED_DLL_FUNCTION AlfaEditText(char *mytext, int edit_params, int nCmdShow)
{
	if (AlfaEditTextPtr != NULL)
	{
		return AlfaEditTextPtr(mytext, edit_params, nCmdShow);
	}
	else return 0;
}


int EXPORTED_DLL_FUNCTION AlfatestCall(int val)
{
	if (AlfatestCallPtr != NULL)
	{
		//return AlfatestCallPtr(val);
		return (int)AlfatestCallPtr;
	}
	else return 0;
}

int EXPORTED_DLL_FUNCTION Alfacallback(int val)
{
	if (_theCallback != NULL)
	{
		//_theCallback(val);
		//return 1;
		return (int)_theCallback;
	}
	else return 0;
}

int EXPORTED_DLL_FUNCTION AlfacallbackGo(int val)
{
	if (_theCallback != NULL)
	{
		_theCallback(val);
		return 1;
	}
	else return 0;
}

unsigned char EXPORTED_DLL_FUNCTION Check_Client_Flag(int client0)
{
	//::WaitForSingleObject(g_hMutex5, INFINITE);
	int client = client0 - 1;
	
	if (client_bitmap[client].flag >= 3)
	{
		client_bitmap[client].flag = 1;
		//::ReleaseMutex(g_hMutex5);
		return 3;
	}
	else
	{
		
		if ((client_bitmap[client].flag == 2) || (client_bitmap[client].flag == 0)) //testing activity  //0
		{
			//reset flag
			client_bitmap[client].flag = 1;
		}
		//::ReleaseMutex(g_hMutex5);
		return client_bitmap[client].flag;
	}

}

void EXPORTED_DLL_FUNCTION Set_Client_Flag(int client0, unsigned char flag)
{
	//::WaitForSingleObject(g_hMutex4, INFINITE);
	int client = client0 - 1;

	client_bitmap[client].flag = flag;
	//::ReleaseMutex(g_hMutex4);
}

void EXPORTED_DLL_FUNCTION Reset_Client_Flag(int client0)
{
	//::WaitForSingleObject(g_hMutex3, INFINITE);
	int client = client0 - 1;
	if (client_bitmap[client].flag != 0)
	{
		strcpy(client_bitmap[client].dump_file, "");
	}
	client_bitmap[client].flag = 0;
	//::ReleaseMutex(g_hMutex3);
}

int EXPORTED_DLL_FUNCTION Deposit_Bitmap(int client0, char *dump_file, int x1, int y1, int x2, int y2, char *drawing_file)
{
	int ret;
	int client = client0 - 1;
	//::WaitForSingleObject(g_hMutex1, INFINITE);
	if (client >= MAX_NUMBER_OF_CLIENTS) client = MAX_NUMBER_OF_CLIENTS - 1;
	
	if (client_bitmap[client].flag != 0)
	{
		strcpy(client_bitmap[client].dump_file, "");
	}

	strcpy(client_bitmap[client].dump_file, dump_file);
	client_bitmap[client].x1 = x1;
	client_bitmap[client].y1 = y1;
	client_bitmap[client].x2 = x2;
	client_bitmap[client].y2 = y2;

	strcpy(client_bitmap[client].drawing_file, drawing_file);  //file name seems to be obvious
	client_bitmap[client].flag = 1;
	
	////MessageBeep(MB_OK);
	////ret = PlaySound("clicked.wav", NULL, SND_FILENAME | SND_ASYNC);
	//::ReleaseMutex(g_hMutex1);
	
	return 1;
}

int EXPORTED_DLL_FUNCTION Return_Active_Clients(void)
{
	//::WaitForSingleObject(g_hMutex6, INFINITE);
	int client;
	int client_no = 0;
	for (client = 0; client < MAX_NUMBER_OF_CLIENTS; client++)
	{
		if (client_bitmap[client].flag != 0) client_no++;
	}
	//::ReleaseMutex(g_hMutex6);
	return client_no;
}

int EXPORTED_DLL_FUNCTION Return_Bitmap(int client0, char *dump_file, int *x1, int *y1, int *x2, int *y2, char *drawing_file)
{
	//::WaitForSingleObject(g_hMutex2, INFINITE);
	int client = client0 - 1;
	if (client >= MAX_NUMBER_OF_CLIENTS) client = MAX_NUMBER_OF_CLIENTS - 1;
    
	if (client_bitmap[client].flag != 0)
	{
		strcpy(dump_file, client_bitmap[client].dump_file);
		*x1 = client_bitmap[client].x1;
		*y1 = client_bitmap[client].y1;
		*x2 = client_bitmap[client].x2;
		*y2 = client_bitmap[client].y2;
		strcpy(drawing_file, client_bitmap[client].drawing_file);

		//MessageBeep(MB_OK);
		//::ReleaseMutex(g_hMutex2);
		return 1;
	}
	else
	{
		//::ReleaseMutex(g_hMutex2);
		return 0;
	}
}


}

