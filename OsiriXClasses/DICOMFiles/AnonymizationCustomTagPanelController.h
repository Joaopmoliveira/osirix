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

@class DCMAttributeTag;

/**
 * Class used to interface with the @"AnonymizationCustomTagPanel" nib file. 
 * It serves the porpouse of changing a given tag through the DCMAttributeTag class.
 */

@interface AnonymizationCustomTagPanelController : NSWindowController {
	IBOutlet NSTextField* groupField;
	IBOutlet NSTextField* elementField;
}

/**
 * Reaction method to when the user selects the cancel button
 */
-(IBAction)cancelButtonAction:(id)sender;

/**
* Reaction method to when the user selects the ok button
 */
-(IBAction)okButtonAction:(id)sender;

/**
* Class used to store the tag, i.e. Dicom information and the relevant keys
 */
@property(assign) DCMAttributeTag* attributeTag;

@end
