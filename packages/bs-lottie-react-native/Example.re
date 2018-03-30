open BsReactNative;

open BsLottieReactNative;

let component = ReasonReact.statelessComponent("Example");

let make = (children) => {
  ...component,
  render: (self) => <LottieView source=(Required(Packager.require("./animation.json"))) />
};