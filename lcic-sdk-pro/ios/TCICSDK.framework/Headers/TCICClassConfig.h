//
//  TCICClassConfig.h
//  TCICSDK
//
//  Created by AlexiChen on 2020/5/22.
//  Copyright © 2020 AlexiChen. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN



@interface TCICClassConfig : NSObject

@property (nonatomic, copy, nonnull) NSString *userId;                                          // 用户ID,必传
@property (nonatomic, copy, nonnull) NSString *token;                                           // token,必传
@property (nonatomic, assign) UInt32 schoolId;                                                  // 学校Id,必传
@property (nonatomic, assign) UInt32 classId;                                                   // 课程ID,必传
@property (nonatomic, strong, nullable) NSDictionary<NSString *, NSString *> *customParams;     // 自定义参数: 内部会自动将customParams内容接拼到query串, key-value均为NSString类型
@property (nonatomic, strong, nullable) NSDictionary *jsParams;
/// iOS16.4后，默认不可以DEBUG webview，若需要，则需将enableWebDebug设置为YES
@property (nonatomic, assign) BOOL enableWebDebug;
/**
 * 简化版接入方式，传入sign(上述关键字段userId/schoolId/classId/token的加密串)，内部会帮解析成TCICClassConfig;
 * 如sign不合法，会返回nil
 */
+ (instancetype)configWithSign:(NSString *_Nonnull)sign;


// 当前config是否有效，主要检查参数userId,token是否为空串,以及schoolId >0, classId>0,
// 以及customParams中是否包含有冲突字段
- (BOOL)isValid;

@end

NS_ASSUME_NONNULL_END
