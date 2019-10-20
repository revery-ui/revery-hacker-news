open Revery;
open Revery.UI;
open Revery.UI.Components;

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
        <View>
          <Elements.Header setRoute currentRoute=route />
          {snd(currentView)}
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
