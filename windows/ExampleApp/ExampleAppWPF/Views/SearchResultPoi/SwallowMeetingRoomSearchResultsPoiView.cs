using ExampleAppWPF.Properties;
using System;
using System.Collections.Generic;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Media;
using System.Windows.Media.Imaging;

namespace ExampleAppWPF
{
    public class EnumToBooleanConverter : IValueConverter
    {
        public object Convert(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            return value.Equals(parameter);
        }

        public object ConvertBack(object value, Type targetType, object parameter, System.Globalization.CultureInfo culture)
        {
            return value.Equals(true) ? parameter : Binding.DoNothing;
        }
    }

    public class SwallowMeetingRoomSearchResultsPoiView : SearchResultPoiViewBase
    {
        public enum AvailalabilityType
        {
            None,
            Available,
            AvailableSoon,
            Occupied
        }

        private Dictionary<string, AvailalabilityType> availabilityStringMap = new Dictionary<string, AvailalabilityType>()
        {
            { "available", AvailalabilityType.Available },
            { "available_soon", AvailalabilityType.AvailableSoon },
            { "occupied", AvailalabilityType.Occupied }
        };

        private AvailalabilityType AvailableStringToEnum(string availabilityString)
        {
            AvailalabilityType availabilityEnum;

            availabilityStringMap.TryGetValue(availabilityString, out availabilityEnum);

            return availabilityEnum;
        }

        private string AvailableEnumToString(AvailalabilityType availabilityEnum)
        {
            foreach(KeyValuePair<string, AvailalabilityType> availabilityPair in availabilityStringMap)
            {
                if(availabilityPair.Value == availabilityEnum)
                {
                    return availabilityPair.Key;
                }
            }

            return string.Empty;
        }
        
        private Image m_categoryIcon = null;
        private Image m_poiImage = null;

        private RadioButton m_availableButton = null;
        private RadioButton m_availableSoonButton = null;
        private RadioButton m_occupiedButton = null;

        private ExampleApp.SearchResultModelCLI m_model;
        private SwallowMeetingRoomResultModel m_swallowMeetingRoomModel;

        public string TitleText { get; set; }
        public AvailalabilityType Availability { get; set; }

        RoutedEventHandler OnAvailableSelected;
        RoutedEventHandler OnAvailableSoonSelected;
        RoutedEventHandler OnOccupiedSelected;

        static SwallowMeetingRoomSearchResultsPoiView()
        {
            DefaultStyleKeyProperty.OverrideMetadata(typeof(SwallowMeetingRoomSearchResultsPoiView), new FrameworkPropertyMetadata(typeof(SwallowMeetingRoomSearchResultsPoiView)));
        }

        public SwallowMeetingRoomSearchResultsPoiView(IntPtr nativeCallerPointer, bool isInKioskMode)
            : base(nativeCallerPointer, isInKioskMode)
        {
            OnAvailableSelected = (object sender, RoutedEventArgs e) => { HandleAvailabilityChanged(AvailalabilityType.Available); };
            OnAvailableSoonSelected = (object sender, RoutedEventArgs e) => { HandleAvailabilityChanged(AvailalabilityType.AvailableSoon); };
            OnOccupiedSelected = (object sender, RoutedEventArgs e) => { HandleAvailabilityChanged(AvailalabilityType.Occupied); };
        }

        public override void OnApplyTemplate()
        {
            m_categoryIcon = (Image)GetTemplateChild("CategoryIcon");
            
            m_poiImage = (Image)GetTemplateChild("PoiImage");

            m_availableButton = (RadioButton)GetTemplateChild("AvailableButton");
            m_availableSoonButton = (RadioButton)GetTemplateChild("AvailableSoonButton");
            m_occupiedButton = (RadioButton)GetTemplateChild("OccupiedButton");

            m_mainContainer = (FrameworkElement)GetTemplateChild("MeetingRoomPoiContainer");

            base.OnApplyTemplate();
        }
        
        protected override void DisplayCustomPoiInfo(Object modelObject)
        {
            m_model = modelObject as ExampleApp.SearchResultModelCLI;
            m_categoryIcon.Source = IconProvider.GetIconForTag(m_model.IconKey, m_isInKioskMode);

            m_swallowMeetingRoomModel = SwallowMeetingRoomResultModel.FromJson(m_model.JsonData);
            Availability = AvailableStringToEnum(m_swallowMeetingRoomModel.Availability);

            if (Settings.Default.UserSettings.ContainsKey(m_model.Title))
            {
                String userAvailability = Settings.Default.UserSettings[m_model.Title];
                Availability = AvailableStringToEnum(userAvailability);
            }

            m_availableButton.Click += OnAvailableSelected;
            m_availableSoonButton.Click += OnAvailableSoonSelected;
            m_occupiedButton.Click += OnOccupiedSelected;

            m_closing = false;
            
            TitleText = m_model.Title;

            m_poiImage.Source = new BitmapImage(new Uri("/Assets/poi_placeholder.png", UriKind.Relative));
            m_poiImage.Stretch = Stretch.Fill;

            OnPropertyChanged("");

            ShowAll();

            base.DisplayCustomPoiInfo(modelObject);
        }

        public override void DismissPoiInfo()
        {
            m_availableButton.Click -= OnAvailableSelected;
            m_availableSoonButton.Click -= OnAvailableSoonSelected;
            m_occupiedButton.Click -= OnOccupiedSelected;

            base.DismissPoiInfo();
        }

        public override void UpdateImageData(string url, bool hasImage, byte[] imgData)
        {
            if (hasImage)
            {
                m_poiImage.Source = LoadImageFromByteArray(imgData);
                m_poiImage.Stretch = Stretch.UniformToFill;
            }
        }

        private void HandleAvailabilityChanged(AvailalabilityType availability)
        {
            ExampleApp.SearchResultPoiViewCLI.AvailabilityChanged(m_nativeCallerPointer, AvailableEnumToString(availability));
        }
    }
}
