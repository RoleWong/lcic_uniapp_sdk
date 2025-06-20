//
//  LCICModule.h
//  lcic-uniapp-sdk
//
//  Created by Role Wong on 2/5/25.
//

#ifndef LCICModule_h
#define LCICModule_h

#import <Foundation/Foundation.h>
#import "DCUni/DCUniModule.h"

NS_ASSUME_NONNULL_BEGIN

@interface LCICModule : DCUniModule

- (void)joinClass:(NSDictionary *)options callback:(UniModuleKeepAliveCallback)callback;

@end

NS_ASSUME_NONNULL_END

#endif /* LCICModule_h */
