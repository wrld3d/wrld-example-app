
/**
 An image view that can load its image from a different bundle.
 */
open class WRLDUtilsImageView: UIImageView
{
    /**
     The identifier of the bundle to load the image from, for example this framework would be
     'com.wrld.WrldUtils'.
     */
    @IBInspectable public var bundleID: String? {
        set { _bundleID = newValue; loadImages() }
        get { return _bundleID }
    }
    private var _bundleID:String?
    
    /**
     The name of the image within that bundle.
     */
    @IBInspectable public var imageName: String? {
        set { _imageName = newValue; loadImages() }
        get { return _imageName }
    }
    private var _imageName:String?
    
    private func loadImages()
    {
        if let bundleID = _bundleID
        {
            if let bundle = Bundle(identifier: bundleID)
            {
                if let imageName = _imageName
                {
                    self.image = UIImage(named: imageName, in: bundle, compatibleWith: nil)
                }
            }
        }
    }
}
