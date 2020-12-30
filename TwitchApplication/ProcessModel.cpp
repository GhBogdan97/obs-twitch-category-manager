#include"ProcessModel.h"


ProcessModel::ProcessModel(System::String^ processName, System::String^ wndName, int processId, int parentProcessId)
{
	name = processName;
	id = processId;
	parentId = parentProcessId;
	windowName = wndName;
}

ProcessModel::ProcessModel()
{
	name = nullptr;
	windowName = nullptr;
	id = 0;
	parentId = 0;
}

bool ProcessModel::operator<(ProcessModel^ pm1, ProcessModel^ pm2)
{
	return System::String::Compare(pm1->name, pm2->name);
}

bool ProcessModel::operator==(ProcessModel^ pm1, ProcessModel^ pm2)
{
	if (Object::ReferenceEquals(pm1, nullptr) && Object::ReferenceEquals(pm2, nullptr))
		return true;

	if (Object::ReferenceEquals(pm1, nullptr) || Object::ReferenceEquals(pm2, nullptr))
		return false;

	return pm1->name == pm2->name;
}

ProcessModel::~ProcessModel()
{
}