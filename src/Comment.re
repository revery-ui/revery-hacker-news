open Revery;
open Revery.UI;

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
      fontSize(Theme.FontSize.base),
      margin(20),
    ];
  let contentContainer = Style.[margin(10)];
  let content =
    Style.[
      backgroundColor(Theme.currentTheme.contents.postBackgroundColor),
      color(Theme.currentTheme.contents.postTextColor),
      fontFamily("Roboto-Regular.ttf"),
      fontSize(Theme.FontSize.base),
    ];
  let contentTitleContainer = Style.[flexDirection(`Row)];
  let contentTitleURL =
    Style.[
      marginLeft(8),
      backgroundColor(Theme.currentTheme.contents.postBackgroundColor),
      color(Colors.lightSlateGray),
      fontFamily("Roboto-Regular.ttf"),
      fontSize(Theme.FontSize.base),
    ];
  let subcontent =
    Style.[
      color(Colors.lightSlateGray),
      fontFamily("Roboto-Regular.ttf"),
      fontSize(Theme.FontSize.base),
    ];
};

let component = React.component("Hackernews_Post");

let make = (~comment: Shared.Comment.t, ~setRoute, ()) =>
  component(hooks => {
    let subcontentText =
      "by " ++ comment.by ++ " " ++ string_of_int(comment.time);

    (
      hooks,
      <View style=Styles.view>
        <View style=Styles.contentContainer>
          <View style=Styles.contentTitleContainer>
            <Text
              style=Styles.content
              text={
                comment.text
                |> Soup.parse
                /* |> Soup.(iter(pre => pre $ "+ p" |> clear)) */
                |> Soup.to_string
              }
            />
          </View>
          <Text style=Styles.subcontent text=subcontentText />
        </View>
      </View>,
    );
  });

let createElement =
    (~children as _, ~comment: Shared.Comment.t, ~setRoute, ()) =>
  make(~comment, ~setRoute, ());
