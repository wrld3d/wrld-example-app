#import "iCarouselTourExplorerViewController.h"
#import "iCarousel.h"
#import "FXImageView.h"
#include "TourModel.h"
#include "Types.h"
#include "ImageHelpers.h"
#include "ColorHelpers.h"
#include "TourExplorerCardView.h"
#include "TwitterCardView.h"
#include "UIHelpers.h"
#include <sstream>
#include <utility>

const bool TestCycleCarouselMode = false;

#define REFLECTION_OFFSET_Y 30.f
#define ITEM_WIDTH 338.f
#define ITEM_WIDTH_IPHONE 250.f
#define ITEM_HEIGHT 222.0f
#define ITEM_HEIGHT_IPHONE 164.0f

#define STATE_NAME 0
#define STATE_IMAGE 1
#define STATE_TEXT 2

#define TWEET_USER_NAME 0
#define TWEET_SCREEN_NAME 1
#define TWEET_TEXT 2
#define TWEET_PROFILE_URL 3
#define TWEET_BANNER_URL 4
#define TWEET_RETWEET_COUNT 5
#define TWEET_FAVORITE_COUNT 6
#define TWEET_CREATED_AT 7
#define TWEET_PROFILE_COLOR 8
#define TWEET_ID 9
#define TWEET_CUTOFF 10
#define TWEET_DOES_LINK_OUT 11
#define TWEET_LINKS_START 12

#define TWEET_LINKS_SIZE 4

@interface iCarouselTourExplorerViewController () <iCarouselDataSource, iCarouselDelegate>
{
    id m_interactionHandlerInstance;
    SEL m_selectionInteractionHandler;
    SEL m_selectionTappedHandler;
    SEL m_currentItemChangedHandler;
    int m_selectionIndex;
    bool m_scrollingToSelected;
    float m_screenWidth;
    float m_screenHeight;
    std::vector< std::pair<bool,std::vector<std::string> > > m_stateViewData;
    ExampleApp::Tours::View::TourExplorer::TourExplorerViewInterop* m_pInterop;
    ImageStore* m_pImageStore;
}

@property (nonatomic, strong) iCarousel *carousel;
@property (nonatomic, strong) UINavigationItem *navItem;
@property (nonatomic, assign) BOOL wrap;
@property (nonatomic, strong) UIView* labelBackground;

@end

@implementation iCarouselTourExplorerViewController


-(id) initWithParams:(float)screenWidth
                    :(float)screenHeight
                    :(float)pixelScale
                    :(id)interactionHandlerInstance
                    :(SEL)selectionInteractionHandler
                    :(SEL)selectionTappedHandler
                    :(SEL)currentItemChangedHandler
                    :(ExampleApp::Tours::View::TourExplorer::TourExplorerViewInterop*)pInterop
                    :(ImageStore*)pImageStore;
{
    if (self = [super init])
    {
        self->m_pInterop = pInterop;
        self->m_screenWidth = screenWidth;
        self->m_screenHeight = screenHeight;
        self->m_interactionHandlerInstance = interactionHandlerInstance;
        self->m_selectionInteractionHandler = selectionInteractionHandler;
        self->m_selectionTappedHandler = selectionTappedHandler;
        self->m_currentItemChangedHandler = currentItemChangedHandler;
        self->m_selectionIndex = -1;
        self->m_scrollingToSelected = false;
        self->m_pImageStore = pImageStore;
        
        CGRect f = CGRectMake(0.f, (m_screenHeight-REFLECTION_OFFSET_Y)-(ITEM_HEIGHT), m_screenWidth, ITEM_HEIGHT);
        [self initView: f];
        
        // Increast "damping" constants.
        self.carousel.decelerationRate = 0.65f;
        self.carousel.bounceDistance = 0.5f;
        return self;
    }
    return nil;
}

- (void) configureTourStatesPresentation:(const ExampleApp::Tours::SdkModel::TourModel&)tour
{
    m_stateViewData.clear();
        
    if(TestCycleCarouselMode)
    {
        //Add dummy 'Cycle' state view for testing
        std::vector<std::string> dummyCycleData;
        
        dummyCycleData.push_back("Cycle");
        dummyCycleData.push_back(nil);
        
        m_stateViewData.push_back(std::make_pair(false, dummyCycleData));
    }
    
    [self configureStateViewData:tour];
    
    [self resetView:0];
}

- (void) configureStateViewData:(const ExampleApp::Tours::SdkModel::TourModel&)tour
{
    const std::vector<ExampleApp::Tours::SdkModel::TourStateModel>& states = tour.States();
    
    for(std::vector<ExampleApp::Tours::SdkModel::TourStateModel>::const_iterator it = states.begin();
        it != states.end();
        ++ it)
    {
        const ExampleApp::Tours::SdkModel::TourStateModel& state = *it;
        
        std::vector<std::string> stateViewData;
        
        if(!state.IsTweet())
        {
            stateViewData.push_back(state.Headline());
            stateViewData.push_back(state.ImagePath());
            stateViewData.push_back(state.Description());
        }
        else
        {
            const ExampleApp::Social::TwitterFeed::TweetModel& tweet = *state.Tweet();
            
            stateViewData.push_back(tweet.GetUserName());
            stateViewData.push_back(tweet.GetUserScreenName());
            stateViewData.push_back(tweet.GetText());
            stateViewData.push_back(tweet.GetProfileImageUrl());
            
            if(!tweet.GetBannerImageUrl().empty())
            {
                stateViewData.push_back(tweet.GetBannerImageUrl() + std::string("/web"));
            }
            else
            {
                stateViewData.push_back(std::string(""));
            }
            
            std::stringstream retweetCount;
            retweetCount << tweet.GetRetweetCount();
            stateViewData.push_back(retweetCount.str());
            
            std::stringstream favoriteCount;
            favoriteCount << tweet.GetFavouriteCount();
            stateViewData.push_back(favoriteCount.str());
            
            stateViewData.push_back(tweet.GetCreatedAt());
            stateViewData.push_back(tweet.GetProfileColor());
            stateViewData.push_back(tweet.GetTweetId());
            
            std::stringstream mediaIndex;
            mediaIndex << tweet.GetMediaIndex();
            stateViewData.push_back(mediaIndex.str());
            
            stateViewData.push_back(tweet.GetDoesLinkOut() ? "1" : "0");
            
            for (std::vector<ExampleApp::Social::TwitterFeed::TweetModel::LinkEntity>::const_iterator it = tweet.GetLinkEntities().begin();
                 it != tweet.GetLinkEntities().end();
                 ++it)
            {
                stateViewData.push_back((*it).deeplinkAddress);
                stateViewData.push_back((*it).httpAddress);
                
                std::stringstream startIndex;
                std::stringstream endIndex;
                
                startIndex << (*it).startIndex;
                endIndex << (*it).endIndex;
                
                stateViewData.push_back(startIndex.str());
                stateViewData.push_back(endIndex.str());
            }
        }
        
        
        m_stateViewData.push_back(std::make_pair(state.IsTweet(), stateViewData));
    }
}

- (void)dealloc
{
	_carousel.delegate = nil;
	_carousel.dataSource = nil;
    
    self.carousel = nil;
    self.navItem = nil;
    
    [super dealloc];
}

- (void)initView :(CGRect)frame
{
    _wrap = NO;
    
	_carousel = [[iCarousel alloc] initWithFrame:frame];
	_carousel.autoresizingMask = UIViewAutoresizingFlexibleWidth | UIViewAutoresizingFlexibleHeight;
    _carousel.type = iCarouselTypeCustom;
	_carousel.delegate = self;
	_carousel.dataSource = self;
}

-(void) resetView:(int)initialCard
{
    self->m_selectionIndex = -1;
    [_carousel scrollToItemAtIndex:initialCard animated:NO];
    [_carousel reloadData];
}

-(UIView*) getView
{
    return _carousel;
}

-(int) getSelectionIndex
{
    if(TestCycleCarouselMode)
    {
        // -1 because we added a dummy state for 'cycle' button
        return self->m_selectionIndex - 1;
    }
    else
    {
        return self->m_selectionIndex;
    }
}

- (int)getItemCount
{
    return static_cast<int>(m_stateViewData.size());
}

- (NSInteger)numberOfItemsInCarousel:(iCarousel *)carousel
{
    return [self getItemCount];
}

- (CGFloat) carouselItemWidth:(iCarousel*)carousel
{
    return [self getItemWidth];
}

- (UIView *)twitterViewForItemAtIndex:(NSInteger)index reusingView:(UIView *)view
{
    TwitterCardView* twitView = nil;
    if(view == nil || [view class] != [TwitterCardView class])
    {
        twitView = [[TwitterCardView alloc] initWithParams:m_pInterop :m_pImageStore];
    }
    else
    {
        twitView = (TwitterCardView*)view;
    }
    
    if(index < m_stateViewData.size())
    {
        std::vector<std::string> data = m_stateViewData[index].second;
        
        NSMutableArray* deeplinkUrls = [[NSMutableArray alloc]init];
        NSMutableArray* linkUrls = [[NSMutableArray alloc]init];
        NSMutableArray* startIndices = [[NSMutableArray alloc]init];
        NSMutableArray* endIndices = [[NSMutableArray alloc]init];
        
        if(data.size() >= TWEET_LINKS_START)
        {
            int linkIndex = 0;
            for(int i = TWEET_LINKS_START; i < data.size(); i += TWEET_LINKS_SIZE, ++linkIndex)
            {
                [deeplinkUrls addObject:[NSString stringWithUTF8String:data[i + 0].c_str()]];
                [linkUrls addObject:[NSString stringWithUTF8String:data[i + 1].c_str()]];
                [startIndices addObject:[NSString stringWithUTF8String:data[i + 2].c_str()]];
                [endIndices addObject:[NSString stringWithUTF8String:data[i + 3].c_str()]];
            }
        }
        
        [twitView setContent:[NSString stringWithUTF8String: data[TWEET_USER_NAME].c_str()]
                  screenName:[NSString stringWithUTF8String: data[TWEET_SCREEN_NAME].c_str()]
                tweetContent:[NSString stringWithUTF8String: data[TWEET_TEXT].c_str()]
                   userImage:[NSString stringWithUTF8String: data[TWEET_PROFILE_URL].c_str()]
                 bannerImage:[NSString stringWithUTF8String: data[TWEET_BANNER_URL].c_str()]
                   createdAt:[NSString stringWithUTF8String: data[TWEET_CREATED_AT].c_str()]
                profileColor:[NSString stringWithUTF8String: data[TWEET_PROFILE_COLOR].c_str()]
                     tweetId:[NSString stringWithUTF8String: data[TWEET_ID].c_str()]
                 tweetCutoff:[[NSString stringWithUTF8String: data[TWEET_CUTOFF].c_str()] integerValue]
                 doesLinkOut:[[NSString stringWithUTF8String: data[TWEET_DOES_LINK_OUT].c_str()]boolValue]
                deeplinkUrls:deeplinkUrls
                    linkUrls:linkUrls
            linkStartIndices:startIndices
              linkEndIndices:endIndices];
        
        
        [endIndices removeAllObjects];
        [endIndices dealloc];
        
        [startIndices removeAllObjects];
        [startIndices dealloc];
        
        [linkUrls removeAllObjects];
        [linkUrls dealloc];
        
        [deeplinkUrls removeAllObjects];
        [deeplinkUrls dealloc];
    }
    
    return twitView;
}

- (UIView *)tourCardViewForItemAtIndex:(NSInteger)index reusingView:(UIView *)view
{
    TourExplorerCardView* tourCardView;
    
    if(view == nil || [view class] != [TourExplorerCardView class])
    {
        tourCardView = [[TourExplorerCardView alloc]init];
    }
    else
    {
        tourCardView = (TourExplorerCardView*)view;
    }
    
    if(index < m_stateViewData.size())
    {
        [tourCardView setContent:[NSString stringWithUTF8String:m_stateViewData[index].second[STATE_IMAGE].c_str()]
                                :[NSString stringWithUTF8String:m_stateViewData[index].second[STATE_NAME].c_str()]
                                :[NSString stringWithUTF8String:m_stateViewData[index].second[STATE_TEXT].c_str()]];
    }
    
    return tourCardView;
}

- (UIView *)carousel:(iCarousel *)carousel viewForItemAtIndex:(NSInteger)index reusingView:(UIView *)view
{
    if(index >= m_stateViewData.size())
    {
        return view;
    }
    
    if(m_stateViewData[index].first)
    {
        return [self twitterViewForItemAtIndex:index reusingView:view];
    }
    else
    {
        return [self tourCardViewForItemAtIndex:index reusingView:view];
    }
}

- (CATransform3D)carousel:(iCarousel *)carousel itemTransformForOffset:(CGFloat)offset baseTransform:(CATransform3D)transform
{
    // implement 'flip3D' style carousel
    // note, in valueForOption, must have rule for 'iCarouselOptionFadeMax' to return 0.f if carousel.type == iCarouselTypeCustom
    //transform = CATransform3DRotate(transform, static_cast<float>(M_PI / 8.0f), 0.0f, 1.0f, 0.0f);
    //return CATransform3DTranslate(transform, 0.0f, 0.0f, offset * carousel.itemWidth);
    
    CGFloat distance = 100.0f; //number of pixels to move the items away from camera
    CGFloat z = - fminf(1.0f, std::abs(offset)) * distance;
    CGFloat spacing = 1.05f;
    CGFloat itemWidth = [self carouselItemWidth:carousel];
    return CATransform3DTranslate(transform, (offset * itemWidth) * spacing, 0.0f, z);
}

-(void)carousel:(iCarousel *)carousel didSelectItemAtIndex:(NSInteger)index
{
    if(TestCycleCarouselMode)
    {
        // index 0 is a dummy to test different carousel modes
        if(index == 0)
        {
            _carousel.type = (iCarouselType)((_carousel.type + 1) % 12);
            [_carousel reloadData];
        }
        else if(m_selectionIndex == index && !m_scrollingToSelected)
        {
            [self->m_interactionHandlerInstance performSelector:self->m_selectionTappedHandler];
        }
        else
        {
            m_scrollingToSelected = true;
            [self->m_interactionHandlerInstance performSelector:self->m_selectionInteractionHandler];
        }
    }
    else if(m_selectionIndex == index && !m_scrollingToSelected)
    {
        [self->m_interactionHandlerInstance performSelector:self->m_selectionTappedHandler];
    }
    else
    {
        m_scrollingToSelected = true;
        [self->m_interactionHandlerInstance performSelector:self->m_selectionInteractionHandler];
    }
}

- (void)carouselDidEndScrollingAnimation:(iCarousel *)carousel
{
    if(TestCycleCarouselMode)
    {
        if(carousel.currentItemIndex > 0)
        {
            m_selectionIndex = carousel.currentItemIndex;
            [self->m_interactionHandlerInstance performSelector:self->m_currentItemChangedHandler];
        }
    }
    else
    {
        m_selectionIndex = static_cast<int>(carousel.currentItemIndex);
        [self->m_interactionHandlerInstance performSelector:self->m_currentItemChangedHandler];
    }
    m_scrollingToSelected = false;
}

- (CGFloat)carousel:(iCarousel *)carousel valueForOption:(iCarouselOption)option withDefault:(CGFloat)value
{
    switch (option)
    {
        case iCarouselOptionWrap:
        {
            return _wrap;
        }
        case iCarouselOptionSpacing:
        {
            return value * 1.05f;
        }
        case iCarouselOptionFadeMax:
        {
            /*if (carousel.type == iCarouselTypeCustom)
            {
                return 0.0f;
            }*/
            return value;
        }
        case iCarouselOptionVisibleItems:
        {
            return 7.0f;
        }
        default:
        {
            return value;
        }
    }
}

- (float) getItemWidth
{
    const bool isPhone = ExampleApp::Helpers::UIHelpers::UsePhoneLayout();
    return isPhone ? ITEM_WIDTH_IPHONE : ITEM_WIDTH;
}

- (float) getItemHeight
{
    const bool isPhone = ExampleApp::Helpers::UIHelpers::UsePhoneLayout();
    return isPhone ? ITEM_HEIGHT_IPHONE : ITEM_HEIGHT;
}

@end
