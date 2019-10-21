open Revery;
open Revery.UI;

type action =
  | ChangeRoute(Shared.Router.t);

module Hackernews = {
  let component = React.component("Hackernews");

  let make = () =>
    component(hooks => {
      let (route, dispatch, hooks) =
        Hooks.reducer(
          ~initialState=Shared.Router.Top,
          (action, _state) =>
            switch (action) {
            | ChangeRoute(newRoute) => newRoute
            },
          hooks,
        );

      let setRoute = route => dispatch(ChangeRoute(route));

      let currentView =
        switch (route) {
        | Comments(id) =>
          Console.log(("ShouldRenderComments", id));
          ("Comments", <PostComments postId=id setRoute />);
        | Top
        | Ask
        | New
        | Jobs
        | Show =>
          Console.log("ShouldRenderPosts");
          ("Posts", <Posts route setRoute />);
        };

      Console.log(("CurrentView", fst(currentView)));

      (
        hooks,
        <View
          style=Style.[
            alignItems(`Center),
            bottom(0),
            flexDirection(`Column),
            left(0),
            position(`Absolute),
            right(0),
            top(0),
          ]>
          <Elements.Header setRoute currentRoute=route />
          <View
            style=Style.[
              padding(24),
              alignSelf(`Center),
              alignItems(`Center),
              flexDirection(`Column),
              justifyContent(`Center),
              overflow(`Scroll),
            ]>
            {snd(currentView)}
          </View>
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
          ~width=1216,
          ~height=864,
          ~decorated=false,
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
