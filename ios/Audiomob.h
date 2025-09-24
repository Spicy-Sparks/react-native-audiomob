#import <AudiomobSDK/AudiomobSDK.h>
#import <React/RCTEventEmitter.h>
#import <React/RCTBridgeModule.h>

@interface Audiomob : RCTEventEmitter <RCTBridgeModule, AdAvailabilityDelegate, AdRequestDelegate, AdPlaybackDelegate>

@property (nonatomic, strong) AudiomobPlugin* audioPlugin;

@end
