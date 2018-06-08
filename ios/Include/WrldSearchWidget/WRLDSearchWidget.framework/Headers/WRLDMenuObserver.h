#pragma once

#include <Foundation/Foundation.h>

/*!
 A method to be invoked when the Search Menu is opened.
 @param fromInteraction true if the menu was opened by a touch event, false if by a method call.
 */
typedef void (^OpenedEvent) (BOOL fromInteraction);

/*!
 A method to be invoked when the Search Menu is closed.
 @param fromInteraction true if the menu was closed by a touch event, false if by a method call.
 */
typedef void (^ClosedEvent) (BOOL fromInteraction);

/*!
 A method to be invoked when an option or one of the options children are selected.
 @param selectedOptionContext NSObject related to the selected item.  Context is attatched at menu creation.
 */
typedef void (^OptionSelectedEvent) (NSObject* selectedOptionContext);

/*!
 A method to be invoked when a menu option is expanded to show it's child content.
 @param expandedOptionContext NSObject related to the selected WRLDMenuOption.  Context is attatched at menu creation.
 @param fromInteraction true if the expand event was fired by a touch event, false if by a method call.
 */
typedef void (^OptionExpandedEvent) (NSObject* expandedOptionContext, BOOL fromInteraction);

/*!
 A method to be invoked when a menu option is collapsed to hide it's child content.
 @param collapsedOptionContext NSObject related to the selected WRLDMenuOption.  Context is attatched at menu creation.
 @param fromInteraction true if the expand event was fired by a touch event, false if by a method call.
 */
typedef void (^OptionCollapsedEvent) (NSObject* collapsedOptionContext, BOOL fromInteraction);

/*!
 An observer that invokes blocks of registered code when menu events occur.
 */
@interface WRLDMenuObserver : NSObject

/*!
 Add a method to be invoked when the menu opens.
 @param event A method that matches the OpenedEvent signature.
 */
- (void) addOpenedEvent: (OpenedEvent) event;

/*!
 Stop invoking the parameter method when the menu opens.
 @param event The method to be removed.
 */
- (void) removeOpenedEvent: (OpenedEvent) event;

/*!
 Add a method to be invoked when the menu closes.
 @param event A method that matches the ClosedEvent signature.
 */
- (void) addClosedEvent: (ClosedEvent) event;

/*!
 Stop invoking the parameter method when the menu closes.
 @param event The method to be removed.
 */
- (void) removeClosedEvent: (ClosedEvent) event;

/*!
 Add a method to be invoked when an option or a child of an option is selected.
 @param event A method that matches the OptionSelectedEvent signature.
 */
- (void) addOptionSelectedEvent: (OptionSelectedEvent) event;

/*!
 Stop invoking the parameter method when an option or a child of an option are selected.
 @param event A method that matches the OptionSelectedEvent signature.
 */
- (void) removeOptionSelectedEvent: (OptionSelectedEvent) event;

/*!
 Add method to be invoked when a menu option is expanded to show it's child content.
 @param event A method that matches the OptionExpandedEvent signature.
 */
- (void) addOptionExpandedEvent: (OptionExpandedEvent) event;

/*!
 Stop invoking the parameter method when a menu option is is expanded.
 @param event A method that matches the OptionExpandedEvent signature.
 */
- (void) removeOptionExpandedEvent: (OptionExpandedEvent) event;

/*!
 Add a method to be invoked when a menu option is collapsed to hide it's child content.
 @param event A method that matches the OptionCollapsedEvent signature.
 */
- (void) addOptionCollapsedEvent: (OptionCollapsedEvent) event;

/*!
 Stop invoking a method when a menu option is collapsed
 @param event A method that matches the OptionCollapsedEvent signature.
 */
- (void) removeOptionCollapsedEvent: (OptionCollapsedEvent) event;

@end
