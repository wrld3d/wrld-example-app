

#include "DirectionsMenuStaticView.h"

#include "DirectionsMenuWayPointViewCell.h"

@implementation DirectionsMenuStaticView

- (id)initWithCoder:(NSCoder *)aDecoder  {
    
    if(self = [super initWithCoder:aDecoder])
    {
        NSLog(@"ss");
        
        UIButton *reverseButton = [self viewWithTag:3];
        [reverseButton.layer setBorderWidth:1.0f];
        [reverseButton.layer setBorderColor:[UIColor whiteColor].CGColor];
        reverseButton.layer.cornerRadius = 3.0f;
        
        UIView *startRouteBgView = [self viewWithTag:1];
        startRouteBgView.layer.cornerRadius = 3.0f;
        
        UIView *endRouteBgView = [self viewWithTag:2];
        endRouteBgView.layer.cornerRadius = 3.0f;
    }
    
    return self;
}


- (void) layoutSubviews
{
    [super layoutSubviews];
    
    _contentHeightConstraint.constant = self.headerView.bounds.size.height + self.bottomBarView.bounds.size.height + self.wayPointsTableView.bounds.size.height + self.hideOptionsView.bounds.size.height;
}

- (IBAction)optionsAction:(id)sender {
 
    if(_optionsButton.isSelected)
    {
        [_optionsButton setSelected:NO];
        
        [_endHeightConstraint setConstant:115.0f];
    
        [UIView animateWithDuration:0.5
                     animations:^{
                         [self layoutIfNeeded];
                     }];
    }
    else
    {
        [_optionsButton setSelected:YES];
        [_endHeightConstraint setConstant:10.0f];
        
        [UIView animateWithDuration:0.5
                         animations:^{
                             [self layoutIfNeeded];
                         }];
    }
    
    
}

#define  UITableViewDataSource

- (NSInteger)tableView:(UITableView *)tableView numberOfRowsInSection:(NSInteger)section
{
    return 7;
}


- (UITableViewCell *)tableView:(UITableView *)tableView cellForRowAtIndexPath:(NSIndexPath *)indexPath
{
    
    DirectionsMenuWayPointViewCell *cell = (DirectionsMenuWayPointViewCell*)[self.wayPointsTableView dequeueReusableCellWithIdentifier:@"DirectionsMenuWayPointViewCell"];
    [cell.wayPointNumberlbl setText:[NSString stringWithFormat:@"%li",(long)indexPath.row+1]];
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

- (void)dealloc {
    [_contentHeightConstraint release];
    [_endHeightConstraint release];
    [_optionsButton release];
    [_exitDirectionsBtn release];
    [_endRouteTextField release];
    [_startRouteTextField release];
    [super dealloc];
}

@end