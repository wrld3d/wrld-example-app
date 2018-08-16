import UIKit
import WrldUtils
import WrldNav

@objc
public class WRLDNavWidgetBase: UIView, WRLDNavModelObserverProtocol
{
    internal let navModeKeyPath = #keyPath(WRLDNavModel.navMode)
    internal let navTopViewPanelHeightKeyPath = #keyPath(WRLDNavWidgetBase.topPanelVisibleHeight)
    internal let navBottomViewPanelHeightKeyPath = #keyPath(WRLDNavWidgetBase.bottomPanelVisibleHeight)
    
    @objc public var observer: WRLDNavModelObserver
    
    @objc public func setViewVisibility(animate: Bool, hideViews: Bool) {}
    
    /**
     The current navigation mode.
     */
    private var m_topPanelVisibleHeight: CGFloat = 0
    @objc(topPanelVisibleHeight) public var topPanelVisibleHeight: CGFloat {
        set
        {
            if m_topPanelVisibleHeight != newValue
            {
                willChangeValue(forKey: navTopViewPanelHeightKeyPath)
                m_topPanelVisibleHeight = newValue
                didChangeValue(forKey: navTopViewPanelHeightKeyPath)
            }
        }
        get { return m_topPanelVisibleHeight }
    }
    
    /**
     The current navigation mode.
     */
    private var m_bottomPanelVisibleHeight: CGFloat = 0
    @objc(bottomPanelVisibleHeight) public var bottomPanelVisibleHeight: CGFloat {
        set
        {
            if m_bottomPanelVisibleHeight != newValue
            {
                willChangeValue(forKey: navBottomViewPanelHeightKeyPath)
                m_bottomPanelVisibleHeight = newValue
                didChangeValue(forKey: navBottomViewPanelHeightKeyPath)
            }
        }
        get { return m_bottomPanelVisibleHeight }
    }
    
    open func updateNavMode(animate: Bool) {}
    
    public override init(frame: CGRect)
    {
        observer = WRLDNavModelObserver()
        m_topPanelVisibleHeight = 0.0
        m_bottomPanelVisibleHeight = 0.0
        super.init(frame: frame)
        observer.delegate = self
    }
    
    public required init?(coder aDecoder: NSCoder)
    {
        observer = WRLDNavModelObserver()
        m_topPanelVisibleHeight = 0.0
        m_bottomPanelVisibleHeight = 0.0
        super.init(coder: aDecoder)
        observer.delegate = self
        
    }
    
    public func eventReceived(key: WRLDNavEvent)
    {
        if(key == WRLDNavEvent.widgetAnimateOut)
        {
            setViewVisibility(animate: true, hideViews: true) 
        }
        
        else if(key == WRLDNavEvent.widgetAnimateIn)
        {
            setViewVisibility(animate: true, hideViews: false)
        }
    }
    
    public func changeReceived(keyPath: String)
    {        
        if(keyPath == navModeKeyPath)
        {
            updateNavMode(animate: true)
            return;
        }
    }
    
    override public func layoutSubviews()
    {
        if let b = superview?.bounds
        {
            frame = b
        }
        
        super.layoutSubviews()
        updateNavMode(animate: false)
    }
}
