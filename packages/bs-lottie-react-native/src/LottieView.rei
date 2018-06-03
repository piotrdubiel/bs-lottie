type asset;

type layer;

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

type progress =
  | Animated(BsReactNative.Animated.Value.t)
  | Float(float);

type resizeMode = [ | `center | `contain | `cover];

let make:
  (
    ~source: source,
    ~progress: progress=?,
    ~speed: float=?,
    ~autoPlay: bool=?,
    ~loop: bool=?,
    ~style: BsReactNative.Style.t=?,
    ~resizeMode: resizeMode=?,
    ~imageAssetsFolder: string=?,
    ~hardwareAccelerationAndroid: bool=?,
    ~enableMergePathsAndroidForKitKatAndAbove: bool=?,
    array(ReasonReact.reactElement)
  ) =>
  ReasonReact.component(ReasonReact.stateless, ReasonReact.noRetainedProps, ReasonReact.actionless);