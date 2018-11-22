import UIKit
import WrldUtils
import WrldNav

@objc
public class WRLDNavWidgetTablet: WRLDNavWidgetBase
{
    @IBOutlet var view: UIView!
    
    //-- Top - Current & Next Instructions ---------------------------------------------------------
    @IBOutlet var topPanelView: UIView!
    @IBOutlet weak var currentDirectionView: WRLDNavCurrentDirectionView!
    @IBOutlet weak var nextDirectionView: WRLDNavNextDirectionView!
    @IBOutlet weak var stepByStepDirectionsView: WRLDNavDirectionsView!
    
    //-- Left hand side - Directions ---------------------------------------------------------------
    @IBOutlet var leftPanelView: UIView!
    @IBOutlet weak var leftInfoViews: UIView!
    @IBOutlet weak var directionsStack: UIStackView!
    @IBOutlet weak var setupJourneyView: WRLDNavSetupJourneyView!
    @IBOutlet weak var leftTimeToDestinationView: WRLDNavTimeToDestinationView!
    @IBOutlet weak var directionsView: WRLDNavDirectionsView!
    
    //-- Bottom - Time to Destination --------------------------------------------------------------
    @IBOutlet var bottomPanelView: UIView!
    @IBOutlet weak var bottomStack: UIStackView!
    @IBOutlet weak var bottomTimeToDestinationView: WRLDNavTimeToDestinationView!
    
    var m_bottomPanelHeight: CGFloat = 0
    var m_isStepByStepNavListShowing: Bool = false;
    
    var _hideViews: Bool = false
    
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
        
        let bundle = Bundle(for: WRLDNavWidgetTablet.self)
        
        let nib = UINib(nibName: "WRLDNavWidgetTablet", bundle: bundle)
        let view: UIView! = nib.instantiate(withOwner: self, options: nil)[0] as! UIView
        view.frame = bounds
        view.autoresizingMask = [.flexibleWidth, .flexibleHeight]
        addSubview(view)
        
        applyShadow(view: nextDirectionView)
        applyShadow(view: leftInfoViews)
        applyShadow(view: directionsView)
        applyShadow(view: stepByStepDirectionsView)

        leftPanelView.translatesAutoresizingMaskIntoConstraints = true
        view.addSubview(leftPanelView)
        
        topPanelView.translatesAutoresizingMaskIntoConstraints = true
        view.addSubview(topPanelView)
        
        bottomPanelView.translatesAutoresizingMaskIntoConstraints = true
        view.addSubview(bottomPanelView)
        
        m_bottomPanelHeight = bottomPanelView.frame.size.height;
    }
    
    func applyShadow(view: UIView)
    {
        view.layer.shadowColor = UIColor.darkGray.cgColor
        view.layer.shadowRadius = 11
        view.layer.shadowOffset = CGSize(width: 0, height: 0)
        view.layer.shadowOpacity = 0.5
        view.layer.masksToBounds = false
    }
    
    public override func point(inside point: CGPoint, with event: UIEvent?) -> Bool
    {
        let leftViewPoint = view.convert(point, to: leftPanelView)
        let pointInsideLeftView = (leftInfoViews.frame.contains(leftViewPoint) || directionsView.frame.contains(leftViewPoint))
        
        let bottomViewPoint = view.convert(point, to: bottomPanelView)
        let pointInsideBottomView = bottomStack.frame.contains(bottomViewPoint)
        
        let topViewPoint = view.convert(point, to: topPanelView)
        let pointInsideTopView = (stepByStepDirectionsView.frame.contains(topViewPoint) || currentDirectionView.frame.contains(topViewPoint) || nextDirectionView.frame.contains(topViewPoint))
        
        return  (pointInsideLeftView || pointInsideBottomView || pointInsideTopView);
    }
    
    public func modelSet()
    {
        if let navModel = observer.navModel()
        {
            setupJourneyView           .observer.setNavModel(navModel) //Left
            leftTimeToDestinationView  .observer.setNavModel(navModel) //Left
            directionsView             .observer.setNavModel(navModel) //Left
            currentDirectionView       .observer.setNavModel(navModel) //Top
            nextDirectionView          .observer.setNavModel(navModel) //Top
            stepByStepDirectionsView   .observer.setNavModel(navModel) //Top
            bottomTimeToDestinationView.observer.setNavModel(navModel) //Bottom
        }
        
        updateNavMode(animate: false)
        updateBottomStack()
    }
    
    public override func eventReceived(key: WRLDNavEvent)
    {
        if key == .showHideListButtonClicked
        {
            setStepByStepDirectionsVisibility(visible: !m_isStepByStepNavListShowing, animate: true)
        }
        
        super.eventReceived(key: key)
    }
    
    func setLeftVisibility(visible: Bool, animate: Bool)
    {
        let frameWidth: Int = 371
        let frameHeight: Int = Int(view.frame.size.height)
        let openFrame   = CGRect(x:           0, y: 0, width: frameWidth, height: frameHeight)
        let closedFrame = CGRect(x: -frameWidth, y: 0, width: frameWidth, height: frameHeight)
        
        let block = {
            self.leftPanelView.frame  = (visible) ? (openFrame) : (closedFrame)
            self.view.setNeedsLayout()
            self.view.layoutIfNeeded()
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
    
    func setDirectionsVisibility(visible: Bool, animate: Bool)
    {
        let frameWidth: Int = Int(directionsView.frame.width)
        let frameHeight: Int = Int(directionsView.frame.height)
        let yPos = Int(directionsView.frame.minY)
        let openFrame   = CGRect(x:           0, y: yPos, width: frameWidth, height: frameHeight)
        let closedFrame = CGRect(x: -frameWidth, y: yPos, width: frameWidth, height: frameHeight)
        
        let block = {
            self.directionsView.frame  = (visible) ? (openFrame) : (closedFrame)
            self.view.setNeedsLayout()
            self.view.layoutIfNeeded()
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
    
    func setTopVisibility(visible: Bool, animate: Bool)
    {
        let frameWidth: Int = Int(view.frame.size.width)
        let frameHeight: Int = Int(view.frame.size.height - bottomStack.frame.size.height)
        let openFrame   = CGRect(x: 0, y:                 0, width: frameWidth, height: frameHeight)
        let closedFrame = CGRect(x: 0, y: -(frameHeight+11), width: frameWidth, height: frameHeight)
        
        let block = {
            self.topPanelView.frame  = (visible) ? (openFrame) : (closedFrame)
            self.view.setNeedsLayout()
            self.view.layoutIfNeeded()
            self.topPanelVisibleHeight = visible ? self.currentDirectionView.bounds.size.height : 0
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
        let frameHeight: Int = Int(m_bottomPanelHeight)
        let openFrame   = CGRect(x: 0, y: ht-frameHeight, width: frameWidth, height: frameHeight)
        let closedFrame = CGRect(x: 0, y:             ht, width: frameWidth, height: frameHeight)
        
        let block = {
            self.bottomPanelView.frame  = (visible) ? (openFrame) : (closedFrame)
            self.view.setNeedsLayout()
            self.view.layoutIfNeeded()
            self.bottomPanelVisibleHeight = visible ? self.bottomPanelView.bounds.size.height : 0
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
    
    func setStepByStepDirectionsVisibility(visible: Bool, animate: Bool)
    {
        m_isStepByStepNavListShowing = visible
        nextDirectionView.setShowHideListButtonState(visible)
        
        let frameWidth: Int = Int(stepByStepDirectionsView.frame.width)
        let frameHeight: Int = Int(stepByStepDirectionsView.frame.height)
        let yPos = Int(nextDirectionView.frame.maxY)
        let openFrame   = CGRect(x: 0, y:         yPos, width: frameWidth, height: frameHeight)
        let closedFrame = CGRect(x: 0, y: -frameHeight, width: frameWidth, height: frameHeight)
        
        let block = {
            self.stepByStepDirectionsView.frame  = (visible) ? (openFrame) : (closedFrame)
            self.view.setNeedsLayout()
            self.view.layoutIfNeeded()
            self.updateTopPanel()
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
    
    //This shows/hides the various UI elements based on the current navigation mode.
    override open func updateNavMode(animate: Bool)
    {
        if(_hideViews)
        {
            setLeftVisibility  (visible: false, animate: animate)
            setTopVisibility   (visible: false, animate: animate)
            setBottomVisibility(visible: false, animate: animate)
        }
        else if let navModel = observer.navModel()
        {
            switch(navModel.navMode)
            {
            case .notReady:
                setLeftVisibility  (visible:  true, animate: animate)
                setTopVisibility   (visible: false, animate: animate) 
                setBottomVisibility(visible: false, animate: animate)
                setDirectionsVisibility(visible: false, animate: animate)
                setStepByStepDirectionsVisibility(visible: false, animate: animate)
                break;
            case .ready:
                setLeftVisibility  (visible:  true, animate: animate)
                setTopVisibility   (visible: false, animate: animate)
                setBottomVisibility(visible: false, animate: animate)
                setDirectionsVisibility(visible:  true, animate: animate)
                setStepByStepDirectionsVisibility(visible: false, animate: false)
                break;
            case .active:
                setLeftVisibility  (visible: false, animate: animate)
                setTopVisibility   (visible:  true, animate: animate)
                setBottomVisibility(visible:  true, animate: animate)
                setStepByStepDirectionsVisibility(visible: false, animate: false)
                break;
            }
        }
    }
    
    //Show/hide the time to destination view when the user clicks the toggle button.
    func updateBottomStack()
    {
        UIView.animate(withDuration: 0.3, animations:
            {
                self.view.setNeedsLayout()
                self.view.layoutIfNeeded()
                self.bottomPanelVisibleHeight = self.bottomStack.bounds.size.height
                
                self.updateTopPanel()
            })
    }
    
    //Update top panel's size according to bottom stack size change
    func updateTopPanel()
    {
        if m_isStepByStepNavListShowing
        {
            let bottomHeight = m_bottomPanelHeight
            let frameHeight: Int = Int(self.view.frame.size.height - bottomHeight)
            let frameWidth: Int = Int(self.view.frame.size.width)
            let newFrame   = CGRect(x: 0, y: 0, width: frameWidth, height: frameHeight)
            self.topPanelView.frame = newFrame
            self.topPanelView.setNeedsLayout()
        }
    }
    
    @objc public override func setViewVisibility(animate: Bool, hideViews: Bool)
    {
        _hideViews = hideViews
        updateNavMode(animate: animate)
    }
}


