// Copyright eeGeo Ltd (2012-2014), All Rights Reserved

#pragma once

namespace ExampleApp
{
namespace FlattenButton
{
class IFlattenButtonViewModule
{
public:

	virtual ~IFlattenButtonViewModule() { }

	virtual FlattenButtonViewController& GetFlattenButtonViewController() const = 0;
	virtual FlattenButtonView& GetFlattenButtonView() const = 0;
};
}
}