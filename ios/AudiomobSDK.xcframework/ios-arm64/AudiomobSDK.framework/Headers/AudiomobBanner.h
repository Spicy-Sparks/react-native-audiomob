#if !defined(SWIFT_DEPRECATED)
# define SWIFT_DEPRECATED __attribute__((deprecated))
#endif
#if !defined(SWIFT_DEPRECATED_MSG)
# define SWIFT_DEPRECATED_MSG(...) __attribute__((deprecated(__VA_ARGS__)))
#endif

#import <AVFoundation/AVFoundation.h>
#import <UIKit/UIKit.h>
#import "AudiomobCountDown.h"

NS_ASSUME_NONNULL_BEGIN

/// The size of the companion banner.
/// - Sizes:
///     - mediumRectangle (300x250).
///     - Mobile Leaderboard (320x50).
///     - NoBanner
typedef NS_ENUM(NSInteger, BannerSize) {
  BannerSizeMediumRectangle = 0,
  BannerSizeMobileLeaderboard = 1,
  BannerSizeNoBanner = 2,
};

enum BannerSize : NSInteger;

@protocol Banner
- (void)showWithBannerData:(NSData * _Nonnull)bannerData bannerSize:(enum BannerSize)bannerSize SWIFT_DEPRECATED_MSG("Use our show(bannerSize: BannerSize) instead.");
- (void)showWithBannerSize:(enum BannerSize)bannerSize;
- (void)hide;
- (void)showSkipButton;
- (void)onReportAdPressed;
- (void)onBannerPressed;
@property (nonatomic, readonly, strong) id <Countdown> _Nonnull countdown;
@property (nonatomic, strong, readonly) UIImageView * _Nullable imageview;
@end

@class NSData;

@interface AudiomobBanner : UIView <Banner>
@property (nonatomic, weak) IBOutlet UIView * _Null_unspecified contentView;
@property (nonatomic, weak) IBOutlet AudiomobCountdown * _Null_unspecified timerView;
@property (nonatomic, weak) IBOutlet UIImageView * _Null_unspecified bannerImageView;
@property (nonatomic, weak) IBOutlet UIButton * _Null_unspecified skipAdButton;
@property (nonatomic, weak) IBOutlet UIImageView * _Null_unspecified skipImage;
@property (nonatomic, weak) IBOutlet UIButton * _Null_unspecified clickthroughButton;
@property (nonatomic, weak) IBOutlet UIButton * _Null_unspecified infoIconButton;
@property (nonatomic, weak) IBOutlet UIButton * _Null_unspecified reportAdButton;
@property (nonatomic) IBInspectable CGFloat timerBorderWidth;
@property (nonatomic, strong) IBInspectable UIColor * _Nonnull timerBackgroundColor;
@property (nonatomic, strong) IBInspectable UIColor * _Nonnull timerBorderFillColor;
@property (nonatomic, strong) IBInspectable UIColor * _Nonnull timerTextColor;
@property (nonatomic) IBInspectable CGFloat timerTextFontSize;
@property (nonatomic) IBInspectable CGFloat heightRatio;
@property (nonatomic) IBInspectable CGFloat widthRatio;
@property (nonatomic) IBInspectable CGFloat timerHeight;
- (nonnull instancetype)initWithFrame:(CGRect)frame ;
- (nullable instancetype)initWithCoder:(NSCoder * _Nonnull)coder ;
- (void)showWithBannerData:(NSData * _Nonnull)bannerData bannerSize:(enum BannerSize)bannerSize;
- (void)hide;
- (void)showSkipButton;
- (void)onReportAdPressed;
- (void)onBannerPressed;
@property (nonatomic, readonly, strong) id <Countdown> _Nonnull countdown;
- (IBAction)clickthroughAction:(id _Nonnull)sender;
- (IBAction)skipAd:(id _Nonnull)sender;
- (IBAction)reportAd:(id _Nonnull)sender;
- (IBAction)infoIconPressed:(id _Nonnull)sender;
@end
NS_ASSUME_NONNULL_END
