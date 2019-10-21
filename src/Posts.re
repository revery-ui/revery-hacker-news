open Revery;
open Revery.UI;
open Revery.UI.Components;

type state =
  | Idle
  | Loading
  | Posts(list(Shared.Post.t));

type action =
  | Fetch
  | NoData
  | Data(list(Shared.Post.t));

let reducer = (action, _state): state => {
  switch (action) {
  | Fetch => Loading
  | NoData => Idle
  | Data(posts) => Posts(posts)
  };
};

let component = React.component("Hackernews_Posts");

let make = (~route, ~setRoute, ()) =>
  component(hooks => {
    let (state, dispatch, hooks) =
      Hooks.reducer(~initialState=Idle, reducer, hooks);

    let fetchPosts = () => {
      dispatch(Fetch);
      Fetch.fetch(Api.urlFromRoute(route))
      |> Lwt.map(
           fun
           | Ok({Fetch.Response.body, _}) =>
             Fetch.Response.Body.toString(body) |> Decode.Post.postIds
           | _ => [],
         )
      |> Lwt.map(Utils.List.take(6))
      |> Lwt.map(ids => {
           let%lwt posts =
             ids
             |> Lwt_list.map_p(id => {
                  let%lwt post =
                    Api.fetchItem(id) |> Lwt.map(Decode.Post.post);
                  Lwt.return(post);
                });
           dispatch(Data(posts));
           Lwt.return();
         })
      |> ignore;
    };

    let hooks =
      Hooks.effect(
        OnMount,
        () => {
          fetchPosts();

          None;
        },
        hooks,
      );

    let hooks =
      Hooks.effect(
        If((!=), route),
        () => {
          fetchPosts();

          None;
        },
        hooks,
      );

    let postsToElements = posts =>
      posts |> Tablecloth.List.map(~f=post => <Post post setRoute />);

    (
      hooks,
      switch (state) {
      | Idle => <Elements.Loader text="Waiting for user input..." />
      | Loading => <Elements.Loader text="Loading..." />
      | Posts(posts) =>
        <View style=Style.[alignSelf(`Stretch)]>
          ...{postsToElements(posts)}
        </View>
      },
    );
  });

let createElement = (~children as _, ~route, ~setRoute, ()) =>
  make(~route, ~setRoute, ());
