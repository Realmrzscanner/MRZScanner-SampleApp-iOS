//
//  ScrollViewController.swift
//  HotelSampleAppSwift
//
//  Created by Vasil Panov on 7/5/19.
//  Copyright © 2019 Vasil Panov. All rights reserved.
//

import Foundation
import UIKit
import MRZScannerSDK

class ScrollViewController : UIViewController, MRZScannerDelegate{
    
    @IBOutlet weak var startScan: UIButton!
    @IBOutlet weak var completeButton: UIButton!
    @IBOutlet weak var scrollView: UIScrollView!
    @IBOutlet weak var surnameEditTxt: UITextField!
    @IBOutlet weak var givenNameEditTxt: UITextField!
    @IBOutlet weak var documentNumberEditTxt: UITextField!
    @IBOutlet weak var issuingCountryEditTxt: UITextField!
    @IBOutlet weak var nationalityEditTxt: UITextField!
    @IBOutlet weak var dateofBirthEditTxt: UITextField!
    @IBOutlet weak var sexEditTxt: UITextField!
    @IBOutlet weak var estimatedIssuingDateEditTxt: UITextField!
    @IBOutlet weak var expirationdateEditTxt: UITextField!
    @IBOutlet weak var optionalvalueeditTxt: UITextField!

    @IBOutlet weak var backButton: UIButton!
    
    var imageData : UIImage?
    var maxCoreSetVar : Int32 = 2
    var mrzScannerController:MRZScannerController?
    
    override func viewDidLoad() {
        
        startScan.layer.cornerRadius = startScan.frame.size.height / 2
        backButton.layer.cornerRadius = startScan.frame.size.height / 2
        completeButton.layer.cornerRadius = completeButton.frame.size.height / 2

        scrollView.contentInset = UIEdgeInsets(top: 0.0,left: 0.0,bottom: 700,right: 0.0)
    }
    
    @IBAction func startScannerAction(_ sender: Any) {
        startScanner()
    }
    
     func startScanner()-> Void {
        DispatchQueue.main.async {
            let currentVC = self
            self.mrzScannerController?.setMaxCPUCores(self.maxCoreSetVar)
            self.mrzScannerController = MRZScannerController.init()
            self.mrzScannerController!.delegate = self
            currentVC.addChild(self.mrzScannerController!)
            self.mrzScannerController?.setMaxCPUCores(self.maxCoreSetVar)
            self.mrzScannerController?.setScannerType(MRZScannerType(rawValue:MRZScannerType.RawValue(0)))
            self.mrzScannerController!.initUI(currentVC)
        }
    }
    
    func successfulDocumentScan(withImageResult resultImage: UIImage!) {
        imageData = resultImage;
        self.mrzScannerController!.dismiss(animated: true, completion: nil)
    }
    
    func successfulScan(withResult result: MRZResultDataModel!) {
    
        if(result != nil){
            self.mrzScannerController?.dismiss(animated: true, completion: nil)
            surnameEditTxt.insertText(result.surnames_readable)
            givenNameEditTxt.insertText(result.given_names_readable)
            documentNumberEditTxt.insertText(result.document_type_readable)
            issuingCountryEditTxt.insertText(result.est_issuing_date_readable)
            nationalityEditTxt.insertText(result.nationality)
            dateofBirthEditTxt.insertText(result.dob_readable)
            sexEditTxt.insertText(result.sex)
            estimatedIssuingDateEditTxt.insertText(result.est_issuing_date_readable)
            expirationdateEditTxt.insertText(result.expiration_date_readable)
            optionalvalueeditTxt.insertText(result.optionals_readable)
        }
    }
    
    func takeImageID()
    {
        MRZScannerController.setPassportActive(true)
        MRZScannerController.setIDActive(true)
        self.mrzScannerController?.setScannerType(MRZScannerType(rawValue:MRZScannerType.RawValue(1)))
    }
    
    @IBAction func completeButtonFunc(_ sender: Any) {
        
    }
    
    
    
}
