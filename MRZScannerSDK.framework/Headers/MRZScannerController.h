
#import <UIKit/UIKit.h>
#import <CoreGraphics/CoreGraphics.h>
#import <CoreImage/CoreImage.h>
#import <AVFoundation/AVFoundation.h>
#import "MRZResultDataModel.h"

typedef enum {
    TYPE_MRZ,
    //    TYPE_BARCODE,
    TYPE_DOCUMENT_IMAGE_ID,
    TYPE_DOCUMENT_IMAGE_PASSPORT
} MRZScannerType;

@protocol MRZScannerDelegate <NSObject>
@optional
- (void) successfulScanWithResult:(MRZResultDataModel*)result;
- (void) successfulDocumentScanWithImageResult:(UIImage*)resultImage;
- (void) scannerWasDismissed;
- (void) scanImageFailed;
- (void) permissionsWereDenied;
@end

@interface MRZScannerController : UIViewController <AVCaptureVideoDataOutputSampleBufferDelegate>

@property (nonatomic, weak) id <MRZScannerDelegate> delegate;

-(void) initUI:(UIViewController*)scannerPresenter;

/**
 Specify the state of night mode. Night mode is used for increasing the ISO and brightness so the scanner performs better in dark environments.
 
 @param active [YES, NO]. Default value is NO.
 */
-(void) setNightModeActive:(BOOL)active;

/**
 Specify whether the scanner should detect and return result for IDs.
 
 @param active [YES, NO]. Default value is YES.
 */
+(void) setIDActive:(BOOL) active;

/**
 Specify whether the scanner should detect and return result for Passports.
 
 @param active [YES, NO]. Default value is YES.
 */
+(void) setPassportActive:(BOOL) active;

/**
 Specify whether the scanner should detect and return result for Visas.
 
 @param active [YES, NO]. Default value is YES.
 */
+(void) setVisaActive:(BOOL) active;

/**
 Specify the maximum number of CPU threads that the scanner can use during the scanning process.
 
 @param maxCPUCores Number of CPU threads. Default value is 2.
 */
-(void) setMaxCPUCores:(int) maxCPUCores;

/**
 Specify which scanner type you want to use. There are two options: "MRZ Scanner" and "Document Image scanner".
 The "MRZ Scanner" option is used to scan for MRZ.
 The "Document image scanner" is used for capturing front and back image of the ID documents.
 
 @param scannerType [SCANNER_TYPE_MRZ, SCANNER_TYPE_DOC_IMAGE_ID, SCANNER_TYPE_DOC_IMAGE_PASSPORT]. Default value is SCANNER_TYPE_MRZ
 */
-(void) setScannerType:(MRZScannerType) scannerType;

/**
 Set the date format in which the parsed dates are formatted.
 
 @param dateFormat The pattern describing the date format. Example: "dd.MM.yyyy"
 */
+(void) setDateFormat:(NSString *) dateFormat;

/**
 Resume scanning after the scanner has been paused/stopped. Usually after a successful scan.
 */
-(void) resumeScanner;

/**
 Stop and close the MRZ Scanner
 */
-(void) closeScanner;

/**
 Register with the licence key provided to remove the asterisks (*) from the result.
 
 @param key The provided licence key.
 @return Returns 0 for success, -1 if registration failed
 */
+(int) registerLicenseWithKey:(NSString*)key;

/**
 @return The current MRZScannerSDK Version.
 */
+(NSString*) getSDKVersion;

/**
 Scan a single image
 
 @param image The UIImage to be scanned.
 @return The result data model.
 */
+(MRZResultDataModel *) scanImage:(UIImage*) image;

/**
 Scan from gallery
 
 @param context The instance of the initializer controller.
 @param mrzDelegate MRZScannerDelegate
 */
+(void) scanFromGallery:(id)context delegate:(id<MRZScannerDelegate>)mrzDelegate;

/**
 Set the scanning rectangle to limit the scanning area. The parameters' values are representing percentages of the scanning preview.
 
 @param x the top left point of the scanning rectangle. [0,...,100] Default value: 1.
 @param y the top left point of the scanning rectangle. [0,...,100] Default value: 30.
 @param width the width of the scanning rectangle. [0,...,100] Default value: 98.
 @param height the height of the scanning rectangle. [0,...,100] Default value: 40.
 */
+(void) setScanningRectangleWithX:(float)x
                                y:(float)y
                            width:(float)width
                           height:(float)height;

/**
 Set valid issuing country codes. Successful scans with country codes not included in the array will be ignored.
 
 @param validIssuingCountries array with active country codes. Example value: @[@"D", @"USA"].
 */
+(void) setValidIssuingCountries:(NSArray<NSString*>*) validIssuingCountries;

/**
 Successful scans with documents that are expired will be ignored and the scanning process will continue until a valid document is found.
 
 @param ignore whether the result should be ignored. Default value: false.
 */
+(void) ignoreResultIfDocumentIsExpired:(BOOL) ignore;

-(void) setCustomOverlayImage:(UIImage *) customImage;

@end
