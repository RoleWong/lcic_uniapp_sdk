# lcic_uniapp_sdk
腾讯云实时互动-教育版, 官方 uni-app Native 原生语言 SDK. 供使用 uni-app 开发的 iOS、Android 项目, 快速接入腾讯云实时互动-教育版.

## 开发环境要求

请根据[《uni-app 原生语言插件》](https://nativesupport.dcloud.net.cn/NativePlugin/use/use.html)使用教程, 学习如何在您的 uni-app 项目中引入原生语言插件.

iOS 版本要求: 11+

android API 要求: 21+

## 前提条件

您已[ 注册腾讯云](https://cloud.tencent.com/document/product/378/17985) 账号，并完成 [实名认证](https://cloud.tencent.com/document/product/378/3629) 。

## 操作步骤

### 步骤一：创建新的应用
1. 登录 [实时互动-教育版 控制台](https://console.cloud.tencent.com/lcic)，进入左侧导航栏的**概览**，选择**新建应用**。

2. 若尚未创建应用，则默认进入“创建应用”界面，输入应用名称，例如 TestLCIC。

   ![](https://write-document-release-1258344699.cos.ap-guangzhou.tencentcos.cn/100027812451/ae9d80244d8411f0a6ac525400bf7822.png)


   若您已创建应用，可前往**应用管理**中，选择使用已有应用即可。

   ![](https://write-document-release-1258344699.cos.ap-guangzhou.tencentcos.cn/100027812451/ae85d2544d8411f0a6ac525400bf7822.png)
   

   > **说明：**
   > 
>   - 移动端需要购买旗舰版或企业尊享版后方可接入。若需创建商用应用，可根据业务需求在[ 购买页](https://buy.cloud.tencent.com/lcic) 创建对应版本的应用。
>   - 应用名称只允许下划线、数字或中英文字符。


### 步骤二：获取 SDKAppId 和密钥(SecretKey)
1. 进入**应用管理 > 应用配置**，获取 [SDKAppId](https://console.cloud.tencent.com/lcic/app) 。

2. 进入 [访问管理(CAM)控制台](https://console.cloud.tencent.com/cam/capi) 获取密钥，若无密钥，需要在 API 密钥管理中进行新建，具体可参见 [访问密钥管理](https://cloud.tencent.com/document/product/598/40488) 。


   ![](https://write-document-release-1258344699.cos.ap-guangzhou.tencentcos.cn/100027812451/ae8d68fb4d8411f0b5e7525400e889b2.png)


### 步骤三：导入 SDK
1. 前往, 购买如下两个免费插件, 并选择该插件绑定的项目。


   - [【官方】腾讯云实时音视频SDK](https://ext.dcloud.net.cn/plugin?id=7774)


   -  腾讯云实时互动-教育版

2. 在HBuilderX里找到项目，在manifest的app原生插件配置中勾选模块，如需要填写参数则参考插件作者的文档添加。


### 步骤四：SDK 授权申请

需要您提交 [腾讯云工单](https://console.cloud.tencent.com/workorder/category)，向我们发送 SDK 权限申请。请按以下模板提供对应信息。在信息确认无误的情况下，我们将会在1个工作日完成。

> **注意：**
> 

> 一个旗舰版仅支持授权一个正式包名，请确认无误后发送相关信息。
> 


> **说明：**
> 

> 包名用于 x5 内核以及快直播播放器签名授权，请提供所需授权的正式应用的 App Name、Package Name 和 Bundle ID 信息。
> 

> 
> 

> **问题标题**
> 
> - 实时互动-教育版  Android SDK 授权申请

> **主要内容**
> 
> - 公司名称：xxx 有限公司
> -  个人姓名：
> -  联系方式：
> -  App Name：
> -  Package Name （Android）：
> -  Bundle ID （iOS）：


### 步骤五：初始化 X5 内核

X5 内核相对于系统 WebView，具有兼容性更好，速度更快等优势。Android 实时互动-教育版 SDK 的组件实现依赖于 x5 内核的 WebView。现提供 x5 内核静态集成方式，能提升 x5 内核加载成功率且无需进程重启即可生效。
1. 检查同意隐私政策协议。
   

   > **注意：**
   > 

   > 建议在同意隐私政策协议之后，再调用初始化 X5 内核的方法，以免上架应用市场时未经用户同意，存在收集个人信息的行为。
   > 

2. 初始化 X5 内核。进入课堂前，**必须先判断 X5 内核是否初始化完成。**onViewInitFinished 方法已经回调，初始化不需要重复调用，回调后可记录状态。

   ``` javascript
   const lcicModule = uni.requireNativePlugin('lcic_uniapp_sdk');
   
   lcicModule.initX5Core({
   						licenseKey: this.config.licenseKey
   					},
   					(ret) => {
   						if (ret && ret.code === 0) {
   							// X5 内核初始化成功, 请记录这个事件.
   						} else {
   							// X5 内核初始化失败.
   						}
   					}
   ```   

   > **注意：**
   > 
>   - initX5Core 中的 licenseKey 参数需要通过 [步骤四](https://cloud.tencent.com/document/product/1639/79898#a231f59c-82c1-4604-b82e-200cd7518803) 发送邮件联系我们获取 X5 内核的 licenseKey。
>   - 如果出现x5初始化失败，可及时 [联系我们](https://cloud.tencent.com/online-service?from=sales&source=PRESALE)。


### 步骤六：获取进入课堂所需参数

参数解释
1. 通过 [控制台](https://console.cloud.tencent.com/lcic) 进入**应用管理 > 应用配置**，获取 [SDKAppId](https://console.cloud.tencent.com/lcic/app) ，即为学校编号(schoolId)信息。

2. 通过云 API 接口 [CreateRoom](https://cloud.tencent.com/document/product/1639/80942) 创建课堂，可以获取到课堂号(classid)信息。

3. 通过调用云 API 接口 [RegisterUser](https://cloud.tencent.com/document/product/1639/80935) 注册用户，可以获取到对应的用户 ID(userid)信息。

4. 通过云 API 接口 [LoginUser](https://cloud.tencent.com/document/product/1639/80938) 登录，可以获取到用户鉴权 token 信息。

5. scene、lng、camera、mic、speaker为非必要参数，如果不设置则使用的是默认值。

<table>
<tr>
<td rowspan="1" colSpan="1" >字段</td>

<td rowspan="1" colSpan="1" >类型</td>

<td rowspan="1" colSpan="1" >含义</td>

<td rowspan="1" colSpan="1" >备注</td>

<td rowspan="1" colSpan="1" >必填</td>
</tr>

<tr>
<td rowspan="1" colSpan="1" >schoolId</td>

<td rowspan="1" colSpan="1" >int</td>

<td rowspan="1" colSpan="1" >学校编号</td>

<td rowspan="1" colSpan="1" >通过控制台进入**应用管理 > 应用配置**，获取 [SDKAppId](https://console.cloud.tencent.com/lcic/app)。</td>

<td rowspan="1" colSpan="1" >是</td>
</tr>

<tr>
<td rowspan="1" colSpan="1" >classId</td>

<td rowspan="1" colSpan="1" >long</td>

<td rowspan="1" colSpan="1" >课堂编号</td>

<td rowspan="1" colSpan="1" >通过[ CreateRoom ](https://cloud.tencent.com/document/product/1639/80942)接口创建返回 RoomId 获取。</td>

<td rowspan="1" colSpan="1" >是</td>
</tr>

<tr>
<td rowspan="1" colSpan="1" >userId</td>

<td rowspan="1" colSpan="1" >string</td>

<td rowspan="1" colSpan="1" >用户账号</td>

<td rowspan="1" colSpan="1" >通过[  RegisterUser  ](https://cloud.tencent.com/document/product/1639/80935)接口获取。</td>

<td rowspan="1" colSpan="1" >是</td>
</tr>

<tr>
<td rowspan="1" colSpan="1" >token</td>

<td rowspan="1" colSpan="1" >string</td>

<td rowspan="1" colSpan="1" >后台鉴权参数</td>

<td rowspan="1" colSpan="1" >通过[  LoginUser  ](https://cloud.tencent.com/document/product/1639/80938)接口获取。</td>

<td rowspan="1" colSpan="1" >是</td>
</tr>

<tr>
<td rowspan="1" colSpan="1" >scene</td>

<td rowspan="1" colSpan="1" >string</td>

<td rowspan="1" colSpan="1" >场景名称</td>

<td rowspan="1" colSpan="1" >用于区分不同的定制布局，通过 [SetAppCustomContent](https://cloud.tencent.com/document/api/1639/81422) 接口配置。</td>

<td rowspan="1" colSpan="1" >否</td>
</tr>

<tr>
<td rowspan="1" colSpan="1" >lng</td>

<td rowspan="1" colSpan="1" >string</td>

<td rowspan="1" colSpan="1" >语言参数</td>

<td rowspan="1" colSpan="1" >当前支持中文(简体)、中文(繁体) 、English、韩语、日语、阿拉伯语、越南语。可拼接相应参数，展示对应语种。参数：zh-CN、zh-TW、en-US、ka、ja、ar、vi。<br><br>还支持西班牙语、法语、德语、泰语、马来语、印尼语等多语种，可联系您的腾讯云商务经理或产品经理来了解。</td>

<td rowspan="1" colSpan="1" >否</td>
</tr>

<tr>
<td rowspan="1" colSpan="1" >camera</td>

<td rowspan="1" colSpan="1" >int</td>

<td rowspan="1" colSpan="1" >初始化开启摄像头</td>

<td rowspan="1" colSpan="1" >1为开启摄像头，0为关闭摄像头，默认 1。</td>

<td rowspan="1" colSpan="1" >否</td>
</tr>

<tr>
<td rowspan="1" colSpan="1" >mic</td>

<td rowspan="1" colSpan="1" >int</td>

<td rowspan="1" colSpan="1" >初始化开启麦克风</td>

<td rowspan="1" colSpan="1" >1为开启麦克风，0为关闭麦克风，默认 1。</td>

<td rowspan="1" colSpan="1" >否</td>
</tr>

<tr>
<td rowspan="1" colSpan="1" >speaker</td>

<td rowspan="1" colSpan="1" >int</td>

<td rowspan="1" colSpan="1" >初始化开启扬声器</td>

<td rowspan="1" colSpan="1" >1为开启扬声器，0为关闭扬声器，默认 1。</td>

<td rowspan="1" colSpan="1" >否</td>
</tr>
</table>


### 步骤七：调起组件主页面

只需传递 4 个参数就可调起 LCIC 组件主页面，分别为学校编号、课堂编号、用户账号和 token。

> **说明：**
> 

> `schoolId`同 [SDKAppId](https://console.cloud.tencent.com/lcic/app)。
> 

``` java
const lcicModule = uni.requireNativePlugin('lcic_uniapp_sdk');

lcicModule.joinClass({
						schoolId: schoolId,
						userId: userId,
						token: token,
						classId: classId,
                        // 其他更多可选参数
					},
					(res) => {
						// 进入课堂成功
					}
				);
```

