using System;
using System.Collections.Generic;
using System.Web;
using System.Web.Services;

[WebService(Namespace = "http://tempuri.org/")]
[WebServiceBinding(ConformsTo = WsiProfiles.BasicProfile1_1)]

public class Service : System.Web.Services.WebService
{
    public Service()
    {
        //Uncomment the following line if using designed components 
        //InitializeComponent(); 
    }

    [WebMethod]
    public string GetMeetingSpaceDetails(string regionCode)
    {
        string json = "";

        if (regionCode == "EMEA")
        {
            json = System.IO.File.ReadAllText(Server.MapPath("~/App_Data/GetMeetingSpaceDetails.json"));
        }

        return json;
    }

    [WebMethod]
    public string GetMeetingSpaceOccupancyDetails(string regionCode)
    {
        string json = "";
        
        if(regionCode == "EMEA")
        {
            json = System.IO.File.ReadAllText(Server.MapPath("~/App_Data/GetMeetingSpaceOccupancyDetails.json"));
        }

        return json;
    }

}