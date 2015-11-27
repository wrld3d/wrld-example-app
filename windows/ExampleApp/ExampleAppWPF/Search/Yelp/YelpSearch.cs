using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.IO;
using System.Net;
using SimpleOAuth;
using System.Windows;
using System.Windows.Threading;

namespace ExampleAppWPF
{
    class YelpAPIClient
    {
        private const string API_HOST = "http://api.yelp.com";

        private const string SEARCH_LIMIT = "20";

        private const string SEARCH_PATH = "/v2/search/";
        private const string BUSINESS_PATH = "/v2/business/";

        private WebRequest m_request;

        private System.Delegate webRequestCallback;
        private IntPtr nativePointer;
        private Dispatcher m_dispatcher;

        private static YelpAPIClient CurrentRequest = null;

        static YelpAPIClient()
        {

        }

        public YelpAPIClient(IntPtr pointer)
        {
            nativePointer = pointer;
            
            if(CurrentRequest != null)
            {
                CurrentRequest.AbortRequest();
                CurrentRequest = this;
            }

            var mainWindow = (MainWindow)Application.Current.MainWindow;
            m_dispatcher = mainWindow.Dispatcher;
        }

        ~YelpAPIClient()
        {
            if(CurrentRequest == this)
            {
                m_request.Abort();
                CurrentRequest = null;
            }
        }

        void AbortRequest()
        {
            m_request.Abort();
        }

        private void PerformRequest(string consumerKey, string consumerSecret, string oAuthToken, string oAuthTokenSecret, string baseURL, Dictionary<string, string> queryParams = null)
        {
            var query = System.Web.HttpUtility.ParseQueryString(String.Empty);

            if (queryParams == null)
            {
                queryParams = new Dictionary<string, string>();
            }

            foreach (var queryParam in queryParams)
            {
                query[queryParam.Key] = queryParam.Value;
            }

            var uriBuilder = new UriBuilder(baseURL);
            uriBuilder.Query = query.ToString();

            m_request = WebRequest.Create(uriBuilder.ToString());
            m_request.Method = "GET";

            m_request.SignRequest(
                new Tokens
                {
                    ConsumerKey = consumerKey,
                    ConsumerSecret = consumerSecret,
                    AccessToken = oAuthToken,
                    AccessTokenSecret = oAuthTokenSecret
                }
            ).WithEncryption(EncryptionMethod.HMACSHA1).InHeader();

            DoWithResponse(m_request as HttpWebRequest, (response) => {

                string body = string.Empty;

                if (response != null)
                {
                    body = new StreamReader(response.GetResponseStream()).ReadToEnd();   
                }

                m_dispatcher.BeginInvoke(webRequestCallback, body, nativePointer);
                CurrentRequest = null;
            });
        }

        void DoWithResponse(HttpWebRequest request, Action<HttpWebResponse> responseAction)
        {
            Action wrapperAction = () =>
            {
                request.BeginGetResponse(new AsyncCallback((iar) =>
                {
                    HttpWebResponse response = null;

                    try
                    {
                        response = (HttpWebResponse)((HttpWebRequest)iar.AsyncState).EndGetResponse(iar);
                    }
                    catch (WebException e)
                    {
                        string body = string.Empty;

                        if (e.Response != null)
                        {
                            body = new StreamReader(e.Response.GetResponseStream()).ReadToEnd();
                        }

                        Debug.WriteLine("HTTP Error: {0}: {1}", e.Message, body);

                        // Response remains null
                    }
                    responseAction(response);
                }), request);
            };
            wrapperAction.BeginInvoke(new AsyncCallback((iar) =>
            {
                var action = (Action)iar.AsyncState;
                action.EndInvoke(iar);
            }), wrapperAction);
        }

        public void Search(string consumerKey, string consumerSecret, string oAuthToken, string oAuthTokenSecret, string term, double latitude, double longitude, System.Delegate callback)
        {
            webRequestCallback = callback;

            string baseURL = API_HOST + SEARCH_PATH;

            var latlong = latitude.ToString() + "," + longitude.ToString();

            var queryParams = new Dictionary<string, string>()
            {
                { "term", term },
                { "ll", latlong },
                { "limit", SEARCH_LIMIT.ToString() }
            };
            PerformRequest(consumerKey, consumerSecret, oAuthToken, oAuthTokenSecret, baseURL, queryParams);
        }
    }
}