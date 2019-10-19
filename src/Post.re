open Revery;
open Revery.UI;
open Revery.UI.Components;

module Styles = {
  let view =
    Style.[
      flexDirection(`Row),
      backgroundColor(Theme.currentTheme.contents.postBackgroundColor),
      marginBottom(1),
    ];
  let numberOfVotes =
    Style.[
      color(Theme.currentTheme.contents.contrastColor),
      fontFamily("Roboto-Bold.ttf"),
      fontSize(Theme.generalFontSize),
      margin(20),
    ];
  let contentContainer = Style.[margin(10)];
  let content =
    Style.[
      backgroundColor(Theme.currentTheme.contents.postBackgroundColor),
      color(Theme.currentTheme.contents.postTextColor),
      fontFamily("Roboto-Regular.ttf"),
      fontSize(Theme.generalFontSize),
    ];
  let contentTitleContainer = Style.[flexDirection(`Row)];
  let contentTitleURL =
    Style.[
      marginLeft(8),
      backgroundColor(Theme.currentTheme.contents.postBackgroundColor),
      color(Colors.lightSlateGray),
      fontFamily("Roboto-Regular.ttf"),
      fontSize(Theme.generalFontSize),
    ];
  let subcontent =
    Style.[
      color(Colors.lightSlateGray),
      fontFamily("Roboto-Regular.ttf"),
      fontSize(Theme.generalFontSize),
    ];
};

let component = React.component("Hackernews_Post");

let make = (~post: Shared.Post.t, ~setRoute, ()) =>
  component(hooks => {
    let subcontentText =
      "by "
      ++ post.author
      ++ " some time ago"
      ++ (
        switch (post.numberOfComments) {
        | None => ""
        | Some(count) => " | " ++ string_of_int(count) ++ " comments"
        }
      );

    let url =
      switch (post.url) {
      | Some(url) => " (" ++ url ++ ")"
      | None => ""
      };
    (
      hooks,
      <View style=Styles.view>
        <Text style=Styles.numberOfVotes text={string_of_int(post.votes)} />
        <View style=Styles.contentContainer>
          <View style=Styles.contentTitleContainer>
            <Text style=Styles.content text={post.title} />
            <Text style=Styles.contentTitleURL text=url />
          </View>
          <Clickable
            onClick={_ => setRoute(Shared.Router.Comments(post.id))}>
            <Text style=Styles.subcontent text=subcontentText />
          </Clickable>
        </View>
      </View>,
    );
  });

let createElement = (~children as _, ~post: Shared.Post.t, ~setRoute, ()) =>
  make(~post, ~setRoute, ());
