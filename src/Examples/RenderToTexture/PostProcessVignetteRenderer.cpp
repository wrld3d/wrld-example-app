// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#include "VectorMath.h"
#include "RenderToTextureExample.h"
#include "TimeHelpers.h"
#include "RenderContext.h"
#include "GLState.h"
#include "ShaderCompiler.h"
#include "PostProcessVignetteRenderer.h"

using namespace Examples;

PostProcessVignetteRenderer::PostProcessVignetteRenderer(Eegeo::Rendering::RenderContext& renderContext)
:m_renderContext(renderContext)
{
	CompileShaders();
	BuildGeometry();
}

PostProcessVignetteRenderer::~PostProcessVignetteRenderer()
{
	Eegeo_GL(glDeleteBuffers(1, &m_glVertexBuffer));
	Eegeo_GL(glDeleteBuffers(1, &m_glIndexBuffer));
    
	m_glVertexBuffer = 0;
	m_glIndexBuffer = 0;
}

std::string PostProcessVignetteRenderer::VertexShader()
{
	return
    "attribute vec2 pos;\n"
    "attribute mediump vec2 uv;\n"
    "varying mediump vec2 DestinationUV;\n"
    "void main(void) { \n"
    "DestinationUV = uv;\n"
    "gl_Position = vec4(pos.xy, 0.0, 1.0);\n"
    "}";
}

std::string PostProcessVignetteRenderer::FragmentShader()
{
	return
    "varying mediump vec2 DestinationUV;\n"
    "uniform sampler2D diffuseTex; \n"
    "void main(void) { \n"
    "highp vec4 colour = texture2D(diffuseTex, DestinationUV.xy); \n"
    "highp float greyscale = dot(colour.rgb, vec3(0.3, 0.59, 0.11)); \n"
    "highp vec2 d = DestinationUV.xy - 0.5;\n"
    "highp float vignetteRadiusModifier = 3.6; \n"
    "colour.rgb = greyscale * vec3(0.9, 0.8, 0.6) * (1.0 - dot(d, d) * vignetteRadiusModifier); \n"
    "gl_FragColor = vec4(colour.rgb, 1.0); \n"
    "}";
}

void PostProcessVignetteRenderer::CompileShaders()
{
	std::string vertexShaderCode = VertexShader();
	std::string fragmentShaderCode = FragmentShader();
    
	GLuint vertexShader = Eegeo::Helpers::ShaderCompiler::CompileShader(vertexShaderCode, GL_VERTEX_SHADER);
	GLuint fragmentShader = Eegeo::Helpers::ShaderCompiler::CompileShader(fragmentShaderCode, GL_FRAGMENT_SHADER);
    
	m_shader.m_programHandle = glCreateProgram();
	glAttachShader(m_shader.m_programHandle, vertexShader);
	glAttachShader(m_shader.m_programHandle, fragmentShader);
	glLinkProgram(m_shader.m_programHandle);
    
	GLint linkSuccess;
	glGetProgramiv(m_shader.m_programHandle, GL_LINK_STATUS, &linkSuccess);
	if (linkSuccess == GL_FALSE)
	{
		GLchar messages[256];
		glGetProgramInfoLog(m_shader.m_programHandle, sizeof(messages), 0, &messages[0]);
		Eegeo_TTY("%s\n", &messages[0]);
		return;
	}
    
	Eegeo_GL(glUseProgram(m_shader.m_programHandle));
    
    Eegeo_GL(m_shader.m_positionSlot = glGetAttribLocation(m_shader.m_programHandle, "pos"));
    Eegeo_GL(m_shader.m_uvSlot = glGetAttribLocation(m_shader.m_programHandle, "uv"));
    Eegeo_GL(m_shader.m_samplerSlot = glGetUniformLocation(m_shader.m_programHandle, "diffuseTex"));
}

void PostProcessVignetteRenderer::BuildGeometry()
{
    const int NumVerts = 4;
    const int NumIndices = 6;
    
	PostProcessVignetteVertex vertexBuffer[NumVerts];
	u16 indexBuffer[NumIndices];
    
    vertexBuffer[0].m_x = -1.f;
    vertexBuffer[0].m_y = 1.f;
    vertexBuffer[0].m_u = 0.f;
    vertexBuffer[0].m_v = 1.f;
    
    vertexBuffer[1].m_x = 1.f;
    vertexBuffer[1].m_y = 1.f;
    vertexBuffer[1].m_u = 1.f;
    vertexBuffer[1].m_v = 1.f;
    
    vertexBuffer[2].m_x = -1.f;
    vertexBuffer[2].m_y = -1.f;
    vertexBuffer[2].m_u = 0.f;
    vertexBuffer[2].m_v = 0.f;
    
    vertexBuffer[3].m_x = 1.f;
    vertexBuffer[3].m_y = -1.f;
    vertexBuffer[3].m_u = 1.f;
    vertexBuffer[3].m_v = 0.f;
    
	indexBuffer[0] = 0;
	indexBuffer[1] = 1;
	indexBuffer[2] = 2;
    
	indexBuffer[3] = 1;
	indexBuffer[4] = 3;
	indexBuffer[5] = 2;
	
	Eegeo_GL(glGenBuffers(1, &m_glVertexBuffer));
	Eegeo_GL(glBindBuffer(GL_ARRAY_BUFFER, m_glVertexBuffer));
	Eegeo_GL(glBufferData(GL_ARRAY_BUFFER, (sizeof(PostProcessVignetteVertex) * NumVerts), vertexBuffer, GL_STATIC_DRAW));
	Eegeo_GL(glBindBuffer (GL_ARRAY_BUFFER, 0));
    
	Eegeo_GL(glGenBuffers(1, &m_glIndexBuffer));
	Eegeo_GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_glIndexBuffer));
	Eegeo_GL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, (sizeof(u16) * NumIndices), indexBuffer, GL_STATIC_DRAW));
	Eegeo_GL(glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, 0));
}

void PostProcessVignetteRenderer::Draw(unsigned textureId)
{
	Eegeo_GL(glUseProgram(m_shader.m_programHandle));
    
    Eegeo::Rendering::GLState& glState = m_renderContext.GetGLState();
    
    bool repeatTexture = false;
    Eegeo::Rendering::TextureMinifyType textureMinifyType = Eegeo::Rendering::TextureMinify_Nearest;
    Eegeo::Helpers::GLHelpers::BindTexture2D(glState, m_shader.m_samplerSlot, textureId, textureMinifyType, repeatTexture);
    
	Eegeo_GL(glEnableVertexAttribArray(m_shader.m_positionSlot));
	Eegeo_GL(glEnableVertexAttribArray(m_shader.m_uvSlot));
    
	Eegeo_GL(glBindBuffer(GL_ARRAY_BUFFER, m_glVertexBuffer));
	Eegeo_GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_glIndexBuffer));
    
	Eegeo_GL(glVertexAttribPointer(m_shader.m_positionSlot, 2, GL_FLOAT, GL_FALSE, sizeof(PostProcessVignetteVertex), 0));
	Eegeo_GL(glVertexAttribPointer(m_shader.m_uvSlot, 2, GL_FLOAT, GL_FALSE, sizeof(PostProcessVignetteVertex), (GLvoid*) (sizeof(float) * 2)));
    
    Eegeo_GL(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, 0));
    
	Eegeo_GL(glBindBuffer(GL_ARRAY_BUFFER, 0));
	Eegeo_GL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
}
