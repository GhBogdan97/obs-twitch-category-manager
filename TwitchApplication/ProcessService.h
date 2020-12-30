#pragma once
#include "ProcessModel.h"
using namespace System::Management;
using namespace System::Collections::Generic;
using namespace System::Runtime::InteropServices;
using namespace System::Diagnostics;
using namespace System::Linq;

ref class ProcessService
{
public:
	ProcessModel^ GetProcessByName(System::String^ processName);
	ProcessModel^ GetProcessById(int processId);
	List<ProcessModel^>^ GetProcessesWithParent(int parentProcessId);
	List<ProcessModel^>^ GetAllProcessesWithWindows();

	[DllImport("user32.dll")]
	static int GetForegroundWindow();

	[DllImport("user32.dll")]
	static int GetWindowText(int hWnd,  System::Text::StringBuilder text, int count);

};

