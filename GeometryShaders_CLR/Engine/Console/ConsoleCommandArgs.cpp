#include "ConsoleCommandArgs.hpp"
#include <algorithm>
ConsoleCommandArgs* m_consoleArgs = NULL;

//===================================================================================================
//               class ConsoleCommandArgs                                                               ==
//===================================================================================================
ConsoleCommandArgs::ConsoleCommandArgs(const std::string & argument_string)
	: m_arg_string(argument_string)
{
	PrepareString();
}


//----------------------------------------------------------------------------------------------
int ConsoleCommandArgs::GetArgumentCount()
{
	std::string chop = m_arg_string;
	chop.erase(0, chop.find("(") + 1);

	int args = 0;
	for (unsigned int i = 0; i < chop.length(); i++)
	{
		if (chop[i] == ',')
		{
			++args;
		}
		if (chop[i] == ')')
		{
			++args;
			break;
		}
	}
	return args;
	;
}


//----------------------------------------------------------------------------------------------
int ConsoleCommandArgs::GetArgumentCountSpaces()
{
	std::string chop = m_arg_string;
	if (chop.length() == 0)
		return 0;

	int args = 0;
	for (unsigned int i = 0; i < chop.length(); i++)
	{
		if (chop[i] == ' ')
		{
			++args;
		}
	}

	if (chop.length() != 0 && args == 0) //There is data, but no spaces. Always 1
		return 1;
	else
		return args + 1;

	;
}


//----------------------------------------------------------------------------------------------
int ConsoleCommandArgs::GetArgumentQuotes()
{
	std::string chop = m_arg_string;
	chop.erase(0, chop.find(" ") + 1);

	int args = 0;
	for (unsigned int i = 0; i < chop.length(); i++)
	{
		if (chop[i] == '"')
		{
			++args;
		}
	}
	return (int)floor(args * .5);
	;
}


//----------------------------------------------------------------------------------------------
void ConsoleCommandArgs::PrepareString()
{
	m_arg_string.erase(0, m_arg_string.find("(") + 1);
}


//----------------------------------------------------------------------------------------------
std::string ConsoleCommandArgs::GetNextString()
{
	std::string token;
	token = m_arg_string.substr(0, m_arg_string.find_first_of(" "));
	m_arg_string.erase(0, m_arg_string.find(" ") + 1);
	return  (std::string)token;
}


//----------------------------------------------------------------------------------------------
std::string ConsoleCommandArgs::GetNextStringQuoted()
{
	std::string token;
	token = m_arg_string.substr(0, m_arg_string.find_first_of("'"));
	m_arg_string.erase(0, m_arg_string.find("'") + 1);
	return  (std::string)token;
}


//----------------------------------------------------------------------------------------------
std::string ConsoleCommandArgs::GetArgument()
{
	std::string out = m_arg_string;
	//out.erase(std::remove(out.begin(), out.end(), " "), out.end());
	out.erase(std::remove(out.begin(), out.end(), ')'), out.end());
	//ERROR?
	return out;
}


//----------------------------------------------------------------------------------------------
float ConsoleCommandArgs::GetNextFloat()
{
	float token;
	token = stof(m_arg_string.substr(0, m_arg_string.find_first_of(",")));
	m_arg_string.erase(0, m_arg_string.find(",") + 1);
	return  (float)token;
}


int ConsoleCommandArgs::GetNextInt()
{
	int token;
	token = stoi(m_arg_string.substr(0, m_arg_string.find_first_of(",")));
	m_arg_string.erase(0, m_arg_string.find(",") + 1);
	return  (int)token;
}

char ConsoleCommandArgs::GetNextChar()
{
	int token;
	token = stoi(m_arg_string.substr(0, m_arg_string.find_first_of(" ")));
	m_arg_string.erase(0, m_arg_string.find(" ") + 1);
	return  (char)token;
}