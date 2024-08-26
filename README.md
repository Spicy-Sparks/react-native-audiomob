# react-native-audiomob

Audiomob ads adapter for react-native

## Installation

```sh
npm install react-native-audiomob
```

## Usage


```js
import { useEffect } from 'react';
import { StyleSheet, View, Text } from 'react-native';
import Audiomob from 'react-native-audiomob';

export default function App() {
  useEffect(() => {
    const apiKey = 'xxxxxxx';
    const bundleId = 'xxxxxxx';
    Audiomob.init(apiKey, bundleId).then(() => {
      Audiomob.onInitCompleted.setListener(() => console.log('init completed'))
      Audiomob.onAudioAdLoaded.setListener(() => console.log('loaded'))
      Audiomob.onAudioAdFailedToLoaded.setListener(() => console.log('failed to load'))
      Audiomob.onAudioAdOpened.setListener(() => console.log('open'))
      Audiomob.onAudioAdPaused.setListener(() => console.log('paused'))
      Audiomob.onAudioAdResumed.setListener(() => console.log('resuemd'))
      setTimeout(Audiomob.showAd, 3000);
      setTimeout(async () => {
        Audiomob.pause()
        console.log(await Audiomob.isPaused())
      }, 4000);
      setTimeout(Audiomob.play, 5000)
    });
    return () => {
      Audiomob.onInitCompleted.removeListener()
      Audiomob.onAudioAdLoaded.removeListener()
      Audiomob.onAudioAdFailedToLoaded.removeListener()
      Audiomob.onAudioAdOpened.removeListener()
      Audiomob.onAudioAdPaused.removeListener()
      Audiomob.onAudioAdResumed.removeListener()
    };
  }, []);

  return (
    <View style={styles.container}>
      <Text>AudioMob</Text>
    </View>
  );
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    alignItems: 'center',
    justifyContent: 'center',
  },
  box: {
    width: 60,
    height: 60,
    marginVertical: 20,
  },
});
```


## Contributing

See the [contributing guide](CONTRIBUTING.md) to learn how to contribute to the repository and the development workflow.

## License

MIT

---

Made with [create-react-native-library](https://github.com/callstack/react-native-builder-bob)
