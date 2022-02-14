const Native = require("bindings")("native.node");

exports.promptSync = Native.prompt;
exports.forcePromptSync = Native.forcePrompt;
exports.loopPrompt = Native.loopPrompt;

exports.prompt = function(str) {
  return new Promise((resolve, reject) => {
    resolve(Native.prompt(str));
  });
}

exports.forcePrompt = function(str) {
  return new Promise((resolve, reject) => {
    resolve(Native.forcePrompt());
  });
}