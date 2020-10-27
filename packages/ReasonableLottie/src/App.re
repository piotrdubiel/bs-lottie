open ReactNative;

type state = {
  rawProgress: float,
  example: Example.t,
  duration: float,
  isPlaying: bool,
  isInverse: bool,
  useImperative: bool,
  loop: bool,
};

type action =
  | ChangeExample(Example.t)
  | ChangeProgress(float)
  | UpdateProgress(float)
  | ChangeDuration(float)
  | ToggleLoop
  | ToggleInverse
  | ToggleImperative
  | Play
  | Played
  | Stop;

let playIcon = Packager.require("./images/play.png");

let pauseIcon = Packager.require("./images/pause.png");

let loopIcon = Packager.require("./images/loop.png");

let inverseIcon = Packager.require("./images/inverse.png");

let playButtonSize = 60.;

let styles =
  StyleSheet.create(
    Style.{
      "controlsRow":
        style(
          ~flexDirection=`row,
          ~justifyContent=`spaceAround,
          ~alignItems=`center,
          ~paddingVertical=16.->dp,
          (),
        ),
      "playButton":
        style(
          ~width=playButtonSize->dp,
          ~height=playButtonSize->dp,
          ~borderRadius=playButtonSize /. 2.,
          ~backgroundColor="#1d8bf1",
          ~justifyContent=`center,
          ~alignItems=`center,
          (),
        ),
      "playButtonIcon":
        style(~width=16.->dp, ~height=16.->dp, ~tintColor="#fff", ()),
      "controlsIcon":
        style(~width=24.->dp, ~height=24.->dp, ~padding=8.->dp, ()),
      "controlsIconEnabled": style(~tintColor="#1d8bf1", ()),
      "controlsIconDisabled": style(~tintColor="#aaa", ()),
      "lottieView":
        style(
          ~position=`absolute,
          ~top=0.->dp,
          ~bottom=0.->dp,
          ~left=0.->dp,
          ~right=0.->dp,
          (),
        ),
      "lottieViewInverse": style(~backgroundColor="black", ()),
    },
  );

[@react.component]
let app = () => {
  let lottieViewRef = React.useRef(Js.Nullable.null);

  let progress = React.useMemo0(() => Animated.Value.create(0.0));

  let (state, dispatch) =
    React.useReducer(
      (state, action) => {
        switch (action) {
        | ChangeExample(example) => {...state, example}
        | ChangeProgress(rawProgress) =>
          Animated.Value.setValue(progress, rawProgress);
          {...state, rawProgress};
        | UpdateProgress(rawProgress) => {...state, rawProgress}
        | ChangeDuration(duration) => {...state, duration}
        | ToggleLoop => {...state, loop: !state.loop}
        | ToggleInverse => {...state, isInverse: !state.isInverse}
        | ToggleImperative => {...state, useImperative: !state.useImperative}
        | Play => {...state, isPlaying: true}
        | Played => {...state, isPlaying: state.loop}
        | Stop => {...state, isPlaying: false}
        };
      },
      {
        rawProgress: 0.,
        example: Example.examples[0],
        duration: 3000.0,
        isPlaying: false,
        isInverse: false,
        useImperative: false,
        loop: true,
      },
    );

  React.useEffect0(() => {
    let listener =
      Animated.Value.addListener(progress, value =>
        dispatch(UpdateProgress(value##value))
      );
    Some(() => Animated.Value.removeListener(progress, listener));
  });

  let handleToggleImperative = () => {
    dispatch(ToggleImperative);
    dispatch(Stop);
  };

  let handlePlay = () => {
    dispatch(Play);
    if (state.useImperative) {
      switch (lottieViewRef.current->Js.Nullable.toOption) {
      | None => ()
      | Some(lottieView) => lottieView->Lottie.play
      };
    };
  };

  let handleStop = () => {
    dispatch(Stop);
    if (state.useImperative) {
      switch (lottieViewRef.current->Js.Nullable.toOption) {
      | None => ()
      | Some(lottieView) => lottieView->Lottie.pause
      };
    };
  };

  React.useEffect4(
    () =>
      if (!state.useImperative) {
        let animation =
          Animated.timing(
            progress,
            Animated.Value.Timing.(
              config(
                ~toValue=fromRawValue(1.0),
                ~easing=Easing.linear,
                ~duration=state.duration,
                ~useNativeDriver=true,
                (),
              )
            ),
          );

        if (state.isPlaying) {
          Animated.Value.setValue(progress, 0.);
          let animation =
            if (state.loop) {
              Animated.loop(animation);
            } else {
              animation;
            };
          Animated.start(
            animation,
            ~endCallback=
              result =>
                if (result.finished) {
                  dispatch(Played);
                },
            (),
          );
        } else {
          Animated.stop(animation);
        };
        Some(() => Animated.stop(animation));
      } else {
        None;
      },
    (state.isPlaying, state.duration, state.loop, state.useImperative),
  );

  let loopIconStyle =
    Style.arrayOption([|
      Some(styles##controlsIcon),
      state.loop ? Some(styles##controlsIconEnabled) : None,
    |]);

  let lottieInverseStyle =
    state.isInverse ? Some(styles##lottieViewInverse) : None;

  let lottieWidthStyle =
    Belt.Option.map(state.example.width, width =>
      Style.(style(~width=width->dp, ()))
    );

  <View style=Style.(style(~flex=1., ()))>
    <ExamplePicker
      example={state.example}
      examples=Example.examples
      onChange={(name, _) =>
        dispatch(ChangeExample(Example.findByName(name)))
      }
    />
    <View
      style=Style.(
        style(~flex=1., ~alignItems=`center, ~justifyContent=`center, ())
      )>
      <Lottie
        ref={lottieViewRef->Ref.value}
        style=Style.(
          arrayOption([|
            Some(styles##lottieView),
            lottieInverseStyle,
            lottieWidthStyle,
          |])
        )
        loop={state.loop}
        source={state.example.getJson()}
        progress
      />
    </View>
    <View
      style=Style.(
        style(~paddingBottom=20.->dp, ~paddingHorizontal=10.->dp, ())
      )>
      <View style=styles##controlsRow>
        <TouchableOpacity onPress={_ => dispatch(ToggleLoop)}>
          <Image
            style=loopIconStyle
            resizeMode=`contain
            source={Image.Source.fromRequired(loopIcon)}
          />
        </TouchableOpacity>
        <TouchableOpacity
          style=styles##playButton
          onPress={_ => state.isPlaying ? handleStop() : handlePlay()}>
          <Image
            style=styles##playButtonIcon
            resizeMode=`contain
            source={Image.Source.fromRequired(
              state.isPlaying ? pauseIcon : playIcon,
            )}
          />
        </TouchableOpacity>
        <TouchableOpacity onPress={_ => dispatch(ToggleInverse)}>
          <Image
            style=styles##controlsIcon
            resizeMode=`contain
            source={Image.Source.fromRequired(inverseIcon)}
          />
        </TouchableOpacity>
      </View>
      <View
        style=Style.(
          style(
            ~flexDirection=`row,
            ~justifyContent=`spaceBetween,
            ~paddingBottom=10.->dp,
            (),
          )
        )>
        <Text> {React.string("Use Imperative API:")} </Text>
        <View />
        <Switch
          onValueChange={_ => handleToggleImperative()}
          value={state.useImperative}
        />
      </View>
      <View style=Style.(style(~paddingBottom=10.->dp, ()))>
        <View> <Text> {React.string("Progress:")} </Text> </View>
        <ReactNativeSlider
          minimumValue=0.
          maximumValue=1.
          value={state.rawProgress}
          onValueChange={value => {
            dispatch(ChangeProgress(value));
            Animated.Value.setValue(progress, value);
          }}
          disabled={state.useImperative}
          minimumTrackTintColor=?{state.useImperative ? Some("#aaa") : None}
        />
      </View>
      <View style=Style.(style(~paddingBottom=10.->dp, ()))>
        <View>
          <Text>
            {React.string(
               "Duration: "
               ++ (
                 state.duration
                 |> Js.Math.round
                 |> int_of_float
                 |> string_of_int
               )
               ++ "ms",
             )}
          </Text>
        </View>
        <ReactNativeSlider
          minimumValue=50.
          maximumValue=10000.
          value={state.duration}
          onValueChange={value => dispatch(ChangeDuration(value))}
        />
      </View>
    </View>
  </View>;
};

// let make = _children => {
//   ...component,
//   initialState: () => {
//     duration: 3000.0,
//     lottieViewRef: ref(None),
//   },
//   subscriptions: ({state, send}) => [
//     Sub(
//       () =>
//         Animated.Value.addListener(state.progress, value =>
//           send(UpdateProgress(value##value))
//         ),
//       Animated.Value.removeListener(state.progress),
//     ),
//   ],
//   reducer: (action, state) =>
//     switch (action) {
//     | ChangeExample(example) => ReasonReact.Update({...state, example})
//     | ChangeProgress(rawProgress) =>
//       ReasonReact.UpdateWithSideEffects(
//         {...state, rawProgress},
//         ({state}) => Animated.Value.setValue(state.progress, rawProgress),
//       )
//     | UpdateProgress(rawProgress) =>
//       ReasonReact.Update({...state, rawProgress})
//     | ChangeDuration(duration) => ReasonReact.Update({...state, duration})
//     | ToggleLoop => ReasonReact.Update({...state, loop: !state.loop})
//     | ToggleInverse =>
//       ReasonReact.Update({...state, isInverse: !state.isInverse})
//     | ToggleImperative =>
//       ReasonReact.UpdateWithSideEffects(
//         {...state, useImperative: !state.useImperative},
//         ({send}) => send(Stop),
//       )
//     | Play =>
//       ReasonReact.UpdateWithSideEffects(
//         {...state, isPlaying: true},
//         ({state, send}) =>
//           if (state.useImperative) {
//             switch (state.lottieViewRef^) {
//             | None => ()
//             | Some(r) => ReasonReact.refToJsObj(r)##play()
//             };
//           } else {
//             Animated.Value.setValue(state.progress, 0.);
//             Animated.CompositeAnimation.start(
//               Animated.Timing.animate(
//                 ~value=state.progress,
//                 ~toValue=`raw(1.0),
//                 ~easing=Animated.Easing.linear,
//                 ~duration=state.duration,
//                 (),
//               ),
//               ~callback=
//                 result =>
//                   if (result##finished == Js.true_) {
//                     send(Played);
//                   },
//               (),
//             );
//           },
//       )
//     | Played =>
//       ReasonReact.UpdateWithSideEffects(
//         {...state, isPlaying: state.loop},
//         ({state, send}) =>
//           if (state.loop) {
//             send(Play);
//           },
//       )
//     | Stop =>
//       ReasonReact.UpdateWithSideEffects(
//         {...state, isPlaying: false},
//         ({state}) =>
//           Animated.Value.setValue(state.progress, state.rawProgress),
//       )
//     },
//   render: ({state, send, handle}) => {
//     let loopIconStyle =
//       Style.concat([
//         styles##controlsIcon,
//         state.loop ? styles##controlsIconEnabled : Style.style([]),
//       ]);
//     let lottieInverseStyle =
//       Style.(state.isInverse ? styles##lottieViewInverse : style([]));
//     let lottieWidthStyle =
//       Style.(
//         switch (state.example.width) {
//         | Some(value) => style([width(Pt(value))])
//         | None => style([])
//         }
//       );

//   },
// };
