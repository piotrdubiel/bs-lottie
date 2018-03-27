/* 
       /**
        * Style attributes for the view, as expected in a standard `View`:
        * http://facebook.github.io/react-native/releases/0.39/docs/view.html#style
        * CAVEAT: border styling is not supported.
        */
       style?: StyleProp<ViewStyle>;

       /**
        * [Android] Relative folder inside of assets containing image files to be animated.
        * Make sure that the images that bodymovin export are in that folder with their names unchanged (should be img_#).
        * Refer to https://github.com/airbnb/lottie-android#image-support for more details.
        * @platform android
        */
       imageAssetsFolder?: string;

       /**
        * [Android]. Uses hardware acceleration to perform the animation. This should only
        * be used for animations where your width and height are equal to the composition width
        * and height, e.g. you are not scaling the animation.
        * @platform android
        */
       hardwareAccelerationAndroid?: boolean;
     }

     /**
      * View hosting the lottie animation. In order to successfully import this definition in
      * your typescript file, you need to import the view as:
      *
      * `import LottieView = require("lottie-react-native");`
      *
      * Otherwise the compiler will give you issues and won't work.
      */
     class AnimatedLottieView extends React.Component<AnimatedLottieViewProps, {}> {
       play(startFrame?: number, endFrame?: number): void;
       reset(): void;
     }

     export = AnimatedLottieView;
   }
   */
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
  | Remote(string);

type sourceJs;

let sourceToJs = (source: source) : sourceJs =>
  switch source {
  | Local(path) => Obj.magic(path)
  | AnimationObject(animation) => Obj.magic(animation)
  | Remote(path) => Obj.magic({"uri": path})
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
    ~resizeMode: string=?,
    unit
  ) =>
  _ =
  "";

let make =
    (~source: source, ~progress=?, ~speed=?, ~autoPlay=?, ~loop=?, ~resizeMode: option(resizeMode)=?, children) =>
  ReasonReact.wrapJsForReason(
    ~reactClass,
    ~props=
      makeProps(
        ~source=sourceToJs(source),
        ~progress=?Js.Option.map((. progress) => progressToJs(progress), progress),
        ~speed?,
        ~autoPlay=?Js.Option.map((. autoPlay) => Js.Boolean.to_js_boolean(autoPlay), autoPlay),
        ~loop=?Js.Option.map((. loop) => Js.Boolean.to_js_boolean(loop), loop),
        ~resizeMode=?Js.Option.map((. mode) => resizeModeToJs(mode), resizeMode),
        ()
      ),
    children
  );