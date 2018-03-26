// Generated by BUCKLESCRIPT VERSION 2.2.3, PLEASE EDIT WITH CARE
'use strict';

var Block = require("bs-platform/lib/js/block.js");
var ReasonReact = require("reason-react/lib/js/src/ReasonReact.js");
var View$BsReactNative = require("bs-react-native/lib/js/src/components/view.js");
var Style$BsReactNative = require("bs-react-native/lib/js/src/style.js");
var LottieView$BsLottieReactNative = require("bs-lottie-react-native/lib/js/src/LottieView.js");

var animations = {
  lottie1: ( require('./animations/LottieLogo1.json'))
};

function app() {
  return ReasonReact.element(/* None */0, /* None */0, View$BsReactNative.make(/* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* Some */[Style$BsReactNative.style(/* :: */[
                          Style$BsReactNative.flex(1),
                          /* :: */[
                            Style$BsReactNative.justifyContent(/* Center */2),
                            /* :: */[
                              Style$BsReactNative.alignItems(/* Center */2),
                              /* [] */0
                            ]
                          ]
                        ])], /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0, /* None */0)(/* array */[ReasonReact.element(/* None */0, /* None */0, LottieView$BsLottieReactNative.make(/* Local */Block.__(0, [animations.lottie1]), /* Some */[0.5], /* None */0, /* Some */[/* true */1], /* None */0, /* None */0, /* array */[]))]));
}

exports.animations = animations;
exports.app = app;
/* animations Not a pure module */
