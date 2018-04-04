open BsReactNative;

open BsLottieReactNative;

type state = {
  progress: AnimatedRe.Value.t,
  rawProgress: float,
  example: Example.t,
  duration: float,
  isPlaying: bool,
  isInverse: bool,
  useImperative: bool,
  loop: bool,
  lottieViewRef: ref(option(ReasonReact.reactRef))
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

let component = ReasonReact.reducerComponent("LottieAnimatedExample");

let playIcon = Packager.require("./images/play.png");

let pauseIcon = Packager.require("./images/pause.png");

let loopIcon = Packager.require("./images/loop.png");

let inverseIcon = Packager.require("./images/inverse.png");

let playButtonSize = 60.;

let s = ReasonReact.stringToElement;

let styles =
  StyleSheet.create(
    Style.(
      {
        "controlsRow":
          style([
            flexDirection(Row),
            justifyContent(SpaceAround),
            alignItems(Center),
            paddingVertical(Pt(16.))
          ]),
        "playButton":
          style([
            width(Pt(playButtonSize)),
            height(Pt(playButtonSize)),
            borderRadius(playButtonSize /. 2.),
            backgroundColor("#1d8bf1"),
            justifyContent(Center),
            alignItems(Center)
          ]),
        "playButtonIcon": style([width(Pt(16.)), height(Pt(16.)), tintColor("#fff")]),
        "controlsIcon": style([width(Pt(24.)), height(Pt(24.)), padding(Pt(8.))]),
        "controlsIconEnabled": style([tintColor("#1d8bf1")]),
        "controlsIconDisabled": style([tintColor("#aaa")]),
        "lottieView":
          style([position(Absolute), top(Pt(0.)), bottom(Pt(0.)), left(Pt(0.)), right(Pt(0.))]),
        "lottieViewInverse": style([backgroundColor("black")])
      }
    )
  );

let setLottieViewRef = (theRef, {ReasonReact.state}) =>
  state.lottieViewRef := Js.Nullable.toOption(theRef);

let make = (_children) => {
  ...component,
  initialState: () => {
    progress: Animated.Value.create(0.),
    rawProgress: 0.,
    example: Example.examples[0],
    duration: 3000.0,
    isPlaying: false,
    isInverse: false,
    useImperative: false,
    loop: true,
    lottieViewRef: ref(None)
  },
  subscriptions: ({state, send}) => [
    Sub(
      () =>
        Animated.Value.addListener(state.progress, (value) => send(UpdateProgress(value##value))),
      Animated.Value.removeListener(state.progress)
    )
  ],
  reducer: (action, state) =>
    switch action {
    | ChangeExample(example) => ReasonReact.Update({...state, example})
    | ChangeProgress(rawProgress) =>
      ReasonReact.UpdateWithSideEffects(
        {...state, rawProgress},
        (({state}) => Animated.Value.setValue(state.progress, rawProgress))
      )
    | UpdateProgress(rawProgress) => ReasonReact.Update({...state, rawProgress})
    | ChangeDuration(duration) => ReasonReact.Update({...state, duration})
    | ToggleLoop => ReasonReact.Update({...state, loop: ! state.loop})
    | ToggleInverse => ReasonReact.Update({...state, isInverse: ! state.isInverse})
    | ToggleImperative =>
      ReasonReact.UpdateWithSideEffects(
        {...state, useImperative: ! state.useImperative},
        (({send}) => send(Stop))
      )
    | Play =>
      ReasonReact.UpdateWithSideEffects(
        {...state, isPlaying: true},
        (
          ({state, send}) =>
            if (state.useImperative) {
              switch state.lottieViewRef^ {
              | None => ()
              | Some(r) => ReasonReact.refToJsObj(r)##play()
              }
            } else {
              Animated.Value.setValue(state.progress, 0.);
              Animated.CompositeAnimation.start(
                Animated.Timing.animate(
                  ~value=state.progress,
                  ~toValue=`raw(1.0),
                  ~easing=Animated.Easing.linear,
                  ~duration=state.duration,
                  ()
                ),
                ~callback=
                  (result) =>
                    if (result##finished == Js.true_) {
                      send(Played)
                    },
                ()
              )
            }
        )
      )
    | Played =>
      ReasonReact.UpdateWithSideEffects(
        {...state, isPlaying: state.loop},
        (
          ({state, send}) =>
            if (state.loop) {
              send(Play)
            }
        )
      )
    | Stop =>
      ReasonReact.UpdateWithSideEffects(
        {...state, isPlaying: false},
        (({state}) => Animated.Value.setValue(state.progress, state.rawProgress))
      )
    },
  render: ({state, send, handle}) => {
    let loopIconStyle =
      Style.concat([
        styles##controlsIcon,
        state.loop ? styles##controlsIconEnabled : Style.style([])
      ]);
    let lottieInverseStyle = Style.(state.isInverse ? styles##lottieViewInverse : style([]));
    let lottieWidthStyle =
      Style.(
        switch state.example.width {
        | Some(value) => style([width(Pt(value))])
        | None => style([])
        }
      );
    <View style=Style.(style([flex(1.)]))>
      <ExamplePicker
        example=state.example
        examples=Example.examples
        onChange=((name) => send(ChangeExample(Example.findByName(name))))
      />
      <View style=Style.(style([flex(1.), alignItems(Center), justifyContent(Center)]))>
        <LottieView
          ref=(handle(setLottieViewRef))
          style=Style.(flatten([|styles##lottieView, lottieInverseStyle, lottieWidthStyle|]))
          loop=state.loop
          source=(state.example.getJson())
          progress=(Animated(state.progress))
          enableMergePathsAndroidForKitKatAndAbove=true
        />
      </View>
      <View style=Style.(style([paddingBottom(Pt(20.)), paddingHorizontal(Pt(10.))]))>
        <View style=styles##controlsRow>
          <TouchableOpacity onPress=(() => send(ToggleLoop))>
            <Image style=loopIconStyle resizeMode=`contain source=(Required(loopIcon)) />
          </TouchableOpacity>
          <TouchableOpacity
            style=styles##playButton onPress=(() => state.isPlaying ? send(Stop) : send(Play))>
            <Image
              style=styles##playButtonIcon
              resizeMode=`contain
              source=(Required(state.isPlaying ? pauseIcon : playIcon))
            />
          </TouchableOpacity>
          <TouchableOpacity onPress=(() => send(ToggleInverse))>
            <Image style=styles##controlsIcon resizeMode=`contain source=(Required(inverseIcon)) />
          </TouchableOpacity>
        </View>
        <View
          style=Style.(
                  style([flexDirection(Row), justifyContent(SpaceBetween), paddingBottom(Pt(10.))])
                )>
          <Text> (s("Use Imperative API:")) </Text>
          <View />
          <Switch onValueChange=((_val) => send(ToggleImperative)) value=state.useImperative />
        </View>
        <View style=Style.(style([paddingBottom(Pt(10.))]))>
          <View> <Text> (s("Progress:")) </Text> </View>
          <Slider
            minimumValue=0.
            maximumValue=1.
            value=state.rawProgress
            onValueChange=((value) => send(ChangeProgress(value)))
            disabled=state.useImperative
          />
        </View>
        <View style=Style.(style([paddingBottom(Pt(10.))]))>
          <View>
            <Text>
              (
                s(
                  "Duration: "
                  ++ (state.duration |> Js.Math.round |> int_of_float |> string_of_int)
                  ++ "ms"
                )
              )
            </Text>
          </View>
          <Slider
            minimumValue=50.
            maximumValue=10000.
            value=state.duration
            onValueChange=((value) => send(ChangeDuration(value)))
            disabled=state.useImperative
          />
        </View>
      </View>
    </View>
  }
};