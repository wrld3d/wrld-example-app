import Foundation
import CoreLocation

/**
 This type is used to describe a location on the map, primarily this is used for the start and end
 locations of a route.
 */
@objc
public class WRLDNavLocation: NSObject
{
    @objc public init(name name_: String,
                      latLon latLon_: CLLocationCoordinate2D,
                      indoorID indoorID_: String? = nil,
                      floorID floorID_: Int = 0)
    {
        name     = name_
        latLon   = latLon_
        indoorID = indoorID_
        floorID  = floorID_
    }
    
    /**
     The name of this location, this is what should be displayed in a search text box.
     */
    @objc(name) public let name: String
    
    /**
     Latitude and Longitude of the location.
     */
    @objc(latLon) public let latLon: CLLocationCoordinate2D
    
    /**
     The name of the building that this location is within, or nil if this is not applicable.
     */
    @objc(indoorID) public let indoorID: String?

    /**
     The floor that this location is on or 0 if not applicable.
     */
    @objc(floorID) public let floorID: Int
}
