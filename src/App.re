open Revery;
open Revery.UI;
open Revery.UI.Components;

module Hackernews = {
  let component = React.component("Hackernews");

  let make = () =>
    component(hooks => {
      let (route, setRoute, hooks) = Hooks.state(Shared.Router.Top, hooks);
      (
        hooks,
        <View>
          <Elements.Header setRoute currentRoute=route />
          {switch (route) {
           | Comments(id) =>
             Console.log(("CanShowCommentsFor", id));
             <View />;
           | _ => <Posts route setRoute />
           }}
        </View>,
      );
    });

  let createElement = (~children as _, ()) => make();
};

let init = app => {
  let _ = Revery.Log.listen((_, msg) => print_endline("LOG: " ++ msg));

  let win =
    App.createWindow(
      app,
      ~createOptions=
        WindowCreateOptions.create(
          ~width=1280,
          ~height=860,
          ~backgroundColor=Theme.currentTheme.contents.overallBackgroundColor,
          (),
        ),
      "Revery Hackernews",
    );

  let _ignore = Revery_Lwt.startEventLoop();

  let element = <Hackernews />;

  let _ = UI.start(win, element);
  ();
};

App.start(init);
