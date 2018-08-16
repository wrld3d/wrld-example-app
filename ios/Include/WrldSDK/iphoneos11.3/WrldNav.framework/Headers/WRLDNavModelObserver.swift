@objc public protocol WRLDNavModelObserverProtocol: class
{
    /**
     Re-implement this if you need to know when the model has been set.
     */
    @objc(modelSet) optional func modelSet()
    
    /**
     Re-implement this to receive property changes from the model.
     */
    @objc(changeReceived:) optional func changeReceived(keyPath: String)
    
    /**
     Re-implement this to receive events from the model.
     */
    @objc(eventReceived:) optional func eventReceived(key: WRLDNavEvent)
}

@objc public class WRLDNavModelObserver: NSObject, WRLDNavModelEventListener
{
    @objc public weak var delegate: WRLDNavModelObserverProtocol?
    private var m_navModel: WRLDNavModel?
    private var m_observerKeys = [String]();
    
    
    /**
     Call this to register for changes from the WRLDNavModel.
     When a change that you have registered for occurs the changeReceived method will be called.
     */
    @objc(registerObserver:) public func registerObserver(observerKey: String)
    {
        m_observerKeys.append(observerKey);
    }
    
    /**
     Call this after registering observers.
     */
    @objc(setNavModel:) public func setNavModel(_ navModel: WRLDNavModel)
    {
        removeObservers()
        m_navModel = navModel
        addObservers()
        delegate?.modelSet?()
    }
    
    /**
     Returns the model that we are observing.
     */
    @objc public func navModel() -> WRLDNavModel?
    {
        return m_navModel
    }
    
    deinit
    {
        removeObservers()
    }
    
    /**
     Called by the WrldNavModelEventListener when a nav event is received.
     */
    public func eventReceived(_ key: WRLDNavEvent)
    {
        delegate?.eventReceived?(key: key)
    }
    
    /**
     Called by observed properties.
     */
    override public func observeValue(forKeyPath keyPath: String?,
                                      of object: Any?,
                                      change: [NSKeyValueChangeKey : Any]?,
                                      context: UnsafeMutableRawPointer?)
    {
        if keyPath != nil
        {
            delegate?.changeReceived?(keyPath: keyPath!)
        }
    }
    
    private func addObservers()
    {
        m_navModel?.registerNavEventListener(self)
        for observerKey in m_observerKeys
        {
            m_navModel?.addObserver(self, forKeyPath:observerKey, options:[.new], context:nil)
        }
    }
    
    private func removeObservers()
    {
        m_navModel?.unregisterNavEventListener(self)
        for observerKey in m_observerKeys
        {
            m_navModel?.removeObserver(self, forKeyPath:observerKey)
        }
    }
}
