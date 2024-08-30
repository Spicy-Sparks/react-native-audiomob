#import <AVFoundation/AVFoundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

/// - The reason for the unmute prompt to show.
///     - phoneMuted:  The phone volume was lowered by the user.
///     - phoneVolumeLowered:  mute switch was turned on.
typedef NS_ENUM(NSInteger, UnmutePromptShowReason) {
  UnmutePromptShowReasonPhoneMuted = 0,
  UnmutePromptShowReasonPhoneVolumeLowered = 1,
};

enum UnmutePromptShowReason : NSInteger;

@protocol UnmutePrompt;

/// Base-class for an AudioMob UI unmute prompt.
@protocol UnmutePrompt
- (void)showWithUnmutePromptReason:(enum UnmutePromptShowReason)unmutePromptReason showStopButton:(BOOL)showStopButton;
- (void)hide;
@end

@class UIStackView;

/// Audiomob default unmute prompt.
@interface AudiomobUnmutePrompt : UIView <UnmutePrompt>
@property (nonatomic, weak) IBOutlet UIView * _Null_unspecified contentView;
@property (nonatomic, weak) IBOutlet UILabel * _Null_unspecified descriptionLabel;
@property (nonatomic, weak) IBOutlet UIStackView * _Null_unspecified buttonsStackView;
@property (nonatomic, weak) IBOutlet UIButton * _Null_unspecified raiseVolume;
@property (nonatomic, weak) IBOutlet NSLayoutConstraint * _Null_unspecified textBottomConstraint;
@property (nonatomic, weak) IBOutlet UIButton * _Null_unspecified stopAd;
@property (nonatomic, weak) IBOutlet NSLayoutConstraint * _Null_unspecified topConstraint;
@property (nonatomic, weak) IBOutlet NSLayoutConstraint * _Null_unspecified bottomConstraint;
@property (nonatomic, weak) IBOutlet NSLayoutConstraint * _Null_unspecified labelBottomConstraint;
- (IBAction)raiseVolumeAction:(id _Nonnull)sender;
- (IBAction)stopAdAction:(id _Nonnull)sender;
- (nonnull instancetype)initWithFrame:(CGRect)frame ;
- (nullable instancetype)initWithCoder:(NSCoder * _Nonnull)coder ;
- (void)hide;
- (void)showWithUnmutePromptReason:(enum UnmutePromptShowReason)unmutePromptReason showStopButton:(BOOL)showStopButton;
@property (nonatomic, strong) IBInspectable UIColor * _Nullable unmutePromptBackgroundColor;
@property (nonatomic, strong) IBInspectable UIColor * _Nullable unmutePromptButtonColor;
@property (nonatomic) IBInspectable CGFloat alignment;
@property (nonatomic, copy) IBInspectable NSString * _Nullable unmutePromptButtonTitle;
@property (nonatomic, copy) IBInspectable NSString * _Nullable unmutePromptRaiseVolumeDescriptionTitle;
@property (nonatomic, copy) IBInspectable NSString * _Nullable unmutePromptMuteDescriptionTitle;
@property (nonatomic, strong) IBInspectable UIColor * _Nullable unmutePromptFontColor;
@property (nonatomic) IBInspectable CGFloat fontSize;
@end

NS_ASSUME_NONNULL_END
