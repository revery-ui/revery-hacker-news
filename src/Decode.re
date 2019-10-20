module Post = {
  open Yojson.Basic;
  open Yojson.Basic.Util;

  let postId = json => json |> to_int;
  let postIds = json => json |> from_string |> to_list |> List.map(postId);

  let post = json =>
    json
    |> from_string
    |> (
      json => {
        Shared.Post.id: json |> member("id") |> to_int,
        title: json |> member("title") |> to_string,
        url: json |> member("url") |> to_string_option,
        author: json |> member("by") |> to_string,
        votes: json |> member("score") |> to_int,
        time: json |> member("time") |> to_int,
        numberOfComments: {
          let kids = json |> member("kids");
          switch (to_list(kids)) {
          | list => Some(List.length(list))
          | exception (Yojson.Basic.Util.Type_error(_, _)) => None
          };
        },
      }
    );
};