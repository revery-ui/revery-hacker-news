module List = {
  let rec take = (n, xs) =>
    switch (xs) {
    | [] => []
    | [x, ...xs] =>
      if (n == 1) {
        [x];
      } else {
        [x, ...take(n - 1, xs)];
      }
    };
};
