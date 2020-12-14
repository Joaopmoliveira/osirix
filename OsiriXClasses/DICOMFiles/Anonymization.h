/*=========================================================================
  Program:   OsiriX

  Copyright (c) OsiriX Team
  All rights reserved.
  Distributed under GNU - LGPL
  
  See http://www.osirix-viewer.com/copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.
=========================================================================*/

#import <Cocoa/Cocoa.h>


@class DCMAttributeTag, AnonymizationPanelController, AnonymizationSavePanelController;

/**
The Anonymization class provides several abstractions to deal with the tags that
 should be anonymized, related with the Dicom standard and it contains wrapper 
 methods to both call the anonimization panel and the c++ objects from dedicated libraries, i.e. DCMTK.
*/
@interface Anonymization : NSObject

/**
 * Method used to obtain the tag (in the form of the DCMAttributeTag class) in the 
 * dicom standard corresponding to the provided string k, and obtain the correct 
 * string representation of said tag
 * */

+(DCMAttributeTag*)tagFromString:(NSString*)k;

/**
 * Method used to create a NSMutableArray from the received NSDictionary. At each 
 * index there is a NSArray composed of a tag (DCMAttribute) and the object 
 * corresponding to said tag. 
 * */
+(NSArray*)tagsValuesArrayFromDictionary:(NSDictionary*)dic;

/**
 * Method used to create a NSMutableDictionary from the received NSArray(this
 *  NSArray is a composition of NSArrays). The Dictionary is composed of 
 * strings and corresponding objects in the NSArrays contained in the received NSArray.
 */
+(NSDictionary*)tagsValuesDictionaryFromArray:(NSArray*)arr;

/**
 * Method used to create an NSArray with the correct dicom tags from the received
 * NSArray composed of strings.
 */
+(NSArray*)tagsArrayFromStringsArray:(NSArray*)strings;

/**
 * Method used to call the anonimization panel, internally it calls the showPanelClass method.
 */
+(AnonymizationPanelController*)showPanelForDefaultsKey:(NSString*)defaultsKey modalForWindow:(NSWindow*)window modalDelegate:(id)delegate didEndSelector:(SEL)sel representedObject:(id)representedObject;

/**
 * Method used to call the save panel, internally it calls the showPanelClass method.
 */
+(AnonymizationSavePanelController*)showSavePanelForDefaultsKey:(NSString*)defaultsKey modalForWindow:(NSWindow*)window modalDelegate:(id)delegate didEndSelector:(SEL)sel representedObject:(id)representedObject;

/**
 * Method used to compare NSArrays of tags (DCMAttributes), returns YES if they are
 *  equal, NO otherwise.
 */
+(BOOL)tagsValues:(NSArray*)a1 isEqualTo:(NSArray*)a2;

/**
 * Method used to anonymize files, which correspond to the dicom images and the files 
 * received in the arguments of the function. Under the hood in uses the DCMTK library
 *  to process these computations.
 */
+(NSDictionary*)anonymizeFiles:(NSArray*)files dicomImages: (NSArray*) dicomImages toPath:(NSString*)dirPath withTags:(NSArray*)intags;

/**
 * Method used to obtain the global variable templateDicomFile which is a 
 * string that contains ?? not sure what is references...
 */
+(NSString*) templateDicomFile;

/**
 * Hiden method of the class, (cannot be called outside the function) to put forth the 
 * relevant anonimization panel (I assume it shows the nib file).
 */
//+(id)showPanelClass:(Class)c forDefaultsKey:(NSString*)defaultsKey modalForWindow:(NSWindow*)window modalDelegate:(id)delegate didEndSelector:(SEL)sel representedObject:(id)representedObject

@end
