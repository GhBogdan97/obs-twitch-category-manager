#pragma once
#include <wtypes.h>
ref class ProcessModel
{
public:
	ProcessModel(System::String^ name, System::String^ windowName, int id, int parentProcessId);
	ProcessModel();
	static bool ProcessModel::operator<(ProcessModel^ pm1, ProcessModel^ pm2);
	static bool ProcessModel::operator==(ProcessModel^ pm1, ProcessModel^ pm2);
	~ProcessModel();

	System::String^ name;
	System::String^ windowName;
	int id;
	int parentId;
private:
	;
};