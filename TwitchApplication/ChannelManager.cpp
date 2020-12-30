#include "ChannelManager.h"

ChannelManager::ChannelManager(DispatchHandler^ handlerParam, BeginInvokeDelegate^ beginInvoke)
{
    processService = gcnew ProcessService();
    configurationService = gcnew ConfigurationService();
    processesWithNoTwitchCategory = gcnew List<ProcessModel^>();
    handler = handlerParam;
    invoke = beginInvoke;
    isProcessWatcherRunning = false;

    if (configurationService->GetProperty(Constants::TokenPropertyValue) != "")
    {
        isProcessWatcherRunning = true;
        System::Threading::Tasks::Task::Run(gcnew System::Action(this, &ChannelManager::MonitorProcesses));
    }
}

void ChannelManager::ToggleProcessWatcherStatus()
{
    isProcessWatcherRunning = !isProcessWatcherRunning;

    if (isProcessWatcherRunning) 
    {
        System::Threading::Tasks::Task::Run(gcnew System::Action(this, &ChannelManager::MonitorProcesses));
    }
}

void ChannelManager::SaveToken(System::String^ token)
{
    configurationService->SaveConfigProperty(Constants::TokenPropertyValue, token);
}

System::String^ ChannelManager::GetToken()
{
    return configurationService->GetProperty(Constants::TokenPropertyValue);
}

void ChannelManager::SaveChannelId(System::String^ channelId)
{
    configurationService->SaveConfigProperty(Constants::ChannelIdPropertyValue, channelId);
}

System::String^ ChannelManager::GetChannelId()
{
    return configurationService->GetProperty(Constants::ChannelIdPropertyValue);
}

void ChannelManager::SaveWindowOnTop(System::String^ windowOnTopValue)
{
    configurationService->SaveConfigProperty(Constants::WindowOnTopPropertyValue, windowOnTopValue);
}

System::String^ ChannelManager::GetWindowOnTop()
{
    return configurationService->GetProperty(Constants::WindowOnTopPropertyValue);
}

ChannelManager::~ChannelManager()
{
    if (processService)
    {
        delete processService;
    }
}

void ChannelManager::MonitorProcesses()
{
    while (isProcessWatcherRunning)
    {
        ProcessModel^ activeGame = ProcessRunningProcesses();

        if (activeGame != nullptr)
        {
            array<ProcessModel^>^ args = gcnew array<ProcessModel^>{activeGame};
            invoke(handler, args);
        }

        System::Threading::Thread::Sleep(5000);
    }
}

ProcessModel^ ChannelManager::GetProcessById(int processId)
{
    return processService->GetProcessById(processId);
}

ProcessModel^ ChannelManager::ProcessRunningProcesses()
{
    List<ProcessModel^>^ processes = gcnew List<ProcessModel^>();
    processes = processService->GetAllProcessesWithWindows();

    if (processes->Count > 0)
    {
        ProcessModel^ proc = processes[0];
        int paranthesisStart = proc->windowName->IndexOf("(");
        int paranthesisEnd = proc->windowName->IndexOf(")");
        if (paranthesisStart > -1 && paranthesisEnd > -1)
        {
            proc->windowName = proc->windowName->Remove(paranthesisStart, paranthesisEnd - paranthesisStart + 1)->Trim();
        }
        return proc;
    }

    return nullptr;
}

List<ProcessModel^>^ ChannelManager::GetGamesForLauncher(System::String^ launcherProcessName)
{
    ProcessModel^ originProcess = processService->GetProcessByName(launcherProcessName);

    if (originProcess != nullptr)
    {
        return processService->GetProcessesWithParent(originProcess->id);
    }

    return gcnew List<ProcessModel^>();
}

