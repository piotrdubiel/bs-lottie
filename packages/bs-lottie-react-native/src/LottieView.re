type asset;

type layer;

/**
 * Serialized animation as generated from After Effects
 */
type animationObject = {
  v: string,
  fr: float,
  ip: int,
  op: float,
  w: int,
  h: int,
  nm: string,
  ddd: int,
  assets: array(asset),
  layers: array(layer)
};

type source =
  | Local(string)
  | AnimationObject(animationObject)
  | Required(BsReactNative.Packager.required)
  | Remote(string);

type sourceJs;

let sourceToJs = (source: source) : sourceJs =>
  switch source {
  | Local(path) => Obj.magic(path)
  | AnimationObject(animation) => Obj.magic(animation)
  | Remote(path) => Obj.magic({"uri": path})
  | Required(require) => Obj.magic(require)
  };

type progress =
  | Animated(BsReactNative.Animated.Value.t)
  | Float(float);

type progressJs;

let progressToJs = (progress: progress) : progressJs =>
  switch progress {
  | Animated(value) => Obj.magic(value)
  | Float(value) => Obj.magic(value)
  };

[@bs.deriving jsConverter]
type resizeMode = [ | `center | `contain | `cover];

[@bs.module] external reactClass : ReasonReact.reactClass = "lottie-react-native";

[@bs.obj]
external makeProps :
  (
    ~source: sourceJs,
    ~progress: progressJs=?,
    ~speed: float=?,
    ~autoPlay: Js.boolean=?,
    ~loop: Js.boolean=?,
    ~style: BsReactNative.Style.t=?,
    ~resizeMode: string=?,
    ~imageAssetsFolder: string=?,
    ~hardwareAccelerationAndroid: Js.boolean=?,
    ~enableMergePathsAndroidForKitKatAndAbove: Js.boolean=?,
    unit
  ) =>
  _ =
  "";

let make =
    (
      ~source: source,
      ~progress=?,
      ~speed=?,
      ~autoPlay=?,
      ~loop=?,
      ~style=?,
      ~resizeMode: option(resizeMode)=?,
      ~imageAssetsFolder=?,
      ~hardwareAccelerationAndroid=?,
      ~enableMergePathsAndroidForKitKatAndAbove=?,
      children
    ) =>
  ReasonReact.wrapJsForReason(
    ~reactClass,
    ~props=
      makeProps(
        ~source=sourceToJs(source),
        ~progress=?Js.Option.map((. progress) => progressToJs(progress), progress),
        ~speed?,
        ~autoPlay=?Utils.optBoolToOptJsBoolean(autoPlay),
        ~loop=?Utils.optBoolToOptJsBoolean(loop),
        ~style?,
        ~resizeMode=?Js.Option.map((. mode) => resizeModeToJs(mode), resizeMode),
        ~imageAssetsFolder?,
        ~hardwareAccelerationAndroid=?Utils.optBoolToOptJsBoolean(hardwareAccelerationAndroid),
        ~enableMergePathsAndroidForKitKatAndAbove=?Utils.optBoolToOptJsBoolean(enableMergePathsAndroidForKitKatAndAbove),
        ()
      ),
    children
  );