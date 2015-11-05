// Copyright eeGeo Ltd (2012-2015), All Rights Reserved

#pragma once

#using "System.dll"
#using "PresentationFramework.dll"

namespace ExampleApp
{
    public ref class SecondaryMenuViewCLIMethods : public System::ComponentModel::INotifyPropertyChanged
	{
        static System::String^ searchText;
	public:

		static void PerformSearchQuery(System::IntPtr nativeCallerPointer, System::String^ searchTerm);

        virtual event System::ComponentModel::PropertyChangedEventHandler ^PropertyChanged;

        void NotifyPropertyChanged(System::String ^info)
        {
            PropertyChanged(this, gcnew System::ComponentModel::PropertyChangedEventArgs(info));
        }

        property System::String^ Text
        {
            System::String^ get()
            {
                return searchText;
            }

            void set(System::String^ i)
            {
                searchText = i;
                NotifyPropertyChanged(i);
            }
        };
	};
}