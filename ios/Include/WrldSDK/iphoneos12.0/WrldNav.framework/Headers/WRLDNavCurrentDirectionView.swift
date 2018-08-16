import UIKit
import WrldUtils

class WRLDNavCurrentDirectionViewCell: UICollectionViewCell
{
    @IBOutlet public weak var currentInstruction: UILabel!
    @IBOutlet public weak var thenInstruction: UILabel!
    @IBOutlet public weak var directionImageView: UIImageView!
}

@objc
public class WRLDNavCurrentDirectionView: UIView, WRLDNavModelObserverProtocol, UICollectionViewDataSource, UICollectionViewDelegate, UICollectionViewDelegateFlowLayout
{
    private let routeKeyPath = #keyPath(WRLDNavModel.route)
    private let currentDirectionKeyPath = #keyPath(WRLDNavModel.currentDirection)
    private let currentDirectionIndexKeyPath = #keyPath(WRLDNavModel.currentDirectionIndex)
    private let selectedDirectionIndexKeyPath = #keyPath(WRLDNavModel.selectedDirectionIndex)
    let cellIdentifier: String = "CurrentDirectionViewCell"
    
    @objc public var observer: WRLDNavModelObserver
    
    @IBOutlet weak var directionsCollectionView: UICollectionView!
    @IBOutlet weak var leftArrow: UIImageView!
    @IBOutlet weak var rightArrow: UIImageView!
    
    private var dotImage: UIImage?
    private var leftArrowImage: UIImage?
    private var rightArrowImage: UIImage?
    
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
        observer.registerObserver(observerKey: routeKeyPath)
        observer.registerObserver(observerKey: currentDirectionKeyPath)
        observer.registerObserver(observerKey: currentDirectionIndexKeyPath)
        observer.registerObserver(observerKey: selectedDirectionIndexKeyPath)
        
        let bundle = Bundle(for: WRLDNavCurrentDirectionView.self)
        
        let nib = UINib(nibName: "WRLDNavCurrentDirectionView", bundle: bundle)
        let view: UIView! = nib.instantiate(withOwner: self, options: nil)[0] as! UIView
        view.frame = bounds
        view.autoresizingMask = [.flexibleWidth, .flexibleHeight]
        addSubview(view)
        
        directionsCollectionView.register(UINib(nibName: "WRLDNavCurrentDirectionViewCell", bundle: bundle), forCellWithReuseIdentifier: cellIdentifier)
        
        directionsCollectionView.delegate = self
        directionsCollectionView.dataSource = self
        clipsToBounds = true
        
        let leftArrowTapGestureRecognizer = UITapGestureRecognizer(target: self, action: #selector(self.leftArrowTapped))
        leftArrow.addGestureRecognizer(leftArrowTapGestureRecognizer)
        leftArrow.isUserInteractionEnabled = true
        
        let rightArrowTapGestureRecognizer = UITapGestureRecognizer(target: self, action: #selector(self.rightArrowTapped))
        rightArrow.addGestureRecognizer(rightArrowTapGestureRecognizer)
        rightArrow.isUserInteractionEnabled = true
        
        dotImage = UIImage(named: "navigation_dot",
                               in: Bundle(for: WRLDNavCurrentDirectionView.self),
                               compatibleWith: nil)
        
        leftArrowImage = UIImage(named: "arrow_left",
                           in: Bundle(for: WRLDNavCurrentDirectionView.self),
                           compatibleWith: nil)
        
        rightArrowImage = UIImage(named: "arrow_right",
                           in: Bundle(for: WRLDNavCurrentDirectionView.self),
                           compatibleWith: nil)
    }
    
    public override func layoutSubviews()
    {
        super.layoutSubviews();

        let contentSize = CGSize(width: directionsCollectionView.frame.width, height: directionsCollectionView.frame.height)
        
        directionsCollectionView.collectionViewLayout.invalidateLayout()
        directionsCollectionView.contentSize = contentSize
        directionsCollectionView.layoutIfNeeded()
        
        if let navModel = observer.navModel()
        {
            if navModel.route != nil
            {
                let indexPath = NSIndexPath(row: navModel.selectedDirectionIndex , section: 0) as IndexPath
                directionsCollectionView.scrollToItem(at: indexPath, at: .left, animated: false)
            }
        }
    }
    
    public func modelSet()
    {
        setupUICollecionView()
    }
    
    public func changeReceived(keyPath: String)
    {
        if(keyPath == routeKeyPath)
        {
            setupUICollecionView()
            return;
        }
        else if(keyPath == currentDirectionKeyPath)
        {
            updateCurrentDirectionCell()
            return;
        }
        else if(keyPath == currentDirectionIndexKeyPath)
        {
            if let navModel = observer.navModel()
            {
                if((navModel.currentDirectionIndex-1) == navModel.selectedDirectionIndex)
                {
                    navModel.selectedDirectionIndex = navModel.currentDirectionIndex
                }
            }
            
            return;
        }
        else if(keyPath == selectedDirectionIndexKeyPath)
        {
            if let navModel = observer.navModel()
            {
                if let directions = navModel.route?.directions
                {
                    if directions.count > navModel.selectedDirectionIndex
                    {
                        scrollToDirection(direction: navModel.selectedDirectionIndex, animate: true)
                    }
                }
            }
            
            return;
        }
    }
    
    public func eventReceived(key: WRLDNavEvent)
    {
        if(key == WRLDNavEvent.routeUpdated)
        {
            if let navModel = observer.navModel()
            {
                setupUICollecionView()
                
                if let directions = navModel.route?.directions
                {
                    if directions.count > navModel.selectedDirectionIndex
                    {
                        scrollToDirection(direction: navModel.selectedDirectionIndex, animate: false)
                    }
                }
            }
        }
    }
    
    func setupUICollecionView()
    {
        directionsCollectionView.reloadData()
        updateArrows(true, false, (observer.navModel()?.selectedDirectionIndex)!)
    }
    
    func updateCurrentDirectionCell()
    {
        if let navModel = observer.navModel()
        {
            let indexPath = NSIndexPath(row: navModel.currentDirectionIndex , section: 0) as IndexPath
            directionsCollectionView.reloadItems(at: [indexPath])
        }
    }
    
    @objc func leftArrowTapped()
    {
        if let navModel = observer.navModel()
        {
            if navModel.selectedDirectionIndex > 0
            {
                navModel.selectedDirectionIndex -= 1
            }
        }
    }
    
    @objc func rightArrowTapped()
    {
        if let navModel = observer.navModel()
        {
            if let directions = navModel.route?.directions
            {
                if(navModel.selectedDirectionIndex < (directions.count-1))
                {
                    navModel.selectedDirectionIndex += 1
                }
            }
        }
    }
    
    func scrollToDirection(direction: Int, animate:Bool)
    {
        let indexPath = NSIndexPath(row: direction , section: 0) as IndexPath
        directionsCollectionView.scrollToItem(at: indexPath, at: .left, animated: animate)
        updateArrows(false, true, (observer.navModel()?.selectedDirectionIndex)!)
    }
    
    private func updateArrows(_ visible: Bool,_ animate: Bool,_ currentDirection: Int)
    {
        if visible
        {
            if let navModel = observer.navModel()
            {
                if let directions = navModel.route?.directions
                {
                    let showLeftArrow = currentDirection > 0
                    updateArrowImageView(leftArrow, visible, animate, showLeftArrow ? leftArrowImage : dotImage)
                    
                    let showRightArrow = currentDirection < (directions.count-1)
                    updateArrowImageView(rightArrow, visible, animate, showRightArrow ? rightArrowImage : dotImage)
                }
            }
        }
        else
        {
            updateArrowImageView(leftArrow, visible, animate)
            updateArrowImageView(rightArrow, visible, animate)
        }
    }
    
    private func updateArrowImageView(_ view: UIImageView, _ visible: Bool,_ animate: Bool,_ image: UIImage? = nil)
    {
        if image != nil
        {
            view.image = image
        }
        
        let block = {
            view.alpha = visible ? 1 : 0
        };
        
        if animate
        {
            UIView.animate(withDuration: 0.15, animations:block)
        }
        else
        {
            block()
        }
    }
    
    //MARK: - UICollectionViewDataSource
    
    public func collectionView(_ collectionView: UICollectionView, numberOfItemsInSection section: Int) -> Int
    {
        if let navModel = observer.navModel()
        {
            if let directions = navModel.route?.directions
            {
                return directions.count
            }
        }
        
        return 0
    }
    
    public func collectionView(_ collectionView: UICollectionView, cellForItemAt indexPath: IndexPath) -> UICollectionViewCell
    {
        let cell = collectionView.dequeueReusableCell(withReuseIdentifier: cellIdentifier, for: indexPath) as! WRLDNavCurrentDirectionViewCell
        
        if let navModel = observer.navModel()
        {
            if let directions = navModel.route?.directions
            {
                let direction: WRLDNavDirection = directions[indexPath.item]
                cell.currentInstruction?.text = direction.instruction
                cell.thenInstruction?.text = direction.thenInstruction
                
                cell.currentInstruction?.numberOfLines = direction.thenInstruction.isEmpty ? 2 : 1;
                cell.currentInstruction?.lineBreakMode = NSLineBreakMode.byTruncatingTail;
                
                let bundle = Bundle(for: WRLDNavCurrentDirectionView.self)
                cell.directionImageView?.image = UIImage.init(named: String(format: "big_%@", direction.icon), in: bundle, compatibleWith: nil)
            }
        }
        else
        {
            cell.currentInstruction.text = ""
            cell.thenInstruction.text = ""
            
            let bundle = Bundle(for: WRLDNavCurrentDirectionView.self)
            cell.directionImageView.image = UIImage.init(named: "big_depart", in: bundle, compatibleWith: nil)
        }
        
        return cell
    }
    
    //MARK: - UICollectionViewDelegate
    public func scrollViewWillBeginDragging(_ scrollView: UIScrollView)
    {
        updateArrows(false, true, (observer.navModel()?.selectedDirectionIndex)!)
    }
    
    public func scrollViewDidEndScrollingAnimation(_ scrollView: UIScrollView)
    {
        updateArrows(true, true, (observer.navModel()?.selectedDirectionIndex)!)
    }
    
    //Forcing scrollview to avoid scrolling vertically
    public func scrollViewDidScroll(_ scrollView: UIScrollView)
    {
        if scrollView.contentOffset.y != 0
        {
            scrollView.contentOffset.y = 0
        }
    }
    
    public func scrollViewDidEndDecelerating(_ scrollView: UIScrollView)
    {
        let currentPage = Int(scrollView.contentOffset.x / scrollView.frame.size.width)
        if let navModel = observer.navModel()
        {
            navModel.selectedDirectionIndex = currentPage
            updateArrows(true, true, currentPage)
        }
    }
    
    //MARK: - UICollectionViewDelegateFlowLayout
    
    public func collectionView(_ collectionView: UICollectionView, layout collectionViewLayout: UICollectionViewLayout, sizeForItemAt indexPath: IndexPath) -> CGSize
    {
        return CGSize(width: collectionView.frame.width, height: collectionView.frame.height)
    }
}
