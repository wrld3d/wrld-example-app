using System.Collections.Generic;
using System.IO;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Json;
using System.Text;

namespace ExampleAppWPF
{
    [DataContract]
    class EegeoResultModel
    {
        [DataMember(Name = "phone")]
        private string m_phone = string.Empty;

        [DataMember(Name = "web")]
        private string m_webUrl = string.Empty;

        [DataMember(Name = "description")]
        private string m_description = string.Empty;

        [DataMember(Name = "image_url")]
        private string m_imageUrl = string.Empty;

        [DataMember(Name = "rating")]
        private double m_rating = 0.0;

        [DataMember(Name = "address")]
        private string m_address = string.Empty;

        [DataMember(Name = "facebook")]
        private string m_facebook = string.Empty;

        [DataMember(Name = "twitter")]
        private string m_twitter = string.Empty;

        [DataMember(Name = "email")]
        private string m_email = string.Empty;

        [DataMember(Name = "custom_view")]
        private string m_webViewUrl = string.Empty;

        [DataMember(Name = "custom_view_height")]
        private int m_webViewHeight = -1;


        public string Phone { get { return m_phone; } }
        public string WebUrl { get { return m_webUrl; } }
        public string ImageUrl { get { return m_imageUrl; } }
        public string RatingsImageUrl { get; private set; }
        public string Address { get { return m_address; } }
        public string Description { get { return m_description; } }
        public string Facebook { get { return m_facebook; } }
        public string Twitter { get { return m_twitter; } }
        public string Email { get { return m_email; } }
        public string WebViewUrl { get { return m_webViewUrl; } }
        public int WebViewHeight { get { return m_webViewHeight; } }

        public static EegeoResultModel FromResultModel(ExampleApp.SearchResultModelCLI model)
        {
            var stream = new MemoryStream(Encoding.Unicode.GetBytes(model.JsonData));
            // First time creating a poi will return "" from json data. Adding json data such as phone number and then removing it will return {} for unknown reason.
            if (model.JsonData == "")
            {
                stream = new MemoryStream(Encoding.Unicode.GetBytes("{}"));
            }

            var serializer = new DataContractJsonSerializer(typeof(EegeoResultModel));
            return (EegeoResultModel)serializer.ReadObject(stream);
        }
    }
}
