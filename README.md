mobile-sdk-harness
==================

* Run ./update.platform.sh to get the latest platform libraries and headers.
* The accompanying project has no code signing, so run in the simulator (or provide your own credentials).
* The platform needs an API key to operate. Sign up at https://appstore.eegeo.com/ to get your API key and introduce it into the following line in ViewController.mm : 
	#define API_KEY "OBTAIN API_KEY FROM https://appstore.eegeo.com AND INSERT IT HERE"
* In AppOnMap.h, change the value of selectedExample to vary the examples:
	* ExampleTypes::DebugSphere demonstrates the plotting of several colored spheres in world at different locations.
	* ExampleTypes::LoadModel demonstrates the loading, rendering and scaling of a model resource.
	* ExampleTypes::ScreenUnproject demonstrates an unproject of a screen point to a world space ray. It also demonstrates a terrain height lookup at the intersection of this unprojected ray with the earth, and the rendering of a sphere centered at that terrain point.