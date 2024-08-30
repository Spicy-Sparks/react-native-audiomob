#import <AVFoundation/AVFoundation.h>

NS_ASSUME_NONNULL_BEGIN

///  - AdRequestResult: The result of the ad request.
///     - noAdAvailable: The ad bid was un-successful..
///     - frequencyCapReached: The frequency cap for this session was reached.
///     - failed: The ad failed to download due to an error.
///     - skippableRequestVolumeNotAudible: The skippble ad was not requested as the device volume is not audible.
///     - backgroundModeNotEnabled: the "background mode" is set to "true" when initializing, but it's not configured in the capabilities.
typedef NS_ENUM(NSInteger, AdRequestResult) {
  AdRequestResultFinished = 0,
  AdRequestResultNoAdAvailable = 1,
  AdRequestResultFrequencyCapReached = 2,
  AdRequestResultFailed = 3,
  AdRequestResultSkippableRequestVolumeNotAudible = 4,
  AdRequestResultBackgroundModeNotEnabled = 5,
};
enum AdRequestResult : NSInteger;

///  - AdPlaybackResultEnum: describe the status for different scenarios of audio
///     - finished: If the ad is finished
///     - stopped: If the ad is stopped via the stopAd function
///     - failed: If ad is failed to play
typedef NS_ENUM(NSInteger, AdPlaybackResult) {
  AdPlaybackResultFinished = 0,
  AdPlaybackResultStopped = 1,
  AdPlaybackResultFailed = 2,
  AdPlaybackResultSkipped = 3,
  AdPlaybackResultCanceled = 4,
};
enum AdPlaybackResult : NSInteger;

/// The reason the ad has been paused.
typedef NS_ENUM(NSInteger, AdPauseReason) {
/// The phone volume was lowered by the user.
  AdPauseReasonPhoneVolumeLowered = 0,
/// The iOS device mute switch was turned on.
  AdPauseReasonPhoneMuted = 1,
/// The app is in the background.
  AdPauseReasonAppInBackground = 2,
/// The method AudioMobPlugin.PauseAd() was called.
  AdPauseReasonPauseMethodCalled = 3,
};

@interface AdAvailability : NSObject

/// An estimation of whether or not you will receive ads in this region.
@property (nonatomic) BOOL adsAvailable;

/// The ISO 3166 alpha-2 country code of the region the user is in.
@property (nonatomic, copy) NSString * _Nonnull geo;

/// Estimated revenue for this ad (if an impression is detected).
@property (nonatomic) float estimatedRevenue;

/// Estimated Cost Per Thousand Impressions for this ad (if an impression is detected).
@property (nonatomic) float estimatedCpm;
- (nonnull instancetype)init ;
@end

@protocol CompanionBanner;

/// AudioAd defines properties for representing audio ad information.
@interface AudioAd : NSObject
/// Estimated revenue for this ad (if an impression is detected).
@property (nonatomic) float estimatedRevenue;
/// Estimated Cost Per Thousand Impressions for this ad (if an impression is detected)..
@property (nonatomic) float estimatedCpm;
/// Duration of the audio ad in seconds.
@property (nonatomic) float duration;
/// The unique identifier of the audio ad.
@property (nonatomic, copy) NSString * _Nonnull id;
/// An optional companion banner associated with the audio ad.
@property (nonatomic, strong) id <CompanionBanner> _Nullable companionBanner;
- (nonnull instancetype)init ;
@end


/**
 1. OnAdRequestStarted: Invoked when an ad is requested by the game.
 2.  OnAdRequestCompleted : Invoked when the ad request completes, with the request result and details about the ad.
 */
@protocol AdRequestDelegate
@optional
- (void)onAdRequestStarted;
- (void)onAdRequestCompletedWithAdRequestResult:(enum AdRequestResult)adRequestResult audioAd:(AudioAd * _Nullable)audioAd;
@end

/**
 1. OnAdPlaybackStarted:Invoked when the ad begins to play, with details about the ad.
 2. OnAdPlaybackCompleted:Invoked when the ad completes playing, with the playback result and details about the ad.
 3. OnAdPaused: Invoked when the ad is paused for any reason with the pause reason enum.
 4.  onAdResumed: nvoked when the ad is resumed
 */
@protocol AdPlaybackDelegate
@optional
- (void)onAdPlaybackStartedWithAudioAd:(AudioAd * _Nonnull)audioAd;
- (void)onAdPlaybackCompletedWithAdPlaybackResult:(enum AdPlaybackResult)adPlaybackResult;
- (void)onAdPausedWithPauseReason:(enum AdPauseReason)pauseReason;
- (void)onAdResumed;
@end

/**
 onAdAvailabilityRetrievedWithAdAvailability: Invoked when the geo availability information is available (user country, fill likelihood and estimated revenue).
 */
@protocol AdAvailabilityDelegate
@optional
- (void)onAdAvailabilityRetrievedWithAdAvailability:(AdAvailability * _Nonnull)adAvailability;
@end

NS_ASSUME_NONNULL_END
