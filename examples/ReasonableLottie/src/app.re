open BsReactNative;

open BsLottieReactNative;

let animations = {"lottie1": [%raw {| require('./animations/LottieLogo1.json')|}]};

let app = () =>
  <View style=Style.(style([flex(1.), justifyContent(Center), alignItems(Center)]))>
    <LottieView autoPlay=true source=(Local(animations##lottie1)) progress=0.5 />
  </View>;