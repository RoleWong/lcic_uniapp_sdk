//
//  TCICClassController.h
//  TIC_Web_SaaS_SDK
//
//  Created by AlexiChen on 2020/5/6.
//  Copyright © 2020 AlexiChen. All rights reserved.
//
// TCICSDKDebugVersion : <:TCICSDKDebugVersion:>
// TCICSDKGitCommitID : <:TCICSDKGitCommitID:>

#import <UIKit/UIKit.h>
#import <TCICSDK/TCICClassConfig.h>
#import <TCICSDK/TCICCustomDef.h>

NS_ASSUME_NONNULL_BEGIN

extern NSString *_Nonnull const TCIC_SDK_Version;
extern NSString *_Nonnull const TCIC_SDK_CommitID;

@interface TCICClassController : UIViewController

// 使用+classRoomWithConfig: 进行构建
+ (instancetype)new  __attribute__((unavailable("Use +classRoomWithConfig: instead")));
- (instancetype)init __attribute__((unavailable("Use +classRoomWithConfig: instead")));
/**
 * 调测型接口：设置本地课堂语言
 * @param lang 语言类型
 */
+ (void)setClassLanuage:(NSString * _Nullable)lang;

/**
 * 更换课堂主域名
 * @param domain 域名地址，若host为nil，则使用默认域名: class.qcloudclass.com
 * @return 是否设置成功
 */
+ (BOOL)setDomain:(NSString * _Nullable)domain;

/**
 * 更换课堂H5Version
 * @param h5Version 域名地址，若h5Version为nil则使用默认版本号:latest
 * @return 是否设置成功
 */
+ (BOOL)setH5Version:(NSString *)h5Version;

/**
 * 进课堂前预加载环境，以便快速进房;
 */
+ (void)preloadClass;

/**
* 使用H5+Native方式使用，请在主线程中调用
* @param roomConfig : 打开课堂所需要的配置
* 如果参数不合法，会返回nil，外部注意处理
*/
+ (instancetype _Nullable)classRoomWithConfig:(TCICClassConfig * _Nonnull)roomConfig;


/**
* 定制消息：注册自定义消息处理逻辑回调
* @param receiver H5与Native定制消息处理逻辑
* 注意事项:
*  1.在viewDidLoad之前调用即可，一般在 classRoomWithConfig 之后即可;
*  2.内部会强引用该对象，其生命周期同当前TCICClassController(释放时会自动释放receiver);
*  3.外部也可提前释放，setCustomMessageDelegate:nil即可;
*/
- (void)setCustomMessageDelegate:(id<TCICCustomMessageReceiver> _Nullable)receiver;


/**
 * 定制消息：向H5发送自定义消息
 * @param customMsg 要发送的消息，业务侧做好定制格式，以便H5侧解析
 * 注意事项：如果底层没准备好的情况下，SDK会先缓存，待底层处理好之后，再一并发送给H5
 */
- (void)sendCustomMessage:(NSString *_Nullable)customMsg;


@end

NS_ASSUME_NONNULL_END
