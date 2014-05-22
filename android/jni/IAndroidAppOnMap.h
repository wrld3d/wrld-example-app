//  Copyright (c) 2014 eeGeo. All rights reserved.

#ifndef IANDROIDAPPONMAP_H_
#define IANDROIDAPPONMAP_H_

class IAndroidAppOnMap : public Eegeo::IAppOnMap
{
public:
	virtual ~IAndroidAppOnMap() {};

	virtual void OnPause() = 0;
	virtual void OnResume() = 0;
};

#endif /* IANDROIDAPPONMAP_H_ */
