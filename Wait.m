/*=========================================================================
  Program:   OsiriX

  Copyright (c) OsiriX Team
  All rights reserved.
  Distributed under GNU - GPL
  
  See http://www.osirix-viewer.com/copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.
=========================================================================*/


#import "Wait.h"
#import "SendController.h"

@implementation Wait

- (void) showWindow: (id) sender
{
	[super showWindow: sender];
	[[self window] makeKeyAndOrderFront: sender];
	[[self window] display];
}

- (void) dealloc
{
	[startTime release];
	
	if( session != 0L) [NSApp endModalSession:session];
	
	[super dealloc];
}

- (void)windowDidLoad
{
	[[self window] center];
//	[[self window] setOpaque:NO];
//	[[self window] setAlphaValue:.8f];
}

- (void)incrementBy:(double)delta
{
	long hours, minutes, seconds;
	NSTimeInterval  thisTime = [NSDate timeIntervalSinceReferenceDate];
	
	if( [progress doubleValue] != 0)
	{
		NSTimeInterval fullWork, intervalElapsed = -[startTime timeIntervalSinceNow];
		
		if( intervalElapsed > 1)
		{
			if( thisTime - lastTimeFrame > 1.0 && thisTime - firstTime > 10.0)
			{
				lastTimeFrame = thisTime;
				
				fullWork = (intervalElapsed * ([progress maxValue] - [progress minValue])) / [progress doubleValue];
				
				fullWork -= intervalElapsed;
				
				hours = fullWork;
				hours /= (60*60);
				minutes = fullWork;
				minutes -= hours*60*60;
				minutes /= 60;
				seconds = fullWork;
				seconds -= hours*60*60 + minutes*60;
				
				[elapsed setStringValue:[NSString stringWithFormat:@"Estimated remaining time: %2.2d:%2.2d:%2.2d", hours, minutes, seconds]];
				[elapsed displayIfNeeded];
				
				#if __LP64__
				#else
				UpdateSystemActivity(UsrActivity);	// avoid sleep or screen saver mode
				#endif
			}
		}
	}
	else
	{
		startTime = [[NSDate date] retain];
		
		if( openSession) session = [NSApp beginModalSessionForWindow:[self window]];
	}
	
	[progress incrementBy:delta];
	
	if( thisTime - lastTimeFrameUpdate > 1.0)
	{
		lastTimeFrameUpdate = thisTime;
		
		[progress displayIfNeeded];
	
		if( openSession) [NSApp runModalSession:session];
	}
}

- (void) setElapsedString :(NSString*) str
{
	[elapsed setStringValue: str];
	[elapsed displayIfNeeded];
}

-(id) initWithString:(NSString*) str :(BOOL) useSession
{
	self = [super initWithWindowNibName:@"Wait"];
    [[self window] center];
	[[self window] setLevel: NSModalPanelWindowLevel];
	if( str) [text setStringValue:str];
	
	startTime = 0L;
	lastTimeFrame = 0;
	lastTimeFrameUpdate = 0;
	session = 0L;
	cancel = NO;
	aborted = NO;
	openSession = useSession;
	_target = 0L;
	firstTime = [NSDate timeIntervalSinceReferenceDate];
	
	return self;
}

-(id) initWithString:(NSString*) str
{
	return [self initWithString: str :YES];
}

-(void) setHide :(BOOL) val
{
	[[self window] setCanHide: val];
}

-(void) setCancel :(BOOL) val
{
	cancel = val;
	[abort setHidden: !val];
	[abort display];
}

- (NSProgressIndicator*) progress
{
	 return progress;
}

-(IBAction) abortButton: (id) sender
{
	aborted = YES;
	[_target abort];
//	[[NSNotificationCenter defaultCenter] postNotificationName:@"DCMAbortSendNotification" object:self];
	[NSApp stopModal];
}

-(BOOL) aborted
{
	return aborted;
}

- (void)setTarget:(id)target{
	_target = target;
}

@end
