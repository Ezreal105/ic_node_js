echo building...
set GYP_MSVS_VERSION=2019 &^
npm install &^
npm run build:ci &^
npm run package:ci &^
npm run publish:ci