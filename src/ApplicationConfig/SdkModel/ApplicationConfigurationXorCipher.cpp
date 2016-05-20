// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "ApplicationConfigurationXorCipher.h"
#include "base64.h"

namespace ExampleApp
{
    namespace ApplicationConfig
    {
        namespace SdkModel
        {
            namespace
            {
                std::string EncryptDecrypt(const std::string& message, const std::string& key)
                {
                    std::string result;
                    result.resize(message.size());

                    const std::string::size_type keyLength = key.size();
                    Eegeo_ASSERT(keyLength > 0);

                    Eegeo_STATIC_ASSERT(sizeof(char) == 1, sizeof_char_not_one);

                    for (int i = 0; i < message.size(); ++i)
                    {
                        int keyIndex = i % keyLength;
                        result[i] = message[i] ^ key[keyIndex];
                    }

                    return result;
                }
            }

            ApplicationConfigurationXorCipher::ApplicationConfigurationXorCipher(const std::string& key)
            : m_key(key)
            {

            }

            std::string ApplicationConfigurationXorCipher::Encrypt(const std::string& message) const
            {
                const std::string& encrypted = EncryptDecrypt(message, m_key);
                return base64_encode((unsigned char const*)encrypted.data(), (int)message.size());
            }

            std::string ApplicationConfigurationXorCipher::Decrypt(const std::string& base64) const
            {
                const std::string& decoded = base64_decode(base64);
                return EncryptDecrypt(decoded, m_key);
            }

        }
    }
}
