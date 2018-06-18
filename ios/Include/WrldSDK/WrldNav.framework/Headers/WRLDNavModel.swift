import Foundation

/**
 This describes the different events that can be sent out to the nav model.
 */
@objc
public enum WRLDNavEvent: Int
{
    case unknown                        //!< An unknown event.
    case startEndButtonClicked          //!< Event called when start or end step-by-step directions button is tapped.
    case selectStartLocationClicked     //!< Event called when start location textbox was tapped.
    case selectEndLocationClicked       //!< Event called when end location textbox was tapped.
    case closeSetupJourneyClicked       //!< Event called when close navigation button was tapped.
    case widgetAnimateOut               //!< Event called when navigation widget should animate out.
    case widgetAnimateIn                //!< Event called when navigation widget should animate in.
    case showHideListButtonClicked      //!< Event called when show or hide list button in step-by-step direction is tapped.
    case startEndLocationsSwapped       //!< Event called when start and end locations are swapped.
    case startLocationClearButtonClicked//!< Event called when start location clear button is tapped.
    case endLocationClearButtonClicked  //!< Event called when end location clear button is tapped.
    case routeUpdated                   //!< Event called when route has updated and views should reload.
}

/**
 Implement this protocol to receive nav model events.
 */
@objc
public protocol WRLDNavModelEventListener: class
{
    /**
     Called when a nav event is received.
     */
    @objc optional func eventReceived(_ key: WRLDNavEvent)
}

/**
 This describes the different states that the nav model can be in.
 */
@objc
public enum WRLDNavMode: Int
{
    case notReady //!< There is currently not a route configured.
    case ready    //!< A route is configured and we are ready to start.
    case active   //!< Navigation is currently running.
}

/**
 This is the model that holds the data that the views display.
 */
@objc
public class WRLDNavModel: NSObject
{
    /**
     The start location of the route. When the user starts a new route they will enter a new start
     and end location using the search UI or by selecting a point on the map, that will populate
     these properties.
     */
    private var m_startLocation: WRLDNavLocation?
    @objc(startLocation) public var startLocation: WRLDNavLocation? {
        set
        {
            if m_startLocation != newValue
            {
                willChangeValue(forKey: "startLocation")
                m_startLocation = newValue
                didChangeValue(forKey: "startLocation")
            }
        }
        get { return m_startLocation }
    }
    
    /**
     The end location of the route.
     @see startLocation
     */
    private var m_endLocation: WRLDNavLocation?
    @objc(endLocation) public var endLocation: WRLDNavLocation? {
        set
        {
            if m_endLocation != newValue
            {
                willChangeValue(forKey: "endLocation")
                m_endLocation = newValue
                didChangeValue(forKey: "endLocation")
            }
        }
        get { return m_endLocation }
    }

    /**
     The list of instructions for the route and the estimated time.
     */
    private var m_route: WRLDNavRoute?
    @objc(route) public var route: WRLDNavRoute? {
        set
        {
            if m_route != newValue
            {
                willChangeValue(forKey: "route")
                m_route = newValue
                didChangeValue(forKey: "route")
            }
        }
        get { return m_route }
    }

    
    /**
     The index of the currently selected direction. This is the direction step that has been
     selected by the user in the UI.
     */
    private var m_selectedDirectionIndex: Int = 0
    @objc(selectedDirectionIndex) public var selectedDirectionIndex: Int {
        set
        {
            if m_selectedDirectionIndex != newValue
            {
                willChangeValue(forKey: "selectedDirectionIndex")
                m_selectedDirectionIndex = newValue
                didChangeValue(forKey: "selectedDirectionIndex")
            }
        }
        get { return m_selectedDirectionIndex }
    }
    
    /**
     The index of the current direction. This is the direction step that the location is currently
     at or have just passed.
     */
    private var m_currentDirectionIndex: Int = 0
    @objc(currentDirectionIndex) public var currentDirectionIndex: Int {
        set
        {
            if m_currentDirectionIndex != newValue
            {
                willChangeValue(forKey: "currentDirectionIndex")
                m_currentDirectionIndex = newValue
                didChangeValue(forKey: "currentDirectionIndex")
            }
        }
        get { return m_currentDirectionIndex }
    }
    
    /**
     The details of the current direction. This is the direction step that the location is currently
     at or have just passed.
     */
    @objc(currentDirection) public var currentDirection: WRLDNavDirection? {
        set
        {
            if(currentDirection != newValue)
            {
                if (m_route != nil && newValue != nil)
                {
                    willChangeValue(forKey: "currentDirection")
                    m_route?.updateDirection(index: m_currentDirectionIndex, direction: newValue!)
                    didChangeValue(forKey: "currentDirection")
                }
            }
        }
        get
        {
            return m_route?.directions[m_currentDirectionIndex]
        }
    }
    
    /**
     Sets the direction at a set index.
     @param index The index for the new direction
     @param direction The new direction
     @return Bool if been successful
     */
    @objc public func setDirection(_ index: Int, direction: WRLDNavDirection?) -> Bool
    {
        if((m_route != nil) && (m_route?.directions != nil) && (direction != nil)){
            
            if(index >= 0 && index < (m_route?.directions.count)!)
            {
                m_route?.updateDirection(index: index, direction: direction!)
                return true
            }
        }
        return false
    }
    
    /**
     The estimated remaining duration of the route in seconds.
     */
    private var m_remainingRouteDuration: TimeInterval = 0
    @objc(remainingRouteDuration) public var remainingRouteDuration: TimeInterval {
        set
        {
            if m_remainingRouteDuration != newValue
            {
                willChangeValue(forKey: "remainingRouteDuration")
                m_remainingRouteDuration = newValue
                didChangeValue(forKey: "remainingRouteDuration")
            }
        }
        get { return m_remainingRouteDuration }
    }
    
    /**
     The current navigation mode.
     */
    private var m_navMode: WRLDNavMode = .notReady
    @objc(navMode) public var navMode: WRLDNavMode {
        set
        {
            if m_navMode != newValue
            {
                willChangeValue(forKey: "navMode")
                m_navMode = newValue
                didChangeValue(forKey: "navMode")
            }
        }
        get { return m_navMode }
    }
    
    /**
     Call this to reveive events from the model. The listener will need to implement the
     eventReceived method, see WRLDNavModelEventListener for an example.
    
     @note You will also need to call unregisterEventListener before destruction.
     @param listener The listener to receive events.
     */
    @objc public func registerNavEventListener(_ listener: WRLDNavModelEventListener)
    {
        m_eventListeners.add(listener)
    }
    
    /**
     Call this to stop a listener from receiving events.
     */
    @objc public func unregisterNavEventListener(_ listener: WRLDNavModelEventListener)
    {
        m_eventListeners.remove(listener)
    }

    /**
     Send a nav event to all listeners.
     */
    @objc public func sendNavEvent(_ key: WRLDNavEvent)
    {
        let enumerator = m_eventListeners.objectEnumerator()
        while let listener = enumerator.nextObject() as? WRLDNavModelEventListener
        {
            listener.eventReceived?(key)
        }
    }
    
    private var m_eventListeners: NSHashTable<WRLDNavModelEventListener> = .weakObjects()
    
    @objc override public class func automaticallyNotifiesObservers(forKey key: String) -> Bool {
        return false
    }
}
