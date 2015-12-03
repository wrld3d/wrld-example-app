using Newtonsoft.Json.Linq;
using System;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace ExampleAppWPF
{
    public class SubMenuListItem : MenuListItem
    {
        string m_iconString;
        ImageSource m_icon;

        public ImageSource Icon
        {
            get { return m_icon; }
        }

        public SubMenuListItem(string json, int zIndex)
            : base(json, false, zIndex)
        {
            JObject parsed = JObject.Parse(json);
            JToken iconField;

            if (parsed.TryGetValue("icon", out iconField))
            {
                m_iconString = iconField.Value<string>();
                m_icon = new BitmapImage(ViewHelpers.MakeUriForImage(string.Format("icon1_{0}.png", m_iconString)));
            }
        }
    }
}