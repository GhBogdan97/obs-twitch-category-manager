#pragma once
#include <sstream>
#include "TwitchService.h"
#include "ChannelManager.h"

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Threading;

namespace TwitchApplication {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Configuration;

	public ref class ManagerForm : public System::Windows::Forms::Form
	{
	public:
		ManagerForm(void);

		void GameUpdated(ProcessModel^ process);

		void Invoke(ChannelManager::DispatchHandler^ handler, array<ProcessModel^>^ args)
		{
			this->BeginInvoke(handler, args);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~ManagerForm()
		{
			if (components)
			{
				delete components;
			}
			if (twitchService)
			{
				delete twitchService;
			}
			if (channelManager)
			{
				delete channelManager;
			}

		}
	private: System::Windows::Forms::Button^ bttStart;
	protected:
	private: System::Windows::Forms::Label^ lblStatus;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::FolderBrowserDialog^ folderBrowserDialog1;
	private: System::Windows::Forms::TextBox^ txtToken;


	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Label^ lblTokenValue;

	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::TabControl^ tabControl1;
	private: System::Windows::Forms::TabPage^ tabPageChannel;
	private: System::Windows::Forms::Button^ bttJustChatting;
	private: System::Windows::Forms::TabPage^ tabPageSettings;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;
		TwitchService^ twitchService;
		ChannelManager^ channelManager;
		ProcessModel^ currentProcess;
		ProcessModel^ tempProcess;

	private: System::Windows::Forms::Label^ lblDetectedGame;
	private: System::Windows::Forms::Label^ lblChannelStatus;

	private: System::Windows::Forms::Button^ bttStartMonitoring;
	private: System::Windows::Forms::Label^ lblMonitoringStatus;
	private: System::Windows::Forms::Label^ lblIsRunning;
	private: System::Windows::Forms::Label^ lblChannelStatusValue;
	private: System::Windows::Forms::ListBox^ lstCategories;
	private: System::Windows::Forms::Button^ bttReset;
	private: System::Windows::Forms::TextBox^ txtChannelID;

	private: System::Windows::Forms::Label^ lblChannelIDValue;
	private: System::Windows::Forms::Label^ lblInfo;
	private: System::Windows::Forms::CheckBox^ cbWindowOnTop;




	private: System::Windows::Forms::Label^ lblActiveGame;




#pragma region Windows Form Designer generated code
		   /// <summary>
		   /// Required method for Designer support - do not modify
		   /// the contents of this method with the code editor.
		   /// </summary>
		   void InitializeComponent(void)
		   {
			   this->txtToken = (gcnew System::Windows::Forms::TextBox());
			   this->button1 = (gcnew System::Windows::Forms::Button());
			   this->lblTokenValue = (gcnew System::Windows::Forms::Label());
			   this->button2 = (gcnew System::Windows::Forms::Button());
			   this->tabControl1 = (gcnew System::Windows::Forms::TabControl());
			   this->tabPageChannel = (gcnew System::Windows::Forms::TabPage());
			   this->bttReset = (gcnew System::Windows::Forms::Button());
			   this->lstCategories = (gcnew System::Windows::Forms::ListBox());
			   this->lblChannelStatusValue = (gcnew System::Windows::Forms::Label());
			   this->lblIsRunning = (gcnew System::Windows::Forms::Label());
			   this->lblMonitoringStatus = (gcnew System::Windows::Forms::Label());
			   this->bttStartMonitoring = (gcnew System::Windows::Forms::Button());
			   this->lblChannelStatus = (gcnew System::Windows::Forms::Label());
			   this->lblDetectedGame = (gcnew System::Windows::Forms::Label());
			   this->lblActiveGame = (gcnew System::Windows::Forms::Label());
			   this->bttJustChatting = (gcnew System::Windows::Forms::Button());
			   this->tabPageSettings = (gcnew System::Windows::Forms::TabPage());
			   this->cbWindowOnTop = (gcnew System::Windows::Forms::CheckBox());
			   this->txtChannelID = (gcnew System::Windows::Forms::TextBox());
			   this->lblChannelIDValue = (gcnew System::Windows::Forms::Label());
			   this->lblInfo = (gcnew System::Windows::Forms::Label());
			   this->tabControl1->SuspendLayout();
			   this->tabPageChannel->SuspendLayout();
			   this->tabPageSettings->SuspendLayout();
			   this->SuspendLayout();
			   // 
			   // txtToken
			   // 
			   this->txtToken->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				   | System::Windows::Forms::AnchorStyles::Right));
			   this->txtToken->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.5F));
			   this->txtToken->Location = System::Drawing::Point(124, 73);
			   this->txtToken->Name = L"txtToken";
			   this->txtToken->Size = System::Drawing::Size(334, 26);
			   this->txtToken->TabIndex = 1;
			   // 
			   // button1
			   // 
			   this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.5F));
			   this->button1->Location = System::Drawing::Point(13, 20);
			   this->button1->Name = L"button1";
			   this->button1->Size = System::Drawing::Size(113, 33);
			   this->button1->TabIndex = 2;
			   this->button1->Text = L"Get Token";
			   this->button1->UseVisualStyleBackColor = true;
			   this->button1->Click += gcnew System::EventHandler(this, &ManagerForm::GetToken_Click);
			   // 
			   // lblTokenValue
			   // 
			   this->lblTokenValue->AutoSize = true;
			   this->lblTokenValue->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.5F));
			   this->lblTokenValue->Location = System::Drawing::Point(9, 77);
			   this->lblTokenValue->Name = L"lblTokenValue";
			   this->lblTokenValue->Size = System::Drawing::Size(54, 20);
			   this->lblTokenValue->TabIndex = 3;
			   this->lblTokenValue->Text = L"Token";
			   // 
			   // button2
			   // 
			   this->button2->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				   | System::Windows::Forms::AnchorStyles::Right));
			   this->button2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.5F));
			   this->button2->Location = System::Drawing::Point(165, 299);
			   this->button2->Name = L"button2";
			   this->button2->Size = System::Drawing::Size(91, 36);
			   this->button2->TabIndex = 4;
			   this->button2->Text = L"Save";
			   this->button2->UseVisualStyleBackColor = true;
			   this->button2->Click += gcnew System::EventHandler(this, &ManagerForm::Save_Click);
			   // 
			   // tabControl1
			   // 
			   this->tabControl1->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				   | System::Windows::Forms::AnchorStyles::Left)
				   | System::Windows::Forms::AnchorStyles::Right));
			   this->tabControl1->Controls->Add(this->tabPageChannel);
			   this->tabControl1->Controls->Add(this->tabPageSettings);
			   this->tabControl1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.5F));
			   this->tabControl1->Location = System::Drawing::Point(12, 12);
			   this->tabControl1->Name = L"tabControl1";
			   this->tabControl1->SelectedIndex = 0;
			   this->tabControl1->Size = System::Drawing::Size(473, 534);
			   this->tabControl1->TabIndex = 5;
			   // 
			   // tabPageChannel
			   // 
			   this->tabPageChannel->Controls->Add(this->bttReset);
			   this->tabPageChannel->Controls->Add(this->lstCategories);
			   this->tabPageChannel->Controls->Add(this->lblChannelStatusValue);
			   this->tabPageChannel->Controls->Add(this->lblIsRunning);
			   this->tabPageChannel->Controls->Add(this->lblMonitoringStatus);
			   this->tabPageChannel->Controls->Add(this->bttStartMonitoring);
			   this->tabPageChannel->Controls->Add(this->lblChannelStatus);
			   this->tabPageChannel->Controls->Add(this->lblDetectedGame);
			   this->tabPageChannel->Controls->Add(this->lblActiveGame);
			   this->tabPageChannel->Controls->Add(this->bttJustChatting);
			   this->tabPageChannel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.5F));
			   this->tabPageChannel->Location = System::Drawing::Point(4, 29);
			   this->tabPageChannel->Name = L"tabPageChannel";
			   this->tabPageChannel->Padding = System::Windows::Forms::Padding(3);
			   this->tabPageChannel->Size = System::Drawing::Size(465, 501);
			   this->tabPageChannel->TabIndex = 0;
			   this->tabPageChannel->Text = L"Channel";
			   this->tabPageChannel->UseVisualStyleBackColor = true;
			   // 
			   // bttReset
			   // 
			   this->bttReset->Location = System::Drawing::Point(182, 87);
			   this->bttReset->Name = L"bttReset";
			   this->bttReset->Size = System::Drawing::Size(121, 29);
			   this->bttReset->TabIndex = 9;
			   this->bttReset->Text = L"Reset";
			   this->bttReset->UseVisualStyleBackColor = true;
			   this->bttReset->Click += gcnew System::EventHandler(this, &ManagerForm::bttReset_Click);
			   // 
			   // lstCategories
			   // 
			   this->lstCategories->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				   | System::Windows::Forms::AnchorStyles::Left)
				   | System::Windows::Forms::AnchorStyles::Right));
			   this->lstCategories->FormattingEnabled = true;
			   this->lstCategories->ItemHeight = 20;
			   this->lstCategories->Location = System::Drawing::Point(23, 140);
			   this->lstCategories->Name = L"lstCategories";
			   this->lstCategories->Size = System::Drawing::Size(425, 224);
			   this->lstCategories->TabIndex = 8;
			   this->lstCategories->SelectedIndexChanged += gcnew System::EventHandler(this, &ManagerForm::lstCategories_SelectedIndexChanged);
			   // 
			   // lblChannelStatusValue
			   // 
			   this->lblChannelStatusValue->AutoSize = true;
			   this->lblChannelStatusValue->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.5F));
			   this->lblChannelStatusValue->Location = System::Drawing::Point(153, 51);
			   this->lblChannelStatusValue->Name = L"lblChannelStatusValue";
			   this->lblChannelStatusValue->Size = System::Drawing::Size(14, 20);
			   this->lblChannelStatusValue->TabIndex = 7;
			   this->lblChannelStatusValue->Text = L" ";
			   // 
			   // lblIsRunning
			   // 
			   this->lblIsRunning->Anchor = System::Windows::Forms::AnchorStyles::Bottom;
			   this->lblIsRunning->AutoSize = true;
			   this->lblIsRunning->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.5F));
			   this->lblIsRunning->Location = System::Drawing::Point(178, 475);
			   this->lblIsRunning->Name = L"lblIsRunning";
			   this->lblIsRunning->Size = System::Drawing::Size(70, 20);
			   this->lblIsRunning->TabIndex = 6;
			   this->lblIsRunning->Text = L"Stopped";
			   // 
			   // lblMonitoringStatus
			   // 
			   this->lblMonitoringStatus->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			   this->lblMonitoringStatus->AutoSize = true;
			   this->lblMonitoringStatus->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.5F));
			   this->lblMonitoringStatus->Location = System::Drawing::Point(19, 475);
			   this->lblMonitoringStatus->Name = L"lblMonitoringStatus";
			   this->lblMonitoringStatus->Size = System::Drawing::Size(145, 20);
			   this->lblMonitoringStatus->TabIndex = 5;
			   this->lblMonitoringStatus->Text = L"Monitoring Status:";
			   // 
			   // bttStartMonitoring
			   // 
			   this->bttStartMonitoring->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			   this->bttStartMonitoring->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.5F));
			   this->bttStartMonitoring->Location = System::Drawing::Point(297, 465);
			   this->bttStartMonitoring->Name = L"bttStartMonitoring";
			   this->bttStartMonitoring->Size = System::Drawing::Size(151, 30);
			   this->bttStartMonitoring->TabIndex = 4;
			   this->bttStartMonitoring->Text = L"Start monitoring";
			   this->bttStartMonitoring->UseVisualStyleBackColor = true;
			   this->bttStartMonitoring->Click += gcnew System::EventHandler(this, &ManagerForm::ToggleMonitoringStatus_Click);
			   // 
			   // lblChannelStatus
			   // 
			   this->lblChannelStatus->AutoSize = true;
			   this->lblChannelStatus->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.5F));
			   this->lblChannelStatus->Location = System::Drawing::Point(19, 51);
			   this->lblChannelStatus->Name = L"lblChannelStatus";
			   this->lblChannelStatus->Size = System::Drawing::Size(128, 20);
			   this->lblChannelStatus->TabIndex = 3;
			   this->lblChannelStatus->Text = L"Channel Status:";
			   // 
			   // lblDetectedGame
			   // 
			   this->lblDetectedGame->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				   | System::Windows::Forms::AnchorStyles::Right));
			   this->lblDetectedGame->AutoEllipsis = true;
			   this->lblDetectedGame->AutoSize = true;
			   this->lblDetectedGame->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.5F));
			   this->lblDetectedGame->Location = System::Drawing::Point(136, 16);
			   this->lblDetectedGame->Name = L"lblDetectedGame";
			   this->lblDetectedGame->Size = System::Drawing::Size(14, 20);
			   this->lblDetectedGame->TabIndex = 2;
			   this->lblDetectedGame->Text = L" ";
			   // 
			   // lblActiveGame
			   // 
			   this->lblActiveGame->AutoSize = true;
			   this->lblActiveGame->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.5F));
			   this->lblActiveGame->Location = System::Drawing::Point(19, 16);
			   this->lblActiveGame->Name = L"lblActiveGame";
			   this->lblActiveGame->Size = System::Drawing::Size(120, 20);
			   this->lblActiveGame->TabIndex = 1;
			   this->lblActiveGame->Text = L"Active window:";
			   // 
			   // bttJustChatting
			   // 
			   this->bttJustChatting->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.5F));
			   this->bttJustChatting->Location = System::Drawing::Point(19, 87);
			   this->bttJustChatting->Name = L"bttJustChatting";
			   this->bttJustChatting->Size = System::Drawing::Size(135, 29);
			   this->bttJustChatting->TabIndex = 0;
			   this->bttJustChatting->Text = L"Just Chatting";
			   this->bttJustChatting->UseVisualStyleBackColor = true;
			   this->bttJustChatting->Click += gcnew System::EventHandler(this, &ManagerForm::bttJustChatting_Click);
			   // 
			   // tabPageSettings
			   // 
			   this->tabPageSettings->Controls->Add(this->cbWindowOnTop);
			   this->tabPageSettings->Controls->Add(this->txtChannelID);
			   this->tabPageSettings->Controls->Add(this->lblChannelIDValue);
			   this->tabPageSettings->Controls->Add(this->txtToken);
			   this->tabPageSettings->Controls->Add(this->button2);
			   this->tabPageSettings->Controls->Add(this->button1);
			   this->tabPageSettings->Controls->Add(this->lblTokenValue);
			   this->tabPageSettings->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.5F));
			   this->tabPageSettings->Location = System::Drawing::Point(4, 29);
			   this->tabPageSettings->Name = L"tabPageSettings";
			   this->tabPageSettings->Padding = System::Windows::Forms::Padding(3);
			   this->tabPageSettings->Size = System::Drawing::Size(465, 501);
			   this->tabPageSettings->TabIndex = 1;
			   this->tabPageSettings->Text = L"Settings";
			   this->tabPageSettings->UseVisualStyleBackColor = true;
			   // 
			   // cbWindowOnTop
			   // 
			   this->cbWindowOnTop->AutoSize = true;
			   this->cbWindowOnTop->CheckAlign = System::Drawing::ContentAlignment::MiddleRight;
			   this->cbWindowOnTop->Location = System::Drawing::Point(6, 213);
			   this->cbWindowOnTop->Name = L"cbWindowOnTop";
			   this->cbWindowOnTop->Size = System::Drawing::Size(177, 24);
			   this->cbWindowOnTop->TabIndex = 8;
			   this->cbWindowOnTop->Text = L"Keep window on top";
			   this->cbWindowOnTop->UseVisualStyleBackColor = true;
			   // 
			   // txtChannelID
			   // 
			   this->txtChannelID->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Left)
				   | System::Windows::Forms::AnchorStyles::Right));
			   this->txtChannelID->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.5F));
			   this->txtChannelID->Location = System::Drawing::Point(123, 154);
			   this->txtChannelID->Name = L"txtChannelID";
			   this->txtChannelID->Size = System::Drawing::Size(334, 26);
			   this->txtChannelID->TabIndex = 5;
			   // 
			   // lblChannelIDValue
			   // 
			   this->lblChannelIDValue->AutoSize = true;
			   this->lblChannelIDValue->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.5F));
			   this->lblChannelIDValue->Location = System::Drawing::Point(8, 158);
			   this->lblChannelIDValue->Name = L"lblChannelIDValue";
			   this->lblChannelIDValue->Size = System::Drawing::Size(92, 20);
			   this->lblChannelIDValue->TabIndex = 6;
			   this->lblChannelIDValue->Text = L"Channel ID";
			   // 
			   // lblInfo
			   // 
			   this->lblInfo->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left)
				   | System::Windows::Forms::AnchorStyles::Right));
			   this->lblInfo->AutoSize = true;
			   this->lblInfo->BackColor = System::Drawing::SystemColors::Window;
			   this->lblInfo->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->lblInfo->ForeColor = System::Drawing::Color::ForestGreen;
			   this->lblInfo->Location = System::Drawing::Point(12, 553);
			   this->lblInfo->Name = L"lblInfo";
			   this->lblInfo->Size = System::Drawing::Size(0, 20);
			   this->lblInfo->TabIndex = 6;
			   // 
			   // ManagerForm
			   // 
			   this->AccessibleName = L"Channel Category Manager";
			   this->ClientSize = System::Drawing::Size(497, 578);
			   this->Controls->Add(this->lblInfo);
			   this->Controls->Add(this->tabControl1);
			   this->Name = L"ManagerForm";
			   this->Text = L"Channel Category Manager";
			   this->tabControl1->ResumeLayout(false);
			   this->tabPageChannel->ResumeLayout(false);
			   this->tabPageChannel->PerformLayout();
			   this->tabPageSettings->ResumeLayout(false);
			   this->tabPageSettings->PerformLayout();
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }
#pragma endregion

		private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e);

		private: System::Void GetToken_Click(System::Object^ sender, System::EventArgs^ e);

		private: System::Void Save_Click(System::Object^ sender, System::EventArgs^ e);

		private: System::Void bttJustChatting_Click(System::Object^ sender, System::EventArgs^ e);

		private: System::Void ToggleMonitoringStatus_Click(System::Object^ sender, System::EventArgs^ e);

		private: System::Void lstCategories_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e);

		private: System::Void bttReset_Click(System::Object^ sender, System::EventArgs^ e);
};
}
void start();

extern "C" __declspec(dllexport) void __stdcall FormMain()
{
	Thread^ t = gcnew Thread(gcnew ThreadStart(start));
	t->ApartmentState = ApartmentState::STA;
	t->Start();
}