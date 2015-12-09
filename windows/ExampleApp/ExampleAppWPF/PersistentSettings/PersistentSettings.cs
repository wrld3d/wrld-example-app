using ExampleAppWPF.Properties;
using System;
using System.Collections.Specialized;

namespace ExampleAppWPF
{
    /// <summary>
    /// This class depends on the containing project having a user setting of type System.Collections.Specialized.StringDictionary
    /// </summary>
    public class PersistentSettings
    {
        private IntPtr m_nativePointer;
        
        public PersistentSettings(IntPtr nativePointer)
        {
            m_nativePointer = nativePointer;

            if(Settings.Default.UserSettings == null)
            {
                Settings.Default.UserSettings = new StringDictionary();

                Settings.Default.Save();
            }
        }

        public bool ContainsKey(string key)
        {
            return Settings.Default.UserSettings.ContainsKey(key);
        }

        private string ValueAt(string key)
        {
            if(!Settings.Default.UserSettings.ContainsKey(key))
            {
                throw new IndexOutOfRangeException("Key not found in persistent settings, please call ContainsKey() before retrieving value");
            }

            return Settings.Default.UserSettings[key];
        }

        private void SetValue<T>(string key, T value)
        {
            if (!Settings.Default.UserSettings.ContainsKey(key))
            {
                Settings.Default.UserSettings.Add(key, value.ToString());
            }
            else
            {
                Settings.Default.UserSettings[key] = value.ToString();
            }

            Settings.Default.Save();
        }

        public bool GetBool(string key)
        {
            return Convert.ToBoolean(ValueAt(key));
        }

        public int GetInt(string key)
        {
            return Convert.ToInt32(ValueAt(key));
        }

        public double GetDouble(string key)
        {
            return Convert.ToDouble(ValueAt(key));
        }

        public string GetString(string key)
        {
            return ValueAt(key);
        }

        public void SetBool(string key, bool value)
        {
            SetValue(key, value);
        }

        public void SetInt(string key, int value)
        {
            SetValue(key, value);
        }

        public void SetDouble(string key, double value)
        {
            SetValue(key, value);
        }

        public void SetString(string key, string value)
        {
            SetValue(key, value);
        }

        public void ClearAll()
        {
            Settings.Default.UserSettings.Clear();
            Settings.Default.Save();
        }
    }
}
