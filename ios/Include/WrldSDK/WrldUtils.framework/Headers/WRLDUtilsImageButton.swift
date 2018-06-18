
/**
 A button view that can load its images from a different bundle.
 */
open class WRLDUtilsImageButton: UIButton
{
    /**
     The identifier of the bundle to load the images from, for example this framework would be
     'com.wrld.WrldUtils'.
     */
    @IBInspectable public var bundleID: String? {
        set { _bundleID = newValue; loadImages() }
        get { return _bundleID }
    }
    private var _bundleID:String?
    
    /**
     The name of the image to use when the button is in the normal state.
     */
    @IBInspectable public var imageName: String? {
        set { _imageName = newValue; loadImages() }
        get { return _imageName }
    }
    private var _imageName:String?
    
    /**
     The name of the image to use when the button is in the down state.
     */
    @IBInspectable public var downImageName: String? {
        set { _downImageName = newValue; loadImages() }
        get { return _downImageName }
    }
    private var _downImageName:String?
    
    /**
     The color of the button in the normal state.
     */
    @IBInspectable public var normalColor: UIColor = UIColor.white
    
    /**
     The color of the button in the highlighted state.
     */
    @IBInspectable public var downColor: UIColor = UIColor.black
    
    override open var isHighlighted: Bool {
        didSet {
            backgroundColor = isHighlighted ? downColor : normalColor
        }
    }
    
    override open func point(inside point: CGPoint, with event: UIEvent?) -> Bool
    {
        return bounds.insetBy(dx: -6.0, dy: -6.0).contains(point)
    }
    
    private func loadImages()
    {
        if let bundleID = _bundleID
        {
            if let bundle = Bundle(identifier: bundleID)
            {
                if let imageName = _imageName
                {
                    if let image = UIImage(named: imageName, in: bundle, compatibleWith: nil)
                    {
                        self.setImage(image, for: .normal)
                    }
                }
                
                if let imageName = _downImageName
                {
                    if let image = UIImage(named: imageName, in: bundle, compatibleWith: nil)
                    {
                        self.setImage(image, for: .selected)
                        self.setImage(image, for: .highlighted)
                    }
                }
            }
        }
    }
}
