type t;
module MakeBrowserWindow =
       (T: {
          type mainToRendererMessages;
          let message: string;
        }) => {
  type webPreferences = {
    .
    devTools: Js.null(bool),
    nodeIntegration: Js.null(bool),
    nodeIntegrationWorker: Js.null(bool),
    nodeIntegrationInSubFrames: Js.null(bool),
    preload: Js.null(string),
    sandbox: Js.null(bool),
    enableRemoteModule: Js.null(bool),
  };
  type windowConfig = {
    .
    width: int,
    height: int,
    frame: Js.null(bool),
    titleBarStyle: Js.null(string),
    fullscreenable: Js.null(bool),
    resizeable: Js.null(bool),
    transparent: Js.null(bool),
    title: Js.null(string),
    backgroundColor: Js.null(string),
    webPreferences: webPreferences,
  };

  [@bs.obj]
  external makeWebPreferences:
    (~preload: string=?) =>
    // ~devTools: bool=?,
    // ~nodeIntegration: bool=?,
    // ~nodeIntegrationWorker: bool=?,
    // ~nodeIntegrationInSubFrames: bool=?,
    // ~sandbox: bool=?,
    // ~enableRemoteModule: bool=?
    webPreferences =
    "";

  [@bs.obj]
  external makeWindowConfig:
    (
      ~width: int,
      ~height: int,
      ~frame: bool=?,
      ~titleBarStyle: [@bs.string] [ | [@bs.as "hidden"] `Hidden]=?,
      ~fullscreenable: bool=?,
      ~resizeable: bool=?,
      ~transparent: bool=?,
      ~title: string=?,
      ~backgroundColor: string=?,
      ~webPreferences: webPreferences=?,
      unit
    ) =>
    windowConfig =
    "";

  [@bs.module "electron"] [@bs.new]
  external make: windowConfig => t = "BrowserWindow";

  [@bs.send] external loadURL: (t, string) => unit = "";

  [@bs.send]
  external on:
    (
      t,
      [@bs.string] [ | [@bs.as "closed"] `Closed | [@bs.as "blur"] `Blur],
      unit => unit
    ) =>
    unit =
    "";

  [@bs.send] [@bs.scope "webContents"]
  external send: (t, string, 'a) => unit = "send";

  let send = (t, arg: T.mainToRendererMessages) =>
    send(t, T.message, arg->Json.toValidJson->Js.Json.stringify);

  [@bs.send] external openDevTools: t => unit = "";

  [@bs.send] external isVisible: t => bool = "";

  [@bs.send] external show: t => unit = "";
  [@bs.send] external hide: t => unit = "";
  [@bs.send] external focus: t => unit = "";

  [@bs.send]
  external setPosition: (t, ~x: int, ~y: int, ~animate: bool) => unit = "";

  type visibility = [ | `Showing | `Hidden];
  let getVisibility = t => isVisible(t) ? `Showing : `Hidden;
  let getBounds = t => Common.boundsFromJs(Common.getBoundsJs(t));
};