using System.Collections.Generic;
using System.IO;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Json;
using System.Text;

namespace ExampleAppWPF
{
    [DataContract]
    class YelpResultModel
    {
        [DataMember(Name = "display_phone")]
        private string m_phone = string.Empty;

        [DataMember(Name = "url")]
        private string m_webUrl = string.Empty;

        [DataMember(Name = "snippet_text")]
        private string m_snippetText = string.Empty;
        
        [DataMember(Name = "image_url")]
        private string m_imageUrl = string.Empty;
        
        [DataMember(Name = "rating")]
        private double m_rating = 0.0;

        [DataMember(Name = "review_count")]
        private int m_reviewCount = 0;

        public string Phone {  get { return m_phone; } }
        public string WebUrl { get { return m_webUrl; } }
        public string ImageUrl { get { return m_imageUrl; } }
        public string RatingsImageUrl { get; private set; }
        public List<string> Reviews { get; private set; }
        public int ReviewCount { get { return m_reviewCount; } }
        
        public static YelpResultModel FromResultModel(ExampleApp.SearchResultModelCLI model)
        {
            MemoryStream stream = new MemoryStream(Encoding.Unicode.GetBytes(model.JsonData));
            DataContractJsonSerializer serializer = new DataContractJsonSerializer(typeof(YelpResultModel));

            stream.Position = 0;
            YelpResultModel result = (YelpResultModel)serializer.ReadObject(stream);

            string ratingString = result.m_rating.ToString();

            if(!ratingString.Contains("."))
            {
                ratingString += ".0";
            }

            ratingString = ratingString.Replace('.', '_');

            result.RatingsImageUrl = "stars_" + ratingString;
            
            result.Reviews = new List<string>();
            result.Reviews.Add(result.m_snippetText);

            return result;
        }

        private YelpResultModel()
        {

        }
    }
}
