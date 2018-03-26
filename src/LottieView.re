/* declare module "lottie-react-native" {
     import { Animated, StyleProp, ViewStyle } from "react-native";

     /**
      * Serialized animation as generated from After Effects
      */
     interface AnimationObject {
       v: string;
       fr: number;
       ip: number;
       op: number;
       w: number;
       h: number;
       nm: string;
       ddd: number;
       assets: any[];
       layers: any[];
     }

     /**
      * Properties of the AnimatedLottieView component
      */
     interface AnimatedLottieViewProps {
       /**
        * The source of animation. Can be referenced as a local asset by a string, or remotely
        * with an object with a `uri` property, or it can be an actual JS object of an
        * animation, obtained (for example) with something like
        * `require('../path/to/animation.json')`
        */
       source: string | AnimationObject | { uri: string };

       /**
        * A number between 0 and 1, or an `Animated` number between 0 and 1. This number
        * represents the normalized progress of the animation. If you update this prop, the
        * animation will correspondingly update to the frame at that progress value. This
        * prop is not required if you are using the imperative API.
        */
       progress?: number | Animated.Value;

       /**
        * The speed the animation will progress. This only affects the imperative API. The
        * default value is 1.
        */
       speed?: number;

       /**
        * A boolean flag indicating whether or not the animation should loop.
        */
       loop?: boolean;

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

       /**
        * Determines how to resize the animated view when the frame doesn't match the raw image
        * dimensions.
        * Refer to https://facebook.github.io/react-native/docs/image.html#resizemode
        */
       resizeMode?: "cover" | "contain" | "center"
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

[@bs.deriving jsConverter]
type resizeMode = [ | `center | `contain | `cover];

[@bs.module] external reactClass : ReasonReact.reactClass = "lottie-react-native";

[@bs.obj]
external makeProps :
  (
    ~source: sourceJs,
    ~progress: float=?,
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
        ~progress?,
        ~speed?,
        ~autoPlay=?Js.Option.map((. autoPlay) => Js.Boolean.to_js_boolean(autoPlay), autoPlay),
        ~loop=?Js.Option.map((. loop) => Js.Boolean.to_js_boolean(loop), loop),
        ~resizeMode=?Js.Option.map((. mode) => resizeModeToJs(mode), resizeMode),
        ()
      ),
    children
  );