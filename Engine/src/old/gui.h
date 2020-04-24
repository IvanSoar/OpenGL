#pragma once

class UserInterface
{
public:
	UserInterface(const UserInterface&) = delete;

	static UserInterface& Get()
	{
		static UserInterface instance;
		return instance;
	}
private:
	UserInterface() {}
};