import UIKit

@objc
public class WRLDNavNextDirectionView: UIView, WRLDNavModelObserverProtocol
{
    private let navModeKeyPath = #keyPath(WRLDNavModel.navMode)
    private let selectedDirectionKeyPath = #keyPath(WRLDNavModel.selectedDirectionIndex)
    
    @objc public var observer: WRLDNavModelObserver

    @IBOutlet weak var iconView: UIImageView!
    @IBOutlet weak var labelView: UILabel!
    @IBOutlet weak var showHideListButton: UIButton?
    
    public override init(frame: CGRect)
    {
        observer = WRLDNavModelObserver()
        super.init(frame: frame)
        observer.delegate = self
        initCommon()
    }
    
    public required init?(coder aDecoder: NSCoder)
    {
        observer = WRLDNavModelObserver()
        super.init(coder: aDecoder)
        observer.delegate = self
        initCommon()
    }
    
    private func initCommon()
    {
        observer.registerObserver(observerKey: navModeKeyPath)
        observer.registerObserver(observerKey: selectedDirectionKeyPath)
        
        let bundle = Bundle(for: WRLDNavNextDirectionView.self)
        
        let nib = UINib(nibName: "WRLDNavNextDirectionView", bundle: bundle)
        let view: UIView! = nib.instantiate(withOwner: self, options: nil)[0] as! UIView
        view.frame = bounds
        view.autoresizingMask = [.flexibleWidth, .flexibleHeight]
        addSubview(view)
    }
    
    @IBAction func showHideListButtonPressed(_ sender: Any)
    {
        if let navModel = observer.navModel()
        {
            navModel.sendNavEvent(.showHideListButtonClicked)
        }
    }
    
    public func setShowHideListButtonState(_ selected: Bool)
    {
        showHideListButton?.isSelected = selected;
    }
    
    public func modelSet()
    {
        updateNextNavInstructionUI()
    }
    
    public func changeReceived(keyPath: String)
    {
        if(keyPath == selectedDirectionKeyPath || keyPath == navModeKeyPath)
        {
            updateNextNavInstructionUI()
            return;
        }
    }
    
    public func eventReceived(key: WRLDNavEvent)
    {
        if(key == WRLDNavEvent.routeUpdated)
        {
            updateNextNavInstructionUI()
        }
    }
    
    private func updateNextNavInstructionUI()
    {
        if let navModel = observer.navModel()
        {
            if let directions = navModel.route?.directions
            {
                let index = navModel.selectedDirectionIndex + 1
                if(index>=0 && index<directions.count)
                {
                    let direction: WRLDNavDirection = directions[index]
                    labelView.text = direction.name
                    
                    let bundle = Bundle(for: WRLDNavNextDirectionView.self)
                    iconView.image = UIImage.init(named: String(format: "small_%@", direction.icon), in: bundle, compatibleWith: nil)
                    
                    labelView.isHidden = false;
                    iconView.isHidden = false;
                }
                else
                {
                    labelView.isHidden = true;
                    iconView.isHidden = true;
                }
            }
        }
    }
}

