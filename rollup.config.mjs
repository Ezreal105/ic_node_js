import typescript from '@rollup/plugin-typescript';
import copy from 'rollup-plugin-copy';
import pkg from './package.json' assert {type: 'json'};

export default [
  {
    input: 'src/index.ts',
    plugins: [typescript(), copy({targets: [{src: 'src/*.dll', dest: 'dist'}]})],
    external: ['ms'],
    output: [
      {file: pkg.main, format: 'cjs'},
      {file: pkg.module, format: 'es'},
    ],
  },
];
