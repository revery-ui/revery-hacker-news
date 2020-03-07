open Revery;
open Revery.UI;
open Revery.Math;
open Revery.UI.Components;

module Card = {
  module Styles = {
    let shadow =
      Style.BoxShadow.make(
        ~yOffset=16.,
        ~xOffset=4.,
        ~blurRadius=16.,
        ~color=Color.hex("#e4e4e4"),
        ~spreadRadius=-22.,
        (),
      );

    let container =
      Style.[
        padding(16),
        flexDirection(`Column),
        flexWrap(`Wrap),
        alignSelf(`Stretch),
        backgroundColor(Theme.currentTheme.contents.postBackgroundColor),
        justifyContent(`FlexStart),
      ];
  };

  let make = (~children, ~style as customStyles=[], ()) =>
    <BoxShadow boxShadow=Styles.shadow>
      <View
        style={Style.merge(~source=Styles.container, ~target=customStyles)}>
        children
      </View>
    </BoxShadow>;
};

module Loader = {
  module Styles = {
    let container = Style.[margin(32)];

    let text =
    Style.[
      marginTop(6),
      color(Colors.black),
      fontFamily("Roboto-Regular.ttf"),
      fontSize(Theme.FontSize.base),
      lineHeight(1.5),
    ];
  };

  let%component make = (~text, ()) => {
    let%hook (rotation, _, _) =
      Hooks.animation(
        Animation.(
          animate(Time.seconds(1))
          |> ease(Easing.ease)
          |> repeat
          |> tween(2., 5.)
        ),
      );

    <View style=Styles.container>
      <Image
        src="spinner.png"
        style=Style.[
          width(48),
          height(48),
          transform([Transform.Rotate(Angle.from_radians(rotation))]),
        ]
      />
      <Text style=Styles.text text />
    </View>;
  };
};

module InteractableView = {
  type state =
    | Idle
    | Hover
    | Active;

  type action =
    | Idle
    | Hover
    | Active;

  let%component make =
                (~children, ~hoverStyles=[], ~activeStyles=[], ~style=[], ()) => {
    let%hook (state, dispatch) =
      Hooks.reducer(~initialState=Idle, (action, _state) =>
        switch (action) {
        | Idle => Idle
        | Hover => Hover
        | Active => Active
        }
      );

    let currentStyle =
      switch (state) {
      | Idle => style
      | Hover => Style.merge(~source=style, ~target=hoverStyles)
      | Active =>
        Style.merge(
          ~source=style,
          ~target=Tablecloth.List.concat([hoverStyles, ...activeStyles]),
        )
      };

    <View
      onMouseOut={_ => dispatch(Idle)}
      onMouseOver={_ => dispatch(Hover)}
      onMouseDown={_ => dispatch(Active)}
      style=currentStyle>
      children
    </View>;
  };
};

module InteractableText = {
  type state =
    | Idle
    | Hover
    | Active;

  let%component make =
                (~hoverStyles=[], ~activeStyles=[], ~style=[], ~text, ()) => {
    let%hook (state, dispatch) =
      Hooks.reducer(~initialState=Idle, (action, _state: state) =>
        switch (action) {
        | `Idle => Idle
        | `Hover => Hover
        | `Active => Active
        }
      );

    let currentStyle =
      switch (state) {
      | Idle => style
      | Hover => Style.merge(~source=style, ~target=hoverStyles)
      | Active =>
        Style.merge(
          ~source=style,
          ~target=Tablecloth.List.concat([hoverStyles, ...activeStyles]),
        )
      };

    <Text
      onMouseOut={_ => dispatch(`Idle)}
      onMouseOver={_ => dispatch(`Hover)}
      onMouseDown={_ => dispatch(`Active)}
      style=currentStyle
      text
    />;
  };
};
module Link = {
  module Styles = {
    let item = active =>
      Style.[
        active
          ? color(Theme.currentTheme.contents.postTextColor)
          : color(Theme.currentTheme.contents.postTextQuietColor),
        fontFamily("Roboto-Black.ttf"),
        alignSelf(`Stretch),
        justifyContent(`Center),
        fontSize(Theme.FontSize.base),
        margin(12),
      ];
  };

  let make = (~text, ~onClick, ~active, ()) =>
    <Clickable onClick>
      <InteractableText
        style={Styles.item(active)}
        hoverStyles=Style.[color(Color.hex("#929292"))]
        text
      />
    </Clickable>;
};

module Header = {
  module Styles = {
    let shadow =
      Style.BoxShadow.make(
        ~yOffset=2.,
        ~xOffset=-3.,
        ~blurRadius=12.,
        ~color=Color.hex("#e4e4e4"),
        ~spreadRadius=-6.,
        (),
      );
    let container =
      Style.[
        paddingHorizontal(24),
        paddingVertical(8),
        justifyContent(`SpaceBetween),
        flexDirection(`Row),
        alignSelf(`Stretch),
        backgroundColor(Theme.currentTheme.contents.postBackgroundColor),
      ];
    let view = Style.[flexDirection(`Row)];
    let logo =
      Style.[
        color(Theme.currentTheme.contents.contrastColor),
        fontFamily("Roboto-Black.ttf"),
        fontSize(Theme.FontSize.extraLarge),
        margin(12),
      ];
  };

  let make = (~setRoute, ~currentRoute, ()) => {
    Shared.Router.(
      <View style=Style.[alignSelf(`Stretch), paddingBottom(12)]>
        <BoxShadow boxShadow=Styles.shadow>
          <View style=Styles.container>
            <View> <Text style=Styles.logo text="Revery HN" /> </View>
            <View style=Styles.view>
              <Link
                active={currentRoute == Top}
                onClick={() => setRoute(Top)}
                text="Top"
              />
              <Link
                active={currentRoute == New}
                onClick={() => setRoute(New)}
                text="New"
              />
              <Link
                active={currentRoute == Show}
                onClick={() => setRoute(Show)}
                text="Show"
              />
              <Link
                active={currentRoute == Ask}
                onClick={() => setRoute(Ask)}
                text="Ask"
              />
              <Link
                active={currentRoute == Jobs}
                onClick={() => setRoute(Jobs)}
                text="Jobs"
              />
            </View>
          </View>
        </BoxShadow>
      </View>
    );
  };
};
