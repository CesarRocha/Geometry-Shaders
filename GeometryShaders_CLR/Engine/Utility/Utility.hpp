//================================================================
//                     Utility.hpp
//================================================================
#pragma once
#ifndef _INCLUDE_UTILITY_
#define _INCLUDE_UTILITY_
#define WINDOWS_LEAN_AND_MEAN
#include "Engine/EngineCommon/EngineCommon.hpp"
#include "Engine/Clock/Clock.hpp"
#include "Engine/Console/Console.hpp"
#include "Engine/Math/Vector2.hpp"
#include "Engine/Math/3D/Vector3.hpp"
#include "Engine/Math/3D/Vector4.hpp"
#include "Engine/Math/3D/Matrix4x4.hpp"
#include "AssertionMacros.hpp"
#include <stdio.h>
#include <string>
#include <vector>
#include <io.h>
#include <windows.h>


//===================================================================================================
static inline bool				DoesFileExist(const std::string* fileName)
{
	std::ifstream infile(fileName->c_str());
	return infile.good();
}

//===================================================================================================
static inline size_t			GetFileLength( FILE* fileHandle )
{
	fseek( fileHandle, 0, SEEK_END );
	size_t size = ftell ( fileHandle );
	fseek( fileHandle, 0, SEEK_SET );
	return size;
}

//===================================================================================================
static inline unsigned char*	LoadBinaryFileToNewBuffer( const std::string& filePath, size_t& out_bufferSize )
{
	//Open File
	FILE* file = nullptr;
	fopen_s( &file, filePath.c_str(), "rb" );
	if( !file )
	{
		std::string error = "Bad File Path: " + filePath;
		MessageBoxA( NULL, error.c_str(), "Loading File Error", MB_OK );
	}

	//Get Size of File
	size_t numBytes = GetFileLength( file );

	//Create Buffer
	unsigned char* buffer = new unsigned char[numBytes];
	

	//Read File
	size_t numBytesRead = fread( buffer, 1, numBytes, file );
	if (numBytesRead != numBytes)
		MessageBoxA( NULL, "Sizes do not match", "Loading File Error", MB_OK );

	//Close File
	fclose( file );

	//Return Buffer
	out_bufferSize = numBytesRead;
	return buffer;
}

//===================================================================================================
bool							LoadBinaryFileToNewBuffer( const std::string& filePath, size_t& out_bufferSize, unsigned char*& out_buffer );

//===================================================================================================
bool							WriteBinaryBufferToFile( std::string& filePath, size_t bufferSize, unsigned char* bufferData );

//===================================================================================================
static inline void				LoadBinaryFileToNewBufferVector(const std::string& filePath, std::vector<unsigned char>& m_buffer )
{
	//Open File
	FILE* file = nullptr;
	fopen_s( &file, filePath.c_str(), "rb" );
	if( !file )
	{
		std::string error = "Bad File Path: " + filePath;
		MessageBoxA( NULL, error.c_str(), "Loading File Error", MB_OK );
	}

	//Get Size of File
	size_t numBytes = GetFileLength( file );

	//Resize Vector
	m_buffer.resize(numBytes);


	//Read File
	fread( (char*)&m_buffer[0], 1, numBytes, file );

	//Close File
	fclose( file );
}

//===================================================================================================
static inline char*				LoadTextFileToNewStringBuffer( const std::string& filePath, size_t& out_bufferSize )
{
	//Open File
	FILE* file = nullptr;
	fopen_s( &file, filePath.c_str(), "rb" );
	if( !file )
	{
		std::string error = "Bad File Path: " + filePath;
		MessageBoxA( NULL, error.c_str(), "Loading File Error", MB_OK );
	}

	//Get Size of File
	size_t numBytes = GetFileLength( file );

	//Create Buffer
	char* buffer = new char[numBytes+1];

	//Read File
	size_t numBytesRead = fread( buffer, 1, numBytes, file );

	if (numBytesRead != numBytes)
		MessageBoxA( NULL, "Sizes do not match", "Loading File Error", MB_OK );

	//Close File
	fclose( file );

	//Return Buffer
	buffer[numBytes] = '\0';
	out_bufferSize = numBytesRead;
	return buffer;
}

//===================================================================================================
static inline bool				FindAllFilesOfType(const std::string& directory, const std::string& searchPattern, std::vector<std::string>& out_filesFound)
{
	//Implementation windows specific
	struct _finddata_t fd;
	std::string searchPath = directory + searchPattern;
	intptr_t searchHandle = _findfirst(  searchPath.c_str(), &fd);
	
	do
	{	
 		out_filesFound.push_back(directory + fd.name);
	}
	while (_findnext(searchHandle, &fd) == 0);
	_findclose(searchHandle);

	
	if(!out_filesFound.empty())
		return true;
	else 
		return false;
}


//===================================================================================================
static inline bool	FindAllFilesOfTypeInFolderAndSubFolder(const std::string& directory, const std::string& searchPattern, const std::string& filter ,std::vector<std::string>& out_filesFound)
{
	//Implementation windows specific
	struct _finddata_t fd;
	std::string searchPath = directory + searchPattern;
	intptr_t searchHandle = _findfirst(searchPath.c_str(), &fd);

	do
	{
		if(fd.name != std::string(".") && fd.name != std::string(".."))
		{
			//Go Deeper
			if ((fd.attrib & _A_SUBDIR) && (fd.name != std::string(".") && fd.name != std::string("..")))
			{
				std::string subDirectory = directory + fd.name + "/";
				FindAllFilesOfTypeInFolderAndSubFolder(subDirectory, searchPattern, filter, out_filesFound);
			}
			else
				out_filesFound.push_back(directory + fd.name);
			//Get IN Current Folder
			//FindAllFilesOfType(directory, filter, out_filesFound);
		}


	} while (_findnext(searchHandle, &fd) == 0);

	_findclose(searchHandle);


	if (!out_filesFound.empty())
		return true;
	else
		return false;
}

//===================================================================================================
static inline bool IsWhitespace( char c )
{
	switch (c) {
	case '\n':
	case '\r':
	case ' ':
	case '\t':
		return true;

	default:
		return false;
	};
}

//===================================================================================================
static inline char* Trim( char *s )
{
	while (IsWhitespace(*s)) 
		++s;

	char* end = s;
	while (*end != NULL) 
		++end;


	if (end > s) 
	{
		--end;
		while ((end > s) && IsWhitespace(*end)) 
		{
			--end;
		}

		++end;
		*end = NULL;
	}

	return s;
}

//===================================================================================================
std::wstring ToWideString(const std::string& str);

//################################################################################################//
//##                      Parser                                                                ##//
//################################################################################################//
class BinaryBufferParser
{
public:

	BinaryBufferParser();
	BinaryBufferParser(const unsigned char* buffer, size_t size);
	BinaryBufferParser(const std::vector<unsigned char>& bytes);
	~BinaryBufferParser();

	int				ReadNextInt();
	char			ReadNextChar(); 
	unsigned int	ReadNextUnsignedInt();
	unsigned char	ReadNextUnsignedChar();
	short			ReadNextShort();
	unsigned short	ReadNextUnsignedShort();
	float			ReadNextFloat();
	double			ReadNextDouble();
	bool			ReadNextBool();
	std::string		ReadNextString();
	Vector2			ReadNextVector2();
	Vector3			ReadNextVector3();
	Vector4			ReadNextVector4();
	Matrix4x4		ReadNextMatrix4x4();
	bool			HadReachedEndOfData();
	vert_t			ReadNextTriangleVertex();
	vert_s			ReadNextSkeletalVertex();
	Rgba			ReadNextRGBA();

	bool CanReadNextSizeofData(size_t size);

	size_t					m_bufferSize;
	const unsigned char*	m_bufferB;
	const char*				m_bufferS;

	std::vector<unsigned char> m_buffer;

	size_t					m_currentIndex;

private:
};
//===================================================================================================

class BinaryFileParser: public BinaryBufferParser
{
public:
	BinaryFileParser();
	BinaryFileParser(const std::string& filePath );
	~BinaryFileParser();
	

private:
};
//===================================================================================================

class BinaryBufferBuilder
{
public:
	BinaryBufferBuilder();
	BinaryBufferBuilder(const size_t& size);
	~BinaryBufferBuilder();

	void	AppendInt(const int& i);
	void	AppendUnsignedInt(const unsigned int& ui);
	void	AppendChar(const char& c); 
	void	AppendUnsignedChar(const unsigned char& uc);
	void	AppendShort(const short& s);
	void	AppendUnsignedShort(const unsigned short& us);
	void	AppendFloat(const float& f);
	void	AppendDouble(const double& d);
	void	AppendBool(const bool& b);
	void	AppendString(const std::string& str);
	void	AppendVector2(const Vector2& v2);
	void	AppendVector3(const Vector3& v3);
	void	AppendVector4(const Vector4& v4);
	void	AppendMatrix4x4(const Matrix4x4& m4);
	void	WriteToFile(const std::string& filePath);

	std::vector<unsigned char> m_builderBuffer;

private:
	template<typename T> void AppendBuffer(const T& location) {AppendBuffer((void* )& location, sizeof(T));}
	void AppendBuffer(void* location, size_t numBytes);
	
};



#endif