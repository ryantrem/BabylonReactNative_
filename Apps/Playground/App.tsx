/**
 * Generated with the TypeScript template
 * https://github.com/react-native-community/react-native-template-typescript
 *
 * @format
 */

import React, { useState } from 'react';
import { SafeAreaView, StatusBar, Button, View } from 'react-native';

import { EngineView } from 'react-native-babylon';
import { Scene, Vector3, Mesh, ArcRotateCamera, Engine } from '@babylonjs/core';

const App = () => {
  const [toggleView, setToggleView] = useState(false);

  const onEngineViewReady = (engine: Engine) => {
    var scene = new Scene(engine);
    scene.createDefaultCamera(true);
    if (scene.activeCamera != null) {
      (scene.activeCamera as ArcRotateCamera).alpha += Math.PI;
    }
    scene.createDefaultLight(true);

    Mesh.CreateBox("box1", 0.3, scene);

    scene.beforeRender = function () {
      scene.meshes[0].rotate(Vector3.Up(), 0.005 * scene.getAnimationRatio());
    };
  };

  return (
    <>
      <StatusBar barStyle="dark-content" />
      <SafeAreaView style={{flex: 1}}>
        { !toggleView &&
          <EngineView style={{flex: 1}} onViewReady={onEngineViewReady} />
        }
        { toggleView &&
          <View style={{flex: 1}}>
            <EngineView style={{flex: 1}} onViewReady={onEngineViewReady} />
          </View>
        }
        <Button title="Toggle View Instance" onPress={() => { setToggleView(!toggleView) }} />
      </SafeAreaView>
    </>
  );
};

export default App;
