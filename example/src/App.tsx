import { useEffect } from 'react';
import { StyleSheet, View, Text } from 'react-native';
import { init, showAd } from 'react-native-audiomob';

export default function App() {
  useEffect(() => {
    (async () => {
      const apiKey = 'xxxxxxx';
      const bundleId = 'xxxxxxx';
      await init(apiKey, bundleId);
      setTimeout(showAd, 3000);
    })();
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
