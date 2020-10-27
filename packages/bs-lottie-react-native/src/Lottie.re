type element;
type ref = ReactNative.Ref.t(element);

[@bs.send] external play: element => unit = "play";

[@bs.send] external reset: element => unit = "reset";

[@bs.send] external pause: element => unit = "pause";

[@bs.send] external resume: element => unit = "pause";

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
  layers: array(layer),
};

type uriSource;

[@bs.obj] external uriSource: (~uri: string) => uriSource;

module Source = {
  type t;

  external fromLocalAsset: string => t = "%identity";
  external fromAnimationObject: animationObject => t = "%identity";
  external fromRequired: ReactNative.Packager.required => t = "%identity";
  external fromUriSource: uriSource => t = "%identity";
};

type progress = ReactNative.Animated.Value.t;

[@react.component] [@bs.module "lottie-react-native"]
external make:
  (
    ~ref: ref=?,
    ~source: Source.t,
    ~progress: progress=?,
    ~speed: float=?,
    ~duration: float=?,
    ~loop: bool=?,
    ~autoPlay: bool=?,
    ~autoSize: bool=?,
    ~style: ReactNative.Style.t=?,
    ~imageAssetsFolder: string=?,
    ~children: React.element=?
  ) =>
  React.element =
  "default";
