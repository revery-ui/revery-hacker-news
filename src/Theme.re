open Revery;

type theme = {
  overallBackgroundColor: Color.t,
  postBackgroundColor: Color.t,
  postTextColor: Color.t,
  postTextQuietColor: Color.t,
  contrastColor: Color.t,
  contrastColorDark: Color.t,
};

let regular = () => {
  overallBackgroundColor: Color.hex("#f2f3f5"),
  postBackgroundColor: Colors.white,
  postTextColor: Color.hex("#444444"),
  postTextQuietColor: Color.hex("#dddddd"),
  contrastColor: Color.hex("#ef6f19"),
  contrastColorDark: Colors.orangeRed,
};

let dark = () => {
  overallBackgroundColor: Colors.black,
  postBackgroundColor: Color.hex("#111111"),
  postTextColor: Colors.white,
  postTextQuietColor: Color.hex("#dddddd"),
  contrastColor: Color.hex("#ef6f19"),
  contrastColorDark: Colors.orangeRed,
};

module FontSize = {
  let base = 14;
  let large = 18;
  let extraLarge = 22;
};

let currentTheme = ref(regular());
