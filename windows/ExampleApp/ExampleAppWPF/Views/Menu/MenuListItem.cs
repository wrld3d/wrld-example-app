using Newtonsoft.Json.Linq;
using System.ComponentModel;

namespace ExampleAppWPF
{
    public class MenuListItem : INotifyPropertyChanged
    {
        private bool m_isSelected;
        private bool m_justRemoved;
        private int m_zIndex;
        private string m_heading;
        private bool m_isExpanded;
        private bool m_justAdded;
        private bool m_isExpandable;

        public event PropertyChangedEventHandler PropertyChanged;
        protected virtual void OnPropertyChanged(string propertyName)
        {
            if (PropertyChanged != null)
                PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
        }

        public bool IsSelected
        {
            get { return m_isSelected; }
            set
            {
                if (value != m_isSelected)
                {
                    m_isSelected = value;
                    this.OnPropertyChanged("IsSelected");
                }
            }
        }

        public bool IsExpandable
        {
            get { return m_isExpandable; }

            set
            {
                if (value != m_isExpandable)
                {
                    m_isExpandable = value;
                    OnPropertyChanged("IsExpandable");
                }
            }
        }

        public MenuListItem(string json, bool isExpanded, int zIndex)
        {
            m_zIndex = zIndex;            
            JObject parsed = JObject.Parse(json);
            m_heading = parsed["name"].Value<string>();
            IsExpanded = isExpanded;
            JustAdded = m_justAdded = false;
            IsExpandable = m_isExpandable = true;
        }

        public int ZIndex
        {
            get { return m_zIndex; }
        }

        public bool IsExpanded
        {
            get { return m_isExpanded; }
            set
            {
                if (m_isExpanded != value)
                {
                    m_isExpanded = value;
                    OnPropertyChanged("IsExpanded");
                }
            }
        }

        public bool JustAdded
        {
            get
            {
                 return m_justAdded;
            }

            set
            {
                if (value != m_justAdded)
                {
                    m_justAdded = value;

                    OnPropertyChanged("JustAdded");
                }
            }
        }

        public bool JustRemoved
        {
            get
            {
                return m_justRemoved;
            }
            set
            {
                if (value != m_justRemoved)
                {
                    m_justRemoved = value;

                    OnPropertyChanged("JustRemoved");
                }
            }
        }

        public string Heading
        {
            get { return m_heading; }
        }
    }
}