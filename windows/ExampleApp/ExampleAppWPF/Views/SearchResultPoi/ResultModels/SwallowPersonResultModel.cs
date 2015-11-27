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
    public class SwallowPersonResultModel
    {
        [DataMember(Name = "name")]
        private string m_name;

        [DataMember(Name = "job_title")]
        private string m_jobTitle;

        [DataMember(Name = "image_filename")]
        private string m_imageFilename;

        [DataMember(Name = "working_group")]
        private string m_workingGroup;

        [DataMember(Name = "office_location")]
        private string m_officeLocation;

        [DataMember(Name = "desk_code")]
        private string m_deskCode;

        public string Name { get { return m_name; } }

        public string JobTitle { get { return m_jobTitle; } }

        public string ImageFilename { get { return m_imageFilename; } }

        public string WorkingGroup { get { return m_workingGroup; } }

        public string OfficeLocation { get { return m_officeLocation; } }

        public string DeskCode { get { return m_deskCode; } }

        public static SwallowPersonResultModel FromJson(string jsonString)
        {
            MemoryStream stream = new MemoryStream(Encoding.Unicode.GetBytes(jsonString));
            DataContractJsonSerializer serializer = new DataContractJsonSerializer(typeof(SwallowPersonResultModel));

            stream.Position = 0;
            return (SwallowPersonResultModel)serializer.ReadObject(stream);
        }
    }
}
