// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#include "DirectionsMenuStaticView.h"
#include "DirectionsMenuWayPointViewCell.h"
#include "MenuSectionViewModel.h"
#include "DirectionsMenuView.h"
#include "DirectionsMenuViewInterop.h"
#include "UIColors.h"

@interface DirectionsMenuStaticView()
{
    ExampleApp::Menu::View::IMenuSectionViewModel* m_pSearchResultsSection;
    UIView *m_pView;
    int selectedIndex;
}

@property (retain, nonatomic) IBOutlet UIView *startRouteBgView;
@property (retain, nonatomic) IBOutlet UIView *endRouteBgView;
@property (retain, nonatomic) IBOutlet NSLayoutConstraint *contentHeightConstraint;
@property (retain, nonatomic) IBOutlet NSLayoutConstraint *endHeightConstraint;
@property (retain, nonatomic) IBOutlet NSLayoutConstraint *startContainerHeightConstraint;
@property (retain, nonatomic) IBOutlet UIButton *optionsButton;
@property (retain, nonatomic) IBOutlet UIButton *reverseButton;
@property (retain, nonatomic) IBOutlet UITableView *wayPointsTableView;

- (IBAction)optionsAction:(id)sender;

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
    
    selectedIndex = -1;
    
    UINib *wayPointsCellNib = [UINib nibWithNibName:@"DirectionsMenuWayPointViewCell" bundle: [NSBundle mainBundle]];
    [self.wayPointsTableView registerNib:wayPointsCellNib forCellReuseIdentifier:@"DirectionsMenuWayPointViewCell"];

}


- (void) layoutSubviews
{
    [super layoutSubviews];
}

- (IBAction)optionsAction:(id)sender {
 
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
    [_wayPointsTableView reloadData];
    

}

#define  UITableViewDataSource

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    
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
    
    ExampleApp::Menu::View::MenuItemModel item = m_pSearchResultsSection->GetItemAtIndex(static_cast<int>(indexPath.row));
    
    DirectionsMenuWayPointViewCell *cell = (DirectionsMenuWayPointViewCell*)[self.wayPointsTableView dequeueReusableCellWithIdentifier:@"DirectionsMenuWayPointViewCell"];
    [cell.wayPointNumberlbl setText:[NSString stringWithFormat:@"%li",(long)indexPath.row+1]];
    
    if(indexPath.row < m_pSearchResultsSection->Size())
    {
        ExampleApp::Menu::View::MenuItemModel item = m_pSearchResultsSection->GetItemAtIndex(static_cast<int>(indexPath.row));
        std::string json = item.SerializeJson();
    }
    
    if(indexPath.row == selectedIndex)
    {
        [cell.mainContainerView setBackgroundColor:[UIColor colorWithRed:16.0f/255.0f green:64.0f/255.0f blue:160.0f/255.0f alpha:1.0f]];
    }
    else
    {
        [cell.mainContainerView setBackgroundColor:[UIColor colorWithRed:248.0f/255.0f green:248.0f/255.0f blue:248.0f/255.0f alpha:1.0f]];
    }
    
    if(indexPath.row == 0)
    {
        [cell.wayPointImageView setImage:[UIImage imageNamed:@"DirectionCard_RouteStart"]];
        [cell.wayPointMainTitlelbl setText:@"Westfield Valley Mall"];
        [cell.wayPointSubCategorylbl setText:@"South Entrance"];
        
    }
    else if (indexPath.row == 1)
    {
        [cell.wayPointImageView setImage:[UIImage imageNamed:@"DirectionCard_EnterMallSelected"]];
        [cell.wayPointMainTitlelbl setText:@"50 yd"];
        [cell.wayPointSubCategorylbl setText:@"Enter Mall"];
        
        
    }
    else if (indexPath.row == 2)
    {
        [cell.wayPointImageView setImage:[UIImage imageNamed:@"DirectionCard_StraightAhead"]];
        [cell.wayPointMainTitlelbl setText:@"40 yd"];
        [cell.wayPointSubCategorylbl setText:@"Turn left along main concourse"];
        
    }
    else if (indexPath.row == 3)
    {
        [cell.wayPointImageView setImage:[UIImage imageNamed:@"DirectionCard_TurnLeft"]];
        [cell.wayPointMainTitlelbl setText:@"Turn Left"];
        [cell.wayPointSubCategorylbl setText:@"Then 400 yd along main course"];
        
    }
    else if (indexPath.row == 4)
    {
        [cell.wayPointImageView setImage:[UIImage imageNamed:@"DirectionCard_ElevatorSelected"]];
        [cell.wayPointMainTitlelbl setText:@"Elevator to 2nd floor"];
        [cell.wayPointSubCategorylbl setText:@""];
        
    }
    else if (indexPath.row == 5)
    {
        [cell.wayPointImageView setImage:[UIImage imageNamed:@"DirectionCard_TurnRight"]];
        [cell.wayPointMainTitlelbl setText:@"Turn Right"];
        [cell.wayPointSubCategorylbl setText:@"Then 50 yd along main concourse"];
        
    }
    else if (indexPath.row == 6)
    {
        [cell.wayPointImageView setImage:[UIImage imageNamed:@"DirectionCard_VeerLeft.png"]];
        [cell.wayPointMainTitlelbl setText:@"Left"];
        [cell.wayPointSubCategorylbl setText:@"The 50 yd along main concourse"];
        
    }
    
    return cell;
}

- (CGFloat)tableView:(UITableView *)tableView heightForRowAtIndexPath:(NSIndexPath *)indexPath {
    
    return 45;
}


- (void)tableView:(UITableView *)tableView didSelectRowAtIndexPath:(NSIndexPath *)indexPath
{
    [tableView deselectRowAtIndexPath:indexPath animated:NO];
    
    DirectionsMenuView *parentView = (DirectionsMenuView *)m_pView;
    ExampleApp::DirectionsMenu::View::DirectionsMenuViewInterop *interop = [parentView getDirectionsMenuInterop];
    interop->HandleWayPointSelected(static_cast<int>(indexPath.row));
    
}

-(void)SetSearchMenuView:(UIView *)_parentView   {
    
    m_pView = _parentView;
}

-(void)SetHighlightItem:(int)highlightItem  {
    
    selectedIndex = highlightItem;
    [_wayPointsTableView reloadData];
}

-(float)getEstimatedHeight {

    if(m_pSearchResultsSection == NULL)
    {
        return _headerView.bounds.size.height + _bottomBarView.bounds.size.height + (_hideOptionsView.bounds.size.height);
    }
    else
    {
        return _headerView.bounds.size.height + _bottomBarView.bounds.size.height + (45  * m_pSearchResultsSection->Size()) + (_hideOptionsView.bounds.size.height);
    }
}

- (void) populateCellWithJson:(std::string)json :(UITableViewCell*)cell
{
    rapidjson::Document document;
    if (!document.Parse<0>(json.c_str()).HasParseError())
    {
        std::string name = document["name"].GetString();
        const std::string icon = document.HasMember("icon") ? document["icon"].GetString() : "misc";
        cell.textLabel.text = [NSString stringWithUTF8String:name.c_str()];
        std::string details = "";
        if (document.HasMember("details"))
        {
            details = document["details"].GetString();
        }
        cell.detailTextLabel.text = [NSString stringWithUTF8String:details.c_str()];

    }
}

- (void)dealloc {
    
    [_contentHeightConstraint release];
    [_endHeightConstraint release];
    [_optionsButton release];
    [_exitDirectionsBtn release];
    [_endRouteTextField release];
    [_startRouteTextField release];
    
    [_startContainerHeightConstraint release];
    [super dealloc];
}

@end