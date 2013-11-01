//
//  ModifiedRenderingExample.h
//  ExampleApp
//
//  Created by eeGeo on 03/05/2013.
//  Copyright (c) 2013 eeGeo. All rights reserved.
//

#ifndef __ExampleApp__ModifiedRenderingExample__
#define __ExampleApp__ModifiedRenderingExample__

#include "IExample.h"

#include <vector>
#include "RenderContext.h"
#include "MeshPool.h"
#include "RenderableItem.h"
#include "DiffuseTexturedMaterial.h"
#include "ShaderCompiler.h"
#include "GlobalLighting.h"
#include "Location.h"

namespace Examples
{
    struct MyShader
    {
        int PositionAttribute;
        int LightDotAttribute;
        int ModelViewProjectionUniform;
        int DiffuseColorUniform;
        int LightColorsUniform;
        int MinVertRangeUniform;
        int MaxVertRangeUniform;
        u32 ProgramHandle;
        
        MyShader()
        {
			std::string vertexShaderCode =
			"attribute highp vec3 Position;\n"
			"attribute highp float Lightdot;\n"
			"varying highp vec4 ColorVarying;\n"
			"uniform highp mat4 ModelViewProjectionMatrix;\n"
			"uniform highp mat4 LightColorMatrix;\n"
			"uniform highp vec4 DiffuseColor;\n"
			"uniform highp vec3 MinVertRange;\n"
			"uniform highp vec3 MaxVertRange;\n"
			"uniform highp vec2 MinUVRange;\n"
			"uniform highp vec2 MaxUVRange;\n"
			"void main(void) { \n"
			"highp vec3 dots = fract(vec3(Lightdot * 1.0, Lightdot * 256.0, Lightdot * 65536.0));"
			"ColorVarying = (LightColorMatrix * vec4(dots, 1.0)) * DiffuseColor;"
			"highp vec3 truePosition = mix(MinVertRange.xyz, MaxVertRange.xyz, Position.xyz);\n"
			"gl_Position = ModelViewProjectionMatrix * vec4(truePosition.xyz, 1.0);\n"
			"}";
            
            std::string fragmentShaderCode =
            "varying highp vec4 ColorVarying;\n"
            "void main(void) { \n"
            "gl_FragColor =  ColorVarying; \n"
            "}";

            GLuint vertexShader = Eegeo::Helpers::ShaderCompiler::CompileShader(vertexShaderCode, GL_VERTEX_SHADER);
            GLuint fragmentShader = Eegeo::Helpers::ShaderCompiler::CompileShader(fragmentShaderCode, GL_FRAGMENT_SHADER);
            
            ProgramHandle = glCreateProgram();
            glAttachShader(ProgramHandle, vertexShader);
            glAttachShader(ProgramHandle, fragmentShader);
            glLinkProgram(ProgramHandle);
            
            GLint linkSuccess;
            glGetProgramiv(ProgramHandle, GL_LINK_STATUS, &linkSuccess);
            if (linkSuccess == GL_FALSE)
            {
                GLchar messages[256];
                glGetProgramInfoLog(ProgramHandle, sizeof(messages), 0, &messages[0]);
                Eegeo_TTY("ERROR COMPILING SHADER :: %s", &messages[0]);
            }
            
            Eegeo_GL(glUseProgram(ProgramHandle));
            PositionAttribute = glGetAttribLocation(ProgramHandle, "Position");
            LightDotAttribute = glGetAttribLocation(ProgramHandle, "Lightdot");
            ModelViewProjectionUniform = glGetUniformLocation(ProgramHandle, "ModelViewProjectionMatrix");
            DiffuseColorUniform = glGetUniformLocation(ProgramHandle, "DiffuseColor");
            LightColorsUniform = glGetUniformLocation(ProgramHandle, "LightColorMatrix");
            MinVertRangeUniform = glGetUniformLocation(ProgramHandle, "MinVertRange");
            MaxVertRangeUniform = glGetUniformLocation(ProgramHandle, "MaxVertRange");
        }
    };
    
    class ModifiedRenderingExample : public IExample
    {
    private:
        struct MyPoolFilterCriteria : Eegeo::Resources::PoolFilterCriteria<Eegeo::Rendering::RenderableItem*>
        {
            ModifiedRenderingExample* owner;
        public:
            MyPoolFilterCriteria(ModifiedRenderingExample* owner):owner(owner) {}
            virtual bool operator()(Eegeo::Rendering::RenderableItem* item);
        };
        
        MyPoolFilterCriteria* pCriteria;
        MyShader shader;
        
        Eegeo::Rendering::RenderContext& renderContext;
        Eegeo::Camera::ICameraProvider& cameraProvider;
        Eegeo::Location::IInterestPointProvider& interestPointProvider;
        Eegeo::Lighting::GlobalLighting& lighting;
        Eegeo::Streaming::IStreamingVolume& visibleVolume;
        Eegeo::Resources::MeshPool<Eegeo::Rendering::RenderableItem*>& buildingPool;
        Eegeo::Resources::MeshPool<Eegeo::Rendering::RenderableItem*>& shadowPool;
        int counter;
        
        void DrawItems(const std::vector<Eegeo::Rendering::RenderableItem*>& items);
        
    public:
        ModifiedRenderingExample(Eegeo::Rendering::RenderContext& renderContext,
                                 Eegeo::Camera::ICameraProvider& cameraProvider,
                                 Eegeo::Location::IInterestPointProvider& interestPointProvider,
                                 Eegeo::Streaming::IStreamingVolume& visibleVolume,
                                 Eegeo::Lighting::GlobalLighting& lighting,
                                 Eegeo::Resources::MeshPool<Eegeo::Rendering::RenderableItem*>& buildingPool,
                                 Eegeo::Resources::MeshPool<Eegeo::Rendering::RenderableItem*>& shadowPool);
        
        void Start();
        void Update();
        void Draw();
        void Suspend();
    };
}

#endif /* defined(__ExampleApp__ModifiedRenderingExample__) */
