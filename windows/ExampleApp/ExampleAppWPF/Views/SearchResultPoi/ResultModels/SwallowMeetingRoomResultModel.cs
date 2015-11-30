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
    public class SwallowMeetingRoomResultModel
    {
        [DataMember(Name = "name")]
        private string m_name;

        [DataMember(Name = "image_filename")]
        private string m_imageFilename;

        [DataMember(Name = "availability")]
        private string m_availability;

        public string Name { get { return m_name; } }

        public string ImageFilename { get { return m_imageFilename; } }

        public string Availability { get { return m_availability; } }

        public static SwallowMeetingRoomResultModel FromJson(string jsonString)
        {
            MemoryStream stream = new MemoryStream(Encoding.Unicode.GetBytes(jsonString));
            DataContractJsonSerializer serializer = new DataContractJsonSerializer(typeof(SwallowMeetingRoomResultModel));

            stream.Position = 0;
            return (SwallowMeetingRoomResultModel)serializer.ReadObject(stream);
        }
    }
}
