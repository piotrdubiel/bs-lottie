# bs-lottie-react-native

## [BuckleScript](https://github.com/bucklescript/bucklescript) bindings for [Lottie for React Native](https://github.com/airbnb/lottie-react-native)

[![npm (scoped)](https://img.shields.io/npm/v/bs-lottie-react-native.svg?style=flat-square)](https://www.npmjs.com/package/bs-lottie-react-native)

---

## Example

See `packages/ReasonableLottie`. It's the original lottie-react-native example recreated in ReasonML.

### TL;DR

```reason
open BsReactNative;

open BsLottieReactNative;

let component = ReasonReact.statelessComponent("Example");

let make = (children) => {
  ...component,
  render: (self) => <LottieView source=(Required(Packager.require("./animation.json"))) />
};
```

## Installation

1. setup your React Native project according to http://airbnb.io/lottie/react-native/react-native.html
1. install this bindings
        
        $ yarn add bs-lottie-react-native bs-react-native reason-react
1.  add `bs-lottie-react-native` (and "bs-react-native", "reason-react" if they arent't there yet) to `bs-dependencies` in your `bsconfig.json`

        {
        ...
        "bs-dependencies": ["bs-react-native", "reason-react", "bs-lottie-react-native"]
        }
