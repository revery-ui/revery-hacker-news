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

  let component = React.component("Hackernews_Card");

  let make = (~children, ~style as customStyles=[], ()) =>
    component(hooks =>
      (
        hooks,
        <BoxShadow boxShadow=Styles.shadow>
          <View
            style={Style.merge(
              ~source=Styles.container,
              ~target=customStyles,
            )}>
            ...children
          </View>
        </BoxShadow>,
      )
    );

  let createElement = (~children, ~style, ()) => make(~children, ~style, ());
};

module Loader = {
  module Styles = {
    let container = Style.[margin(32)];
  };

  let component = React.component("Hackernews_Loader");

  let make = (~text, ()) =>
    component(hooks => {
      let (rotation, hooks) =
        Hooks.animation(
          Animated.floatValue(0.),
          Animated.options(
            ~toValue=96.,
            ~duration=Seconds(20.),
            ~delay=Seconds(0.),
            ~direction=`Normal,
            ~repeat=true,
            ~easing=Easing.ease,
            (),
          ),
          hooks,
        );

      (
        hooks,
        <View style=Styles.container>
          <Image
            src="spinner.png"
            style=Style.[
              width(48),
              height(48),
              transform([Transform.Rotate(Angle.from_radians(rotation))]),
            ]
          />
        </View>,
      );
    });

  let createElement = (~children as _, ~text, ()) => make(~text, ());
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

  let component = React.component("Hackernews_Interactable");

  let make =
      (
        ~children: list(React.syntheticElement),
        ~hoverStyles=[],
        ~activeStyles=[],
        ~style=[],
        (),
      ) =>
    component(hooks => {
      let (state, dispatch, hooks) =
        Hooks.reducer(
          ~initialState=Idle,
          (action, _state) =>
            switch (action) {
            | Idle => Idle
            | Hover => Hover
            | Active => Active
            },
          hooks,
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

      (
        hooks,
        <View
          onMouseOut={_ => dispatch(Idle)}
          onMouseOver={_ => dispatch(Hover)}
          onMouseDown={_ => dispatch(Active)}
          style=currentStyle>
          ...children
        </View>,
      );
    });

  let createElement =
      (~children, ~hoverStyles=[], ~activeStyles=[], ~style=[], ()) =>
    make(~children, ~hoverStyles, ~activeStyles, ~style, ());
};

module InteractableText = {
  type state =
    | Idle
    | Hover
    | Active;

  type action =
    | Idle
    | Hover
    | Active;

  let component = React.component("Hackernews_InteractableText");

  let make =
      (
        ~children: list(React.syntheticElement),
        ~hoverStyles=[],
        ~activeStyles=[],
        ~style=[],
        ~text,
        (),
      ) =>
    component(hooks => {
      let (state, dispatch, hooks) =
        Hooks.reducer(
          ~initialState=Idle,
          (action, _state) =>
            switch (action) {
            | Idle => Idle
            | Hover => Hover
            | Active => Active
            },
          hooks,
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

      (
        hooks,
        <Text
          onMouseOut={_ => dispatch(Idle)}
          onMouseOver={_ => dispatch(Hover)}
          onMouseDown={_ => dispatch(Active)}
          style=currentStyle
          text
        />,
      );
    });

  let createElement =
      (~children, ~hoverStyles=[], ~activeStyles=[], ~style=[], ~text, ()) =>
    make(~children, ~hoverStyles, ~activeStyles, ~style, ~text, ());
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
  let component = React.component("Hackernews_Link");

  let make = (~text, ~onClick, ~active, ()) =>
    component(hooks =>
      (
        hooks,
        <Clickable onClick>
          <InteractableText
            style={Styles.item(active)}
            hoverStyles=Style.[color(Color.hex("#929292"))]
            text
          />
        </Clickable>,
      )
    );

  let createElement = (~children as _, ~text, ~onClick, ~active, ()) =>
    make(~text, ~onClick, ~active, ());
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

  let component = React.component("Hackernews_Header");

  let make = (~setRoute, ~currentRoute, ()) =>
    component(hooks =>
      Shared.Router.(
        hooks,
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
        </View>,
      )
    );

  let createElement = (~children as _, ~setRoute, ~currentRoute, ()) =>
    make(~setRoute, ~currentRoute, ());
};
