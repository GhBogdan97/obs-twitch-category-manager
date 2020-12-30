#include "ManagerForm.h"

using namespace TwitchApplication;

[STAThread]
void start() {
	try
	{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	TwitchApplication::ManagerForm form;
	Application::Run(% form);
	}
	catch (Exception^ ex)
	{
		MessageBox::Show(ex->Message);
		MessageBox::Show(ex->InnerException->Message);
	}
}

ManagerForm::ManagerForm(void)
{
	InitializeComponent();

	twitchService = gcnew TwitchService();
	ChannelManager::DispatchHandler^ handler = gcnew ChannelManager::DispatchHandler(this, &ManagerForm::GameUpdated);
	ChannelManager::BeginInvokeDelegate^ handler2 = gcnew ChannelManager::BeginInvokeDelegate(this, &ManagerForm::Invoke);
	channelManager = gcnew ChannelManager(handler, handler2);

	System::String^ token = channelManager->GetToken();
	System::String^ channelId = channelManager->GetChannelId();
	bool windowOnTop = Convert::ToBoolean(channelManager->GetWindowOnTop());
	txtToken->Text = token;
	txtChannelID->Text = channelId;
	cbWindowOnTop->Checked = windowOnTop;
	this->TopMost = cbWindowOnTop->Checked;

	if (String::IsNullOrEmpty(txtToken->Text) && String::IsNullOrEmpty(txtChannelID->Text))
	{
		MessageBox::Show("Token or Channel Id are empty. Please visit the settings page. ", "Channel Category Manager");
		bttStartMonitoring->Enabled = false;
	}
	else
	{
		bttStartMonitoring->Text = "Stop monitoring";
		lblIsRunning->Text = "Running";
		lblInfo->Text = "Monitoring started. You can start playing.";
	}
}

System::Void ManagerForm::MyForm_Load(System::Object^ sender, System::EventArgs^ e)
{
	System::String^ token = channelManager->GetToken();
	System::String^ channelId = channelManager->GetChannelId();
	txtToken->Text = token;
	txtChannelID->Text = channelId;

	if (String::IsNullOrEmpty(txtToken->Text) && String::IsNullOrEmpty(txtChannelID->Text))
	{
		MessageBox::Show("Token or Channel Id are empty. Please visit the settings page. ");
		bttStartMonitoring->Enabled = false;
	}
}

void ManagerForm::GameUpdated(ProcessModel^ process)
{
	try
	{
		tempProcess = process;
		if (process->windowName == lblDetectedGame->Text || process->windowName == "Channel Category Manager" || process->windowName == "Task Switching")
		{
			return;
		}

		if (currentProcess != nullptr && (channelManager->GetProcessById(currentProcess->id) != nullptr || process->windowName == currentProcess->windowName))
		{
			return;
		}

		List<System::String^>^ categoriesFound = twitchService->SearchGameCategory(process->windowName);
		lblDetectedGame->Text = process->windowName;
		bool exactCategoryFound = false;

		if (categoriesFound->Count == 0)
		{
			lblChannelStatusValue->Text = "No category found for this game.";
			lstCategories->Items->Clear();
			return;
		}

		for each (System::String ^ cat in categoriesFound)
		{
			if (cat == process->windowName)
			{
				exactCategoryFound = true;
			}
		}

		if (categoriesFound->Count == 1 || exactCategoryFound)
		{
			twitchService->SetCategory(process->windowName);
			lblChannelStatusValue->Text = "Game category updated.";
			currentProcess = process;
			return;
		}

		if (categoriesFound->Count > 1)
		{
			lstCategories->Items->Clear();
			for each (System::String ^ category in categoriesFound)
			{
				lstCategories->Items->Add(category);
			}
		}
	}
	catch (System::Exception^ ex)
	{
		lblChannelStatusValue->Text = ex->Message;
	}
}

System::Void ManagerForm::GetToken_Click(System::Object^ sender, System::EventArgs^ e)
{

	System::String^ resultUrl = twitchService->GetAuthUrl();
	System::Diagnostics::Process::Start(resultUrl);
}

System::Void ManagerForm::Save_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (!String::IsNullOrEmpty(txtToken->Text) && !String::IsNullOrEmpty(txtChannelID->Text))
	{
		bttStartMonitoring->Enabled = true;
		channelManager->SaveToken(txtToken->Text);
		channelManager->SaveChannelId(txtChannelID->Text);
		channelManager->SaveWindowOnTop(cbWindowOnTop->Checked ? "True" : "False");

		twitchService->RefreshTokenFromConfig();
		this->TopMost = cbWindowOnTop->Checked;
		lblInfo->Text = "Settings Saved.";
	}
	else
	{
		MessageBox::Show("Token should not be empty.");
		lblInfo->Text = "Token should not be empty.";
	}
}

System::Void ManagerForm::bttJustChatting_Click(System::Object^ sender, System::EventArgs^ e)
{
	if (channelManager->isProcessWatcherRunning)
	{
		channelManager->ToggleProcessWatcherStatus();
		bttStartMonitoring->Text = "Start monitoring";
		lblIsRunning->Text = "Stopped";
		lblDetectedGame->Text = "";
		twitchService->SetCategory("Just Chatting");
		lblChannelStatusValue->Text = "Just Chatting.";
		lblInfo->Text = "Channel set to ""Just Chatting""";
	}
}

System::Void ManagerForm::ToggleMonitoringStatus_Click(System::Object^ sender, System::EventArgs^ e)
{
	channelManager->ToggleProcessWatcherStatus();

	if (channelManager->isProcessWatcherRunning)
	{
		bttStartMonitoring->Text = "Stop monitoring";
		lblIsRunning->Text = "Running";
		lblInfo->Text = "Monitoring started. You can start playing.";
	}
	else
	{
		bttStartMonitoring->Text = "Start monitoring";
		lblIsRunning->Text = "Stopped";
		lblDetectedGame->Text = "";
		lblChannelStatusValue->Text = "";
		lblInfo->Text = "Monitoring stopped.";
	}
}

System::Void ManagerForm::lstCategories_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e)
{
	System::String^ selectedCategory = lstCategories->SelectedItem->ToString();
	twitchService->SetCategory(selectedCategory);
	lblChannelStatusValue->Text = "Game category updated.";
	currentProcess = tempProcess;
	lblInfo->Text = "Game category updated.";
}

System::Void ManagerForm::bttReset_Click(System::Object^ sender, System::EventArgs^ e)
{
	lstCategories->Items->Clear();
	lblChannelStatusValue->Text = "";
	lblDetectedGame->Text = "";
	currentProcess = nullptr;
	tempProcess = nullptr;
}

