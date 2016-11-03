//
//  DirectionSuggestionTableViewCell.m
//  ExampleApp
//
//  Created by Qaiser Shehzad on 11/1/16.
//
//

#import "DirectionSuggestionTableViewCell.h"

@implementation DirectionSuggestionTableViewCell

- (void)awakeFromNib {
    [super awakeFromNib];
    // Initialization code
}

- (void)setSelected:(BOOL)selected animated:(BOOL)animated {
    [super setSelected:selected animated:animated];

    // Configure the view for the selected state
}

- (void)dealloc {
    [_titleLabel release];
    [super dealloc];
}
@end
