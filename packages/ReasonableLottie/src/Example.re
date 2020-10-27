open ReactNative;
open Lottie;

type t = {
  name: string,
  getJson: unit => Source.t,
  width: option(float),
};

let makeExample = (~width=?, name, getJson): t => {name, getJson, width};

let examples = [|
  makeExample("Hamburger Arrow", () =>
    Source.fromRequired(Packager.require("./animations/HamburgerArrow.json"))
  ),
  makeExample(
    "Hamburger Arrow (200 px)",
    () =>
      Source.fromRequired(
        Packager.require("./animations/HamburgerArrow.json"),
      ),
    ~width=200.,
  ),
  makeExample("Line Animation", () =>
    Source.fromRequired(Packager.require("./animations/LineAnimation.json"))
  ),
  makeExample("Lottie Logo 1", () =>
    Source.fromRequired(Packager.require("./animations/LottieLogo1.json"))
  ),
  makeExample("Lottie Logo 2", () =>
    Source.fromRequired(Packager.require("./animations/LottieLogo2.json"))
  ),
  makeExample("Lottie Walkthrough", () =>
    Source.fromRequired(
      Packager.require("./animations/LottieWalkthrough.json"),
    )
  ),
  makeExample("Pin Jump", () =>
    Source.fromRequired(Packager.require("./animations/PinJump.json"))
  ),
  makeExample("Twitter Heart", () =>
    Source.fromRequired(Packager.require("./animations/TwitterHeart.json"))
  ),
  makeExample("Watermelon", () =>
    Source.fromRequired(Packager.require("./animations/Watermelon.json"))
  ),
  makeExample("Motion Corpse", () =>
    Source.fromRequired(
      Packager.require("./animations/MotionCorpse-Jrcanest.json"),
    )
  ),
  makeExample("9 Squares", () =>
    Source.fromRequired(
      Packager.require("./animations/9squares-AlBoardman.json"),
    )
  ),
|];

let findByName = name =>
  List.find(example => example.name == name, Array.to_list(examples));
