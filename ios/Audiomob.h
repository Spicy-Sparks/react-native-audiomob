
#ifdef RCT_NEW_ARCH_ENABLED
#import "RNAudiomobSpec.h"

@interface Audiomob : NSObject <NativeAudiomobSpec>
#else
#import <React/RCTBridgeModule.h>

@interface Audiomob : NSObject <RCTBridgeModule>
#endif

@end
