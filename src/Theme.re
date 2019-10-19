open Revery;

type theme = {
  overallBackgroundColor: Color.t,
  postBackgroundColor: Color.t,
  postTextColor: Color.t,
  contrastColor: Color.t,
  contrastColorDark: Color.t,
};

let regular = () => {
  overallBackgroundColor: Color.hex("#f2f3f5"),
  postBackgroundColor: Colors.white,
  postTextColor: Colors.black,
  contrastColor: Colors.darkOrange,
  contrastColorDark: Colors.orangeRed,
};

let dark = () => {
  overallBackgroundColor: Colors.black,
  postBackgroundColor: Color.hex("#111111"),
  postTextColor: Colors.white,
  contrastColor: Colors.darkOrange,
  contrastColorDark: Colors.orangeRed,
};

let generalFontSize = 13;

let currentTheme = ref(regular());
