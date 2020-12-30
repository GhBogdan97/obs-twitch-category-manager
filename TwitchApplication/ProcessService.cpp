#include "ProcessService.h"
#include <utility>

ProcessModel^ ProcessService::GetProcessByName(System::String^ processName)
{
	ManagementObjectSearcher^ searcher = gcnew ManagementObjectSearcher("ROOT\\CIMV2", System::String::Format("Select * From Win32_Process Where Name='{0}'", processName));
	ManagementObjectCollection^ collection = searcher->Get();
	for each (ManagementObject^ var in collection)
	{
		System::String^ processName = (System::String^)var["Name"];
		UINT processId = (UINT)var["ProcessId"];
		UINT parentProcessId = (UINT)var["ParentProcessId"];
		Process^ process = Process::GetProcessById(processId);

		return gcnew ProcessModel(processName, process->MainWindowTitle, processId, parentProcessId);
	}

	return nullptr;
}

ProcessModel^ ProcessService::GetProcessById(int processId)
{
	try
	{
		Process^ process = Process::GetProcessById(processId);
		return gcnew ProcessModel(process->ProcessName, process->MainWindowTitle, processId, processId);
	}
	catch (System::Exception^ ex)
	{
		return nullptr;
	}
}

List<ProcessModel^>^ ProcessService::GetProcessesWithParent(int parentProcessId)
{
	List<ProcessModel^>^ foundProcesses = gcnew List<ProcessModel^>();
	ManagementObjectSearcher^ searcher = gcnew ManagementObjectSearcher(System::String::Format("Select * From Win32_Process Where ParentProcessId='{0}'", parentProcessId));
	ManagementObjectCollection^ collection = searcher->Get();
	for each (ManagementObject ^ var in collection)
	{
		System::String^ processName = (System::String^)var["Name"];
		UINT processId = (UINT)var["ProcessId"];
		UINT parentProcessId = (UINT)var["ParentProcessId"];
		Process^ process = Process::GetProcessById(processId);

		if (process->MainWindowTitle->Length > 0 && !process->ProcessName->Contains("steamwebhelper"))
		{
			ProcessModel^ processModel = gcnew ProcessModel(processName, process->MainWindowTitle, processId, parentProcessId);
			foundProcesses->Add(processModel);
		}
	}

	return Enumerable::ToList(Enumerable::Distinct(foundProcesses));
}

List<ProcessModel^>^ ProcessService::GetAllProcessesWithWindows()
{
	array<Process^>^ processes = Process::GetProcesses();
	List<ProcessModel^>^ processesWithWindows = gcnew List<ProcessModel^>();
	int x = GetForegroundWindow();

	for each (Process^ proc in processes)
	{
		if (proc->MainWindowTitle != "")
		{
			bool isGame = false;

			int windowHandle = proc->MainWindowHandle.ToInt32();

			if (x == windowHandle)
			{
				isGame = true;
			}

			if (isGame)
			{
				processesWithWindows->Add(gcnew ProcessModel(proc->ProcessName, proc->MainWindowTitle, proc->Id, proc->Id));
				break;
			}
		}
	}

	return processesWithWindows;
}
