#pragma once
class ISaveable
{
public:
	virtual void Save(const string file_name) = 0;
};

