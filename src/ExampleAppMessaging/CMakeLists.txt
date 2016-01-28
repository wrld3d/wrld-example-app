set(headers ${headers} ../src/ExampleAppMessaging
)
set(currsources
  ../src/ExampleAppMessaging/BidirectionalBus.h
  ../src/ExampleAppMessaging/CMakeLists.txt
  ../src/ExampleAppMessaging/DispatchQueue.h
  ../src/ExampleAppMessaging/NativeToUiMessageCatalog.h
  ../src/ExampleAppMessaging/SdkDomainEventsMessageCatalog.h
  ../src/ExampleAppMessaging/SdkModelDomainEventBus.h
  ../src/ExampleAppMessaging/UiToNativeMessageCatalog.h
)
set(sources ${sources} ${currsources})
source_group(\\src\\ExampleAppMessaging FILES ${currsources})
