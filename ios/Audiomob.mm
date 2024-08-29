#import "Audiomob.h"
#import <AudiomobSDK/AudiomobSDK.h>

NSString *const kInitCompleted = @"INIT_COMPLETED";
NSString *const kAudioAdEnded = @"AUDIOAD_ENDED";
NSString *const kAudioAdPaused = @"AUDIOAD_PAUSED";
NSString *const kAudioAdResumed = @"AUDIOAD_RESUMED";
NSString *const kAudioAdOpened = @"AUDIOAD_OPENED";
NSString *const kAudioAdLoaded = @"AUDIOAD_LOADED";
NSString *const kAudioAdFailedToLoad = @"AUDIOAD_FAILED_TO_LOAD";

@implementation Audiomob
RCT_EXPORT_MODULE()

- (NSArray<NSString *> *)supportedEvents {
    return @[
        kInitCompleted,
        kAudioAdEnded,
        kAudioAdPaused,
        kAudioAdResumed,
        kAudioAdOpened,
        kAudioAdLoaded,
        kAudioAdFailedToLoad
    ];
}

RCT_EXPORT_METHOD(init:(NSString *)apiKey
                  bundleId:(NSString *)bundleId
                  resolve:(RCTPromiseResolveBlock)resolve
                  reject:(RCTPromiseRejectBlock)reject)
{
    AVAudioSession *session = [AVAudioSession sharedInstance];
    NSError *error = nil;

    [session setCategory:AVAudioSessionCategoryPlayback
                   mode:AVAudioSessionModeDefault
                options:0
                  error:&error];

    if (error) {
        NSLog(@"Error setting category: %@", error.localizedDescription);
    }

    [session setActive:YES error:&error];

    if (error) {
        NSLog(@"Error activating session: %@", error.localizedDescription);
    }
    
    self.audioPlugin = [[AudiomobPlugin alloc] init];

    [self.audioPlugin initialiseWithApiKey:apiKey
                             bundleId:bundleId
               backgroundModeEnabled:YES];
    
    [self.audioPlugin setAdAvailabilityDelegateWithDelegate:self];
    [self.audioPlugin setAdPlaybackDelegateWithDelegate:self];
    [self.audioPlugin setAdRequestDelegateWithDelegate:self];
    
    [self.audioPlugin getAdAvailabilityWithPlacement:PlacementSkippable];

    resolve(nil);
}

RCT_EXPORT_METHOD(showAd:(RCTPromiseResolveBlock)resolve
                  reject:(RCTPromiseRejectBlock)reject)
{
    [self.audioPlugin requestAndPlayAd];
    resolve(nil);
}

RCT_EXPORT_METHOD(play:(RCTPromiseResolveBlock)resolve
                  reject:(RCTPromiseRejectBlock)reject)
{
    [self.audioPlugin resumePausedAd];
    resolve(nil);
}

RCT_EXPORT_METHOD(pause:(RCTPromiseResolveBlock)resolve
                  reject:(RCTPromiseRejectBlock)reject)
{
    [self.audioPlugin pauseAd];
    resolve(nil);
}

RCT_EXPORT_METHOD(isPaused:(RCTPromiseResolveBlock)resolve
                  reject:(RCTPromiseRejectBlock)reject)
{
    resolve([NSNumber numberWithBool:[self.audioPlugin isAdPaused]]);
}

- (void)onAdAvailabilityRetrievedWithAdAvailability:(AdAvailability*) adAvailability {
#if DEBUG
    [self sendEventWithName:kInitCompleted body:nil];
#else
    if (adAvailability.adsAvailable)
        [self sendEventWithName:kInitCompleted body:nil];
#endif
}

- (void)onAdPlaybackCompletedWithAdPlaybackResult:(enum AdPlaybackResult)adPlaybackResult {
    [self sendEventWithName:kAudioAdEnded body:nil];
}

- (void)onAdPlaybackStartedWithAudioAd:(AudioAd *)audioAd {
    [self sendEventWithName:kAudioAdOpened body:nil];
}

- (void)onAdPausedWithPauseReason:(enum AdPauseReason)pauseReason {
    [self sendEventWithName:kAudioAdPaused body:nil];
}

- (void)onAdResumed {
    [self sendEventWithName:kAudioAdResumed body:nil];
}

- (void)onAdRequestCompletedWithAdRequestResult:(enum AdRequestResult)adRequestResult audioAd:(AudioAd * _Nullable)audioAd {
    if (adRequestResult == AdRequestResultFinished) {
        NSMutableDictionary *args = [[NSMutableDictionary alloc] init];
        if (audioAd != nil) {
            args[@"bannerImage"] = audioAd.companionBanner.image;
            args[@"estimatedCpm"] = @(audioAd.estimatedCpm);
            args[@"estimatedRevenue"] = @(audioAd.estimatedRevenue);
            args[@"duration"] = @(audioAd.duration);
        }
        [self sendEventWithName:kAudioAdLoaded body:args];
    }
    else [self sendEventWithName:kAudioAdFailedToLoad body:nil];
}

- (void)onAdRequestStarted {
    
}

@end
