#if !defined(SWIFT_DEPRECATED)
# define SWIFT_DEPRECATED __attribute__((deprecated))
#endif
#if !defined(SWIFT_DEPRECATED_MSG)
# define SWIFT_DEPRECATED_MSG(...) __attribute__((deprecated(__VA_ARGS__)))
#endif

NS_ASSUME_NONNULL_BEGIN
#pragma clang diagnostic ignored "-Wobjc-protocol-method-implementation"

@class NSString;


typedef NS_ENUM(NSInteger, Placement) {
  PlacementRewarded = 0,
  PlacementSkippable = 1,
};

enum Placement : NSInteger;

/// Audiomob’s Public API for developers to interact with the SDK.
@interface AudiomobPlugin : NSObject
- (nonnull instancetype)init ;

/// Send Advertising ID from users who’ve consented to tracking.
@property (nonatomic) BOOL sendAdvertisingId;

/// Send consent strings set by a Consent Management Platform or in NSUserDefaults.
@property (nonatomic) BOOL sendConsentStrings;

/// Send IDFA  from users who’ve consented to tracking.
@property (nonatomic) BOOL sendIdfvAsAFallback;

/// Do not send any device identifiers from non-consented users.
@property (nonatomic) BOOL doNotSendAnyDeviceIdsForNonConsentedUsers;

/// Only send contextual signals.
@property (nonatomic) BOOL onlySendContextualSignals;

/// True if the silent mode has been enabled.
@property (nonatomic, readonly) BOOL silentModeIsEnabled;

/// The longest audio ad duration that will be returned by the server (in seconds).
@property (nonatomic) NSInteger maxDuration;

// MARK: Public APIs
/// Initialises the plugin and creates a session
/// - parameters:
///     - APKKey: created on dashboard
///     - BundleID: developer bundle Id
///     - backgroundModeEnabled: A boolean value indicating whether background mode should be enabled or not.
///     - CompletionHandler: invoked on completion     
- (void)initialiseWithApiKey:(NSString * _Nonnull)apiKey bundleId:(NSString * _Nonnull)bundleId backgroundModeEnabled:(BOOL)backgroundModeEnabled completionHandler:(void (^ _Nullable)(BOOL))completionHandler;

/// Initialises the plugin and creates a session
/// - parameters:
///     - APKKey: created on dashboard
///     - BundleID: developer bundle Id
- (void)initialiseWithApiKey:(NSString * _Nonnull)apiKey bundleId:(NSString * _Nonnull)bundleId;

/// Initialises the plugin and creates a session
/// - parameters:
///     - APKKey: created on dashboard
///     - BundleID: developer bundle Id
///     - backgroundModeEnabled: A boolean value indicating whether background mode should be enabled or not.
- (void)initialiseWithApiKey:(NSString * _Nonnull)apiKey bundleId:(NSString * _Nonnull)bundleId backgroundModeEnabled:(BOOL)backgroundModeEnabled;

// MARK: Public APIs
/// Initialises the plugin.
/// - parameters:
///     - APKKey: created on dashboard
///     - BundleID: developer bundle Id
///     - CompletionHandler: invoked on completion
- (void)initialiseWithApiKey:(NSString * _Nonnull)apiKey bundleId:(NSString * _Nonnull)bundleId completionHandler:(void (^ _Nullable)(BOOL))completionHandler;

/// Requests an audio ad and begins the ad playback when it’s downloaded.
/// - parameters:
///   - unmutePrompt: The unmute prompt is shown to the player when the audio is low or the phone is on mute..
///   - adPlayingNotice: The AdPlayingNotice shown to the user when the image banner is disabled or there is no banner image..
///   - placement: Placement of the ad.
///   - banner: The image banner shown to the user when the ad has a companion image..
///   - bannerSize: Size of the banner.
- (void)requestAndPlayAdWithUnmutePrompt:(id <UnmutePrompt> _Nullable)unmutePrompt adPlayingNotice:(id <AdPlayingNotice> _Nullable)adPlayingNotice placement:(enum Placement)placement banner:(id <Banner> _Nullable)banner bannerSize:(enum BannerSize)bannerSize;

/// Requests a background audio ad and begins the ad playback when it’s downloaded.
- (void)requestAndPlayAd;

/// Request to increase the volume threshould when customizing unmute prompt.
- (void)onRaiseVolumePressed;

/// Stops the audio ad playback.
- (void)stopAd;

/// Skips the ad if the ad is skippable and 5 seconds of playback has been completed.
- (void)skipAd;

/// Use this method to get the geo availability information (user country, fill likelihood and estimated revenue).
- (void)getAdAvailability SWIFT_DEPRECATED_MSG("Use getAdAvailability(placement) instead.");

/// Use this method to get the geo availability information (user country, fill likelihood and estimated revenue) for a specified placement.
- (void)getAdAvailabilityWithPlacement:(enum Placement)placement;


/// Register your AdRequestDelegate to get notified about any changes ad request.
///
/// Use the methods of this protocol to manage the following features:
///  - Ad is requested
///  - Ad request completed
/// - Parameters:
///   - delegate: AdRequestDelegate
- (void)setAdRequestDelegateWithDelegate:(id <AdRequestDelegate> _Nonnull)delegate;


/// Register your AdPlaybackDelegate to get notified about any changes ad request.
///
/// Use the methods of this protocol to manage the following features:
///  - Ad begins to play
///  - Ad is palyed, with the playback result and details about the ad
/// - Parameters:
///   - delegate: AdPlaybackDelegate
- (void)setAdPlaybackDelegateWithDelegate:(id <AdPlaybackDelegate> _Nonnull)delegate;
/// Register your AdAvailabilityDelegate to get notified about AdAvailabiltiy Information.
/// \param delegate AdAvailabilityDelegate
///
- (void)setAdAvailabilityDelegateWithDelegate:(id <AdAvailabilityDelegate> _Nonnull)delegate;

/// Pause current playing audio Ad.
- (void)pauseAd;

/// - Returns: True if the ad is paused for any reason.
- (BOOL)isAdPaused ;

/// Pause current paused audio Ad.
- (void)resumePausedAd;

/// Set custom user information to be sent in the ad request.
/// - Parameters:
///   - type: String
///   - id: String
- (void)setCustomUserWithType:(NSString * _Nonnull)type id:(NSString * _Nonnull)id;

/// setting true, the server will return test ads even if live ads are enabled on the dashboard.
- (void)setForceTestAdsWithValue:(BOOL)value;

/// Setting value true, the SDK will try to get the location of the user
- (void)setSendGeoLocationWithValue:(BOOL)value;

/// - Returns: True if an ad has begun playing and has not yet finished
- (BOOL)hasAdBegunPlaying;

/// Opens the browser to an ad report form that the user can fill in if they find the currently playing ad inappropriate, irrelevant or repetitive.
- (void)reportAd;

- (void)onBannerPressed;

/// - Returns: The time remaining for the current ad playback
- (float)getTimeRemaining ;

/// - Returns: True if the phone volume is above the minimum required volume to request an audio ad of the given placement.
- (BOOL)deviceVolumeAboveThresholdWithPlacement:(enum Placement)placement ;

/// - Returns: True if the phone volume is above the minimum required volume to request an audio ad of the given placement and the device is not in silent mode.
- (BOOL)deviceVolumeIsAudibleWithPlacement:(enum Placement)placement ;

/// - Returns: Information about the audio ad that is currently playing.
-(AudioAd *) getPlayingAd;

@end

@implementation AudiomobPlugin (Convenience)

- (void)initialiseWithApiKey:(NSString * _Nonnull)apiKey bundleId:(NSString * _Nonnull)bundleId {
    [self initialiseWithApiKey:apiKey bundleId:bundleId completionHandler:nil];
}

- (void)initialiseWithApiKey:(NSString * _Nonnull)apiKey bundleId:(NSString * _Nonnull)bundleId backgroundModeEnabled:(BOOL)backgroundModeEnabled {
    [self initialiseWithApiKey:apiKey bundleId:bundleId backgroundModeEnabled: backgroundModeEnabled completionHandler:nil];
}

@end

@protocol CompanionBanner
@property (nonatomic) enum BannerSize bannerSize;
@property (nonatomic, copy) NSData * _Nonnull image;
@property (nonatomic) BOOL backupBanner;
@end


NS_ASSUME_NONNULL_END
