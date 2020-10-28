# bs-lottie-react-native

## [BuckleScript](https://github.com/bucklescript/bucklescript) bindings for [Lottie for React Native](https://github.com/airbnb/lottie-react-native)

[![npm (scoped)](https://img.shields.io/npm/v/bs-lottie-react-native.svg?style=flat-square)](https://www.npmjs.com/package/bs-lottie-react-native)

---

## Example

See `packages/ReasonableLottie`. It's the original lottie-react-native example recreated in ReasonML.

### TL;DR

```reason
open ReactNative;

[@react.component]
let make = () => {
  render: () => <Lottie source=(Required(Packager.require("./animation.json"))) />
};
```

## Installation

Setup your React Native project according to [http://airbnb.io/lottie/react-native/react-native.html](http://airbnb.io/lottie/react-native/react-native.html)

Install this bindings with its peer dependencies

```bash
yarn add bs-lottie-react-native bs-react-native reason-react
```

Add `bs-lottie-react-native` (and "bs-react-native", "reason-react" if they arent't there yet) to `bs-dependencies` in your `bsconfig.json`

```json
{
  "bs-dependencies": ["bs-react-native", "reason-react", "bs-lottie-react-native"]
}
```
