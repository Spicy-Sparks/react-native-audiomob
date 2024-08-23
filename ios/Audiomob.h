#import <AudiomobSDK/AudiomobSDK.h>
#import <React/RCTEventEmitter.h>

#ifdef RCT_NEW_ARCH_ENABLED
#import "RNAudiomobSpec.h"

@interface Audiomob : RCTEventEmitter <NativeAudiomobSpec, AdAvailabilityDelegate, AdRequestDelegate, AdPlaybackDelegate>
#else
#import <React/RCTBridgeModule.h>

@interface Audiomob : RCTEventEmitter <RCTBridgeModule, AdAvailabilityDelegate, AdRequestDelegate, AdPlaybackDelegate>
#endif

@property (nonatomic, strong) AudiomobPlugin* audioPlugin;

@end
