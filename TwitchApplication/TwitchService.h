#pragma once
#include <string>
#include <sstream>
#include "ConfigurationService.h"
using namespace System::Net;
using namespace System::Collections::Generic;

ref class TwitchService
{
public:
	TwitchService();
	System::String^ GetAuthUrl();
	void SetCategory(System::String^ gameName);
	void RefreshTokenFromConfig();
	List<System::String^>^ SearchGameCategory(System::String^ gameName);

private:
	System::String^ twitchToken;
	System::String^ twitchChannelId;
	System::String^ twitchClientId;
	ConfigurationService^ configService;
};

