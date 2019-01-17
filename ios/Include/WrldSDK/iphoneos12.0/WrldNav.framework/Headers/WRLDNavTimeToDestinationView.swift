import UIKit

@objc
public class WRLDNavTimeToDestinationView: UIView, WRLDNavModelObserverProtocol
{
    private let remainingRouteDurationKeyPath = #keyPath(WRLDNavModel.remainingRouteDuration)
    private let navModeKeyPath = #keyPath(WRLDNavModel.navMode)
    
    @objc public var observer: WRLDNavModelObserver
    
    @IBOutlet public weak var timeBigNumber: UILabel!
    @IBOutlet public weak var timeSmallNumber: UILabel!
    @IBOutlet public weak var timeBigUnits: UILabel!
    @IBOutlet public weak var timeSmallUnits: UILabel!
    @IBOutlet public weak var startEndButton: UIButton!
    
    var m_startIcon: UIImage?
    var m_endIcon: UIImage?
    
    public override init(frame: CGRect)
    {
        observer = WRLDNavModelObserver();
        super.init(frame: frame)
        observer.delegate = self
        initCommon()
    }
    
    public required init?(coder aDecoder: NSCoder)
    {
        observer = WRLDNavModelObserver();
        super.init(coder: aDecoder)
        observer.delegate = self
        initCommon()
    }
    
    private func initCommon()
    {
        observer.registerObserver(observerKey: remainingRouteDurationKeyPath)
        observer.registerObserver(observerKey: navModeKeyPath)
        
        let bundle = Bundle(for: WRLDNavTimeToDestinationView.self)
        
        let nib = UINib(nibName: "WRLDNavTimeToDestinationView", bundle: bundle)
        let view: UIView! = nib.instantiate(withOwner: self, options: nil)[0] as! UIView
        view.frame = bounds
        view.autoresizingMask = [.flexibleWidth, .flexibleHeight]
        addSubview(view)
        
        m_startIcon = UIImage.init(named: "start_icon", in: bundle, compatibleWith: nil)
        m_endIcon   = UIImage.init(named: "end_icon",   in: bundle, compatibleWith: nil)
        
        startEndButton.layer.cornerRadius = 4
        startEndButton.clipsToBounds = true
        startEndButton.imageView?.contentMode = .scaleAspectFit
    }
    
    public func modelSet()
    {
        updateTimeUI()
        updateButtonUI()
    }
    
    public func changeReceived(keyPath: String)
    {
        if(keyPath == remainingRouteDurationKeyPath)
        {
            updateTimeUI()
            return;
        }
        
        if(keyPath == navModeKeyPath)
        {
             updateButtonUI()
             return;
        }
    }
    
    private func updateTimeUI()
    {
        if let duration = observer.navModel()?.remainingRouteDuration
        {
            let hours = Int(duration / 3600)
            let minutes = Int(duration / 60) - (hours * 60)
            let seconds = Int(duration) - (minutes * 60)
            
            if(hours > 0)
            {
                if(hours >= 24)
                {
                    let days = Int(hours / 24)
                    let remainingHours = days % 24
                    
                    timeBigNumber.text = String(format: "%d", days)
                    timeSmallNumber.text = String(format: "%d", remainingHours)
                    
                    timeBigUnits.text = days > 1 ? "days" : "day"
                    timeSmallUnits.text = remainingHours > 1 ? "hours" : "hour"
                }
                else
                {
                    timeBigNumber.text = String(format: "%d", hours)
                    timeSmallNumber.text = String(format: "%d", minutes)
                    
                    timeBigUnits.text = hours > 1 ? "hours" : "hour"
                    timeSmallUnits.text = minutes > 1 ? "mins" : "min"
                }
            }
            else
            {
                timeBigNumber.text = String(format: "%d", minutes)
                timeSmallNumber.text = String(format: "%d", seconds)
                
                timeBigUnits.text = minutes > 1 ? "mins" : "min"
                timeSmallUnits.text = "sec"
            }
        }
    }
    
    private func updateButtonUI()
    {
        if let navMode = observer.navModel()?.navMode
        {
            switch(navMode)
            {
            case .notReady:
                startEndButton.isHidden = true
                break;
            case .ready:
                UIView.performWithoutAnimation {
                    startEndButton.setTitle("Start", for: .normal)
                    startEndButton.isHidden = false
                    startEndButton.setImage(m_startIcon, for: .normal)
                    startEndButton.layoutIfNeeded()
                }
                break;
            case .active:
                UIView.performWithoutAnimation {
                    startEndButton.setTitle("End", for: .normal)
                    startEndButton.isHidden = false
                    startEndButton.setImage(m_endIcon, for: .normal)
                    startEndButton.layoutIfNeeded()
                }
                break;
            }
        }
    }

    @IBAction func startEndButtonClicked(_ sender: Any)
    {
        observer.navModel()?.sendNavEvent(.startEndButtonClicked)
    }
}
