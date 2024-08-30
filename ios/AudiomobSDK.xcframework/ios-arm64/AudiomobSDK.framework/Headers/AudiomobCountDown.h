#import <AVFoundation/AVFoundation.h>
#import <UIKit/UIKit.h>

NS_ASSUME_NONNULL_BEGIN

@protocol Countdown
@property (nonatomic, readonly) double refreshRate;
- (void)show;
- (void)hide;
- (void)updateCountdownWithTimeRemaining:(float)timeRemaining percentageRemaining:(float)percentageRemaining;
@end

@class CircleProgressBarView;
@class AudiomobCountdown;
@protocol Countdown;

@interface AudiomobCountdown : UIView <Countdown>
@property (nonatomic, weak) IBOutlet UIView * _Null_unspecified contentView;
@property (nonatomic, weak) IBOutlet CircleProgressBarView * _Null_unspecified circleProgressView;
@property (nonatomic, weak) IBOutlet UILabel * _Null_unspecified timerValueLabel;
- (nonnull instancetype)initWithFrame:(CGRect)frame ;
- (nullable instancetype)initWithCoder:(NSCoder * _Nonnull)coder ;
- (void)hide;
- (void)show;
- (void)updateCountdownWithTimeRemaining:(float)timeRemaining percentageRemaining:(float)percentageRemaining;
@property (nonatomic, readonly) double refreshRate;
- (void)setTimeLeftWithCounter:(float)counter percentageRemaining:(float)percentageRemaining;
@end

NS_ASSUME_NONNULL_END
