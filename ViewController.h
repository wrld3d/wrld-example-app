#import <UIKit/UIKit.h>
#import <GLKit/GLKit.h>
#import "AppInterface.h"
#import "AppOnMap.h"
#import "ViewControllerBase.h"
#import "External/Reachability/Reachability.h"

@interface ViewController : ViewControllerBase{

    MyApp * myApp;
    bool precaching;
    
    IBOutlet UITextField* fps;
    IBOutlet UITextField* smoothedFrameTime;
    IBOutlet UITextField* mem;
    IBOutlet UITextField* terrains;
    IBOutlet UITextField* buildings;
    IBOutlet UITextField* models;
    IBOutlet UITextField* camera;
    IBOutlet UITextField* payloads;
    IBOutlet UITextField* renderData;
    
    IBOutlet UIButton* debug;
    IBOutlet UIButton* clearCache;
    IBOutlet UIButton* precacheVolume;
    IBOutlet UIProgressView* precacheVolumeProgress;
    IBOutlet UIButton* toggleMidokiModels;
    IBOutlet UIButton* wireframeBuildings;
    
    IBOutlet UIButton* streamingEnabled;
    
    //debug jump
    IBOutlet UIButton* places;
    IBOutlet UIButton* sf;
    IBOutlet UIButton* ldn;
    IBOutlet UIButton* ny;
    IBOutlet UIButton* chic;
    IBOutlet UIButton* la;
    IBOutlet UIButton* edin;
    IBOutlet UIButton* dun;
}

@property (nonatomic, retain) IBOutlet UITextField* fps;
@property (nonatomic, retain) IBOutlet UITextField* smoothedFrameTime;
@property (nonatomic, retain) IBOutlet UITextField* mem;
@property (nonatomic, retain) IBOutlet UITextField* terrains;
@property (nonatomic, retain) IBOutlet UITextField* buildings;
@property (nonatomic, retain) IBOutlet UITextField* models;
@property (nonatomic, retain) IBOutlet UITextField* camera;
@property (nonatomic, retain) IBOutlet UITextField* payloads;
@property (nonatomic, retain) IBOutlet UITextField* renderData;

@property (nonatomic, retain) IBOutlet UIButton* debug;
@property (nonatomic, retain) IBOutlet UIButton* clearCache;
@property (nonatomic, retain) IBOutlet UIButton* precacheVolume;
@property (nonatomic, retain) IBOutlet UIProgressView* precacheVolumeProgress;
@property (nonatomic, retain) IBOutlet UIButton* toggleMidokiModels;
@property (nonatomic, retain) IBOutlet UIButton* reinflateBuildings;

@property (nonatomic, retain) IBOutlet UIButton* streamingEnabled;

//debug places
@property (nonatomic, retain) IBOutlet UIButton* places;
@property (nonatomic, retain) IBOutlet UIButton* sf;
@property (nonatomic, retain) IBOutlet UIButton* ldn;
@property (nonatomic, retain) IBOutlet UIButton* ny;
@property (nonatomic, retain) IBOutlet UIButton* chic;
@property (nonatomic, retain) IBOutlet UIButton* la;
@property (nonatomic, retain) IBOutlet UIButton* edin;
@property (nonatomic, retain) IBOutlet UIButton* dun;

@end
