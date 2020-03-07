open Revery;
open Revery.UI;

type action =
  | ChangeRoute(Shared.Router.t);

module Hackernews = {
  let%component make = () => {
    let%hook (route, dispatch) =
      Hooks.reducer(~initialState=Shared.Router.Top, (action, _state) =>
        switch (action) {
        | ChangeRoute(newRoute) => newRoute
        }
      );

    let setRoute = route => dispatch(ChangeRoute(route));

    let currentView =
      switch (route) {
      | Comments(id) =>
        /* <PostComments postId=id setRoute /> */
        <Posts route postId={Some(id)} setRoute />
      | Top
      | Ask
      | New
      | Jobs
      | Show =>
        // Console.log("ShouldRenderPosts");
        <Posts route postId=None setRoute />;
      };

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
        currentView
      </View>
    </View>;
  };
};

let init = app => {
  let win =
    App.createWindow(
      app,
      ~createOptions=
        WindowCreateOptions.create(
          ~width=1216,
          ~height=864,
          ~backgroundColor=Theme.currentTheme.contents.overallBackgroundColor,
          (),
        ),
      "Revery Hackernews",
    );

  let _startEventLoop = Revery_Lwt.startEventLoop();

  let element = <Hackernews />;

  let _uiStart = UI.start(win, element);
  ();
};

App.start(init);
