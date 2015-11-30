using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Json;
using System.Text;
using System.Threading.Tasks;

namespace ExampleAppWPF
{
    [DataContract]
    public class SwallowDepartmentResultModel
    {
        [DataMember(Name = "name")]
        private string m_name;

        [DataMember(Name = "image_filename")]
        private string m_imageFilename;

        [DataMember(Name = "description")]
        private string m_description;

        public string Name { get { return m_name; } }
        
        public string ImageFilename { get { return m_imageFilename; } }
        
        public string Description { get { return m_description; } }

        public static SwallowDepartmentResultModel FromJson(string jsonString)
        {
            MemoryStream stream = new MemoryStream(Encoding.Unicode.GetBytes(jsonString));
            DataContractJsonSerializer serializer = new DataContractJsonSerializer(typeof(SwallowDepartmentResultModel));

            stream.Position = 0;
            return (SwallowDepartmentResultModel)serializer.ReadObject(stream);
        }
    }
}
