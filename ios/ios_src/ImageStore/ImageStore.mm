// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#import "ImageStore.h"

typedef std::pair<UIImageView*, ImageLoadedCallback> ViewCallbackPair;

struct ImageOperationData
{
    ImageFetchOperation* inFlightOperation;
    std::vector<ViewCallbackPair> viewCallbacks;
};

struct StoredImageData
{
    UIImage* image;
    std::vector<UIImageView*> views;
};

@implementation ImageStore
{
    NSOperationQueue* m_pOperationQueue;
    
    std::map<std::string, StoredImageData> m_imageStoreMap;
    std::map<std::string, ImageOperationData> m_urlImageOperationMap;
    
    NSLock* m_pOperationLock;
}

- (id) init;
{
    if(self = [super init])
    {
        m_pOperationQueue = [[NSOperationQueue alloc]init];
        m_pOperationQueue.maxConcurrentOperationCount = 1;
    }
    
    return self;
}

- (void)dealloc
{
    for(std::map<std::string, ImageOperationData>::const_iterator it = m_urlImageOperationMap.begin(); it != m_urlImageOperationMap.end(); ++it)
    {
        const std::vector<ViewCallbackPair>& callbacks = (*it).second.viewCallbacks;
        
        for(std::vector<ViewCallbackPair>::const_iterator callbackIt = callbacks.begin(); callbackIt != callbacks.end(); ++callbackIt)
        {
            [(*callbackIt).second release];
        }
    }
    
    m_urlImageOperationMap.clear();
    
    for(std::map<std::string, StoredImageData>::iterator it = m_imageStoreMap.begin(); it != m_imageStoreMap.end(); ++it)
    {
        const std::vector<UIImageView*>& views = (*it).second.views;
        
        for(std::vector<UIImageView*>::const_iterator viewIt = views.begin(); viewIt != views.end(); ++viewIt)
        {
            (*viewIt).image = nil;
        }
        
        [(*it).second.image release];
    }
    
    m_imageStoreMap.clear();
    
    [m_pOperationQueue cancelAllOperations];
    [m_pOperationQueue release];
    
    [super dealloc];
}

- (void) loadImage:(std::string)urlString :(UIImageView*)targetView :(ImageLoadedCallback)callback
{
    [self loadImage:urlString :targetView :callback :0.0f];
}

- (void) loadImage:(std::string)urlString :(UIImageView*)targetView :(ImageLoadedCallback)callback :(float)cropSize;
{
    [self releaseImageForView:targetView];
    
    [m_pOperationLock lock];
    
    std::map<std::string, StoredImageData>::iterator it = m_imageStoreMap.find(urlString);
    
    if(it != m_imageStoreMap.end())
    {
        (*it).second.views.push_back(targetView);
        
        callback((*it).second.image);
    }
    else
    {
        if(m_urlImageOperationMap.find(urlString) == m_urlImageOperationMap.end())
        {
            ImageFetchOperation* imageFetchOperation = [[ImageFetchOperation alloc]initWithParams:[NSURL URLWithString:[NSString stringWithUTF8String:urlString.c_str()]] : cropSize];
            imageFetchOperation.delegate = self;
            imageFetchOperation.queuePriority = NSOperationQueuePriorityVeryHigh;
            
            [m_pOperationQueue addOperation:imageFetchOperation];
            
            ImageOperationData imageLoadDetails;
            
            imageLoadDetails.inFlightOperation = imageFetchOperation;
            imageLoadDetails.viewCallbacks.push_back(ViewCallbackPair(targetView, [[callback copy]retain]));
            
            m_urlImageOperationMap[urlString] = imageLoadDetails;
        }
        else
        {
            m_urlImageOperationMap[urlString].viewCallbacks.push_back(ViewCallbackPair(targetView, [[callback copy]retain]));
        }
    }
    
    [m_pOperationLock unlock];
}

- (void) onImageFetchComplete:(NSURL*)url :(UIImage*)image
{
    [m_pOperationLock lock];
    
    std::string urlString = [[url absoluteString]UTF8String];
    
    if(m_urlImageOperationMap.find(urlString) != m_urlImageOperationMap.end())
    {
        const std::vector<ViewCallbackPair>& viewCallbacks = m_urlImageOperationMap[urlString].viewCallbacks;
        
        for(std::vector<ViewCallbackPair>::const_iterator it = viewCallbacks.begin(); it != viewCallbacks.end(); ++it)
        {
            ImageLoadedCallback __block callback = [(*it).second copy];
            [(*it).second release];
            
            [[NSOperationQueue mainQueue] addOperationWithBlock:^()
            {
                callback(image);
                [callback release];
            }];
            
            std::map<std::string, StoredImageData>::iterator imageStoreMapIt = m_imageStoreMap.find(urlString);
            
            if(imageStoreMapIt == m_imageStoreMap.end())
            {
                if(image != nil)
                {
                    StoredImageData storedImageData;
                    storedImageData.image = [image retain];
                    storedImageData.views.push_back((*it).first);
                    
                    m_imageStoreMap[urlString] = storedImageData;
                }
            }
            else
            {
                (*imageStoreMapIt).second.views.push_back((*it).first);
            }
        }
        
        m_urlImageOperationMap.erase(urlString);
    }
    
    [m_pOperationLock unlock];
}

- (void) releaseImageForView:(UIImageView*)view
{
    [m_pOperationLock lock];
    
    for(std::map<std::string, ImageOperationData>::iterator it = m_urlImageOperationMap.begin(); it != m_urlImageOperationMap.end(); ++it)
    {
        std::vector<ViewCallbackPair>& viewCallbacks = (*it).second.viewCallbacks;
        
        for(std::vector<ViewCallbackPair>::iterator viewCallbackIt = viewCallbacks.begin(); viewCallbackIt != viewCallbacks.end(); ++viewCallbackIt)
        {
            if((*viewCallbackIt).first == view)
            {
                viewCallbacks.erase(viewCallbackIt);
                break;
            }
        }
        
        if(viewCallbacks.empty())
        {
            [(*it).second.inFlightOperation cancel];
            m_urlImageOperationMap.erase(it);
            break;
        }
    }
    
    for(std::map<std::string, StoredImageData>::iterator it = m_imageStoreMap.begin(); it != m_imageStoreMap.end(); ++it)
    {
        std::vector<UIImageView*>& views = (*it).second.views;
        
        for(std::vector<UIImageView*>::iterator viewIt = views.begin(); viewIt != views.end(); ++viewIt)
        {
            if((*viewIt) == view)
            {
                views.erase(viewIt);
                break;
            }
        }
        
        if(views.empty())
        {
            [(*it).second.image release];
            m_imageStoreMap.erase(it);
            break;
        }
    }
    
    view.image = nil;
    
    [m_pOperationLock unlock];
}

@end