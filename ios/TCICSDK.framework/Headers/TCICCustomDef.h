//
//  TCICCustomDef.h
//  TCICSDK
//
//  Created by 陈耀武 on 2020/10/29.
//  Copyright © 2020 陈耀武. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN


/**
 * 自定义通道接收者
 */
@protocol TCICCustomMessageReceiver <NSObject>

@required

/**
* H5向Native发送消息
* @param jsonMsg 发送的定制消息;
* 注意事项：
*   1. 若业务侧接收到消息后，异步调用sendCustomMsg回复；
*/

- (void)onRecvCustomMessage:(NSString *_Nonnull)jsonMsg;

@end



NS_ASSUME_NONNULL_END
