
/**
 Implement this protocol to receive click events from the image buttons within the text field.
 */
@objc
public protocol WRLDUtilsTextFieldDelegate: class
{
    /**
     Called when the left image button is pressed.
     */
    @objc optional func leftButtonClicked(textField: WRLDUtilsTextField)
    
    /**
     Called when the right image button is pressed.
     */
    @objc optional func rightButtonClicked(textField: WRLDUtilsTextField)
}

/**
 A text field that contains images to the left and right of the text field. These images can be
 loaded from a different bundle.
 */
@objc
public class WRLDUtilsTextField: UITextField
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
     The name of the image to use for the left icon when the button is in the normal state.
     */
    @IBInspectable public var leftImageName: String? {
        set { _leftImageName = newValue; loadImages() }
        get { return _leftImageName }
    }
    private var _leftImageName:String?
    
    /**
     The name of the image to use for the left icon when the button is in the highlighted state.
     */
    @IBInspectable public var leftDownName: String? {
        set { _leftDownName = newValue; loadImages() }
        get { return _leftDownName }
    }
    private var _leftDownName:String?
    
    /**
     Padding to the left of the left image.
     */
    @IBInspectable public var leftPadding: CGFloat {
        set { _leftPadding = newValue;}
        get { return _leftPadding }
    }
    private var _leftPadding:CGFloat = 0
    
    /**
     The name of the image to use for the right icon when the button is in the normal state.
     */
    @IBInspectable public var rightImageName: String? {
        set { _rightImageName = newValue; loadImages() }
        get { return _rightImageName }
    }
    private var _rightImageName:String?
    
    /**
     The name of the image to use for the right icon when the button is in the highlighted state.
     */
    @IBInspectable public var rightDownName: String? {
        set { _rightDownName = newValue; loadImages() }
        get { return _rightDownName }
    }
    private var _rightDownName:String?
    
    /**
     Padding to the right of the right image.
     */
    @IBInspectable public var rightPadding: CGFloat {
        set { _rightPadding = newValue;}
        get { return _rightPadding }
    }
    private var _rightPadding:CGFloat = 0
    
    private var _rightButtonView: UIButton?
    private var _leftButtonView: UIButton?
    
    
    public weak var buttonDelegate: WRLDUtilsTextFieldDelegate?
    
    open override func rightViewRect(forBounds bounds: CGRect) -> CGRect
    {
        var rect = super.rightViewRect(forBounds: bounds)
        rect.origin.x -= _rightPadding
        return rect
    }
    
    open override func leftViewRect(forBounds bounds: CGRect) -> CGRect
    {
        var rect = super.leftViewRect(forBounds: bounds)
        rect.origin.x += _leftPadding
        return rect
    }
    
    enum ButtonSide
    {
        case right
        case left
    }
    
    private func getButton(side: ButtonSide) -> UIButton
    {
        var button: UIButton? = (side == .right) ? _rightButtonView : _leftButtonView
        
        if(button == nil)
        {
            button = UIButton(type: .custom)
            button?.frame = CGRect(x: 0, y: 0, width: 20, height: 20)
            if(side == .right)
            {
                button?.addTarget(self, action:#selector(self.rightButtonClicked), for: .touchUpInside)
                _rightButtonView = button
                rightView = button
                rightViewMode = .always
            }
            else
            {
                button?.addTarget(self, action:#selector(self.leftButtonClicked), for: .touchUpInside)
                _leftButtonView = button
                leftView = button
                leftViewMode = .always
            }
        }
        
        return button!
    }
    
    @objc public func rightButtonClicked()
    {
        buttonDelegate?.rightButtonClicked?(textField: self)
    }
    
    @objc public func leftButtonClicked()
    {
        buttonDelegate?.leftButtonClicked?(textField: self)
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
                if let image = loadImage(bundle, _leftImageName)
                {
                    getButton(side: .left).setImage(image, for: .normal)
                }
                
                if let image = loadImage(bundle, _rightImageName)
                {
                    getButton(side: .right).setImage(image, for: .normal)
                }
                
                if let image = loadImage(bundle, _leftDownName)
                {
                    getButton(side: .left).setImage(image, for: .selected)
                    getButton(side: .left).setImage(image, for: .highlighted)
                }
                
                if let image = loadImage(bundle, _rightDownName)
                {
                    getButton(side: .right).setImage(image, for: .selected)
                    getButton(side: .right).setImage(image, for: .highlighted)
                }
            }
        }
    }
}
