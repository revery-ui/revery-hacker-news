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

let%component make = (~route, ~setRoute: Shared.Router.t => unit, ~postId, ()) => {
  let%hook (state, dispatch) = Hooks.reducer(~initialState=Idle, reducer);

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

  let%hook () =
    Hooks.effect(
      OnMount,
      () => {
        fetchPosts();

        None;
      },
    );

  let%hook () =
    Hooks.effect(
      If((!=), route),
      () => {
        fetchPosts();

        None;
      },
    );

  switch (postId) {
  | Some(id) => <PostComments postId=id setRoute />
  | _ =>
    switch (state) {
    | Idle => <Elements.Loader text="Waiting for user input..." />
    | Loading => <Elements.Loader text="Loading..." />
    | Posts(posts) =>
      <View style=Style.[alignSelf(`Stretch)]>
        {posts
         |> Tablecloth.List.map(~f=post => <Post post setRoute />)
         |> React.listToElement}
      </View>
    }
  };
};
