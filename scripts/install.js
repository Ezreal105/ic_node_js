const os = require("os");
const exec = require("child_process").execSync;

if (os.platform() === "win32") {
  exec("node-pre-gyp install --fallback-to-build");
}
