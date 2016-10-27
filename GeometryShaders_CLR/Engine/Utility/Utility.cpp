//================================================================
//                     Utility.cpp
//================================================================
#include "Engine/Utility/Utility.hpp"

//================================================================
//================================================================
BinaryBufferParser::BinaryBufferParser()
	:m_currentIndex(0)
{
}
BinaryBufferParser::BinaryBufferParser(const unsigned char* buffer, size_t size)
	:m_bufferB(buffer)
	,m_bufferSize(size)
	,m_currentIndex(0)
{
}
BinaryBufferParser::BinaryBufferParser(const std::vector<unsigned char>& bytes)
{
	UNUSED(bytes);
}
BinaryBufferParser::~BinaryBufferParser()
{
}

int				BinaryBufferParser::ReadNextInt()
{
 	int i = *(int*)(&m_buffer[m_currentIndex]);
 	m_currentIndex += sizeof(int);
 	return i; 
}
unsigned int	BinaryBufferParser::ReadNextUnsignedInt()
{
	unsigned int ui = *(unsigned int*)(&m_buffer[m_currentIndex]);
	m_currentIndex += sizeof(unsigned int);
	return ui; 
}
char			BinaryBufferParser::ReadNextChar()
{
	char c = *(char*)(&m_buffer[m_currentIndex]);
	m_currentIndex += sizeof(char);
	return c; 
}
unsigned char	BinaryBufferParser::ReadNextUnsignedChar()
{
	unsigned char uc = *(unsigned char*)(&m_buffer[m_currentIndex]);
	m_currentIndex += sizeof(unsigned char);
	return uc; 
}
short			BinaryBufferParser::ReadNextShort()
{
	short s = *(short*)(&m_buffer[m_currentIndex]);
	m_currentIndex += sizeof(short);
	return s; 
}
unsigned short	BinaryBufferParser::ReadNextUnsignedShort()
{
	unsigned short us = *(unsigned short*)(&m_buffer[m_currentIndex]);
	m_currentIndex += sizeof(unsigned short);
	return us; 
}
float			BinaryBufferParser::ReadNextFloat()
{
	float f = *(float*)(&m_buffer[m_currentIndex]);
	m_currentIndex += sizeof(float);
	return f; 
}
double			BinaryBufferParser::ReadNextDouble()
{
	double d = *(double*)(&m_buffer[m_currentIndex]);
	m_currentIndex += sizeof(double);
	return d; 
}
bool			BinaryBufferParser::ReadNextBool()
{
	bool b = *(bool*)(&m_buffer[m_currentIndex]);
	m_currentIndex += sizeof(bool);
	return b; 
}
std::string		BinaryBufferParser::ReadNextString()
{
	std::string nextString = "";
	unsigned char nextChar;
	nextChar = ReadNextUnsignedChar();
	nextString += nextChar;
	while (nextChar != '\0')
	{
		nextChar = ReadNextUnsignedChar();
		nextString += nextChar;
	}
	return nextString;
}

Vector2			BinaryBufferParser::ReadNextVector2()
{
	Vector2 nextVector2;
	nextVector2.x = ReadNextFloat();
	nextVector2.y = ReadNextFloat();
	return nextVector2;
}
Vector3			BinaryBufferParser::ReadNextVector3()
{
	Vector3 nextVector3;
	nextVector3.x = ReadNextFloat();
	nextVector3.y = ReadNextFloat();
	nextVector3.z = ReadNextFloat();
	return nextVector3;
}
Vector4			BinaryBufferParser::ReadNextVector4()
{
	Vector4 nextVector4;
	nextVector4.x = ReadNextFloat();
	nextVector4.y = ReadNextFloat();
	nextVector4.z = ReadNextFloat();
	nextVector4.w = ReadNextFloat();
	return nextVector4; 
}

Matrix4x4		BinaryBufferParser::ReadNextMatrix4x4()
{
	Matrix4x4 m4 = *(Matrix4x4*)(&m_buffer[m_currentIndex]);
	m_currentIndex += sizeof(Matrix4x4);
	return m4; 
}
Rgba			BinaryBufferParser::ReadNextRGBA()
{
	Rgba color;
	color.r = ReadNextUnsignedChar();
	color.g = ReadNextUnsignedChar();
	color.b = ReadNextUnsignedChar();
	color.a = ReadNextUnsignedChar();
	return color;
}
vert_t			BinaryBufferParser::ReadNextTriangleVertex()
{
	vert_t nextVert;
	//check if valid or not
		
	nextVert.m_position = ReadNextVector3();
	nextVert.m_color = ReadNextRGBA();
	nextVert.m_uv = ReadNextVector2();
	nextVert.m_norm = ReadNextVector3();
	nextVert.m_tang = ReadNextVector3();
	nextVert.m_bitang = ReadNextVector3();
	return nextVert;
}
vert_s			BinaryBufferParser::ReadNextSkeletalVertex()
{
	vert_s nextVert;
	//check if valid or not

	nextVert.m_position = ReadNextVector3();
	nextVert.m_color = ReadNextRGBA();
	nextVert.m_uv = ReadNextVector2();
	nextVert.m_normal = ReadNextVector3();
	nextVert.m_tangent = ReadNextVector3();
	nextVert.m_bitangent = ReadNextVector3();
	return nextVert;
}

//================================================================
//================================================================
BinaryFileParser::BinaryFileParser()
{
}
BinaryFileParser::BinaryFileParser(const std::string& filePath)
{
	//m_bufferB = LoadBinaryFileToNewBuffer(filePath, m_bufferSize);
	LoadBinaryFileToNewBufferVector(filePath, m_buffer);
	m_bufferSize= m_buffer.size();
	//m_bufferS = LoadTextFileToNewStringBuffer(filePath, m_bufferSize);
}
BinaryFileParser::~BinaryFileParser()
{
// 	if(m_bufferB != NULL)
// 		delete m_bufferB;
// 	if(m_bufferS != NULL)
// 		delete m_bufferS;
}

//================================================================
//================================================================
BinaryBufferBuilder::BinaryBufferBuilder()
{

}
BinaryBufferBuilder::BinaryBufferBuilder(const size_t& size)
{
	m_builderBuffer.reserve(size); 
}
BinaryBufferBuilder::~BinaryBufferBuilder()
{
}

void BinaryBufferBuilder::AppendInt(const int& i)
{
	AppendBuffer(i);
}
void BinaryBufferBuilder::AppendChar(const char& c)
{
	AppendBuffer(c);
}
void BinaryBufferBuilder::AppendUnsignedChar(const unsigned char& uc)
{
	AppendBuffer(uc);
}	 
void BinaryBufferBuilder::AppendShort(const short& s)
{
	AppendBuffer(s);
}	 
void BinaryBufferBuilder::AppendUnsignedShort(const unsigned short& us)
{
	AppendBuffer(us);
}	 
void BinaryBufferBuilder::AppendFloat(const float& f)
{
	AppendBuffer(f);
}
void BinaryBufferBuilder::AppendDouble(const double& d)
{
	AppendBuffer(d);
}	 
void BinaryBufferBuilder::AppendBool(const bool& b)
{
	AppendBuffer(b);
}
void BinaryBufferBuilder::AppendString(const std::string& str)
{
	UNUSED(str);
	//AppendBuffer(str);
//DANGER USE LENGTH instead of size of
}	 
void BinaryBufferBuilder::AppendVector2(const Vector2& v2)
{
	AppendBuffer(v2);
}	 
void BinaryBufferBuilder::AppendVector3(const Vector3& v3)
{
	AppendBuffer(v3);
} 
void BinaryBufferBuilder::AppendVector4(const Vector4& v4)
{
	AppendBuffer(v4);
}	 
void BinaryBufferBuilder::AppendMatrix4x4(const Matrix4x4& m4)
{
	AppendBuffer(m4);
}	 
void BinaryBufferBuilder::AppendBuffer(void* location, size_t numBytes)
{
	unsigned char* loc = (unsigned char*)location;
	for(unsigned char i = 0; i < numBytes; i++)
	{
		m_builderBuffer.push_back(*loc);
		loc++;
	}
}
void BinaryBufferBuilder::WriteToFile(const std::string& filePath)
{
	FILE* file = nullptr;
	fopen_s( &file, filePath.c_str(), "wb" );
	fwrite( &m_builderBuffer[0], sizeof(char), m_builderBuffer.size(), file );
	fclose (file);
}

//################################################################################################//
//##                                                                                            ##//
//################################################################################################//
bool 	LoadBinaryFileToNewBuffer( const std::string& filePath, size_t& out_bufferSize, unsigned char*& out_buffer )
{
	//Open File
	FILE* file = nullptr;
	fopen_s( &file, filePath.c_str(), "rb" );
	if( !file )
	{
		std::string error = "Bad File Path: " + filePath;
		MessageBoxA( NULL, error.c_str(), "Loading File Error", MB_OK );
		return false;
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
	out_buffer = buffer;
	return true;
}

bool WriteBinaryBufferToFile(std::string& filePath, size_t bufferSize, unsigned char* bufferData)
{
	FILE* file = nullptr;
	errno_t error = fopen_s( &file, filePath.c_str(), "wb" );
	if( error )
		return false;

	fwrite( bufferData, 1, bufferSize, file );
	fclose( file );
	return true;
}

std::wstring ToWideString(const std::string& str)
{
	int stringLength = MultiByteToWideChar(CP_ACP, 0, str.data(), str.length(), 0, 0);
	std::wstring wstr(stringLength, 0);
	MultiByteToWideChar(CP_ACP, 0,  str.data(), str.length(), &wstr[0], stringLength);
	return wstr;
}

