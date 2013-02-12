mobile-sdk-harness
==================

* Run ./update.platform.sh to get the latest platform libraries and headers.
* The accompanying project has no code signing, so run in the simulator (or provide your own credentials).
* In AppOnMap.h, change the value of selectedExample to vary the examples:
	* ExampleTypes::DebugSphere demonstrates the plotting of several colored spheres in world at different locations.
	* ExampleTypes::LoadModel demonstrates the loading, rendering and scaling of a model resource.
	* ExampleTypes::ScreenUnproject demonstrates an unproject of a screen point to a world space ray. It also demonstrates a terrain height lookup at the intersection of this unprojected ray with the earth, and the rendering of a sphere centered at that terrain point.