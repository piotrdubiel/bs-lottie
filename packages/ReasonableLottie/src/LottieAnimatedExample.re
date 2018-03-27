open BsReactNative;

open BsLottieReactNative;

type state = {progress: AnimatedRe.Value.t};

type action =
  | Noop;

let component = ReasonReact.reducerComponent("LottieAnimatedExample");

let animations = {"lottie1": [%raw {| require('./animations/LottieLogo1.json')|}]};

let make = (_children) => {
  ...component,
  initialState: () => {progress: Animated.Value.create(0.0)},
  didMount: (self) => {
    Animated.CompositeAnimation.start(
      Animated.Timing.animate(
        ~value=self.state.progress,
        ~toValue=`raw(1.0),
        ~easing=Animated.Easing.linear,
        ~duration=10000.0,
        ()
      ),
      ()
    );
    ReasonReact.NoUpdate
  },
  reducer: (action, _state) =>
    switch action {
    | Noop => ReasonReact.NoUpdate
    },
  render: (self) =>
    <LottieView
      loop=true
      source=(Local(animations##lottie1))
      progress=(Animated(self.state.progress))
    />
};