#include "Engine/Renderer/Shader/MeshRenderer.hpp"


//===================================================================================================
//               class MeshRenderer                                                                ==
//===================================================================================================
MeshRenderer::MeshRenderer()
{
}
MeshRenderer::MeshRenderer(Mesh mesh, Material material, BufferType bufferType)
	:m_fogStartDistance(100)
	,m_fogEndDistance(200)
	,m_fogColorAndIntensity(Vector3( 0.1f, 0.1f, 0.1f))
	,m_bufferType(bufferType)
	,m_VBO(NULL)
	,m_IBO(NULL)
	,m_startTime(0.0)
{
	m_mesh = mesh;
	GLCheckError(__FILE__,  __LINE__ -1);

	m_material = material;
	GLCheckError(__FILE__,  __LINE__ -1);

	m_VBO = CreateVAO(m_mesh.m_vboID);
	if(bufferType == IBO)
		m_IBO = CreateIBO(m_mesh.m_vboID);
}



//===================================================================================================
GLuint	MeshRenderer::CreateVAO(GLuint buffer_ID)
{
	GLuint vao_ID;
	glGenVertexArrays( 1, &vao_ID );
	if( vao_ID == NULL ){
		assert(0);
		return NULL;
	}
	GLCheckError(__FILE__,  __LINE__ -1);

	GLint max_attributes;
	glGetIntegerv( GL_MAX_VERTEX_ATTRIBS, &max_attributes );
	glBindVertexArray( vao_ID );
	glBindBuffer( GL_ARRAY_BUFFER, buffer_ID );
	GLCheckError(__FILE__,  __LINE__ -1);
	

	ProgramBindAttribute( m_material.m_shader.m_programID, "inPosition", 3, GL_FLOAT, GL_FALSE, sizeof(vert_t), offsetof(vert_t, m_position) );
	ProgramBindAttribute( m_material.m_shader.m_programID, "inUV0", 2, GL_FLOAT, GL_FALSE, sizeof(vert_t), offsetof(vert_t, m_uv) );
	ProgramBindAttribute( m_material.m_shader.m_programID, "inNormal", 3, GL_FLOAT, GL_FALSE, sizeof(vert_t), offsetof(vert_t, m_norm) );
	ProgramBindAttribute( m_material.m_shader.m_programID, "inTangent", 3, GL_FLOAT, GL_FALSE, sizeof(vert_t), offsetof(vert_t, m_tang) );
	ProgramBindAttribute( m_material.m_shader.m_programID, "inBiTangent", 3, GL_FLOAT, GL_FALSE, sizeof(vert_t), offsetof(vert_t, m_bitang) );
	ProgramBindAttribute( m_material.m_shader.m_programID, "inColor", 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(vert_t), offsetof(vert_t, m_color) );
	GLCheckError(__FILE__,  __LINE__ -1);
	glBindBuffer( GL_ARRAY_BUFFER, 0 );

	return vao_ID;
}
void	MeshRenderer::DestroyVAO(GLuint vao_ID)
{
	if( vao_ID != NULL)
		glDeleteVertexArrays( 1, &vao_ID );
}
GLuint	MeshRenderer::CreateIBO(GLuint buffer_ID)
{
	GLuint ibo_ID;
	glGenVertexArrays( 1, &ibo_ID );
	if( ibo_ID == NULL ){
		assert(0);
		return NULL;
	}
	GLCheckError(__FILE__,  __LINE__ -1);

	GLint max_attributes;
	glGetIntegerv( GL_MAX_VERTEX_ATTRIBS, &max_attributes );
	glBindVertexArray( ibo_ID );
	glBindBuffer( GL_ARRAY_BUFFER, buffer_ID );
	GLCheckError(__FILE__,  __LINE__ -1);


	ProgramBindAttribute( m_material.m_shader.m_programID, "inPosition", 3, GL_FLOAT, GL_FALSE, sizeof(vert_t), offsetof(vert_t, m_position) );
	ProgramBindAttribute( m_material.m_shader.m_programID, "inUV0", 2, GL_FLOAT, GL_FALSE, sizeof(vert_t), offsetof(vert_t, m_uv) );
	ProgramBindAttribute( m_material.m_shader.m_programID, "inNormal", 3, GL_FLOAT, GL_FALSE, sizeof(vert_t), offsetof(vert_t, m_norm) );
	ProgramBindAttribute( m_material.m_shader.m_programID, "inTangent", 3, GL_FLOAT, GL_FALSE, sizeof(vert_t), offsetof(vert_t, m_tang) );
	ProgramBindAttribute( m_material.m_shader.m_programID, "inBiTangent", 3, GL_FLOAT, GL_FALSE, sizeof(vert_t), offsetof(vert_t, m_bitang) );
	ProgramBindAttribute( m_material.m_shader.m_programID, "inColor", 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(vert_t), offsetof(vert_t, m_color) );
	GLCheckError(__FILE__,  __LINE__ -1);
	glBindBuffer( GL_ARRAY_BUFFER, 0 );

	return ibo_ID;
}
void	MeshRenderer::DestroyIBO(GLuint ibo_ID)
{
	if( ibo_ID != NULL)
		glDeleteVertexArrays( 1, &ibo_ID );
}



//===================================================================================================
bool	MeshRenderer::ProgramBindAttribute(GLuint program_ID, const char* inName, GLint count, GLenum shader_type, GLboolean normalize, GLsizei stride, GLsizei offset)
{
	GLint loc = glGetAttribLocation( program_ID, inName );
	GLCheckError(__FILE__,  __LINE__ -1);

	if( loc < 0 )
		return false;

	glEnableVertexAttribArray( loc );
	GLCheckError(__FILE__,  __LINE__ -1);

	glVertexAttribPointer( loc, count, shader_type, normalize, stride, (GLvoid*) offset );
	GLCheckError(__FILE__,  __LINE__ -1);

	return true;
}
void	MeshRenderer::ProgramBind( GLuint program_ID )
{
	glUseProgram(program_ID);
}
bool	MeshRenderer::ProgramBindFloat( GLuint program_ID, const char* name, const float& val)
{
	GLint loc = ProgramFindAndCheck( program_ID, name, GL_FLOAT);
	if(loc < 0)
		return false;

	glUniform1fv( loc, 1, &val);
	return true;
}
bool	MeshRenderer::ProgramBindMatrix( GLuint program_ID, const char* name, const Matrix4x4& matrix)
{
	GLint loc = glGetUniformLocation( program_ID, name );
	if( loc < 0 ) 
		return false;

	GLuint index;
	glGetUniformIndices( program_ID, 1, &name, &index );
	if( index >= 0 )
	{
		GLint count;
		GLenum type;
		glGetActiveUniform( program_ID, index, 0, NULL, &count, &type, NULL);
		assert( type == GL_FLOAT_MAT4 );
	}

	glUniformMatrix4fv( loc, 1, GL_FALSE, (GLfloat*)&matrix);////
	return true;
}
bool	MeshRenderer::ProgramBindSamplerIndex( GLuint program_ID, const char* name, GLint index)
{
	GLint loc = ProgramFindAndCheck( program_ID, name, GL_SAMPLER_2D );
	if(loc < 0 )
		return false;

	glUniform1iv( loc, 1, (GLint*)&index);
	return true;
}
bool	MeshRenderer::ProgramBindVec3( GLuint program_ID, const char* name, const Vector3& val)
{
	GLint loc = glGetUniformLocation( program_ID, name );
	if( loc < 0 ) 
		return false;

	glUniform3f( loc, val.x, val.y, val.z);
	return true;
}
bool	MeshRenderer::ProgramBindVec4( GLuint program_ID, const char* name, const Vector4& val)
{
	GLint loc = glGetUniformLocation( program_ID, name );
	if( loc < 0 ) 
		return false;

	glUniform4f( loc, val.x, val.y, val.z, val.w);
	return true;
}
GLuint	MeshRenderer::ProgramFindAndCheck( GLuint program_ID, const char* name, GLenum type)
{
	GLint loc = glGetUniformLocation( program_ID, name);
	if(loc < 0)
		return loc;

	GLuint index; 
	glGetUniformIndices( program_ID, 1, &name, &index );
	if(index >= 0)
	{
		GLint count;
		GLenum check_type;
		glGetActiveUniform( program_ID, index, 0, NULL, &count, &check_type, NULL);
		assert(type == check_type);
		if(type == check_type)
			return loc;
	}
	GLint i = -1;
	return  i;
}
void	MeshRenderer::GLCheckError(const std::string& file, int line)
{
#if defined(OPENGL_CHECK_ERRORS)
	GLenum error = glGetError();
	if(error != GL_NO_ERROR)
	{
		const GLubyte* errString;
		errString = gluErrorString(error);
		std::stringstream out;
		out << line;
		std::string header = "Shader Error";

		std::string message = file + "\n" + "Line: " + out.str() + "\n" + ConsolePrintf("0x%04x \n" , error) + (const char*)errString;

		MessageBoxA ( NULL, message.c_str(), header.c_str(), MB_OK | MB_ICONEXCLAMATION );
		if( error == 1282)
			g_programIsRunning = false;
	}
#endif

}



//===================================================================================================
void MeshRenderer::Render(const Matrix4x4& view, const Matrix4x4& projection, const Matrix4x4& model, const Vector3& cameraPosition, const double& deltaSeconds )
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_CULL_FACE);

	static float startTime = 0.0f;
	m_startTime += (float)deltaSeconds;


	ProgramBind( m_material.m_shader.m_programID );


	glBindVertexArray( m_VBO );
	if(m_bufferType == IBO)
		glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, m_IBO );


	//Time
	ProgramBindFloat(  m_material.m_shader.m_programID, "gTime", m_startTime );


	//MVP
	ProgramBindMatrix( m_material.m_shader.m_programID, "gModel",				model);
	ProgramBindMatrix( m_material.m_shader.m_programID, "gView",				view);
	ProgramBindMatrix( m_material.m_shader.m_programID, "gProj",				projection);
	ProgramBindVec3(   m_material.m_shader.m_programID, "gCameraPosition",		cameraPosition);


	//Lights
	BindLights();
	ProgramBindVec4(   m_material.m_shader.m_programID,	"gMaterialAmbientLight",m_material.m_materialAmbientLight);
	ProgramBindFloat(  m_material.m_shader.m_programID,	"gShininess",			m_material.m_shine );


	//Fog
	ProgramBindFloat(  m_material.m_shader.m_programID, "gFogStart",			m_fogStartDistance );
	ProgramBindFloat(  m_material.m_shader.m_programID, "gFogEnd",				m_fogEndDistance );
	ProgramBindVec3(   m_material.m_shader.m_programID, "gFogColor",			m_fogColorAndIntensity);


	//Textures
	BindDiffuse();
	BindNormal();
	BindSpecular();


	if(m_bufferType == GEOPOINT)
	{
		glDrawArrays(GL_POINTS, 0, m_mesh.m_vboVertCount);
		GLCheckError( __FILE__,  __LINE__ -1);
	}
	if(m_bufferType == GEOTRIANGLE)
	{
		glDrawArrays(GL_TRIANGLES, 0, m_mesh.m_vboVertCount);
		GLCheckError( __FILE__,  __LINE__ -1);
	}
	else if(m_bufferType == VBO)
	{
		glDrawArrays( GL_TRIANGLES, 0, m_mesh.m_vboVertCount);
		GLCheckError( __FILE__,  __LINE__ -1);
	}
	else if(m_bufferType == IBO)
	{
		glDrawElements( GL_TRIANGLES, m_mesh.m_iboIndexCount, GL_UNSIGNED_INT, nullptr);
		GLCheckError( __FILE__,  __LINE__ -1);
	}



	glBindVertexArray( NULL );
	glUseProgram(NULL);
	GLCheckError( __FILE__,  __LINE__ -1);
}
void MeshRenderer::BindLights()
{
	for(int i = 0; i < m_material.m_lightCount; i++)
	{				
		std::stringstream out;
		out << i;
		std::string LightPosition    =  "lights[" + out.str() + "].gLightPosition" ;	
		std::string LightColor		 = 	"lights[" + out.str() + "].gLightColor";	
		std::string LightIntensity	 =  "lights[" + out.str() + "].glightIntensity";
		std::string Direction		 = 	"lights[" + out.str() + "].gLightDirection";		
		std::string LightAmbient     =  "lights[" + out.str() + "].gLightAmbient";     
		std::string LightWeight		 =  "lights[" + out.str() + "].gLightWeight";		 
		std::string LightAngle		 =  "lights[" + out.str() + "].gLightAngle";		 
		std::string LightSpotPower	 =  "lights[" + out.str() + "].gLightSpotPower";	 
		std::string LightMinSf		 =  "lights[" + out.str() + "].gLightMinSf";		 
		std::string LightMinIntensity=  "lights[" + out.str() + "].gLightMinIntensity";
		std::string LightMaxIntensity=  "lights[" + out.str() + "].gLightMaxIntensity";

		ProgramBindVec3(   m_material.m_shader.m_programID,			LightPosition.c_str(),			m_material.m_lightArray[i].m_lightPosition);
		ProgramBindVec4(   m_material.m_shader.m_programID,			LightColor.c_str(),				Rgba::RgbaToVector4(m_material.m_lightArray[i].m_lightColor));
		ProgramBindFloat(  m_material.m_shader.m_programID,			LightIntensity.c_str(),			m_material.m_lightArray[i].m_lightIntensity);
		ProgramBindVec3(   m_material.m_shader.m_programID,			Direction.c_str(),				m_material.m_lightArray[i].m_lightDirection );

		ProgramBindFloat(   m_material.m_shader.m_programID,		LightAmbient.c_str(),      		m_material.m_lightArray[i].m_lightAmbient);
		ProgramBindFloat(   m_material.m_shader.m_programID,		LightWeight.c_str(),		  	m_material.m_lightArray[i].m_lightWeight); 
		ProgramBindFloat(   m_material.m_shader.m_programID,		LightAngle.c_str(),		  		m_material.m_lightArray[i].m_lightAngle);
		ProgramBindFloat(   m_material.m_shader.m_programID,		LightSpotPower.c_str(),	  		m_material.m_lightArray[i].m_lightSpotPower);
		ProgramBindFloat(   m_material.m_shader.m_programID,		LightMinSf.c_str(),		  		m_material.m_lightArray[i].m_lightMinSf);
		ProgramBindFloat(   m_material.m_shader.m_programID,		LightMinIntensity.c_str(), 		m_material.m_lightArray[i].m_lightMinIntensity );
		ProgramBindFloat(   m_material.m_shader.m_programID,		LightMaxIntensity.c_str(), 		m_material.m_lightArray[i].m_lightMaxIntensity );
	}

	ProgramBindVec3(   m_material.m_shader.m_programID,			"gLightPosition",			m_material.m_light.m_lightPosition);
	ProgramBindVec4(   m_material.m_shader.m_programID,			"gLightColor",				m_material.m_light.m_lightColor );
}
void MeshRenderer::BindDiffuse()
{	
	GLint  def_index  = 0;
	//Set Default if missing
	if(m_material.m_sampler.GetDiffuse() == NULL)	{
		unsigned char plainWhiteTexel[3] = {255, 255, 255};
		m_material.m_sampler.SetDiffuse(Texture::CreateMissingTexture("DefaultDiffuse", plainWhiteTexel, IntVector2(1,1), 3));
	}
	//Don't bind if missing
	if(m_material.m_sampler.GetDiffuse() != NULL)	{
		ProgramBindSamplerIndex( m_material.m_shader.m_programID, "gTexDiffuse", def_index);
		GLCheckError( __FILE__,  __LINE__ -1);
		glActiveTexture( GL_TEXTURE0 + def_index );

		glBindTexture( GL_TEXTURE_2D, m_material.m_sampler.GetDiffuse()->GetPlatformHandle());
		GLCheckError( __FILE__,  __LINE__ -1);

		glBindSampler( def_index, m_material.m_sampler.m_samplerID);
		GLCheckError( __FILE__,  __LINE__ -1);
		glDisable(GL_TEXTURE_2D);
	}
}
void MeshRenderer::BindNormal()
{
	GLint  norm_index = 1;

	//Set Default if missing
	if(m_material.m_sampler.GetNormal() == NULL)	{
		unsigned char lightBlueTexel[3] = {127, 127, 255};
		m_material.m_sampler.SetNormal(Texture::CreateMissingTexture("DefaultNormal", lightBlueTexel, IntVector2(1,1), 3));
	}
	//Don't bind if missing
	if(m_material.m_sampler.GetNormal() != NULL)	{
		ProgramBindSamplerIndex( m_material.m_shader.m_programID, "gTexNormal", norm_index);
		GLCheckError( __FILE__,  __LINE__ -1);
		glActiveTexture( GL_TEXTURE0 + norm_index );

		glBindTexture( GL_TEXTURE_2D, m_material.m_sampler.GetNormal()->GetPlatformHandle());
		GLCheckError( __FILE__,  __LINE__ -1);

		glBindSampler( norm_index, m_material.m_sampler.m_samplerID);
		GLCheckError( __FILE__,  __LINE__ -1); 
		glDisable(GL_TEXTURE_2D);
	}
}
void MeshRenderer::BindSpecular()
{
	GLint  spec_index = 2;

	//Set Default if missing
	if(m_material.m_sampler.GetSpecular() == NULL)	{
		unsigned char darkYellowTexel[3] = {127, 127, 0};
		m_material.m_sampler.SetSpecular(Texture::CreateMissingTexture("DefaultSpecular", darkYellowTexel, IntVector2(1,1), 3));
	}
	//Don't bind if missing
	if(m_material.m_sampler.GetSpecular() != NULL)	{
		ProgramBindSamplerIndex( m_material.m_shader.m_programID, "gTexSpecular", spec_index);
		GLCheckError( __FILE__,  __LINE__ -1);
		glActiveTexture( GL_TEXTURE0 + spec_index );

		glBindTexture( GL_TEXTURE_2D, m_material.m_sampler.GetSpecular()->GetPlatformHandle());
		GLCheckError( __FILE__,  __LINE__ -1);

		glBindSampler( spec_index, m_material.m_sampler.m_samplerID);
		GLCheckError( __FILE__,  __LINE__ -1);
		glDisable(GL_TEXTURE_2D);
	}
}