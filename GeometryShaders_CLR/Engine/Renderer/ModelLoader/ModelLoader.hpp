#pragma once
#ifndef _INCLUDE_MODEL_LOADER
#define _INCLUDE_MODEL_LOADER_
#include "Engine/Utility/Utility.hpp"
#include "Engine/Renderer/Shader/Material.hpp"
#include "Engine/Renderer/Shader/Mesh.hpp"
#include "Engine/Renderer/Shader/MaterialDependants/Shader.hpp"
#include "Engine/Renderer/Shader/MeshRenderer.hpp"



//===================================================================================================
//			class ModelLoader																	   ==
//===================================================================================================
class ModelLoader
{
public:
	ModelLoader();
	ModelLoader(const std::string& fileName, const std::string& specialShaderName = "", const BufferType& bufferType = VBO);



	void CreateModelShader(const std::string& specialShaderName);
	void LoadTexturesIntoModelSampler(const std::string& fileName);
	void CreateModelMesh(const std::string& fileName, const BufferType& bufferType);
	void CreateModelRenderer(BufferType bufferType);

	Mesh GetModelMesh()		{return m_modelMesh;}
	MeshRenderer m_modelRenderer;
	Mesh		 m_modelMesh;
private:
	Sampler		 m_modelSampler;
	Shader		 m_modelShader;
	Material	 m_modelMaterial;
};
#endif