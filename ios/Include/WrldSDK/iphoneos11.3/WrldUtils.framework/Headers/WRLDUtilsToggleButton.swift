
/**
 A button with two states each with its own images that can be loaded from a different bundle.
 */
@objc
public class WRLDUtilsToggleButton: UIButton
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
     The name of the image to use when the toggle button is in the on state.
     */
    @IBInspectable public var onImageName: String? {
        set { _onImageName = newValue; loadImages() }
        get { return _onImageName }
    }
    private var _onImageName:String?
    
    /**
     The name of the image to use when the toggle button is in the on state and down.
     */
    @IBInspectable public var onDownName: String? {
        set { _onDownName = newValue; loadImages() }
        get { return _onDownName }
    }
    private var _onDownName:String?
    
    /**
     The name of the image to use when the toggle button is in the off state.
     */
    @IBInspectable public var offImageName: String? {
        set { _offImageName = newValue; loadImages() }
        get { return _offImageName }
    }
    private var _offImageName:String?
    
    /**
     The name of the image to use when the toggle button is in the off state and down.
     */
    @IBInspectable public var offDownName: String? {
        set { _offDownName = newValue; loadImages() }
        get { return _offDownName }
    }
    private var _offDownName:String?
    
    /**
     The toggle state of the button.
     */
    @IBInspectable public var toggleState: Bool {
        set { _toggleState = newValue; updateImage() }
        get { return _toggleState }
    }
    private var _toggleState:Bool = true
    
    private var _onImage: UIImage?
    private var _onImageDown: UIImage?
    private var _offImage: UIImage?
    private var _offImageDown: UIImage?
    
    /**
     Initialize the button with a frame.
     */
    public override init(frame: CGRect)
    {
        super.init(frame: frame)
        initCommon()
    }
    
    /**
     Initialize the button with a coder.
     */
    public required init?(coder aDecoder: NSCoder)
    {
        super.init(coder: aDecoder)
        initCommon()
    }
    
    private func initCommon()
    {
        addTarget(self, action:#selector(self.buttonClicked), for: .touchUpInside)        
    }
    
    private func loadImage(_ bundle: Bundle, _ path: String?) -> UIImage?
    {
        if let imagePath = path
        {
            return UIImage(named: imagePath, in: bundle, compatibleWith: nil)
        }
        return nil
    }
    
    private func loadImages()
    {
        if let bundleID = _bundleID
        {
            if let bundle = Bundle(identifier: bundleID)
            {
                _onImage      = loadImage(bundle, _onImageName )
                _onImageDown  = loadImage(bundle, _onDownName  )
                _offImage     = loadImage(bundle, _offImageName)
                _offImageDown = loadImage(bundle, _offDownName )
            }
        }
        
        updateImage()
    }
    
    private func updateImage()
    {
        setImage((_toggleState) ? _onImage : _offImage, for: .normal)
        setImage((_toggleState) ? _onImageDown : _offImageDown, for: .selected)
        setImage((_toggleState) ? _onImageDown : _offImageDown, for: .highlighted)
    }    
    
    @objc public func buttonClicked()
    {
        _toggleState = !_toggleState
        updateImage()
        sendActions(for: .valueChanged)
    }
}
