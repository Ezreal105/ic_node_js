echo building...
python --version
npm config set python C:\\Python37-x64\\python.exe &^
set GYP_MSVS_VERSION=2019 &&^
npm install &&^
npm run build:ci &&^
npm run package:ci &&^
set NODE_PRE_GYP_GITHUB_TOKEN=%node_pre_gyp_github_token% &&^
npm run publish:ci