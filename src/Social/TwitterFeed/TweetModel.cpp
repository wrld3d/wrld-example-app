// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "types.h"
#include "TweetModel.h"
#include "LatLongAltitude.h"
#include <sstream>

namespace ExampleApp
{
    namespace Social
    {
        namespace TwitterFeed
        {
            TweetModel::TweetModel(const std::string& tweetId,
                                   const std::string& text,
                                   const std::string& userName,
                                   const std::string& baseUserName,
                                   const std::string& userScreenName,
                                   const std::string& baseUserScreenName,
                                   const std::string& userId,
                                   const std::string& bannerImageUrl,
                                   const std::string& profileImageUrl,
                                   const std::string& baseProfileImageUrl,
                                   bool isRetweet,
                                   bool isReply,
                                   std::vector<std::string> mediaUrls,
                                   std::string expandedMediaUrl,
                                   bool hasAttachedVideo,
                                   std::vector<LinkEntity> linkEntities,
                                   int retweetCount,
                                   int favoriteCount,
                                   const std::string& createdAt,
                                   const std::string& placeName,
                                   const std::string& profileColor,
                                   int mediaIndex,
                                   bool hasCoordinates,
                                   Eegeo::Space::LatLong coordinates)
            : m_tweetId(tweetId)
            , m_text(text)
            , m_userName(userName)
            , m_baseUserName(baseUserName)
            , m_userScreenName(userScreenName)
            , m_baseUserScreenName(baseUserScreenName)
            , m_userId(userId)
            , m_bannerImageUrl(bannerImageUrl)
            , m_profileImageUrl(profileImageUrl)
            , m_baseProfileImageUrl(baseProfileImageUrl)
            , m_isRetweet(isRetweet)
            , m_isReply(isReply)
            , m_mediaUrls(mediaUrls)
            , m_expandedMediaUrl(expandedMediaUrl)
            , m_hasAttachedVideo(hasAttachedVideo)
            , m_linkEntities(linkEntities)
            , m_retweetCount(retweetCount)
            , m_favoriteCount(favoriteCount)
            , m_createdAt(createdAt)
            , m_placeName(placeName)
            , m_profileColor(profileColor)
            , m_mediaIndex(mediaIndex)
            , m_doesLinkOut(false)
            , m_hasCoordinates(hasCoordinates)
            , m_coordinates(coordinates)
            {
                
            }
            
            TweetModel::~TweetModel()
            {
                
            }
            
            const std::string& TweetModel::GetTweetId() const
            {
                return m_tweetId;
            }
            
            const std::string& TweetModel::GetText() const
            {
                return m_text;
            }
            
            const std::string& TweetModel::GetUserName() const
            {
                return m_userName;
            }
            
            const std::string& TweetModel::GetBaseUserName() const
            {
                return m_baseUserName;
            }
            
            const std::string& TweetModel::GetUserScreenName() const
            {
                return m_userScreenName;
            }
            
            const std::string& TweetModel::GetBaseUserScreenName() const
            {
                return m_baseUserScreenName;
            }
            
            const std::string& TweetModel::GetUserId() const
            {
                return m_userId;
            }
            
            const std::string& TweetModel::GetBannerImageUrl() const
            {
                return m_bannerImageUrl;
            }
            
            const std::string& TweetModel::GetProfileImageUrl() const
            {
                return m_profileImageUrl;
            }
            
            const std::string& TweetModel::GetBaseProfileImageUrl() const
            {
                return m_baseProfileImageUrl;
            }
            
            bool TweetModel::IsRetweet() const
            {
                return m_isRetweet;
            }
            
            bool TweetModel::IsReply() const
            {
                return m_isReply;
            }
            
            int TweetModel::GetRetweetCount() const
            {
                return m_retweetCount;
            }
            
            int TweetModel::GetFavouriteCount() const
            {
                return m_favoriteCount;
            }
            
            const std::string& TweetModel::GetCreatedAt() const
            {
                return m_createdAt;
            }
            
            const std::string& TweetModel::GetPlaceName() const
            {
                return m_placeName;
            }
            
            const std::string& TweetModel::GetProfileColor() const
            {
                return m_profileColor;
            }
            
            const std::string& TweetModel::GetFirstAttachedImageUrl() const
            {
                if(m_mediaUrls.size() == 0)
                {
                    return GetProfileImageUrl();
                }
                
                return m_mediaUrls.front();
            }
            
            const std::string& TweetModel::GetExpandedMediaUrl() const
            {
                return m_expandedMediaUrl;
            }
            
            const bool TweetModel::HasAttachedVideo() const
            {
                return m_hasAttachedVideo;
            }
            
            const std::vector<TweetModel::LinkEntity>& TweetModel::GetLinkEntities() const
            {
                return m_linkEntities;
            }
            
            const int TweetModel::GetMediaIndex() const
            {
                return m_mediaIndex;
            }
            
            const bool TweetModel::GetDoesLinkOut() const
            {
                return m_doesLinkOut;
            }
            
            void TweetModel::SetDoesLinkOut(bool doesLinkOut)
            {
                m_doesLinkOut = doesLinkOut;
            }
            
            const bool TweetModel::HasCoordinates() const
            {
                return m_hasCoordinates;
            }
            
            const Eegeo::Space::LatLong& TweetModel::GetCoordinates() const
            {
                Eegeo_ASSERT(HasCoordinates(), "Cannot get coordinates as none available for this tweet");
                return m_coordinates;
            }
            
            TweetModel* TweetModel::GetNewTweetModelFromJsonDocument(rapidjson::Document& jsonDocument, unsigned int index)
            {
                const char* TextKey = "text";
                const char* IdStrKey = "id_str";
                const char* RetweetKey = "retweeted_status";
                const char* ReplyKey = "in_reply_to_status_id";
                const char* UserKey = "user";
                const char* NameKey = "name";
                const char* ScreenNameKey = "screen_name";
                const char* BannerKey = "profile_banner_url";
                const char* ProfileKey = "profile_image_url";
                const char* EntitiesKey = "entities";
                const char* MediaKey = "media";
                const char* MediaUrlKey = "media_url";
                const char* RetweetCountKey = "retweet_count";
                const char* FavoriteCountKey = "favorite_count";
                const char* CreatedAtKey = "created_at";
                const char* PlaceKey = "place";
                const char* PlaceBoxKey = "bounding_box";
                const char* PlaceNameKey = "name";
                const char* ProfileBackgroundKey = "profile_link_color";
                const char* UrlsKey = "urls";
                const char* ExpandedUrlKey = "expanded_url";
                const char* IndicesKey = "indices";
                const char* UsersMentionsKey = "user_mentions";
                const char* HashTagsKey = "hashtags";
                const char* ExtendedEntitiesKey = "extended_entities";
                const char* MediaTypeKey = "type";
                const char* CoordinatesKey = "coordinates";
                
                Eegeo_ASSERT(jsonDocument[index].HasMember(TextKey) && jsonDocument[index].HasMember(IdStrKey));
                
                std::string text = jsonDocument[index][TextKey].GetString();
                std::string tweetId = jsonDocument[index][IdStrKey].GetString();
                
                bool isRetweet = jsonDocument[index].HasMember(RetweetKey);
                
                bool isReply = jsonDocument[index].HasMember(ReplyKey) && !jsonDocument[index][ReplyKey].IsNull();
                
                std::string userName;
                std::string userScreenName;
                std::string userId;
                std::string bannerImageUrl = "";
                std::string profileImageUrl = "";
                std::string profileColor = "";
                
                if(isRetweet)
                {
                    Eegeo_ASSERT(jsonDocument[index][RetweetKey].HasMember(UserKey));
                    
                    Eegeo_ASSERT(jsonDocument[index][RetweetKey][UserKey].HasMember(NameKey));
                    userName = jsonDocument[index][RetweetKey][UserKey][NameKey].GetString();
                    
                    Eegeo_ASSERT(jsonDocument[index][RetweetKey][UserKey].HasMember(ScreenNameKey));
                    userScreenName = jsonDocument[index][RetweetKey][UserKey][ScreenNameKey].GetString();
                    
                    Eegeo_ASSERT(jsonDocument[index][RetweetKey][UserKey].HasMember(IdStrKey));
                    userId = jsonDocument[index][RetweetKey][UserKey][IdStrKey].GetString();
                    
                    if(jsonDocument[index][RetweetKey][UserKey].HasMember(BannerKey))
                    {
                        bannerImageUrl = jsonDocument[index][RetweetKey][UserKey][BannerKey].GetString();
                    }
                    
                    if(jsonDocument[index][RetweetKey][UserKey].HasMember(ProfileKey))
                    {
                        profileImageUrl = jsonDocument[index][RetweetKey][UserKey][ProfileKey].GetString();
                    }
                    
                    if(bannerImageUrl == "")
                    {
                        Eegeo_ASSERT(jsonDocument[index][RetweetKey][UserKey].HasMember(ProfileBackgroundKey));
                        
                        profileColor = jsonDocument[index][RetweetKey][UserKey][ProfileBackgroundKey].GetString();
                    }
                }
                else
                {
                    Eegeo_ASSERT(jsonDocument[index].HasMember(UserKey));
                    
                    Eegeo_ASSERT(jsonDocument[index][UserKey].HasMember(NameKey));
                    userName = jsonDocument[index][UserKey][NameKey].GetString();
                    
                    Eegeo_ASSERT(jsonDocument[index][UserKey].HasMember(ScreenNameKey));
                    userScreenName = jsonDocument[index][UserKey][ScreenNameKey].GetString();
                    
                    Eegeo_ASSERT(jsonDocument[index][UserKey].HasMember(IdStrKey));
                    userId = jsonDocument[index][UserKey][IdStrKey].GetString();
                    
                    if(jsonDocument[index][UserKey].HasMember(BannerKey))
                    {
                        bannerImageUrl = jsonDocument[index][UserKey][BannerKey].GetString();
                    }
                    
                    if(jsonDocument[index][UserKey].HasMember(ProfileKey))
                    {
                        profileImageUrl = jsonDocument[index][UserKey][ProfileKey].GetString();
                    }
                    
                    if(bannerImageUrl == "")
                    {
                        Eegeo_ASSERT(jsonDocument[index][UserKey].HasMember(ProfileBackgroundKey));
                        
                        profileColor = jsonDocument[index][UserKey][ProfileBackgroundKey].GetString();
                    }
                }
                
                size_t extensionSearchPos = profileImageUrl.find("_normal.");
                if(extensionSearchPos != std::string::npos)
                {
                    profileImageUrl.erase(extensionSearchPos, 7);
                }
                
                Eegeo_ASSERT(jsonDocument[index].HasMember(UserKey));
                
                Eegeo_ASSERT(jsonDocument[index][UserKey].HasMember(NameKey));
                
                std::string baseUserName = jsonDocument[index][UserKey][NameKey].GetString();
                
                Eegeo_ASSERT(jsonDocument[index][UserKey].HasMember(ScreenNameKey));
                
                std::string baseUserScreenName = jsonDocument[index][UserKey][ScreenNameKey].GetString();
                
                Eegeo_ASSERT(jsonDocument[index][UserKey].HasMember(ProfileKey));
                
                std::string baseProfileImageUrl = jsonDocument[index][UserKey][ProfileKey].GetString();
                
                std::vector<std::string> mediaUrls;
                std::vector<std::string> videoUrls;
                std::vector<LinkEntity> linkEntities;
                int mediaIndex = INT_MAX;
                
                if(jsonDocument[index].HasMember(EntitiesKey))
                {
                    if(jsonDocument[index][EntitiesKey].HasMember(MediaKey) && jsonDocument[index][EntitiesKey][MediaKey].IsArray())
                    {
                        for(int i = 0; i < jsonDocument[index][EntitiesKey][MediaKey].Size(); ++i)
                        {
                            if(jsonDocument[index][EntitiesKey][MediaKey][i].HasMember(MediaUrlKey))
                            {
                                mediaUrls.push_back(jsonDocument[index][EntitiesKey][MediaKey][i][MediaUrlKey].GetString());
                                
                                Eegeo_ASSERT(jsonDocument[index][EntitiesKey][MediaKey][i].HasMember(IndicesKey) && jsonDocument[index][EntitiesKey][MediaKey][i][IndicesKey].IsArray());
                                
                                int startIndex = jsonDocument[index][EntitiesKey][MediaKey][i][IndicesKey][0u].GetInt();
                                
                                if (startIndex < mediaIndex)
                                {
                                    mediaIndex = startIndex;
                                }
                            }
                        }
                    }
                    
                    if(jsonDocument[index].HasMember(ExtendedEntitiesKey) && jsonDocument[index][ExtendedEntitiesKey].HasMember(MediaKey) && jsonDocument[index][ExtendedEntitiesKey][MediaKey].IsArray())
                    {
                        for(int i = 0; i < jsonDocument[index][ExtendedEntitiesKey][MediaKey].Size(); ++i)
                        {
                            Eegeo_ASSERT(jsonDocument[index][ExtendedEntitiesKey][MediaKey][i].HasMember(MediaTypeKey));
                            
                            std::string mediaType = jsonDocument[index][ExtendedEntitiesKey][MediaKey][i][MediaTypeKey].GetString();
                            
                            if(mediaType != "video")
                            {
                                continue;
                            }
                            
                            Eegeo_ASSERT(jsonDocument[index][ExtendedEntitiesKey][MediaKey][i].HasMember(MediaUrlKey));
                            
                            videoUrls.push_back(jsonDocument[index][ExtendedEntitiesKey][MediaKey][i][MediaUrlKey].GetString());
                            
                            Eegeo_ASSERT(jsonDocument[index][ExtendedEntitiesKey][MediaKey][i].HasMember(IndicesKey) && jsonDocument[index][ExtendedEntitiesKey][MediaKey][i][IndicesKey].IsArray());
                            
                            int startIndex = jsonDocument[index][ExtendedEntitiesKey][MediaKey][i][IndicesKey][0u].GetInt();
                            
                            if (startIndex < mediaIndex)
                            {
                                mediaIndex = startIndex;
                            }
                        }
                    }
                    
                    if(jsonDocument[index][EntitiesKey].HasMember(UrlsKey) && jsonDocument[index][EntitiesKey][UrlsKey].IsArray())
                    {
                        for(int i = 0; i < jsonDocument[index][EntitiesKey][UrlsKey].Size(); ++i)
                        {
                            Eegeo_ASSERT(jsonDocument[index][EntitiesKey][UrlsKey][i].HasMember(ExpandedUrlKey));
                            Eegeo_ASSERT(jsonDocument[index][EntitiesKey][UrlsKey][i].HasMember(IndicesKey) && jsonDocument[index][EntitiesKey][UrlsKey][i][IndicesKey].IsArray());
                            
                            linkEntities.push_back(LinkEntity(jsonDocument[index][EntitiesKey][UrlsKey][i][IndicesKey][0u].GetInt(),
                                                              jsonDocument[index][EntitiesKey][UrlsKey][i][IndicesKey][1u].GetInt(),
                                                              std::string(jsonDocument[index][EntitiesKey][UrlsKey][i][ExpandedUrlKey].GetString())));
                        }
                    }
                    
                    if(jsonDocument[index][EntitiesKey].HasMember(UsersMentionsKey) && jsonDocument[index][EntitiesKey][UsersMentionsKey].IsArray())
                    {
                        for(int i = 0; i < jsonDocument[index][EntitiesKey][UsersMentionsKey].Size(); ++i)
                        {
                            Eegeo_ASSERT(jsonDocument[index][EntitiesKey][UsersMentionsKey][i].HasMember(ScreenNameKey));
                            Eegeo_ASSERT(jsonDocument[index][EntitiesKey][UsersMentionsKey][i].HasMember(IndicesKey) && jsonDocument[index][EntitiesKey][UsersMentionsKey][i][IndicesKey].IsArray());
                            
                            std::stringstream userUrl;
                            
                            userUrl << "https://twitter.com/" << jsonDocument[index][EntitiesKey][UsersMentionsKey][i][ScreenNameKey].GetString();
                            
                            linkEntities.push_back(LinkEntity(jsonDocument[index][EntitiesKey][UsersMentionsKey][i][IndicesKey][0u].GetInt(),
                                                              jsonDocument[index][EntitiesKey][UsersMentionsKey][i][IndicesKey][1u].GetInt(),
                                                              userUrl.str()));
                        }
                    }
                    
                    if(jsonDocument[index][EntitiesKey].HasMember(HashTagsKey) && jsonDocument[index][EntitiesKey][HashTagsKey].IsArray())
                    {
                        for(int i = 0; i < jsonDocument[index][EntitiesKey][HashTagsKey].Size(); ++i)
                        {
                            Eegeo_ASSERT(jsonDocument[index][EntitiesKey][HashTagsKey][i].HasMember(TextKey));
                            Eegeo_ASSERT(jsonDocument[index][EntitiesKey][HashTagsKey][i].HasMember(IndicesKey) && jsonDocument[index][EntitiesKey][HashTagsKey][i][IndicesKey].IsArray());
                            
                            std::stringstream userUrl;
                            
                            userUrl << "https://twitter.com/hashtag/" << jsonDocument[index][EntitiesKey][HashTagsKey][i][TextKey].GetString();
                            
                            linkEntities.push_back(LinkEntity(jsonDocument[index][EntitiesKey][HashTagsKey][i][IndicesKey][0u].GetInt(),
                                                              jsonDocument[index][EntitiesKey][HashTagsKey][i][IndicesKey][1u].GetInt(),
                                                              userUrl.str()));
                        }
                    }
                }
                
                if(mediaUrls.empty())
                {
                    mediaUrls.push_back("");
                }
                
                std::string expandedMediaUrl = "https://mobile.twitter.com/" + userScreenName + "/status/";
                
                if(!isRetweet)
                {
                    expandedMediaUrl += tweetId;
                }
                else
                {
                    Eegeo_ASSERT(jsonDocument[index][RetweetKey].HasMember(IdStrKey));
                    expandedMediaUrl += jsonDocument[index][RetweetKey][IdStrKey].GetString();
                }
                
                bool hasAttachedVideo = !videoUrls.empty();
                
                int retweetCount = 0;
                
                if(jsonDocument[index].HasMember(RetweetCountKey))
                {
                    retweetCount = jsonDocument[index][RetweetCountKey].GetInt();
                }
                
                int favoriteCount = 0;
                
                if(jsonDocument[index].HasMember(FavoriteCountKey))
                {
                    favoriteCount = jsonDocument[index][FavoriteCountKey].GetInt();
                }
                
                Eegeo_ASSERT(jsonDocument[index].HasMember(CreatedAtKey));
                
                std::string createdAt = jsonDocument[index][CreatedAtKey].GetString();
                
                std::string placeName = "";
                
                bool hasCoordinates = false;
                Eegeo::Space::LatLong coordinatesLatLong(0, 0);
                
                if(jsonDocument[index].HasMember(CoordinatesKey) && !jsonDocument[index][CoordinatesKey].IsNull())
                {
                    rapidjson::Value& coordinates = jsonDocument[index][CoordinatesKey][CoordinatesKey];
                    float lat = (float)coordinates[(rapidjson::SizeType)(1)].GetDouble();
                    float lon = (float)coordinates[(rapidjson::SizeType)(0)].GetDouble();
                    coordinatesLatLong.SetLatitude(Eegeo::Math::Deg2Rad(lat));
                    coordinatesLatLong.SetLongitude(Eegeo::Math::Deg2Rad(lon));
                    hasCoordinates = true;
                }
                
                if(jsonDocument[index].HasMember(PlaceKey) && !jsonDocument[index][PlaceKey].IsNull())
                {
                    Eegeo_ASSERT(jsonDocument[index][PlaceKey].HasMember(PlaceNameKey));
                    
                    placeName = jsonDocument[index][PlaceKey][PlaceNameKey].GetString();
                    if(placeName == "[Place name removed]")
                    {
                        placeName = "";
                    }
                    
                    if(jsonDocument[index][PlaceKey].HasMember(PlaceBoxKey) && !jsonDocument[index][PlaceKey][PlaceBoxKey].IsNull())
                    {
                        rapidjson::Value& coordinates = jsonDocument[index][PlaceKey][PlaceBoxKey][CoordinatesKey];
                        GetLatLongFromBoxCoordinates(coordinates, coordinatesLatLong);
                        hasCoordinates = true;
                    }
                    
                }
                
                TweetModel* tweetModel = Eegeo_NEW(TweetModel)(tweetId,
                                                               text,
                                                               userName,
                                                               baseUserName,
                                                               userScreenName,
                                                               baseUserScreenName,
                                                               userId,
                                                               bannerImageUrl,
                                                               profileImageUrl,
                                                               baseProfileImageUrl,
                                                               isRetweet,
                                                               isReply,
                                                               mediaUrls,
                                                               expandedMediaUrl,
                                                               hasAttachedVideo,
                                                               linkEntities,
                                                               retweetCount,
                                                               favoriteCount,
                                                               createdAt,
                                                               placeName,
                                                               profileColor,
                                                               mediaIndex,
                                                               hasCoordinates,
                                                               coordinatesLatLong);
                
                return tweetModel;
            }
            
            void TweetModel::GetLatLongFromBoxCoordinates(rapidjson::Value& coordinates, Eegeo::Space::LatLong& out_latLong)
            {
                double totalLat = 0.0;
                double totalLon = 0.0;
                
                for(int i = 0; i < 4; i++)
                {
                    rapidjson::Value& coordinate = coordinates[(rapidjson::SizeType)(0)][(rapidjson::SizeType)(i)];
                    double lat = coordinate[(rapidjson::SizeType)(1)].GetDouble();
                    double lon = coordinate[(rapidjson::SizeType)(0)].GetDouble();
                    
                    totalLat += lat;
                    totalLon += lon;
                }
                
                out_latLong.SetLatitude(Eegeo::Math::Deg2Rad(totalLat/4.0));
                out_latLong.SetLongitude(Eegeo::Math::Deg2Rad(totalLon/4.0));
            }
        }
    }
}
