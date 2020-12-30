#pragma once
#include <string>
#include "Constants.h"
using namespace System::Configuration;
using namespace System::Collections;

ref class ConfigurationService
{
public:
	ConfigurationService();
	System::String^ GetProperty(System::String^ propertyName);
	void SaveConfigProperty(System::String^ propertyName, System::String^ propertyValue);

private:
	static System::Configuration::Configuration^ configuration;
	System::String^ keyToCompareWith;
	bool CompareKeys(System::String^ key);
};

