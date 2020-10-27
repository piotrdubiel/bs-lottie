open ReactNative;

[@react.component]
let make = (~example: Example.t, ~onChange, ~examples: array(Example.t)) => {
  <ReactNativePicker
    selectedValue={example.name}
    onValueChange=onChange
    style=Style.(
      style(
        ~marginBottom=Platform.os == Platform.ios ? (-30.0)->dp : 0.0->dp,
        (),
      )
    )>
    {ReasonReact.array(
       Array.map(
         example =>
           Example.(
             <ReactNativePicker.Item
               key={example.name}
               label={example.name}
               value={example.name}
             />
           ),
         examples,
       ),
     )}
  </ReactNativePicker>;
};
