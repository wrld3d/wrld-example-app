// Copyright eeGeo Ltd 2016, All Rights Reserved

#include "LoadingScreenModule.h"
#include "ScreenProperties.h"
#include "LoadingScreenConfig.h"
#include "LoadingScreen.h"
#include "TextureNameHelpers.h"
#include "ShaderIdGenerator.h"
#include "MaterialIdGenerator.h"
#include "GlBufferPool.h"
#include "VertexLayoutPool.h"
#include "VertexBindingPool.h"
#include "ITextureFileLoader.h"

namespace ExampleApp
{
    void LoadingScreenModule::Register(const std::shared_ptr<Hypodermic::ContainerBuilder>& builder)
    {
        builder->registerInstanceFactory([](Hypodermic::ComponentContext& context)
                                         {
                                             const std::shared_ptr<Eegeo::Rendering::ScreenProperties>& screenProperties = context.resolve<Eegeo::Rendering::ScreenProperties>();
                                             
                                             Eegeo::Rendering::LoadingScreenConfig loadingScreenConfig;
                                             loadingScreenConfig.layout = Eegeo::Rendering::LoadingScreenLayout::Centred;
                                             loadingScreenConfig.backgroundColor = Eegeo::v4::One();
                                             loadingScreenConfig.loadingBarColor = Eegeo::v4(135.0f/255.0f, 213.0f/255.f, 245.0f/255.f, 1.0f);
                                             loadingScreenConfig.loadingBarBackgroundColor = Eegeo::v4(0.5f, 0.5f, 0.5f, 1.0f);
                                             loadingScreenConfig.fadeOutDurationSeconds = 1.5f;
                                             loadingScreenConfig.screenWidth = screenProperties->GetScreenWidth();
                                             loadingScreenConfig.screenHeight = screenProperties->GetScreenHeight();
                                             loadingScreenConfig.screenOversampleScaling = screenProperties->GetOversampleScale();
                                             loadingScreenConfig.loadingBarOffset = Eegeo::v2(0.5f, 0.1f);
                                             
                                             Eegeo::Rendering::LoadingScreen* loadingScreen = Eegeo::Rendering::LoadingScreen::Create(
                                                                                                                                      Eegeo::Helpers::TextureNameHelpers::GetImageNameForDevice("SplashScreen", ".png"),
                                                                                                                                      loadingScreenConfig,
                                                                                                                                      *(context.resolve<Eegeo::Rendering::Shaders::ShaderIdGenerator>()),
                                                                                                                                      *(context.resolve<Eegeo::Rendering::Materials::MaterialIdGenerator>()),
                                                                                                                                      *(context.resolve<Eegeo::Rendering::GlBufferPool>()),
                                                                                                                                      *(context.resolve<Eegeo::Rendering::VertexLayouts::VertexLayoutPool>()),
                                                                                                                                      *(context.resolve<Eegeo::Rendering::VertexLayouts::VertexBindingPool>()),
                                                                                                                                      *(context.resolve<Eegeo::Helpers::ITextureFileLoader>()));
                                             return std::shared_ptr<Eegeo::Rendering::LoadingScreen>(loadingScreen);
                                         }).singleInstance();
    }
}
