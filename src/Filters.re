module Input = {
  type typ =
    | Float(option(float))
    | Number(option(int))
    | Text(string);
  [@react.component]
  let make = (~id, ~value, ~onBlur, ~onChange, ~label) => {
    <input
      className="threshold-input"
      id
      type_={
        switch (value) {
        | Float(_)
        | Number(_) => "number"
        | Text(_) => "text"
        }
      }
      onBlur
      onChange
      value={
        switch (value) {
        | Float(float) =>
          float
          |> Js.Option.map((. int) => Js.Float.toString(int))
          |> Js.Option.getWithDefault("")
        | Number(int) =>
          int
          |> Js.Option.map((. int) => Js.Int.toString(int))
          |> Js.Option.getWithDefault("")
        | Text(text) => text
        }
      }
      placeholder=label
    />;
  };
};

module H1 = {
  [@react.component]
  let make = (~text) => {
    <h1 className="text-big font-bold"> {React.string(text)} </h1>;
  };
};

module H2 = {
  [@react.component]
  let make = (~text) => {
    <h2 className="text-md font-bold pt-3"> {React.string(text)} </h2>;
  };
};

module P = {
  [@react.component]
  let make = (~text) => {
    <p className="text-base font-regular"> {React.string(text)} </p>;
  };
};

module Footer = {
  module A = {
    [@react.component]
    let make = (~href, ~str) => {
      <a className="font-bold" href> {React.string(str)} </a>;
    };
  };
  [@react.component]
  let make = () => {
    <div className="py-3 overflow-scroll text-base">
      <div>
        <span>
          {React.string("Created by ")}
          <A href="https://twitter.com/wokalski" str="Wojtek Czekalski" />
        </span>
      </div>
      <div>
        <span className="text-gray-400 text-base">
          {React.string("Data provided by ")}
          <A
            href="https://github.com/CSSEGISandData/COVID-19"
            str="CSSE at Johns Hopkins University"
          />
        </span>
      </div>
      <div>
        <span className="text-gray-400 text-base">
          {React.string("Contribute on ")}
          <A
            href="https://github.com/wokalski/COVID-19charts.com"
            str="Github"
          />
          {React.string(" or contact the author at: ")}
          <br />
          {React.string("me (at) wczekalski.com")}
        </span>
      </div>
    </div>;
  };
};

module MultiValueContainer = {
  [@react.component]
  let make = (~children) => {
    <div> children </div>;
  };
};

module Radio = {
  module Circle = {
    [@react.component]
    let make = (~selected) => {
      let selected = selected ? "-selected" : "";
      <div className={"radio-button-ring" ++ selected}>
        <div className={"radio-button-circle" ++ selected} />
      </div>;
    };
  };
  [@react.component]
  let make = (~values, ~selectedValue, ~format, ~onChange) => {
    <div className="flex flex-col">
      {Belt.Array.mapU(
         values,
         (. value) => {
           let text = format(value);
           let selected = value == selectedValue;
           let fontWeight = selected ? "font-bold" : "font-regular";
           <button
             className="flex items-center py-1"
             onClick={_ => onChange(value)}>
             <Circle selected={value == selectedValue} />
             <span className={"text-black text-base pl-2 " ++ fontWeight}>
               {React.string(text)}
             </span>
           </button>;
         },
       )
       |> React.array}
    </div>;
  };
};

module RadioSection = {
  [@react.component]
  let make = (~text, ~values, ~selectedValue, ~format, ~onChange) => {
    <div> <H2 text /> <Radio values selectedValue format onChange /> </div>;
  };
};

module Locations = {
  module Remove = {
    [@react.component]
    let make = () => {
      <svg
        className="legend-remove-button"
        width="14px"
        height="14px"
        viewBox="0 0 14 14"
        version="1.1"
        xmlns="http://www.w3.org/2000/svg">
        <defs />
        <g
          id="Page-1"
          stroke="none"
          strokeWidth="1"
          fill="none"
          fillRule="evenodd">
          <g id="Desktop" transform="translate(-575.000000, -253.000000)">
            <g id="Group-2" transform="translate(572.000000, 250.000000)">
              <g id="Group-3">
                <rect id="Rectangle-2" x="3" y="3" width="14" height="14" />
                <path
                  d="M11.8994949,7.89949494 L14.8994949,7.89949494 C16.0040644,7.89949494 16.8994949,8.79492544 16.8994949,9.89949494 C16.8994949,11.0040644 16.0040644,11.8994949 14.8994949,11.8994949 L11.8994949,11.8994949 L11.8994949,14.8994949 C11.8994949,16.0040644 11.0040644,16.8994949 9.89949494,16.8994949 C8.79492544,16.8994949 7.89949494,16.0040644 7.89949494,14.8994949 L7.89949494,11.8994949 L4.89949494,11.8994949 C3.79492544,11.8994949 2.89949494,11.0040644 2.89949494,9.89949494 C2.89949494,8.79492544 3.79492544,7.89949494 4.89949494,7.89949494 L7.89949494,7.89949494 L7.89949494,4.89949494 C7.89949494,3.79492544 8.79492544,2.89949494 9.89949494,2.89949494 C11.0040644,2.89949494 11.8994949,3.79492544 11.8994949,4.89949494 L11.8994949,7.89949494 Z"
                  id="Combined-Shape"
                  transform="translate(9.899495, 9.899495) rotate(45.000000) translate(-9.899495, -9.899495) "
                />
              </g>
            </g>
          </g>
        </g>
      </svg>;
    };
  };
  module Button = {
    [@react.component]
    let make =
        (
          ~location as {Location.secondaryColor, primaryColor, text, id},
          ~onClick,
        ) => {
      <button
        onClick={_ => onClick(id)}
        className="flex items-center py-1 location-button">
        <Remove />
        <span
          style={ReactDOMRe.Style.make(
            ~color=secondaryColor,
            ~backgroundColor=primaryColor,
            (),
          )}
          className="text-base font-bold ml-2 rounded p-1">
          {React.string(text)}
        </span>
      </button>;
    };
  };
  [@react.component]
  let make = (~allLocations, ~locations, ~setLocations) => {
    <div>
      <H2 text="Locations" />
      {Belt.Array.mapU(locations, (. location) => {
         <Button
           location
           onClick={removedId => {
             setLocations(locations =>
               Js.Array.filter(id => id != removedId, locations)
             )
           }}
         />
       })
       |> React.array}
      <div className="pt-1">
        <ReactSelect
          value={Belt.Array.mapU(locations, (. {Location.text, id}) =>
            {ReactSelect.value: id, label: text}
          )}
          components={"IndicatorSeparator": Js.null}
          styles={
            "control": base =>
              Js.Obj.assign(
                base,
                {
                  "color": Colors.colors##fggray,
                  "fontWeight": "regular",
                  "flex": "1",
                  "width": "130px",
                  "minHeight": "29px",
                  "height": "29px",
                  "fontSize": "14px",
                  "border": 0,
                  "backgroundColor": Colors.colors##bggray,
                  "borderRadius": "4px",
                },
              ),
            "option": base => Js.Obj.assign(base, {"fontSize": "14px"}),
            "noOptionsMessage": base =>
              Js.Obj.assign(base, {"fontSize": "14px"}),
          }
          controlShouldRenderValue=false
          isMulti=true
          name="Locations"
          options=allLocations
          placeholder="Add location"
          isClearable=false
          onChange={newSelection => {
            switch (Js.Nullable.toOption(newSelection)) {
            | Some(newSelection) =>
              setLocations(_ => {
                Belt.Array.mapU(newSelection, (. {ReactSelect.value}) =>
                  value
                )
              })
            | None => setLocations(_ => [||])
            }
          }}
          noOptionsMessage={() => Some(React.string("Unknown location"))}
        />
      </div>
    </div>;
  };
};

module ThresholdInput = {
  [@react.component]
  let make = (~threshold as (threshold, setThreshold)) => {
    <div>
      <H2 text="Threshold (# of cases)" />
      <div className="pt-1">
        <Input
          id="nr_of_cases"
          value={Input.Number(threshold)}
          onBlur=ignore
          onChange={ev => {
            let value =
              ReactEvent.Form.target(ev)##value |> int_of_string_opt;
            setThreshold(_ => value);
          }}
          label="1"
        />
      </div>
    </div>;
  };
};

type scale =
  | Logarithmic
  | Linear;

type timeline =
  | RelativeToThreshold
  | CalendarDates;

type chartType =
  | NumberOfCases;

[@react.component]
let make =
    (
      ~locations,
      ~allLocations,
      ~setLocations,
      ~scale as (scale, setScale),
      ~timeline as (timeline, setTimeline),
      ~threshold,
    ) => {
  <div className="w-full md:w-64 p-4">
    <H1 text={js|Stay at home|js} />
    <P
      text={js|Most important charts to help you understand the COVID-19 outlook for your location.|js}
    />
    <RadioSection
      text={js|Chart type|js}
      values=[|NumberOfCases|]
      selectedValue=NumberOfCases
      format={
        fun
        | NumberOfCases => "Number of cases"
      }
      onChange=ignore
    />
    <RadioSection
      text={js|Scale|js}
      values=[|Logarithmic, Linear|]
      selectedValue=scale
      format={
        fun
        | Logarithmic => "Logarithmic"
        | Linear => "Linear"
      }
      onChange={scale => setScale(_ => scale)}
    />
    <Locations setLocations allLocations locations />
    <RadioSection
      text={js|Timeline|js}
      values=[|RelativeToThreshold, CalendarDates|]
      selectedValue=timeline
      format={
        fun
        | RelativeToThreshold => "Relative to threshold"
        | CalendarDates => "Calendar dates"
      }
      onChange={timeline => setTimeline(_ => timeline)}
    />
    <ThresholdInput threshold />
    <Footer />
  </div>;
};
