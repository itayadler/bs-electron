// Generated by BUCKLESCRIPT VERSION 4.0.5, PLEASE EDIT WITH CARE
'use strict';

var Electron = require("electron");
var Json$BsElectron = require("./Json.bs.js");

function MakeIpcMain() {
  var on = function (cb) {
    Electron.ipcMain.on("message", (function ($$event, arg) {
            return cb($$event, Json$BsElectron.fromValidJson(JSON.parse(arg)));
          }));
    return /* () */0;
  };
  return /* module */[/* on */on];
}

exports.MakeIpcMain = MakeIpcMain;
/* electron Not a pure module */
