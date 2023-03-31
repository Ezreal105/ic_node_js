echo building...
npm config set python C:\\Python39-x64\\python.exe &^
set GYP_MSVS_VERSION=2019 &&^
npm install &&^
npm run build:addon &&^
npm run package:addon &&^
set NODE_PRE_GYP_GITHUB_TOKEN=%node_pre_gyp_github_token% &&^
npm run publish:addon