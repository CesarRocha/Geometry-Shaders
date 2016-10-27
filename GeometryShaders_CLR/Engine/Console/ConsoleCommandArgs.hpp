#pragma once
#ifndef _ConsoleCommandArgs_
#define _ConsoleCommandArgs_
#include <string>

struct ConsoleCommandArgs
{
public:
	ConsoleCommandArgs(const std::string& argument_string);

	int GetArgumentCount();
	int GetArgumentCountSpaces();
	int GetArgumentQuotes();
	void PrepareString();
	std::string GetNextString();
	std::string GetNextStringQuoted();
	std::string GetArgument();
	float GetNextFloat();

	char GetNextChar();

	short GetNextShort();
	bool NextIsString();
	bool NextIsInt();
	int GetNextInt();
	bool NextIsFloat();
	bool NextIsBoolean();
	bool GetNextBoolean();


	std::string m_arg_string;
private:
};
extern ConsoleCommandArgs* m_consoleArgs;
typedef void(*command_callback) (ConsoleCommandArgs &args);


#endif // !_ConsoleCommandArgs_
