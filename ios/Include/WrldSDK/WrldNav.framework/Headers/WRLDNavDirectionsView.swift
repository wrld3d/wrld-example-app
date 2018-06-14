import UIKit
import WrldUtils

class WRLDNavDirectionsViewCell: UITableViewCell
{
    @IBOutlet public weak var directionIconView: UIImageView!
    @IBOutlet public weak var labelView: UILabel!
}

class WRLDNavDirectionsViewDotCell: UITableViewCell
{

}

@objc
public class WRLDNavDirectionsView: UIView, WRLDNavModelObserverProtocol, UITableViewDelegate, UITableViewDataSource
{
    private let routeKeyPath = #keyPath(WRLDNavModel.route)
    private let currentDirectionKeyPath = #keyPath(WRLDNavModel.currentDirection)
    private let currentDirectionIndexKeyPath = #keyPath(WRLDNavModel.currentDirectionIndex)
    private let selectedDirectionIndexKeyPath = #keyPath(WRLDNavModel.selectedDirectionIndex)
    
    @objc public var observer: WRLDNavModelObserver
    
    @IBOutlet weak var tableView: UITableView!
    @IBOutlet weak var whiteFadeImage: WRLDUtilsImageView!
    
    let cellIdentifier: String = "Direction"
    let dotCellIdentifier: String = "Dot"
    let cellHeight = 40
    
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
        super.awakeFromNib()
        observer.registerObserver(observerKey: routeKeyPath)
        observer.registerObserver(observerKey: currentDirectionKeyPath)
        observer.registerObserver(observerKey: currentDirectionIndexKeyPath)
        observer.registerObserver(observerKey: selectedDirectionIndexKeyPath)
        
        let bundle = Bundle(for: WRLDNavDirectionsView.self)
        
        let nib = UINib(nibName: "WRLDNavDirectionsView", bundle: bundle)
        let view: UIView! = nib.instantiate(withOwner: self, options: nil)[0] as! UIView
        view.frame = bounds
        view.autoresizingMask = [.flexibleWidth, .flexibleHeight]
        addSubview(view)
        
        tableView.register(UINib(nibName: "WRLDNavDirectionsViewCell", bundle: bundle), forCellReuseIdentifier: cellIdentifier)
        tableView.register(UINib(nibName: "WRLDNavDirectionsViewDotCell", bundle: bundle), forCellReuseIdentifier: dotCellIdentifier)
        tableView.dataSource = self
        tableView.delegate = self
        clipsToBounds = true
    }
    
    private func updateWhiteFade()
    {
        var count = 0
        if let directions = observer.navModel()?.route?.directions
        {
            count = directions.count
        }
        
        let contentHeight = CGFloat(count * cellHeight)
        
        let hide = ((tableView.contentOffset.y >= (contentHeight - tableView.frame.size.height)) ||
                    (contentHeight < tableView.frame.size.height))

        UIView.animate(withDuration: 1.4, animations:{self.whiteFadeImage.alpha = hide ? 0.0 : 1.0})
    }
    
    public func tableView(_ tableView: UITableView, numberOfRowsInSection section: Int) -> Int
    {
        if let directions = observer.navModel()?.route?.directions
        {
            return directions.count + 1
        }
        
        return 0;
    }
    
    public func tableView(_ tableView: UITableView, cellForRowAt indexPath: IndexPath) -> UITableViewCell
    {
        let row = indexPath.row;
        var count = 0
        if let directions = observer.navModel()?.route?.directions
        {
            count = directions.count
            if(row>=0 && row<count)
            {
                let cell = tableView.dequeueReusableCell(withIdentifier: cellIdentifier) as! WRLDNavDirectionsViewCell
                let direction: WRLDNavDirection = directions[row]
                cell.labelView?.text = direction.name;
                
                cell.directionIconView?.image =
                    UIImage(named: String(format: "small_%@", direction.icon),
                            in: Bundle(for: WRLDNavDirectionsView.self),
                            compatibleWith: nil)
                
                cell.backgroundColor = (observer.navModel()?.currentDirectionIndex == row) ?
                    UIColor(red: 0.85, green: 0.92, blue: 0.96, alpha: 1.0) : //#D9EAF5
                    UIColor(red: 1.00, green: 1.00, blue: 1.00, alpha: 1.0)
                
                return cell
            }
        }
        
        if(row==count)
        {
            let cell: WRLDNavDirectionsViewDotCell = tableView.dequeueReusableCell(withIdentifier: dotCellIdentifier) as! WRLDNavDirectionsViewDotCell
            cell.selectionStyle = UITableViewCellSelectionStyle.none
            return cell
        }
        
        let cell = tableView.dequeueReusableCell(withIdentifier: cellIdentifier) as! WRLDNavDirectionsViewCell
        cell.directionIconView?.image = nil
        cell.labelView?.text = nil
        return cell
    }
    
    public func tableView(_ tableView: UITableView, heightForRowAt indexPath: IndexPath) -> CGFloat
    {
        return CGFloat(cellHeight)
    }
    
    public func tableView(_ tableView: UITableView, willDisplay cell: UITableViewCell, forRowAt indexPath: IndexPath)
    {
        updateWhiteFade()
    }
    
    public func changeReceived(keyPath: String)
    {
        if (currentDirectionKeyPath == keyPath)
        {
            let indexPath = IndexPath(item: (observer.navModel()?.currentDirectionIndex)!, section: 0)
            tableView.reloadRows(at: [indexPath], with: UITableViewRowAnimation.none);
        }
        else if(keyPath == selectedDirectionIndexKeyPath)
        {
            updateNextNavInstructionUI()
        }
        else
        {
            tableView.reloadData()
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
        tableView.reloadData()
        let selectedDirection = observer.navModel()?.selectedDirectionIndex;
        let currentDirection = observer.navModel()?.currentDirectionIndex;
        let tableSelectedDirectionIndex = tableView.indexPathForSelectedRow;
        if(selectedDirection != tableSelectedDirectionIndex?.row)
        {
            let newIndexPath = IndexPath.init(row: selectedDirection!, section: 0);
            if(currentDirection != selectedDirection)
            {
                tableView.selectRow(at: newIndexPath, animated: false, scrollPosition: UITableViewScrollPosition.none);
            }
            else if(tableSelectedDirectionIndex != nil)
            {
                tableView.deselectRow(at: tableSelectedDirectionIndex!, animated: false)
            }
        }
    }
    
    public func tableView(_ tableView: UITableView, willSelectRowAt indexPath: IndexPath) -> IndexPath?
    {
        if let directions = observer.navModel()?.route?.directions
        {
            if indexPath.row < directions.count
            {
                return indexPath
            }
        }
        
        return nil
    }
    
    public func tableView(_ tableView: UITableView, didSelectRowAt indexPath: IndexPath)
    {
        observer.navModel()?.selectedDirectionIndex = indexPath.row;
    }
}
