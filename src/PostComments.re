open Revery;
open Revery.UI;
open Revery.UI.Components;

type state =
  | Idle
  | Loading
  | Data(list(Shared.Comment.t));

type action =
  | Fetch
  | NoData
  | Data(list(Shared.Comment.t));

let reducer = (action, _state): state => {
  switch (action) {
  | Fetch => Loading
  | NoData => Idle
  | Data(comments) => Data(comments)
  };
};

let component = React.component("Hackernews_PostComments");

let make = (~postId, ~setRoute, ()) =>
  component(hooks => {
    let (state, dispatch, hooks) =
      Hooks.reducer(~initialState=Idle, reducer, hooks);

    let fetchComments = () => {
      Fetch.fetch(Api.item(postId))
      |> Lwt.map(
           fun
           | Ok({Fetch.Response.body, _}) => {
               let kids =
                 Fetch.Response.Body.toString(body)
                 |> Yojson.Basic.from_string
                 |> Yojson.Basic.Util.member("kids");

               let result =
                 switch (Yojson.Basic.Util.to_list(kids)) {
                 | list => list |> List.map(Yojson.Basic.Util.to_int)
                 | exception (Yojson.Basic.Util.Type_error(_, _)) => []
                 };

               result;
             }
           | _ => [],
         )
      |> Lwt.map(Utils.List.take(5))
      |> Lwt.map(ids => {
           let%lwt comments =
             ids
             |> Lwt_list.map_p(id => {
                  let%lwt comment = Api.fetchItem(id);
                  let comment =
                    comment
                    |> Yojson.Safe.from_string
                    |> Shared.Comment.of_yojson
                    |> (
                      fun
                      | Ok(comment) => Some(comment)
                      | _ => None
                    );

                  Lwt.return(comment);
                });

           let comments = Tablecloth.Option.values(comments);

           dispatch(Data(comments));
           Lwt.return();
         })
      |> ignore;
    };

    let hooks =
      Hooks.effect(
        OnMount,
        () => {
          fetchComments();

          None;
        },
        hooks,
      );

    let hooks =
      Hooks.effect(
        If((!=), postId),
        () => {
          fetchComments();

          None;
        },
        hooks,
      );

    (
      hooks,
      <View style=Style.[alignSelf(`Stretch), alignItems(`Stretch)]>
        <Elements.Link
          text="Back"
          onClick={_ => setRoute(Shared.Router.Top)}
          active=true
        />
        {switch (state) {
         | Idle => <Elements.Loader text="Waiting for user input..." />
         | Loading => <Elements.Loader text="Loading..." />
         | Data(comments) =>
           <View>
             ...{comments |> List.map(comment => <Comment comment setRoute />)}
           </View>
         }}
      </View>,
    );
  });

let createElement = (~children as _, ~postId, ~setRoute, ()) =>
  make(~postId, ~setRoute, ());
