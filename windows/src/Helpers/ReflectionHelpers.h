// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#include <type_traits>
#include <vcclr.h>

#using "System.dll"

namespace ExampleApp
{
    namespace Helpers
    {
        namespace ReflectionHelpers
        {
            inline System::Type^ GetTypeFromAssembly(System::String^ assemblyName, System::String^ typeName)
            {
                return System::Reflection::Assembly::Load(assemblyName)->GetType(typeName);
            }

            inline System::Type^ GetTypeFromEntryAssembly(System::String^ typeName)
            {
                System::Reflection::Assembly^ entryAssem = System::Reflection::Assembly::GetEntryAssembly();
                return entryAssem->GetType(typeName);
            }

            inline System::String^ GetEntryAssemblyName(System::String^ typeName)
            {
                System::Reflection::Assembly^ entryAssem = System::Reflection::Assembly::GetEntryAssembly();
                return entryAssem->GetName()->Name;
            }

            inline array<System::Type^>^ CreateTypes(...array<System::Type^>^ types)
            {
                return types;
            }

            inline array<System::Object^>^ CreateObjects(...array<System::Object^>^ objects)
            {
                return objects;
            }

            inline System::String^ ConvertUTF8ToManagedString(const char* input)
            {
                size_t stringByteCount = strlen(input);
                array<System::Byte>^ stringBytes = gcnew array<System::Byte>(static_cast<int>(stringByteCount));
                System::Runtime::InteropServices::Marshal::Copy(System::IntPtr((void*)input), stringBytes, 0, static_cast<int>(stringByteCount));

                return System::Text::Encoding::UTF8->GetString(stringBytes);
            }

            inline System::String^ ConvertUTF8ToManagedString(const std::string& input)
            {
                return ConvertUTF8ToManagedString(input.c_str());
            }

			inline std::string ConvertManagedStringToUTF8(System::String^ input)
			{
				array<System::Byte>^ bytes = System::Text::Encoding::UTF8->GetBytes(input);

				std::string output;
				output.resize(bytes->Length);
				System::Runtime::InteropServices::Marshal::Copy(bytes, 0, System::IntPtr((void*)output.data()), bytes->Length);

				return output;
			}

            template<typename ...Args>
            struct Method
            {
                gcroot<System::Type^> m_classType;
                gcroot<System::Object^> m_classObject;
                gcroot<System::String^> m_methodName;

                Method() = default;
                Method(Method const&) = delete;
                Method(Method &&) = delete;

                Method(System::Type^ classType, System::Object^ object, System::String ^name)
                {
                    m_classType = classType;
                    m_methodName = name;
                    m_classObject = object;
                }

                void SetupMethod(System::Type^ classType, System::Object^ object, System::String ^name)
                {
                    m_classType = classType;
                    m_methodName = name;
                    m_classObject = object;
                }

                template<typename T = void>
                T Call(Args... args) const
                {
                    return (T)(m_classType->GetMethod(m_methodName)->Invoke(m_classObject, CreateObjects(args...)));
                }

                void operator()(Args... args)
                {
                    System::Reflection::MethodInfo^ currentMethod = m_classType->GetMethod(m_methodName);

                    array<System::Object^>^ objectArray = CreateObjects(args...);

                   //WIP
                    /* array<System::Reflection::ParameterInfo^>^ methodParams = currentMethod->GetParameters();

                    System::Collections::IEnumerator^ enum0 = methodParams->GetEnumerator();

                    int i = 0;
                    while (enum0->MoveNext())
                    {
                        System::Reflection::ParameterInfo^ param = safe_cast<System::Reflection::ParameterInfo^>(enum0->Current);
                        auto type = param->ParameterType;

                        if (!objectArray[i]->GetType()->IsEquivalentTo(type))
                        {
                            Eegeo_ASSERT(false, "Paramter %d doesn't match with C# function", i);
                        }

                        if (i++ >= objectArray->Length)
                        {
                            Eegeo_ASSERT(false, "Extra paramters in C++ call");
                        }
                    }

                    if (i < objectArray->Length)
                    {
                        Eegeo_ASSERT(false, "Missing paramters in C++ call");
                    }*/

                    currentMethod->Invoke(m_classObject, objectArray);
                }
            };

            //template<class T, typename = std::enable_if_t<std::is_void<T>::value>>
            template<>
            struct Method<void>
            {
                gcroot<System::Type^> m_classType;
                gcroot<System::Object^> m_classObject;
                gcroot<System::String^> m_methodName;

                Method() = default;
                Method(Method const&) = delete;
                Method(Method &&) = delete;

                Method(System::Type^ classType, System::Object^ object, System::String ^name)
                {
                    m_classType = classType;
                    m_methodName = name;
                    m_classObject = object;
                }

                void SetupMethod(System::Type^ classType, System::Object^ object, System::String ^name)
                {
                    m_classType = classType;
                    m_methodName = name;
                    m_classObject = object;
                }

                template<typename T = void>
                T Call() const
                {
                    return (T)(m_classType->GetMethod(m_methodName)->Invoke(m_classObject, CreateObjects(nullptr)));
                }

                void operator()() const
                {
                    m_classType->GetMethod(m_methodName)->Invoke(m_classObject, CreateObjects(nullptr));
                }
            };
        }
    }
}
