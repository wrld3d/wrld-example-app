// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

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
