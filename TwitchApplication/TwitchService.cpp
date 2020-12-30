#include "TwitchService.h"
using namespace System::IO;
using namespace System::Text::RegularExpressions;

TwitchService::TwitchService()
{
	configService = gcnew ConfigurationService();
	twitchToken = configService->GetProperty(Constants::TokenPropertyValue);
	twitchClientId = configService->GetProperty(Constants::ClientIdPropertyValue);
	twitchChannelId = configService->GetProperty(Constants::ChannelIdPropertyValue);
}

System::String^ TwitchService::GetAuthUrl()
{
	System::String^ twitchUrl = "https://id.twitch.tv/oauth2/authorize";
	System::String^ redirectUrl = "https%3A%2F%2Fgithub.com%2FGhBogdan97%2Fobs-twitch-category-manager";
	std::ostringstream oss;
	return twitchUrl + "?client_id=" + twitchClientId + "&redirect_uri=" + redirectUrl + "&response_type=token&scope=channel_editor";
}

void TwitchService::SetCategory(System::String^ gameName)
{
	try
	{
		System::String^ url = "https://api.twitch.tv/kraken/channels/" + twitchChannelId;
		HttpWebRequest^ request = (HttpWebRequest^)WebRequest::Create(url);
		request->Method = "PUT";
		request->Accept = "application/vnd.twitchtv.v5+json";
		request->Headers->Add("Authorization", "OAuth " + twitchToken);

		System::String^ body = "{\"channel\":{\"game\":\"" + gameName + "\"}}";
		array<unsigned char>^ ex = System::Text::Encoding::UTF8->GetBytes(body);
		request->ContentLength = ex->Length;
		request->ContentType = "application/json";
		Stream^ requestStream = request->GetRequestStream();
		requestStream->Write(ex, 0, ex->Length);
		requestStream->Close();

		WebResponse^ response = request->GetResponse();
	}
	catch (System::Exception^ ex)
	{
		ex->Message;
	}
}

void TwitchService::RefreshTokenFromConfig()
{
	twitchToken = configService->GetProperty(Constants::TokenPropertyValue);
	twitchChannelId = configService->GetProperty(Constants::ChannelIdPropertyValue);
}

List<System::String^>^ TwitchService::SearchGameCategory(System::String^ gameName)
{
	ServicePointManager::SecurityProtocol = SecurityProtocolType::Tls12;
	if (twitchToken == "" || twitchClientId == "")
	{
		throw gcnew System::ArgumentNullException("Token or client id are empty. Please visit the settings page.");
	}

	try
	{
		List<System::String^>^ categories = gcnew List<System::String^>();
		System::String^ twitchUrl = "https://api.twitch.tv/kraken/search/games?query='" + gameName + "'";
		HttpWebRequest^ request = (HttpWebRequest^)WebRequest::Create(twitchUrl);
		request->Method = "GET";
		request->Accept = "application/vnd.twitchtv.v5+json";
		request->Headers->Add("Client-ID", twitchClientId);
		request->Headers->Add("Authorization", "OAuth " + twitchToken);
		WebResponse^ response = request->GetResponse();
		System::String^ responseValue = "";
		{
			StreamReader^ reader = gcnew StreamReader(response->GetResponseStream());
			responseValue = reader->ReadToEnd();
		}

		System::String^ matchStr = "\"name\" ?: ?\"[^\"]*"+ gameName +"[^\"]*\"";
		MatchCollection^ matches = Regex::Matches(responseValue, matchStr, RegexOptions::IgnoreCase);
		for each (Match^ match in matches)
		{
			System::String^ splittedValue = match->Value->Split(':')[1];
			System::String^ foundCategory = splittedValue->Trim()->Replace("\"", "");
			categories->Add(foundCategory);
		}
		return categories;
	}
	catch (System::Exception^ ex)
	{
		System::Windows::Forms::MessageBox::Show(ex->Message);
		return nullptr;
	}
}
