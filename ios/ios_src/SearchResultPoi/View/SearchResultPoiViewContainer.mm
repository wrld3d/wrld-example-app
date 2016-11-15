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
#include "SwallowPersonSearchResultPoiView.h"
#include "SwallowMeetingRoomSearchResultPoiView.h"
#include "SwallowWorkingGroupSearchResultPoiView.h"
#include "SwallowFacilitySearchResultPoiView.h"
#include "SwallowDepartmentSearchResultPoiView.h"
#include "EegeoSearchResultPoiView.h"
#include "ExampleTourSearchResultPoiView.h"
#include "SwallowSearchConstants.h"

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

    self->m_pCurrentActiveVendorView = [self createSearchResultPoiViewForVendor:pModel->GetVendor() :pModel->GetCategory()];
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

- (UIView<SearchResultPoiView>*) createSearchResultPoiViewForVendor:(const std::string&)vendor :(const std::string&)category
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
    else if(vendor == ExampleApp::Search::EegeoVendorName && category == ExampleApp::Search::Swallow::SearchConstants::PERSON_CATEGORY_NAME)
    {
        return [[SwallowPersonSearchResultPoiView alloc] initWithInterop:m_pInterop];
    }
    else if(vendor == ExampleApp::Search::EegeoVendorName && category == ExampleApp::Search::Swallow::SearchConstants::MEETING_ROOM_CATEGORY_NAME)
    {
        return [[SwallowMeetingRoomSearchResultPoiView alloc] initWithInterop:m_pInterop];
    }
    else if(vendor == ExampleApp::Search::EegeoVendorName && category == ExampleApp::Search::Swallow::SearchConstants::WORKING_GROUP_CATEGORY_NAME)
    {
        return [[SwallowWorkingGroupSearchResultPoiView alloc] initWithInterop:m_pInterop];
    }
    else if(vendor == ExampleApp::Search::EegeoVendorName && (category == ExampleApp::Search::Swallow::SearchConstants::PRINT_STATION_CATEGORY_NAME
                                                              || category == ExampleApp::Search::Swallow::SearchConstants::TOILETS_CATEGORY_NAME
                                                              || category == ExampleApp::Search::Swallow::SearchConstants::FACILITY_CATEGORY_NAME
                                                              || category == ExampleApp::Search::Swallow::SearchConstants::EMERGENCY_EXIT_CATEGORY_NAME
                                                              || category == ExampleApp::Search::Swallow::SearchConstants::STATIONERY_CATEGORY_NAME))
    {
        return [[SwallowFacilitySearchResultPoiView alloc] initWithInterop:m_pInterop];
    }
    else if(vendor == ExampleApp::Search::EegeoVendorName && category == ExampleApp::Search::Swallow::SearchConstants::DEPARTMENT_CATEGORY_NAME)
    {
        return [[ExampleTourSearchResultPoiView alloc] initWithInterop:m_pInterop];
        return [[SwallowDepartmentSearchResultPoiView alloc] initWithInterop:m_pInterop];
    }
    
    Eegeo_ASSERT(false, "Unknown POI vendor %s, cannot create view instance.\n", vendor.c_str());
    return NULL; // This is just to avoid warning for no return value after assert.
}

@end
