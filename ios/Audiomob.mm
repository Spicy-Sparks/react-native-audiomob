#import "Audiomob.h"
#import <AudiomobSDK/AudiomobSDK.h>

@implementation Audiomob
RCT_EXPORT_MODULE()

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

    resolve(nil);
}

RCT_EXPORT_METHOD(showAd:(RCTPromiseResolveBlock)resolve
                  reject:(RCTPromiseRejectBlock)reject)
{
    [self.audioPlugin getAdAvailabilityWithPlacement:(enum Placement)PlacementRewarded];
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
    [self.audioPlugin requestAndPlayAd];
#else
    if (adAvailability.adsAvailable)
        [self.audioPlugin requestAndPlayAd];
#endif
}

- (void)onAdPlaybackStartedWithAudioAd:(AudioAd *)audioAd {
    NSLog(@"OOOOH");
}

- (void)onAdPlaybackCompletedWithAdPlaybackResult:(enum AdPlaybackResult)adPlaybackResult {
    NSLog(@"OOOOH");
}

@end
