// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DirectionsMenuStaticView.h"
#include "DirectionsMenuWayPointViewCell.h"
#include "MenuSectionViewModel.h"
#include "DirectionsMenuView.h"
#include "DirectionsMenuViewInterop.h"
#include "UIColors.h"
#include "DirectionSuggestionTableViewCell.h"
#include "LatLongAltitude.h"

@interface DirectionsMenuStaticView()
{
    ExampleApp::Menu::View::IMenuSectionViewModel* m_pSearchResultsSection;
    
    std::vector< ExampleApp::Search::SdkModel::SearchResultModel> m_pSuggestionsResults;

    ExampleApp::Search::SdkModel::SearchResultModel m_pStartLoc;
    ExampleApp::Search::SdkModel::SearchResultModel m_pEndLoc;
    
    UIView *m_pView;
    int selectedIndex;
    int searchType;
    BOOL startLocationSearched;
    BOOL endLocationSearched;
    BOOL startMyLocationSelected;
}

@property (retain, nonatomic) IBOutlet UIView *startRouteBgView;
@property (retain, nonatomic) IBOutlet UIView *endRouteBgView;
@property (retain, nonatomic) IBOutlet NSLayoutConstraint *contentHeightConstraint;
@property (retain, nonatomic) IBOutlet NSLayoutConstraint *endHeightConstraint;
@property (retain, nonatomic) IBOutlet NSLayoutConstraint *startContainerHeightConstraint;
@property (retain, nonatomic) IBOutlet UIButton *optionsButton;
@property (retain, nonatomic) IBOutlet UITableView *wayPointsTableView;

- (IBAction)optionsAction:(id)sender;
@property (retain, nonatomic) IBOutlet NSLayoutConstraint *heightDropSpacingConstraint;
@property (retain, nonatomic) IBOutlet UIView *suggestionsView;
@property (retain, nonatomic) IBOutlet UILabel *minCounterLabel;
@property (retain, nonatomic) IBOutlet UILabel *secCounterLabel;
@property (retain, nonatomic) IBOutlet UILabel *staticMinsLabel;

@property (retain, nonatomic) IBOutlet UITableView *suggestionsTableView;
@end

@implementation DirectionsMenuStaticView

- (void)awakeFromNib
{
    m_pSearchResultsSection = NULL;
    //Changes done directly here, we have an object
    [_reverseButton.layer setBorderWidth:1.0f];
    [_reverseButton.layer setBorderColor:[UIColor whiteColor].CGColor];
    _reverseButton.layer.cornerRadius = 3.0f;
    
    _startRouteBgView.layer.cornerRadius = 3.0f;
    _endRouteBgView.layer.cornerRadius = 3.0f;
    
    _wayPointsTableView.delegate = self;
    _wayPointsTableView.dataSource = self;
    
    _suggestionsTableView.delegate = self;
    _suggestionsTableView.dataSource = self;
    
    selectedIndex = -1;
    searchType = -1;
    startMyLocationSelected = true;
    
    UINib *wayPointsCellNib = [UINib nibWithNibName:@"DirectionsMenuWayPointViewCell" bundle: [NSBundle mainBundle]];
    [self.wayPointsTableView registerNib:wayPointsCellNib forCellReuseIdentifier:@"DirectionsMenuWayPointViewCell"];

    
    UINib *suggestionCellNib = [UINib nibWithNibName:@"DirectionSuggestionsViewCell" bundle: [NSBundle mainBundle]];
    [self.suggestionsTableView registerNib:suggestionCellNib forCellReuseIdentifier:@"DirectionSuggestionsViewCell"];
    
    [_startRouteTextField setText:@"My Location"];
    
    [self.minCounterLabel setHidden:YES];
    [self.secCounterLabel setHidden:YES];
    [self.staticMinsLabel setHidden:YES];

}


- (void) layoutSubviews
{
    [super layoutSubviews];
}
- (IBAction)cancelSuggestions:(id)sender
{
    _heightDropSpacingConstraint.constant = 0;
    _suggestionsView.hidden = true;
    searchType = -1;
    [self layoutIfNeeded];
    
    
}
- (void)showStartSuggestions
{
    _heightDropSpacingConstraint.constant = 0;
    _suggestionsView.hidden = false;
    searchType = 1;
    _myLocation.hidden = false;
    [self layoutIfNeeded];
}
- (void)showEndSuggestions
{
    _heightDropSpacingConstraint.constant = 55;
    _suggestionsView.hidden = false;
    searchType = 2;
    _myLocation.hidden = true;
    [self layoutIfNeeded];
}
- (void)reverseAction
{
    ExampleApp::Search::SdkModel::SearchResultModel temp = m_pStartLoc;
    m_pStartLoc = m_pEndLoc;
    m_pEndLoc = temp;

    NSString *temptextStart = _startRouteTextField.text;
    _startRouteTextField.text = _endRouteTextField.text;
    _endRouteTextField.text = temptextStart;
    
}
- (IBAction)optionsAction:(id)sender
{
 
    if(_optionsButton.isSelected)
    {
        [_optionsButton setSelected:NO];
        
        [_endHeightConstraint setConstant:115.0f];
        [_startContainerHeightConstraint setConstant:55.0f];
        [UIView animateWithDuration:0.5
                     animations:^{
                         [self layoutIfNeeded];
                     }];
    }
    else
    {
        [_optionsButton setSelected:YES];
        [_endHeightConstraint setConstant:64.0f];
        [_startContainerHeightConstraint setConstant:0.f];
        [UIView animateWithDuration:0.5
                         animations:^{
                             [self layoutIfNeeded];
                         }];
    }
    
    
}

- (void)updateSearchResultsSection:(ExampleApp::Menu::View::IMenuSectionViewModel*)section  {
    
     m_pSearchResultsSection = section;    
    
    [self UpdateRouteTime];
    [_wayPointsTableView reloadData];
    

}
- (void)updateStartSuggestions:(const std::vector<ExampleApp::Search::SdkModel::SearchResultModel>&) results
{
    m_pSuggestionsResults = results;
    startLocationSearched = false;
    if (m_pSuggestionsResults.size() > 0)
    {
        [self showStartSuggestions];
    }
    [_suggestionsTableView reloadData];
    
}

- (void)updateEndSuggestions:(const std::vector<ExampleApp::Search::SdkModel::SearchResultModel>&) results
{
    m_pSuggestionsResults = results;
    endLocationSearched = false;
    
    if (m_pSuggestionsResults.size() > 0)
    {
        [self showEndSuggestions];
    }
    [_suggestionsTableView reloadData];
    
}
#define  UITableViewDataSource

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    
    if (tableView == _suggestionsTableView)
    {
        
        return m_pSuggestionsResults.size();
        
    }
    if(m_pSearchResultsSection == NULL)
    {
        return 0;
    }
    else
    {
        return m_pSearchResultsSection->Size();        
    }
}



- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    if (tableView == _suggestionsTableView) {
        
        ExampleApp::Search::SdkModel::SearchResultModel item = m_pSuggestionsResults[(static_cast<int>(indexPath.row))];
        
        DirectionSuggestionTableViewCell *cell = (DirectionSuggestionTableViewCell*)[self.suggestionsTableView dequeueReusableCellWithIdentifier:@"DirectionSuggestionsViewCell"];
        
        [cell.titleLabel setText:[NSString stringWithFormat:@"%s",item.GetTitle().c_str()]];

        return cell;
        
    }
    
    
    DirectionsMenuWayPointViewCell *cell = (DirectionsMenuWayPointViewCell*)[self.wayPointsTableView dequeueReusableCellWithIdentifier:@"DirectionsMenuWayPointViewCell"];
    [cell.wayPointNumberlbl setText:[NSString stringWithFormat:@"%li",(long)indexPath.row+1]];
    
    if(indexPath.row < m_pSearchResultsSection->Size())
    {
        ExampleApp::Menu::View::MenuItemModel item = m_pSearchResultsSection->GetItemAtIndex(static_cast<int>(indexPath.row));
 
        std::string json = item.SerializeJson();
        
        rapidjson::Document document;
        
        if (!document.Parse<0>(json.c_str()).HasParseError())
        {
            std::string title = document.HasMember("name") ? document["name"].GetString() : "";
            
            std::string subTitle = document.HasMember("details") ? document["details"].GetString() : "";
            
            std::string icon = document.HasMember("icon") ? document["icon"].GetString() : "misc";
            
            std::string duration = document.HasMember("duration") ? document["duration"].GetString() : "";
            
            [cell.wayPointImageView setImage:[UIImage imageNamed:[NSString stringWithCString:icon.c_str() encoding:NSUTF8StringEncoding]]];
            [cell.wayPointMainTitlelbl setText:[NSString stringWithCString:title.c_str() encoding:NSUTF8StringEncoding]];
            [cell.wayPointSubCategorylbl setText:@""];

        }
        
    }
    
    if(indexPath.row == selectedIndex)
    {
        [cell.mainContainerView setBackgroundColor:[UIColor colorWithRed:16.0f/255.0f green:64.0f/255.0f blue:160.0f/255.0f alpha:1.0f]];
    }
    else
    {
        [cell.mainContainerView setBackgroundColor:[UIColor colorWithRed:248.0f/255.0f green:248.0f/255.0f blue:248.0f/255.0f alpha:1.0f]];
    }
    
    return cell;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    return 45;
}


- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    [tableView deselectRowAtIndexPath:indexPath animated:NO];
    
    if (tableView == _suggestionsTableView) {
    
        ExampleApp::Search::SdkModel::SearchResultModel item = m_pSuggestionsResults[(static_cast<int>(indexPath.row))];
        
        if(searchType == 1 ) //start
        {
            m_pStartLoc = item;
            startLocationSearched = true;
            [_startRouteTextField setText:[NSString stringWithFormat:@"%s",item.GetTitle().c_str()]];
            [self cancelSuggestions:nil];
            [_endRouteTextField becomeFirstResponder];
        }
        
        if(searchType == 2) //end
        {
            m_pEndLoc = item;
            endLocationSearched = true;
            [_endRouteTextField setText:[NSString stringWithFormat:@"%s",item.GetTitle().c_str()]];
            [self cancelSuggestions:nil];
        }
        
        return;
    }
    DirectionsMenuView *parentView = (DirectionsMenuView *)m_pView;
    ExampleApp::DirectionsMenu::View::DirectionsMenuViewInterop *interop = [parentView getDirectionsMenuInterop];
    interop->HandleWayPointSelected(static_cast<int>(indexPath.row));
    
}

-(void)UpdateRouteTime  {
    
    
    [self.minCounterLabel setHidden:YES];
    [self.secCounterLabel setHidden:YES];
    [self.staticMinsLabel setHidden:YES];
    
    if( m_pSearchResultsSection->Size() > 0)
    {
        ExampleApp::Menu::View::MenuItemModel item = m_pSearchResultsSection->GetItemAtIndex(static_cast<int>(0));
        
        std::string json = item.SerializeJson();
        
        rapidjson::Document document;
        
        if (!document.Parse<0>(json.c_str()).HasParseError())
        {
            std::string subTitle = document.HasMember("details") ? document["details"].GetString() : "";
            
            std::string duration = document.HasMember("duration") ? document["duration"].GetString() : "";
            
            int duration_sec = std::stoi( subTitle );
            int mins = duration_sec / 60;
            int sec = duration_sec % 60;
            [self.minCounterLabel setText:[NSString stringWithFormat:@"%i",mins]];
            [self.secCounterLabel setText:[NSString stringWithFormat:@"%isec",sec]];
            
            [self.minCounterLabel setHidden:NO];
            [self.secCounterLabel setHidden:NO];
            [self.staticMinsLabel setHidden:NO];
            
        }
    }
}

- (Eegeo::Space::LatLong) GetStartLocation
{
    if (startLocationSearched)
    {
      return m_pStartLoc.GetLocation();
    }
    return Eegeo::Space::LatLong(0.0f,0.0f);
}
- (Eegeo::Space::LatLong) GetEndLocation
{
    if (endLocationSearched)
    {
        return m_pEndLoc.GetLocation();
    }
    return Eegeo::Space::LatLong(0.0f,0.0f);

}
- (void) resetSuggestionItem
{
    startLocationSearched = false;
    endLocationSearched = false;
    startMyLocationSelected = true;
}
- (BOOL) shouldPerformSearch
{
    if ((startLocationSearched || startMyLocationSelected) && endLocationSearched)
    {
        return true;
    }
    return false;
}
-(void)SetSearchMenuView:(UIView *)_parentView   {
    
    m_pView = _parentView;
}

- (IBAction)MyLocationSelected:(id)sender {
    
    startMyLocationSelected = true;
    [_startRouteTextField setText:@"My Location"];
    [self cancelSuggestions:nil];
    [_endRouteTextField becomeFirstResponder];
    
}

-(void)SetHighlightItem:(int)highlightItem  {
    
    selectedIndex = highlightItem;
    [_wayPointsTableView reloadData];
}

-(float)getEstimatedHeight {

    if(m_pSearchResultsSection == NULL || m_pSearchResultsSection->Size() == 0)
    {
        if (searchType  == 1) {
            return _headerView.bounds.size.height + _bottomBarView.bounds.size.height + (_hideOptionsView.bounds.size.height) + 150;
        }
        if (searchType  == 2) {
            return _headerView.bounds.size.height + _bottomBarView.bounds.size.height + (_hideOptionsView.bounds.size.height) + 175;
        }
        return _headerView.bounds.size.height + _bottomBarView.bounds.size.height + (_hideOptionsView.bounds.size.height);
    }
    else
    {
        return _headerView.bounds.size.height + _bottomBarView.bounds.size.height + (45  * m_pSearchResultsSection->Size()) + (_hideOptionsView.bounds.size.height);
    }
}

- (void)dealloc {
    
    [_contentHeightConstraint release];
    [_endHeightConstraint release];
    [_optionsButton release];
    [_exitDirectionsBtn release];
    [_endRouteTextField release];
    [_startRouteTextField release];\
    
    [_startContainerHeightConstraint release];
    [_heightDropSpacingConstraint release];
    [_suggestionsView release];
    [_suggestionsTableView release];
    [_myLocation release];
    [_minCounterLabel release];
    [_secCounterLabel release];
    [_staticMinsLabel release];
    [super dealloc];
}

@end