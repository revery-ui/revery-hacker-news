open Revery;
open Revery.UI;
open Revery.UI.Components;

module Styles = {
  let container = Style.[flexDirection(`Row), marginBottom(24)];
  let numberOfVotesContainer =
    Style.[
      alignItems(`Center),
      justifyContent(`Center),
      alignItems(`Center),
      margin(8),
      backgroundColor(Color.rgba(0., 0., 0., 0.)),
    ];
  let numberOfVotes =
    Style.[
      alignSelf(`Stretch),
      color(Theme.currentTheme.contents.contrastColor),
      fontFamily("Roboto-Black.ttf"),
      fontSize(Theme.FontSize.large),
      justifyContent(`Center),
      margin(20),
      width(36),
    ];
  let content =
    Style.[
      backgroundColor(Theme.currentTheme.contents.postBackgroundColor),
      color(Theme.currentTheme.contents.postTextColor),
      textWrap(TextWrapping.WhitespaceWrap),
      fontFamily("Roboto-Black.ttf"),
      fontSize(Theme.FontSize.large),
      lineHeight(1.5),
    ];
  let contentTitleContainer =
    Style.[flexDirection(`Row), alignItems(`FlexEnd)];
  let contentTitleURL =
    Style.[
      marginBottom(2),
      marginLeft(12),
      backgroundColor(Theme.currentTheme.contents.postBackgroundColor),
      color(Colors.lightSlateGray),
      fontFamily("Roboto-Regular.ttf"),
      fontSize(Theme.FontSize.base),
      lineHeight(1.5),
    ];
  let subcontent =
    Style.[
      color(Colors.lightSlateGray),
      fontFamily("Roboto-Regular.ttf"),
      fontSize(Theme.FontSize.base),
    ];
};

let component = React.component("Hackernews_Post");

let make = (~post: Shared.Post.t, ~setRoute, ()) =>
  component(hooks => {
    let handleOpenUrl =
      fun
      | Some(url) => Sys.command("open " ++ url) |> ignore
      | _ => ();

    let subcontentText =
      "by "
      ++ post.author
      ++ " "
      ++ string_of_int(post.time)
      ++ (
        switch (post.numberOfComments) {
        | None => ""
        | Some(count) => " | " ++ string_of_int(count) ++ " comments"
        }
      );

    let url = post.url |> Tablecloth.Option.withDefault(~default="");

    (
      hooks,
      <View style=Styles.container>
        <View style=Styles.numberOfVotesContainer>
          <Text style=Styles.numberOfVotes text={string_of_int(post.votes)} />
        </View>
        <Elements.Card style=Style.[width(704)]>
          <View style=Styles.contentTitleContainer>
            <Text style=Styles.content text={post.title} />
            <Clickable onClick={_ => handleOpenUrl(post.url)}>
              <Text
                style=Styles.contentTitleURL
                text={Utils.Uri.toHost(url)}
              />
            </Clickable>
          </View>
          <Clickable
            onClick={_ => setRoute(Shared.Router.Comments(post.id))}>
            <Text style=Styles.subcontent text=subcontentText />
          </Clickable>
        </Elements.Card>
      </View>,
    );
  });

let createElement = (~children as _, ~post: Shared.Post.t, ~setRoute, ()) =>
  make(~post, ~setRoute, ());
