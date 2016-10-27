#include "Engine/Renderer/ModelLoader/ModelLoader.hpp"



//===================================================================================================
//				class ModelLoader																   ==
//===================================================================================================
ModelLoader::ModelLoader()
{
}
ModelLoader::ModelLoader(const std::string& fileName, const std::string& specialShaderName, const BufferType& bufferType)
{
	CreateModelShader(specialShaderName);

	LoadTexturesIntoModelSampler(fileName);

	CreateModelMesh("../Run_Win32/data/model/" + fileName + "/" + fileName + ".c23", bufferType);

	CreateModelRenderer(bufferType);
}



//===================================================================================================
void ModelLoader::CreateModelShader(const std::string& specialShaderName)
{
	if(specialShaderName != "")
		m_modelShader = Shader("../Run_Win32/shaders/model", "../Run_Win32/shaders/" + specialShaderName, "../Run_Win32/shaders/model");
	else
		m_modelShader = Shader("../Run_Win32/shaders/model",  "../Run_Win32/shaders/model");
}
void ModelLoader::LoadTexturesIntoModelSampler(const std::string& fileName)
{
 	Texture* diffuse = Texture::CreateOrGetTexture("../Run_Win32/data/model/" + fileName + "/" + fileName + "_diffuse.png");
	if(diffuse != nullptr)
		m_modelSampler.SetDiffuse(Texture::CreateOrGetTexture("../Run_Win32/data/model/" + fileName + "/" + fileName + "_diffuse.png"));

	Texture* specular = Texture::CreateOrGetTexture("../Run_Win32/data/model/" + fileName + "/" + fileName + "_normal.png");
	if(specular !=  nullptr)
		m_modelSampler.SetNormal( specular );

	m_modelMaterial = Material(m_modelShader, m_modelSampler);
	UNUSED(fileName);
}
void ModelLoader::CreateModelMesh(const std::string& filePath, const BufferType& bufferType)
{
	BinaryFileParser modelParser( filePath );


	std::string GC23;
	GC23.resize(4);
	GC23[0] = modelParser.ReadNextUnsignedChar();
	GC23[1] = modelParser.ReadNextUnsignedChar();
	GC23[2] = modelParser.ReadNextUnsignedChar();
	GC23[3] = modelParser.ReadNextUnsignedChar();
	unsigned char subtype = modelParser.ReadNextUnsignedChar();
	unsigned char version = modelParser.ReadNextUnsignedChar();
	std::string comment = modelParser.ReadNextString();
	ConsolePrintf("Magic Number: %c%c%c%c \n", GC23[0], GC23[1], GC23[2], GC23[3]);
	ConsolePrintf("Subtype: %u \n", subtype);
	ConsolePrintf("Version: %u \n", version);
	ConsolePrintf("Comment: %s \n", comment);


	//===================================================================================================
	if (GC23 != "GC23")	{
		vert_t verts[] = {vert_t( Vector3( 0.0f,  0.0f,  0.0f    ), Vector2(0.0f, 0.0f), Vector3(0.0f, 0.0f,  0.0f ))};
		m_modelMesh = Mesh(verts, 1);
		ConsolePrintf("Wrong Magic Number \n", NULL);
		MessageBoxA( NULL, "Imported Model Incompatible (.C23)", "Magic Number Error", MB_OK);
		return;
	}


	//===================================================================================================
	if(subtype == 2)
	{
		vert_t* verts = nullptr;

		//Get number of vertex's
		unsigned int numVerts = modelParser.ReadNextUnsignedInt();
		verts = new vert_t[numVerts];

		//Get vertex
		for(unsigned int i = 0; i < numVerts; i++)
			verts[i] = modelParser.ReadNextTriangleVertex();

		//Get VBO Data
		if(bufferType == VBO)
			m_modelMesh = Mesh(verts, numVerts, 0, 0); 
		m_modelMesh.GLCheckError(__FILE__,  __LINE__ -1);

		//Get Index Data
		if(bufferType == IBO)
		{
			unsigned int totalNumberOfIndexs = modelParser.ReadNextUnsignedInt();
			unsigned int* indexNumber;
			indexNumber = new unsigned int[totalNumberOfIndexs];
			for(unsigned int i = 0; i < totalNumberOfIndexs; i++)
				indexNumber[i] = modelParser.ReadNextUnsignedInt();

			m_modelMesh = Mesh(verts, numVerts, indexNumber, totalNumberOfIndexs  ); 
			m_modelMesh.GLCheckError(__FILE__,  __LINE__ -1);
		}
	}

	//===================================================================================================
	if(subtype == 4)
	{
		vert_s* verts = nullptr;

		//Get number of bones
		unsigned char numBones = modelParser.ReadNextUnsignedChar();

		//Get bone transforms
		Matrix4x4* boneTransforms;
		boneTransforms = new Matrix4x4[numBones];
		for(unsigned int index = 0; index < numBones; index++)
 			boneTransforms[index] = modelParser.ReadNextMatrix4x4();

		//Get number of vertex's
		unsigned int numVerts = modelParser.ReadNextUnsignedInt();
		verts = new vert_s[numVerts];

		//Get vertex
		for(unsigned int i = 0; i < numVerts; i++)
			verts[i] = modelParser.ReadNextSkeletalVertex();

		//Get VBO Data
		if(bufferType == VBO)
			m_modelMesh = Mesh(verts, numVerts, 0, 0); 
		m_modelMesh.GLCheckError(__FILE__,  __LINE__ -1);
 
		//Get Index Data
		if(bufferType == IBO)
		{
			unsigned int totalNumberOfIndexs = modelParser.ReadNextUnsignedInt();
			unsigned int* indexNumber;
			indexNumber = new unsigned int[totalNumberOfIndexs];
			for(unsigned int i = 0; i < totalNumberOfIndexs; i++)
				indexNumber[i] = modelParser.ReadNextUnsignedInt();

 		//	m_modelMesh = Mesh(verts, numVerts, indexNumber, totalNumberOfIndexs, numBones, boneTransforms ); 
 			m_modelMesh.GLCheckError(__FILE__,  __LINE__ -1);
 		}
	}
}
void ModelLoader::CreateModelRenderer(BufferType bufferType)
{
	m_modelRenderer = MeshRenderer(m_modelMesh, m_modelMaterial, bufferType);
}


