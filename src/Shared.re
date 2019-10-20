module Router = {
  type t =
    | Top
    | New
    | Show
    | Ask
    | Jobs
    | Comments(int);
};

module Post = {
  type t = {
    id: int,
    title: string,
    url: option(string),
    author: string,
    votes: int,
    time: int,
    numberOfComments: option(int),
  };
};

module Comment = {
  [@deriving yojson({strict: false})]
  type t = {
    id: int,
    text: string,
    by: string,
    time: int,
  };
};
