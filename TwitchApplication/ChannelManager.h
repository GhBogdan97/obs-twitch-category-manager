#pragma once
#include "ProcessService.h"
#include "ConfigurationService.h"
#include "TwitchService.h"
using namespace System::Threading::Tasks;

ref class ChannelManager
{
public:
	delegate void DispatchHandler(ProcessModel^ arg);
	delegate void BeginInvokeDelegate(ChannelManager::DispatchHandler^ handler, array<ProcessModel^>^ args);
	ChannelManager(DispatchHandler^ handler, BeginInvokeDelegate^ beginInvoke);
	void ToggleProcessWatcherStatus();
	void SaveToken(System::String^ token);
	System::String^ GetToken();
	void SaveChannelId(System::String^ token);
	System::String^ GetChannelId();
	void SaveWindowOnTop(System::String^ checkedState);
	System::String^ GetWindowOnTop();

	~ChannelManager();
	bool isProcessWatcherRunning;
	ProcessModel^ GetProcessById(int processId);
private:
	ProcessService^ processService;
	DispatchHandler^ handler;
	BeginInvokeDelegate^ invoke;
	ConfigurationService^ configurationService;
	TwitchService^ twitchService;
	void MonitorProcesses();
	ProcessModel^ ProcessRunningProcesses();
	List<ProcessModel^>^ GetGamesForLauncher(System::String^ launcherProcessName);
	List<ProcessModel^>^ processesWithNoTwitchCategory;
};

