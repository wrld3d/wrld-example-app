// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include <string>
#include <algorithm>
#include "SearchResultPoiView.h"
#include "MathFunc.h"
#include "UIColors.h"
#include "ImageHelpers.h"
#include "IconResources.h"
#include "StringHelpers.h"
#import "UIView+TouchExclusivity.h"
#include "SearchResultPoiViewContainer.h"
#include "SearchResultPoiViewInterop.h"
#include "App.h"
#include "SearchResultModel.h"
#include "SearchVendorNames.h"
#include "YelpSearchResultPoiView.h"
#include "GeoNamesSearchResultPoiView.h"
#include "ExampleTourSearchResultPoiView.h"

@interface SearchResultPoiViewContainer()<UIGestureRecognizerDelegate>
{
}
@end

@implementation SearchResultPoiViewContainer

- (id)initWithoutParams
{
    self = [super init];
    
    if(self)
    {
        m_pInterop = Eegeo_NEW(ExampleApp::SearchResultPoi::View::SearchResultPoiViewInterop)(self);
    }

    return self;
}

- (void)dealloc
{
    Eegeo_DELETE m_pInterop;
    [self removeFromSuperview];
    [super dealloc];
}

- (void) open:(const ExampleApp::Search::SdkModel::SearchResultModel*)pModel :(bool)isPinned
{
    Eegeo_ASSERT(m_pCurrentActiveVendorView == NULL);

    self->m_pCurrentActiveVendorView = [self createSearchResultPoiViewForVendor:pModel->GetVendor()];
    [[self superview] addSubview: self->m_pCurrentActiveVendorView];
    [self->m_pCurrentActiveVendorView layoutSubviews];
    [self->m_pCurrentActiveVendorView setContent:pModel :isPinned];
    [self->m_pCurrentActiveVendorView setFullyActive];
}

- (void) close
{
    Eegeo_ASSERT(m_pCurrentActiveVendorView != NULL);
    
    [self->m_pCurrentActiveVendorView setFullyInactive];
    [self->m_pCurrentActiveVendorView removeFromSuperview];
    [self->m_pCurrentActiveVendorView release];
    
    m_pCurrentActiveVendorView = NULL;
}

- (void) updateImage:(const std::string&)url :(bool)success bytes:(const std::vector<Byte>*)bytes;
{
    Eegeo_ASSERT(m_pCurrentActiveVendorView != NULL);
    
    [self->m_pCurrentActiveVendorView updateImage:url :success bytes:bytes];
}

- (ExampleApp::SearchResultPoi::View::SearchResultPoiViewInterop*)getInterop
{
    return m_pInterop;
}

- (UIView<SearchResultPoiView>*) createSearchResultPoiViewForVendor:(const std::string&)vendor
{
    if(vendor == ExampleApp::Search::YelpVendorName)
    {
        return [[YelpSearchResultPoiView alloc] initWithInterop:m_pInterop];
    }
    else if(vendor == ExampleApp::Search::GeoNamesVendorName)
    {
        return [[GeoNamesSearchResultPoiView alloc] initWithInterop:m_pInterop];
    }
    else if(vendor == ExampleApp::Search::ExampleTourVendorName)
    {
        return [[ExampleTourSearchResultPoiView alloc] initWithInterop:m_pInterop];
    }
    
    Eegeo_ASSERT(false, "Unknown POI vendor %s, cannot create view instance.\n", vendor.c_str());
    return NULL; // This is just to avoid warning for no return value after assert.
}

@end
