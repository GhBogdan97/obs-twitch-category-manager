#include "ConfigurationService.h"

ConfigurationService::ConfigurationService()
{
	configuration = ConfigurationManager::OpenExeConfiguration(System::Reflection::Assembly::GetExecutingAssembly()->Location);
}

System::String^ ConfigurationService::GetProperty(System::String^ propertyName)
{
	System::String^ propertyValue = "";
	keyToCompareWith = propertyName;
	cli::array<System::String^>^ keys = configuration->AppSettings->Settings->AllKeys;
	if (!System::Array::Exists(keys, gcnew System::Predicate<System::String^>(this, &ConfigurationService::CompareKeys)))
	{
		return propertyValue;
	}
	return (System::String^)configuration->AppSettings->Settings[propertyName]->Value;
}

void ConfigurationService::SaveConfigProperty(System::String^ propertyName, System::String^ propertyValue)
{
	keyToCompareWith = propertyName;
	cli::array<System::String^>^ keys = configuration->AppSettings->Settings->AllKeys;
	if (System::Array::Exists(keys, gcnew System::Predicate<System::String^>(this, &ConfigurationService::CompareKeys)))
	{
		configuration->AppSettings->Settings->Remove(propertyName);
	}
	configuration->AppSettings->Settings->Add(propertyName, propertyValue);
	configuration->Save();
}

bool ConfigurationService::CompareKeys(System::String^ key)
{
	return key == keyToCompareWith;
}
