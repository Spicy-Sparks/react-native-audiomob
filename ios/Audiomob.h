#import <AudiomobSDK/AudiomobSDK.h>

#ifdef RCT_NEW_ARCH_ENABLED
#import "RNAudiomobSpec.h"

@interface Audiomob : NSObject <NativeAudiomobSpec, AdAvailabilityDelegate, AdPlaybackDelegate>
#else
#import <React/RCTBridgeModule.h>

@interface Audiomob : NSObject <RCTBridgeModule, AdAvailabilityDelegate, AdPlaybackDelegate>
#endif

@property (nonatomic, strong) AudiomobPlugin* audioPlugin;

@end
