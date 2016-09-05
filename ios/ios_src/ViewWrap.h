// Copyright eeGeo Ltd 2016, All Rights Reserved

#pragma once

#include "Types.h"

template <typename T>
class ViewWrap : private Eegeo::NonCopyable
{
public:
    ViewWrap(T* view)
    : m_pView(view)
    {
    }
    
    ~ViewWrap()
    {
        [m_pView release];
    }
    
    T* Get() const { return m_pView; }
private:
    T* m_pView;
};