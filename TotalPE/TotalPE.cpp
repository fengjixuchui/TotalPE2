// TotalPE.cpp : main source file for TotalPE.exe
//

#include "pch.h"
#include "resource.h"
#include "MainFrm.h"
#include <ThemeHelper.h>
#include "Helpers.h"
#include "AppSettings.h"

CAppModule _Module;
AppSettings g_Settings;

//#ifdef _DEBUG
//#pragma comment(lib, "../External/Capstone/Capstoned.lib")
//#else
//#pragma comment(lib, "../External/Capstone/Capstone.lib")
//#endif

extern "C" int Scintilla_RegisterClasses(void* hInstance);

#pragma comment(lib, "imm32")

int Run(LPCTSTR /*lpstrCmdLine*/ = nullptr, int nCmdShow = SW_SHOWDEFAULT) {
	CMessageLoop theLoop;
	_Module.AddMessageLoop(&theLoop);

	auto wndMain = new CMainFrame ;
	if (wndMain->CreateEx() == nullptr) {
		ATLTRACE(_T("Main window creation failed!\n"));
		return 0;
	}

	wndMain->ShowWindow(nCmdShow);

	int nRet = theLoop.Run();

	_Module.RemoveMessageLoop();
	return nRet;
}

int WINAPI _tWinMain(HINSTANCE hInstance, HINSTANCE /*hPrevInstance*/, LPTSTR lpstrCmdLine, int nCmdShow) {
	HRESULT hRes = ::CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
	ATLASSERT(SUCCEEDED(hRes));

//	ThemeHelper::SetNativeDarkMode(true);

	AtlInitCommonControls(ICC_BAR_CLASSES | ICC_LISTVIEW_CLASSES);

	hRes = _Module.Init(nullptr, hInstance);
	ATLASSERT(SUCCEEDED(hRes));

	Helpers::ExtractModules();

	Scintilla_RegisterClasses(hInstance);

	ThemeHelper::Init();

	int nRet = Run(lpstrCmdLine, nCmdShow);

	_Module.Term();
	::CoUninitialize();

	return nRet;
}
