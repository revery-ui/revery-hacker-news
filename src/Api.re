let baseURL = "https://hacker-news.firebaseio.com/v0";
let top = baseURL ++ "/topstories.json";
let latest = baseURL ++ "/newstories.json";
let show = baseURL ++ "/showstories.json";
let ask = baseURL ++ "/askstories.json";
let jobs = baseURL ++ "/jobstories.json";

let item = (id: int) => baseURL ++ "/item/" ++ string_of_int(id) ++ ".json";

let urlFromRoute =
  Shared.Router.(
    fun
    | Top => top
    | New => latest
    | Show => show
    | Ask => ask
    | Jobs => jobs
    | _ => top
  );

let fetchItemIds = url => {
  let%lwt response = Fetch.fetch(url);

  let result =
    switch (response) {
    | Ok({body, _}) => Fetch.Response.Body.toString(body)
    | Error(_) => "Error!"
    };

  Lwt.return(result);
};

let fetchItemIdsFromRoute = route => route |> urlFromRoute |> fetchItemIds;
let fetchItem = id => {
  let%lwt result =
    Fetch.(
      fetch(item(id))
      |> Lwt.map(
           fun
           | Ok({Response.body, _}) => Response.Body.toString(body)
           | _ => "Error!",
         )
    );

  Lwt.return(result);
};
