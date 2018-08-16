import UIKit
import WrldUtils

@objc
public class WRLDNavSetupJourneyView: UIView, WRLDNavModelObserverProtocol, UITextFieldDelegate, WRLDUtilsTextFieldDelegate
{
    private let startLocationKeyPath = #keyPath(WRLDNavModel.startLocation)
    private let endLocationKeyPath = #keyPath(WRLDNavModel.endLocation)
    
    @objc public var observer: WRLDNavModelObserver
    
    @IBOutlet var view: UIView!
    @IBOutlet weak var startLineEdit: WRLDUtilsTextField!
    @IBOutlet weak var endLineEdit: WRLDUtilsTextField!
    @IBOutlet weak var swapButton: WRLDUtilsImageButton!
    @IBOutlet weak var closeButton: WRLDUtilsImageButton!
    
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
        observer.registerObserver(observerKey: startLocationKeyPath)
        observer.registerObserver(observerKey: endLocationKeyPath)
        
        let bundle = Bundle(for: WRLDNavSetupJourneyView.self)
        
        let nib = UINib(nibName: "WRLDNavSetupJourneyView", bundle: bundle)
        let view: UIView! = nib.instantiate(withOwner: self, options: nil)[0] as! UIView
        view.frame = bounds
        view.autoresizingMask = [.flexibleWidth, .flexibleHeight]
        addSubview(view)
        
        startLineEdit.delegate = self
        endLineEdit.delegate = self
        
        styleButton(button: swapButton)
        styleButton(button: closeButton)
        
        startLineEdit.buttonDelegate = self
        endLineEdit.buttonDelegate = self
    }
    
    func styleButton(button: WRLDUtilsImageButton)
    {
        button.layer.cornerRadius = 4
    }
    
    public func modelSet()
    {
        updateStartLocationUI()
        updateEndLocationUI()
    }
    
    public func changeReceived(keyPath: String)
    {
        if(keyPath == startLocationKeyPath)
        {
            updateStartLocationUI()
            return;
        }

        if(keyPath == endLocationKeyPath)
        {
            updateEndLocationUI()
            return;
        }
    }
    
    public func textFieldShouldBeginEditing(_ textField: UITextField) -> Bool
    {
        view.endEditing(true)
        
        if(textField == startLineEdit)
        {
            observer.navModel()?.sendNavEvent(.selectStartLocationClicked)
        }
        else if(textField == endLineEdit)
        {
            observer.navModel()?.sendNavEvent(.selectEndLocationClicked)
        }
        return false
    }
    
    public func rightButtonClicked(textField: WRLDUtilsTextField)
    {
        if let navModel = observer.navModel()
        {
            if(textField == startLineEdit)
            {
                navModel.sendNavEvent(.startLocationClearButtonClicked)
            }
                
            else if(textField == endLineEdit)
            {
                navModel.sendNavEvent(.endLocationClearButtonClicked)
            }
        }
    }
    
    public func setHidden(isHidden: Bool)
    {
        self.startLineEdit.alpha = isHidden ? 0.0 : 1.0
        self.endLineEdit.alpha = isHidden ? 0.0 : 1.0
        self.isHidden = isHidden
    }
    
    public func leftButtonClicked(textField: WRLDUtilsTextField)
    {
        
    }
    
    private func updateStartLocationUI()
    {
        startLineEdit.text = observer.navModel()?.startLocation?.name
    }
    
    private func updateEndLocationUI()
    {
        endLineEdit.text = observer.navModel()?.endLocation?.name
    }
    
    @IBAction func swapButtonClicked(_ sender: Any)
    {
        if let navModel = observer.navModel()
        {
            let startLocation = navModel.endLocation
            navModel.endLocation = navModel.startLocation
            navModel.startLocation = startLocation
            navModel.sendNavEvent(.startEndLocationsSwapped)
        }
    }
    
    @IBAction func closeButtonClicked(_ sender: Any)
    {
        observer.navModel()?.sendNavEvent(.closeSetupJourneyClicked)
    }
}

