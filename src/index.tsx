import { NativeModules, Platform } from 'react-native';

const LINKING_ERROR =
  `The package 'react-native-audiomob' doesn't seem to be linked. Make sure: \n\n` +
  Platform.select({ ios: "- You have run 'pod install'\n", default: '' }) +
  '- You rebuilt the app after installing the package\n' +
  '- You are not using Expo Go\n';

const Audiomob = NativeModules.Audiomob
  ? NativeModules.Audiomob
  : new Proxy(
      {},
      {
        get() {
          throw new Error(LINKING_ERROR);
        },
      }
    );

export function init(apiKey: string, bundleId: string): Promise<void> {
  return Audiomob.init(apiKey, bundleId);
}

export function showAd(): void {
  return Audiomob.showAd();
}
