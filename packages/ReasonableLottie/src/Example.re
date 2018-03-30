open BsLottieReactNative;

open BsReactNative;

type t = {
  name: string,
  getJson: unit => LottieView.source,
  width: option(float)
};

let makeExample = (~width=?, name, getJson) : t => {name, getJson, width};

let examples = [|
  makeExample(
    "Hamburger Arrow",
    () => Required(Packager.require("./animations/HamburgerArrow.json"))
  ),
  makeExample(
    "Hamburger Arrow (200 px)",
    () => Required(Packager.require("./animations/HamburgerArrow.json")),
    ~width=200.
  ),
  makeExample(
    "Line Animation",
    () => Required(Packager.require("./animations/LineAnimation.json"))
  ),
  makeExample("Lottie Logo 1", () => Required(Packager.require("./animations/LottieLogo1.json"))),
  makeExample("Lottie Logo 2", () => Required(Packager.require("./animations/LottieLogo2.json"))),
  makeExample(
    "Lottie Walkthrough",
    () => Required(Packager.require("./animations/LottieWalkthrough.json"))
  ),
  makeExample("Pin Jump", () => Required(Packager.require("./animations/PinJump.json"))),
  makeExample("Twitter Heart", () => Required(Packager.require("./animations/TwitterHeart.json"))),
  makeExample("Watermelon", () => Required(Packager.require("./animations/Watermelon.json"))),
  makeExample(
    "Motion Corpse",
    () => Required(Packager.require("./animations/MotionCorpse-Jrcanest.json"))
  )
|];

let findByName = (name) => List.find((example) => example.name == name, Array.to_list(examples));