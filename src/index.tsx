import { NativeEventEmitter, NativeModules, Platform } from 'react-native';

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

const eventEmitter = new NativeEventEmitter(Audiomob);

const ON_INIT_COMPLETED = 'INIT_COMPLETED';
const ON_AUDIOAD_ENDED = 'AUDIOAD_ENDED';
const ON_AUDIOAD_PAUSED = 'AUDIOAD_PAUSED';
const ON_AUDIOAD_RESUMED = 'AUDIOAD_RESUMED';
const ON_AUDIOAD_OPENED = 'AUDIOAD_OPENED';
const ON_AUDIOAD_LOADED = 'AUDIOAD_LOADED';
const ON_AUDIOAD_FAILED_TO_LOAD = 'AUDIOAD_FAILED_TO_LOAD';

const init = (apiKey: string, bundleId: string): Promise<void> => {
  return Audiomob.init(apiKey, bundleId);
};

const showAd = () => {
  return Audiomob.showAd();
};

const pause = () => {
  return Audiomob.pause();
};

const play = () => {
  return Audiomob.play();
};

const isPaused = (): Promise<boolean> => {
  return Audiomob.isPaused;
};

const onInitCompleted = {
  setListener: (listener: (data: { available: boolean }) => void): void => {
    eventEmitter.removeAllListeners(ON_INIT_COMPLETED);
    eventEmitter.addListener(ON_INIT_COMPLETED, listener);
  },
  removeListener: () => eventEmitter.removeAllListeners(ON_INIT_COMPLETED),
};

const onAudioAdEnded = {
  setListener: (listener: () => void) => {
    eventEmitter.removeAllListeners(ON_AUDIOAD_ENDED);
    eventEmitter.addListener(ON_AUDIOAD_ENDED, listener);
  },
  removeListener: () => eventEmitter.removeAllListeners(ON_AUDIOAD_ENDED),
};

const onAudioAdPaused = {
  setListener: (listener: () => void) => {
    eventEmitter.removeAllListeners(ON_AUDIOAD_PAUSED);
    eventEmitter.addListener(ON_AUDIOAD_PAUSED, listener);
  },
  removeListener: () => eventEmitter.removeAllListeners(ON_AUDIOAD_PAUSED),
};

const onAudioAdResumed = {
  setListener: (listener: () => void) => {
    eventEmitter.removeAllListeners(ON_AUDIOAD_RESUMED);
    eventEmitter.addListener(ON_AUDIOAD_RESUMED, listener);
  },
  removeListener: () => eventEmitter.removeAllListeners(ON_AUDIOAD_RESUMED),
};

const onAudioAdOpened = {
  setListener: (listener: () => void) => {
    eventEmitter.removeAllListeners(ON_AUDIOAD_OPENED);
    eventEmitter.addListener(ON_AUDIOAD_OPENED, listener);
  },
  removeListener: () => eventEmitter.removeAllListeners(ON_AUDIOAD_OPENED),
};

const onAudioAdLoaded = {
  setListener: (listener: () => void) => {
    eventEmitter.removeAllListeners(ON_AUDIOAD_LOADED);
    eventEmitter.addListener(ON_AUDIOAD_LOADED, listener);
  },
  removeListener: () => eventEmitter.removeAllListeners(ON_AUDIOAD_LOADED),
};

const onAudioAdFailedToLoaded = {
  setListener: (listener: () => void) => {
    eventEmitter.removeAllListeners(ON_AUDIOAD_FAILED_TO_LOAD);
    eventEmitter.addListener(ON_AUDIOAD_FAILED_TO_LOAD, listener);
  },
  removeListener: () => eventEmitter.removeAllListeners(ON_AUDIOAD_FAILED_TO_LOAD),
};

export default {
  init,
  showAd,
  pause,
  play,
  isPaused,
  onInitCompleted,
  onAudioAdEnded,
  onAudioAdPaused,
  onAudioAdResumed,
  onAudioAdOpened,
  onAudioAdLoaded,
  onAudioAdFailedToLoaded
};