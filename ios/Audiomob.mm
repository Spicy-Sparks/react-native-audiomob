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
    
    dispatch_sync(dispatch_get_main_queue(), ^{
        self.audioPlugin = [[AudiomobPlugin alloc] init];
        
        [self.audioPlugin initialiseWithApiKey:apiKey
                                 bundleId:bundleId
                   backgroundModeEnabled:YES];
        
        [self.audioPlugin setAdAvailabilityDelegateWithDelegate:self];
        [self.audioPlugin setAdPlaybackDelegateWithDelegate:self];
        [self.audioPlugin setAdRequestDelegateWithDelegate:self];
        
        [self.audioPlugin getAdAvailabilityWithPlacement:PlacementSkippable];

        resolve(nil);
    });
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
    NSMutableDictionary *args = [[NSMutableDictionary alloc] init];
#if DEBUG
    args[@"available"] = [NSNumber numberWithBool:YES];
#else
    args[@"available"] = [NSNumber numberWithBool:adAvailability.adsAvailable];
#endif
    [self sendEventWithName:kInitCompleted body:args];
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
            if (audioAd.companionBanner != nil) {
                NSString *base64Str = [audioAd.companionBanner.image base64EncodedStringWithOptions:NSDataBase64Encoding64CharacterLineLength];
                args[@"bannerImage"] = [@"data:image/png;base64," stringByAppendingString:base64Str];
            }
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
