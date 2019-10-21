module List = {
  let rec take = (numItems, someList) =>
    switch (someList) {
    | [] => []
    | [item, ...someList] =>
      if (numItems == 1) {
        [item];
      } else {
        [item, ...take(numItems - 1, someList)];
      }
    };
};

module Uri = {
  let toHost = url =>
    Uri.of_string(url)
    |> Uri.host
    |> Tablecloth.Option.withDefault(~default=url);
};
