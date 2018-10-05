import UIKit
import WrldUtils
import WrldNav

@objc
public class WRLDNavWidgetPhone: WRLDNavWidgetBase
{
    @IBOutlet var view: UIView!
    
    //-- The panel at the top that configures the journey ------------------------------------------
    @IBOutlet var topSetupJourneyPanel: UIView!
    @IBOutlet weak var topStackView: UIStackView!
    @IBOutlet weak var setupJourneyView: WRLDNavSetupJourneyView!
    @IBOutlet weak var topToggleButton: WRLDUtilsToggleButton!
    
    //-- The panel at the top that gives instructions ----------------------------------------------
    @IBOutlet var topInstructionPanel: UIView!
    @IBOutlet weak var instructionStackView: UIStackView!
    @IBOutlet weak var currentDirectionView: WRLDNavCurrentDirectionView!
    @IBOutlet weak var nextDirectionView: WRLDNavNextDirectionView! 
    
    //-- The bottom time to destination & directions views -----------------------------------------
    @IBOutlet var bottomPanel: UIView!
    @IBOutlet weak var bottomStackView: UIStackView!
    @IBOutlet weak var bottomToggleButton: WRLDUtilsToggleButton!
    @IBOutlet weak var timeToDestinationView: WRLDNavTimeToDestinationView!
    @IBOutlet weak var directionsView: WRLDNavDirectionsView!
    @IBOutlet var bottomPanelMask: UIView!
    
    @IBOutlet weak var setupJourneySafeArea: NSLayoutConstraint!
    @IBOutlet weak var instructionsPanelSafeArea: NSLayoutConstraint!
    
    var _hideViews: Bool = false
    var _dontCollapseTop: Bool = false
    var _safeAreaBottom: Int = 0
    
    public override init(frame: CGRect)
    {
        super.init(frame: frame)
        initCommon()
    }
    
    public required init?(coder aDecoder: NSCoder)
    {
        super.init(coder: aDecoder)
        initCommon()
    }
    
    private func initCommon()
    {
        observer.registerObserver(observerKey: navModeKeyPath)
        
        let bundle = Bundle(for: WRLDNavWidgetPhone.self)
        
        let nib = UINib(nibName: "WRLDNavWidgetPhone", bundle: bundle)
        let view: UIView! = nib.instantiate(withOwner: self, options: nil)[0] as! UIView
        view.frame = bounds
        view.autoresizingMask = [.flexibleWidth, .flexibleHeight]
        addSubview(view)
        
        topSetupJourneyPanel.translatesAutoresizingMaskIntoConstraints = true
        view.addSubview(topSetupJourneyPanel)
        
        topInstructionPanel.translatesAutoresizingMaskIntoConstraints = true
        view.addSubview(topInstructionPanel)
        
        bottomPanel.translatesAutoresizingMaskIntoConstraints = true
        view.addSubview(bottomPanel)
        
        if #available(iOS 11.0, *) {
            setupJourneySafeArea.constant = 0
            instructionsPanelSafeArea.constant = 0
            _safeAreaBottom = Int((UIApplication.shared.keyWindow?.safeAreaInsets.bottom)!)
        } else {
            setupJourneySafeArea.constant = UIApplication.shared.statusBarFrame.height
            instructionsPanelSafeArea.constant = UIApplication.shared.statusBarFrame.height
        }
        
        bottomPanelMask.translatesAutoresizingMaskIntoConstraints = true
        view.addSubview(bottomPanelMask)
    }
    
    public override func point(inside point: CGPoint, with event: UIEvent?) -> Bool
    {
        if(_hideViews)
        {
            return false
        }
        
        return (topStackView.frame.contains(view.convert(point, to: topSetupJourneyPanel)) ||
                instructionStackView.frame.contains(view.convert(point, to: topInstructionPanel)) ||
                bottomStackView.frame.contains(view.convert(point, to: bottomPanel)))
    }
    
    public func modelSet()
    {
        if let navModel = observer.navModel()
        {
            setupJourneyView     .observer.setNavModel(navModel)
            currentDirectionView .observer.setNavModel(navModel)
            nextDirectionView    .observer.setNavModel(navModel)
            timeToDestinationView.observer.setNavModel(navModel)
            directionsView       .observer.setNavModel(navModel)
        }
        
        updateNavMode(animate: false)
        updateTopStack()
        updateBottomStack()
    }
    
    func setTopSetupJourneyVisibility(visible: Bool, animate: Bool)
    {
        let frameWidth: Int = Int(view.frame.size.width)
        let frameHeight: Int = 135
        let openFrame   = CGRect(x: 0, y:                 0, width: frameWidth, height: frameHeight)
        let closedFrame = CGRect(x: 0, y: -(frameHeight+20), width: frameWidth, height: frameHeight)
        
        let block = {
            self.topSetupJourneyPanel.frame  = (visible) ? (openFrame) : (closedFrame)
        };
        
        if(animate == true)
        {
            UIView.animate(withDuration: 0.3, animations:block)
        }
        else
        {
            block()
        }
    }
    
    func setTopInstructionVisibility(visible: Bool, animate: Bool)
    {
        let frameWidth: Int = Int(view.frame.size.width)
        let frameHeight: Int = 155
        let openFrame   = CGRect(x: 0, y:                 0, width: frameWidth, height: frameHeight)
        let closedFrame = CGRect(x: 0, y: -(frameHeight+11), width: frameWidth, height: frameHeight)
        
        let block = {
            self.topInstructionPanel.frame  = (visible) ? (openFrame) : (closedFrame)
        };
        
        if(animate == true)
        {
            UIView.animate(withDuration: 0.3, animations:block)
        }
        else
        {
            block()
        }
    }
    
    func setBottomVisibility(visible: Bool, animate: Bool)
    {
        let ht = Int(view.frame.size.height)
        let frameWidth: Int = Int(view.frame.size.width)
        let frameHeight: Int = 312
        let openFrame   = CGRect(x: 0, y: ht-_safeAreaBottom - frameHeight, width: frameWidth, height: frameHeight)
        let closedFrame = CGRect(x: 0, y:             ht-_safeAreaBottom, width: frameWidth, height: frameHeight)
        let openMaskFrame = CGRect(x: 0, y: ht-_safeAreaBottom, width: frameWidth, height: _safeAreaBottom)
        let closedMaskFrame = CGRect(x: 0, y: ht, width: frameWidth, height: _safeAreaBottom)
        
        let block = {
            self.bottomPanel.frame  = (visible) ? (openFrame) : (closedFrame)
            self.bottomPanelMask.frame = (visible) ? (openMaskFrame) : (closedMaskFrame)
        };
        
        if(visible == false && self.bottomToggleButton.toggleState == true)
        {
            self.bottomToggleButton.toggleState = false;
            updateBottomStack();
        }
        
        if(animate == true)
        {
            UIView.animate(withDuration: 0.3, animations:block)
        }
        else
        {
            block()
        }
    }
    
    //This is called when the Nav mode changes to hide/show various elements of the UI.
    override open func updateNavMode(animate: Bool)
    {
        if(_hideViews)
        {
            setTopSetupJourneyVisibility(visible: false, animate: animate)
            setTopInstructionVisibility (visible: false, animate: animate)
            setBottomVisibility         (visible: false, animate: animate)
        }
        else if let navModel = observer.navModel()
        {
            switch(navModel.navMode)
            {
            case .notReady:
                setTopSetupJourneyVisibility(visible:  true, animate: animate)
                setTopInstructionVisibility (visible: false, animate: animate)
                setBottomVisibility         (visible:  false, animate: animate)
                break;
            case .ready:
                setTopSetupJourneyVisibility(visible:  true, animate: animate)
                setTopInstructionVisibility (visible: false, animate: animate)
                setBottomVisibility         (visible:  true, animate: animate)
                break;
            case .active:
                setTopSetupJourneyVisibility(visible: false, animate: animate)
                setTopInstructionVisibility (visible:  true, animate: animate)
                setBottomVisibility         (visible:  true, animate: animate)
                break;
            }
        }
        view.setNeedsLayout()
        view.layoutIfNeeded()
        topPanelVisibleHeight = calculateTopPanelVisibleHeight()
        bottomPanelVisibleHeight = calculateBottomPanelVisibleHeight()
    }
    
    func calculateTopPanelVisibleHeight() -> CGFloat
    {
        var height : CGFloat = 0.0
        if(_hideViews)
        {
            return height
        }
        
        if let navModel = observer.navModel()
        {
            switch(navModel.navMode)
            {
            case .notReady:
                height += topToggleButton.bounds.height
                height += topStackView.bounds.size.height
                break
            case .ready:
                height += topToggleButton.bounds.height
                height += topStackView.bounds.size.height
                break
            case .active:
                height = topInstructionPanel.bounds.size.height
                break
            }
        }
        
        return height
    }
    
    func calculateBottomPanelVisibleHeight() -> CGFloat
    {
        var height : CGFloat = 0.0
        if(_hideViews)
        {
            return height
        }
        
        height += bottomStackView.bounds.size.height
        return height
    }
    
    func updateTopStack()
    {
        UIView.animate(withDuration: 0.3, animations:
            {
                self.setupJourneyView.setHidden(isHidden: !(self.topToggleButton.toggleState))
                self.view.setNeedsLayout()
                self.view.layoutIfNeeded()
                self.topPanelVisibleHeight = self.calculateTopPanelVisibleHeight()
        })
    }
    
    func updateBottomStack()
    {
        UIView.animate(withDuration: 0.3, animations:
            {
                self.directionsView.isHidden = !(self.bottomToggleButton.toggleState)
                self.view.setNeedsLayout()
                self.view.layoutIfNeeded()
                self.bottomPanelVisibleHeight = self.calculateBottomPanelVisibleHeight()
        })
    }
    
    @IBAction func topToggleButtonValueChanged(_ sender: Any)
    {
        if(bottomToggleButton.toggleState == true && topToggleButton.toggleState == true)
        {
            _dontCollapseTop = true
        }
        
        updateTopStack()
    }
    
    @IBAction func bottomToggleButtonValueChanged(_ sender: Any)
    {
        updateBottomStack()
        
        if(!_dontCollapseTop)
        {
            topToggleButton.toggleState = !bottomToggleButton.toggleState
            updateTopStack()
        }
    }
    
    @objc public override func setViewVisibility(animate: Bool, hideViews: Bool)
    {
        _hideViews = hideViews
        updateNavMode(animate: animate)
    }
}

