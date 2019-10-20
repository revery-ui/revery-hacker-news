open Revery;
open Revery.UI;
open Revery.UI.Components;

module Loader = {
  module Styles = {
    let container = Style.[margin(32)];

    let text =
      Style.[
        color(Colors.lightSlateGray),
        fontFamily("Roboto-Regular.ttf"),
        fontSize(Theme.generalFontSize),
      ];
  };

  let component = React.component("Hackernews_Loader");

  let make = (~text, ()) =>
    component(hooks =>
      (
        hooks,
        <View style=Styles.container> <Text style=Styles.text text /> </View>,
      )
    );

  let createElement = (~children as _, ~text, ()) => make(~text, ());
};

module Link = {
  module Styles = {
    let container = bgColor => Style.[backgroundColor(bgColor)];

    let item =
      Style.[
        color(Colors.white),
        fontFamily("Roboto-Regular.ttf"),
        fontSize(Theme.generalFontSize),
        margin(12),
      ];
  };
  let component = React.component("Hackernews_Link");

  let make = (~text, ~onClick, ~active, ()) =>
    component(hooks => {
      let (bgColor, setBgColor, hooks) =
        Hooks.state(Theme.currentTheme.contents.contrastColor, hooks);

      let bgColor =
        active ? Theme.currentTheme.contents.contrastColorDark : bgColor;

      (
        hooks,
        <View
          onMouseOut={_ =>
            setBgColor(Theme.currentTheme.contents.contrastColor)
          }
          onMouseOver={_ =>
            setBgColor(Theme.currentTheme.contents.contrastColorDark)
          }
          style={Styles.container(bgColor)}>
          <Clickable onClick> <Text style=Styles.item text /> </Clickable>
        </View>,
      );
    });

  let createElement = (~children as _, ~text, ~onClick, ~active, ()) =>
    make(~text, ~onClick, ~active, ());
};

module Header = {
  module Styles = {
    let container =
      Style.[
        height(48),
        flexDirection(`Row),
        alignItems(`Center),
        backgroundColor(Theme.currentTheme.contents.contrastColor),
      ];
    let view = Style.[flexDirection(`Row)];
    let logo =
      Style.[
        color(Colors.white),
        fontFamily("Roboto-BoldItalic.ttf"),
        fontSize(16),
        margin(12),
      ];
  };

  let component = React.component("Hackernews_Header");

  let make = (~setRoute, ~currentRoute, ()) =>
    component(hooks =>
      Shared.Router.(
        hooks,
        <View style=Styles.container>
          <View> <Text style=Styles.logo text="Revery Hacker News" /> </View>
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
        </View>,
      )
    );

  let createElement = (~children as _, ~setRoute, ~currentRoute, ()) =>
    make(~setRoute, ~currentRoute, ());
};
