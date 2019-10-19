module Router = {
  type route =
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
