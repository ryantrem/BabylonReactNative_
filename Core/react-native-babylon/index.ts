import { NativeModules } from 'react-native';

const { Babylon } = NativeModules;

export default Babylon;

export const TestVal = "test val 2";

export * from './TestView';