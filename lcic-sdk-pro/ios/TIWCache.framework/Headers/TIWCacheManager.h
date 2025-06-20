#import <Foundation/Foundation.h>

@interface TIWCacheConfig : NSObject
/// 应用唯一标识
@property (nonatomic, assign) NSInteger sdkAppId;
/// 机构唯一标识
@property (nonatomic, assign) NSInteger schoolId;
/// 用户唯一标识
@property (nonatomic, copy) NSString *userId;
/// 网络资源包存放的本地目录
@property (nonatomic, copy) NSString *resourceDir;
/// 配置文件的网络地址
@property (nonatomic, copy) NSString *configUrl;
/// 本地配置文件路径，主要用于首次加载
@property (nonatomic, copy) NSString *configPath;
/// 本地资源包路径，主要用于首次加载
@property (nonatomic, copy) NSString *resourcePath;
/// 本地课件缓存目录，非必填，建议使用Cache目录，preloadCourseware必填
@property (nonatomic, copy) NSString *courseCacheDir;
/// 本地文件缓存目录，非必填，建议使用Cache目录，preloadFile时必填
@property (nonatomic, copy) NSString *cacheFileDir;
@end

/**
 * @brief 内部类
 */
@interface TIWMediaInfo : NSObject
/// 媒体分片大小
@property (nonatomic, assign) NSInteger fragSize;
/// 支持的媒体格式
@property (nonatomic, copy) NSString *supportFomats;
@end

@protocol TIWCacheDelegate <NSObject>

@optional

// force 不为0时，说明底层已强制更新
- (void)onTIWCacheUpdateResourceCompleted:(int32_t)force;

/**
 * @brief 课件缓存包下载成功与否回调
 * @param errcode : 0 , 成功 , 其他为错误
 * @param message : 0 , 成功 , 其他为错误
 */
- (void)onTIWCacheCoursewareDownloaded:(NSString *)zipUrl errorCode:(int32_t)errcode message:(NSString *)message;

/**
 * @brief 课件缓存包下载进度回调
 * @param progress : [-1, 100] , 下载进度，正常情况下为 [0, 100], 出错时，会返回progress -1
 * @param errMsg : progress = -1时，错误信息
 */
- (void)onTIWCacheCoursewareDownloading:(NSString *)zipUrl progress:(int32_t)progress errMessage:(NSString *)errMsg;

/**
 * @brief 文件下载成功与否回调
 * @param errcode : 0 , 成功 , 其他为错误
 * @param message : 0 , 成功 , 其他为错误
 */
- (void)onTIWCacheFileDownloaded:(NSString *)fileUrl errorCode:(int32_t)errcode message:(NSString *)message;
/**
 * @brief  文件下载进度回调
 * @param progress : [-1, 100] , 下载进度，正常情况下为 [0, 100], 出错时，会返回progress -1
 * @param errMsg : progress = -1时，错误信息
 */
- (void)onTIWCacheFileDownloading:(NSString *)zipUrl progress:(int32_t)progress errMessage:(NSString *)errMsg;

@end

@interface TIWCacheManager : NSObject

@property (nonatomic, weak) id<TIWCacheDelegate> delegate;

/**
 * @brief 获取单例
 */
+ (instancetype)shareInstance;

/**
 * @brief 销毁单例
 */
+ (void)destroyInstance;

/**
 * @brief 设置缓存配置
 * @param config 配置
 */
- (void)setConfig:(TIWCacheConfig *)config;

/**
 * @brief 获取资源的本地路径
 * @param url 网络 url
 * @return 本地资源路径，空则表示本地资源不存在
 */
- (NSString *)getResourcePath:(NSString *)url;

/**
 * @brief 启用和关闭缓存
 * @param enable 是否启用，默认为 YES
 */
- (void)enableCache:(bool)enable;

/**
 * @brief 刷新本地配置文件
 */
- (void)refreshServerConfig;

/**
 * @brief 获取当前版本
 * @return 版本号
 */
+ (NSString *)getVersion;

/**
 * @brief 打开和关闭控制台日志
 * @param enable 是否打开，默认为 YES
 */
- (void)enableConsole:(BOOL)enable;

/**
 * @brief 打开和关闭日志上报
 * @param enable 是否打开，默认为 YES
 */
- (void)enableReport:(BOOL)enable;

/**
 * @brief 获取媒体信息
 * @return 媒体信息
 * @warning 内部接口
 */
- (TIWMediaInfo *)getMediaInfo;

/**
 * @brief 开始打印日志
 * @param label 当前日志的唯一标示，记录开始时间以计算耗时
 * @warning 内部接口
 */
- (void)logStart:(NSString *)label;

/**
 * @brief 结束打印日志
 * @param label 当前日志的唯一标示，用以计算耗时
 * @param module 日志模块
 * @param action 当前行为
 * @param param 行为参数
 * @param ext   行为扩展字段
 * @param code  错误码
 * @param desc  错误描述
 * @warning 内部接口
 */
- (void)logEnded:(NSString *)label
          module:(NSString *)module
          action:(NSString *)action
           param:(NSString *)param
           ext:(NSString *)ext
            code:(NSInteger)code
            desc:(NSString *)desc;

/**
 * @brief 缓存课件资源包，方便在使用时，最好提前下载。如果进入课中时，还未下载完成，不会生效;
 *
 * @param zipUrl 课件zip地址，不能为空
 * @retentSec 保留时间，秒数, <=0 时无限期保存
 * 注意事项：需要在setConfig后使用，且TIWCacheConfig.courseCacheDir必填
 *
 * @return YES: 基础参数检查没问题，传入底层继续下载，后续会回调onTIWCacheCoursewareDownloading/onTIWCacheCoursewareDownloaded; NO : 参数检查不通过或未设置TIWCacheConfig.courseCacheDir必填
 */
- (BOOL)preloadCourseware:(NSString *)zipUrl retentionTime:(NSInteger)retentSec;

/**
 * @brief 缓存单个文件，方便在使用时，最好提前下载。如果进入课中时，还未下载完成，不会生效;
 *
 * @param fileUrl 文件地址，不能为空
 * @retentSec 保留时间，秒数, <0 时无限期保存
 * 注意事项：需要在setConfig后使用，且TIWCacheConfig.cacheFileDir必填
 *
 * @return YES: 基础参数检查没问题，传入底层继续下载，后续会回调onTIWCacheFileDownloading/onTIWCacheFileDownloaded； NO : 参数检查不通过或未设置TIWCacheConfig.cacheFileDir
 */
- (BOOL)preloadFile:(NSString *)fileUrl retentionTime:(NSInteger)retentSec;
@end
