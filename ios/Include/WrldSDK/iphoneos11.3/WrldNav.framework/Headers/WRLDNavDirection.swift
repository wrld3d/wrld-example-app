import Foundation
import CoreLocation

/**
 This type is used to describe a single direction in a list of directions that form a route.
 */
@objc
public class WRLDNavDirection: NSObject
{
    /**
     Initialize an interior or exterior direction.
     */
    @objc public init(name name_: String,
                      icon icon_: String,
                      instruction instruction_: String,
                      thenInstruction thenInstruction_: String,
                      path path_: [CLLocationCoordinate2D],
                      indoorID indoorID_: String? = nil,
                      floorID floorID_: Int = 0,
                      isMultiFloor isMultiFloor_: Bool = false)
    {
        name            = name_
        icon            = icon_
        instruction     = instruction_
        thenInstruction = thenInstruction_
        path            = path_
        indoorID        = indoorID_
        floorID         = floorID_
        isMultiFloor    = isMultiFloor_
    }
    
    /**
     The short name of this instruction.
     */
    @objc(name) public let name: String
    
    /**
     The name of the icon. This gets prefixed to sellect the correct icon from the assets.
     */
    @objc(icon) public let icon: String
    
    /**
     The main part of the instruction for this step.
     */
    @objc(instruction) public let instruction: String
    
    /**
     The then instruction for this step.
     */
    @objc(thenInstruction) public let thenInstruction: String
    
    /**
     The geographic path of this direction.
     */
    @objc(path) public let path: [CLLocationCoordinate2D]
    
    /**
     The name of the building that this location is within, or nil if this is not applicable.
     */
    @objc(indoorID) public let indoorID: String?
    
    /**
     The floor that this location is on or 0 if not applicable.
     */
    @objc(floorID) public let floorID: Int
    
    /**
     Whether the direction is multifloor or not
     */
    @objc(isMultiFloor) public let isMultiFloor: Bool
}
