open BsReactNative;

let component = ReasonReact.statelessComponent("ExamplePicker");

let make = (~example: Example.t, ~onChange, ~examples: array(Example.t), _children) => {
  ...component,
  render: (_self) =>
    <Picker
      selectedValue=example.name
      onValueChange=onChange
      style=Style.(
              style([
                Platform.equals(IOS(Phone)) ? marginBottom(Pt((-30.0))) : marginBottom(Pt(0.0))
              ])
            )>
      (
        ReasonReact.arrayToElement(
          Array.map(
            (example) =>
              Example.(<Picker.Item key=example.name label=example.name value=example.name />),
            examples
          )
        )
      )
    </Picker>
};