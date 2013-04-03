#import <UIKit/UIKit.h>
#import <GLKit/GLKit.h>
#import "AppInterface.h"
#import "AppOnMap.h"
#import "External/Reachability/Reachability.h"

@interface ViewController : GLKViewController <UIGestureRecognizerDelegate>{

    MyApp * myApp;
    bool precaching;
    Eegeo::Rendering::RenderContext* m_renderContext;
    Eegeo::Blitter* m_pBlitter;
    
    UIRotationGestureRecognizer *gestureRotation;
    UIPinchGestureRecognizer *gesturePinch;
    UIPanGestureRecognizer* gesturePan;
    UITapGestureRecognizer* gestureTap;
    UITapGestureRecognizer* gestureDoubleTap;
    UILongPressGestureRecognizer* gesturePress;
    float _previousDist;
    
    IBOutlet UITextField* fps;
    IBOutlet UITextField* avgfps;
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
    IBOutlet UIButton* wireframeBuildings;
    
    IBOutlet UIButton* toggleCollapse;
    IBOutlet UIButton* streamingEnabled;
    IBOutlet UIButton* resetCounters;
    
    //debug jump
    IBOutlet UIButton* places;
    IBOutlet UIButton* sf;
    IBOutlet UIButton* ldn;
    IBOutlet UIButton* ny;
    IBOutlet UIButton* chic;
    IBOutlet UIButton* la;
    IBOutlet UIButton* edin;
    IBOutlet UIButton* glasgow;
    IBOutlet UIButton* sandiego;
    IBOutlet UIButton* cambridge;
    IBOutlet UIButton* oban;
    IBOutlet UIButton* barcelona;
    IBOutlet UIButton* kyoto;
    
    //resource data
    IBOutlet UIButton* resBtnBuildings;
    IBOutlet UIButton* resBtnLandmarks;
    IBOutlet UIButton* resBtnLcm;
    IBOutlet UIButton* resBtnModels;
    IBOutlet UIButton* resBtnPlacenames;
    IBOutlet UIButton* resBtnRoads;
    IBOutlet UIButton* resBtnShadows;
    
    IBOutlet UITextField* resTxtTotalsForAllRes;
    IBOutlet UITextField* resTxtNumResourcesRequested;
    IBOutlet UITextField* resTxtTotalBytesLoaded;
    IBOutlet UITextField* resTxtBytesLoadedFromCacheAndWeb;
    IBOutlet UITextField* resTxtAvgBytesPerSuccessLoad;
    IBOutlet UITextField* resTxtTotalByRequestOutcome;
    IBOutlet UITextField* resTxtAvgLoadTimes;
    IBOutlet UITextField* resTxtAvgBuild;
}

- (void) initInputs;
- (void) initGraphics;
- (void) initWorld;
- (void) initHUD;

- (void) update;
- (void) updateDebugHUD:(CFTimeInterval)timeNow;

@property (nonatomic, retain) IBOutlet UITextField* avgfps;
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
@property (nonatomic, retain) IBOutlet UIButton* reinflateBuildings;

@property (nonatomic, retain) IBOutlet UIButton* toggleCollapse;
@property (nonatomic, retain) IBOutlet UIButton* resetCounters;
@property (nonatomic, retain) IBOutlet UIButton* streamingEnabled;

//debug places
@property (nonatomic, retain) IBOutlet UIButton* places;
@property (nonatomic, retain) IBOutlet UIButton* sf;
@property (nonatomic, retain) IBOutlet UIButton* ldn;
@property (nonatomic, retain) IBOutlet UIButton* ny;
@property (nonatomic, retain) IBOutlet UIButton* chic;
@property (nonatomic, retain) IBOutlet UIButton* la;
@property (nonatomic, retain) IBOutlet UIButton* edin;
@property (nonatomic, retain) IBOutlet UIButton* glasgow;
@property (nonatomic, retain) IBOutlet UIButton* sandiego;
@property (nonatomic, retain) IBOutlet UIButton* cambridge;
@property (nonatomic, retain) IBOutlet UIButton* oban;
@property (nonatomic, retain) IBOutlet UIButton* barcelona;
@property (nonatomic, retain) IBOutlet UIButton* kyoto;

//resource data
@property (nonatomic, retain) IBOutlet UIButton* resBtnBuildings;
@property (nonatomic, retain) IBOutlet UIButton* resBtnLandmarks;
@property (nonatomic, retain) IBOutlet UIButton* resBtnLcm;
@property (nonatomic, retain) IBOutlet UIButton* resBtnModels;
@property (nonatomic, retain) IBOutlet UIButton* resBtnPlacenames;
@property (nonatomic, retain) IBOutlet UIButton* resBtnRoads;
@property (nonatomic, retain) IBOutlet UIButton* resBtnShadows;
@property (nonatomic, retain) IBOutlet UITextField* resTxtTotalsForAllRes;
@property (nonatomic, retain) IBOutlet UITextField* resTxtNumResourcesRequested;
@property (nonatomic, retain) IBOutlet UITextField* resTxtTotalBytesLoaded;
@property (nonatomic, retain) IBOutlet UITextField* resTxtBytesLoadedFromCacheAndWeb;
@property (nonatomic, retain) IBOutlet UITextField* resTxtAvgBytesPerSuccessLoad;
@property (nonatomic, retain) IBOutlet UITextField* resTxtTotalByRequestOutcome;
@property (nonatomic, retain) IBOutlet UITextField* resTxtAvgLoadTimes;
@property (nonatomic, retain) IBOutlet UITextField* resTxtAvgBuild;

@end
