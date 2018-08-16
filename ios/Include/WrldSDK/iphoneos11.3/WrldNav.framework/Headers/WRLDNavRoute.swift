import Foundation

/**
 A list of directions that forms a route.
 */
@objc
public class WRLDNavRoute: NSObject
{
    /**
     Initialize a route with a list of directions.
     */
    @objc public init(estimatedRouteDuration estimatedRouteDuration_: TimeInterval,
                      directions directions_: [WRLDNavDirection])
    {
        estimatedRouteDuration = estimatedRouteDuration_
        m_directions           = directions_
    }
    
    /**
     The estimated total duration of the route.
     */
    @objc(estimatedRouteDuration) public let estimatedRouteDuration: TimeInterval
    
    /**
     The list of directions that forms the route.
     */
    private var m_directions: [WRLDNavDirection]
    @objc(directions) public var directions: [WRLDNavDirection]
    {
        get { return m_directions }
    }
    
    /**
     Update direction at the given index.
     */
    @objc public func updateDirection(index index_: Int, direction direction_: WRLDNavDirection)
    {
        m_directions[index_] = direction_
    }
}
