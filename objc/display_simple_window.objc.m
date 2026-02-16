/******************************************************************************
 *                                  LICENSE                                   *
 ******************************************************************************
 *  This file is free software: you can redistribute it and/or modify         *
 *  it under the terms of the GNU General Public License as published by      *
 *  the Free Software Foundation, either version 3 of the License, or         *
 *  (at your option) any later version.                                       *
 *                                                                            *
 *  This file is distributed in the hope that it will be useful,              *
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of            *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the             *
 *  GNU General Public License for more details.                              *
 *                                                                            *
 *  You should have received a copy of the GNU General Public License         *
 *  along with this file.  If not, see <https://www.gnu.org/licenses/>.       *
 ******************************************************************************
 *  Purpose:                                                                  *
 *      Uses GNUstep to display a 'Hello, World' window.                      *
 ******************************************************************************
 *  Author:     Ryan Maguire                                                  *
 *  Date:       February 15, 2026                                             *
 ******************************************************************************/
#import <Foundation/Foundation.h>
#import <AppKit/AppKit.h>

int main(int argc, const char *argv[])
{
    NSAutoreleasePool *pool = [[NSAutoreleasePool alloc] init];

    [NSApplication sharedApplication];

    NSRect frame = NSMakeRect(100, 100, 300, 150);

    NSWindow *window = [[NSWindow alloc]
        initWithContentRect:frame
                  styleMask:(NSTitledWindowMask |
                             NSClosableWindowMask |
                             NSMiniaturizableWindowMask)
                    backing:NSBackingStoreBuffered
                      defer:NO];

    [window setTitle:@"Hello, World!"];
    [window makeKeyAndOrderFront:nil];

    NSTextField *label = [
        [NSTextField alloc] initWithFrame:NSMakeRect(50, 60, 200, 30)
    ];

    [label setStringValue:@"Hello, World!"];
    [label setBezeled:NO];
    [label setDrawsBackground:NO];
    [label setEditable:NO];
    [label setSelectable:NO];
    [label setAlignment:NSTextAlignmentCenter];

    [[window contentView] addSubview:label];

    [NSApp run];

    [pool drain];
    return NSApplicationMain(argc, argv);
}
