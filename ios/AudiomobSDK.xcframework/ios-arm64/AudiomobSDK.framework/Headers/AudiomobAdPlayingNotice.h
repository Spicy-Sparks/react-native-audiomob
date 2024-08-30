#import <AVFoundation/AVFoundation.h>
#import <UIKit/UIKit.h>
#import "AudiomobCountDown.h"

@protocol AdPlayingNotice
- (void)show;
- (void)hide;
- (void)showSkipButton;
@property (nonatomic, readonly, strong) id <Countdown> _Nonnull countdown;
@end


/// A default UI ad playing notice (shown when no banner image).
@interface AudiomobAdPlayingNotice : UIView <AdPlayingNotice>
@property (nonatomic, weak) IBOutlet UIView * _Null_unspecified contentView;
@property (nonatomic, weak) IBOutlet AudiomobCountdown * _Null_unspecified timerView;
@property (nonatomic, weak) IBOutlet UILabel * _Null_unspecified audioAdLabel;
@property (nonatomic, weak) IBOutlet UIButton * _Null_unspecified skipAdButton;
@property (nonatomic, weak) IBOutlet UIButton * _Null_unspecified infoIconButton;
@property (nonatomic, weak) IBOutlet UIButton * _Null_unspecified reportAdButton;
@property (nonatomic, weak) IBOutlet UIImageView * _Null_unspecified audioImageView;
@property (nonatomic, weak) IBOutlet NSLayoutConstraint * _Null_unspecified timerRatio;
@property (nonatomic, weak) IBOutlet NSLayoutConstraint * _Null_unspecified audioImageLeadingConstraint;
@property (nonatomic, weak) IBOutlet NSLayoutConstraint * _Null_unspecified timerTrailingConstraint;
@property (nonatomic, weak) IBOutlet NSLayoutConstraint * _Null_unspecified timerCenterConstraint;
@property (nonatomic, weak) IBOutlet UIImageView * _Null_unspecified skipAdImage;
@property (nonatomic, strong) IBInspectable UIColor * _Nonnull textColor;
@property (nonatomic) IBInspectable CGFloat timerTextFontSize;
@property (nonatomic) IBInspectable CGFloat timerBorderWidth;
@property (nonatomic, strong) IBInspectable UIColor * _Nonnull timerBackgroundColor;
@property (nonatomic, strong) IBInspectable UIColor * _Nonnull timerBorderFillColor;
@property (nonatomic, strong) IBInspectable UIColor * _Nonnull timerTextColor;
@property (nonatomic) IBInspectable CGFloat heightRatio;
@property (nonatomic) IBInspectable CGFloat widthRatio;
@property (nonatomic, copy) IBInspectable NSString * _Nullable audioAdText;
@property (nonatomic) IBInspectable BOOL audioImage;
@property (nonatomic) IBInspectable CGFloat timerHeight;
@property (nonatomic, strong) IBInspectable UIColor * _Nullable viewBackgroundColor;
- (nonnull instancetype)initWithFrame:(CGRect)frame ;
- (nullable instancetype)initWithCoder:(NSCoder * _Nonnull)coder ;
- (void)show;
@property (nonatomic, readonly, strong) id <Countdown> _Nonnull countdown;
- (void)hide;
- (void)showSkipButton;
- (IBAction)skipAd:(id _Nonnull)sender;
- (IBAction)reportAd:(id _Nonnull)sender;
- (IBAction)infoIconPressed:(id _Nonnull)sender;
@end
