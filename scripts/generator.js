const basic_out_list = ["int *", "float *", "char **"];
const basic_list = [
  "char **",
  "unsigned char *",
  "char *",
  "int",
  "long",
  "unsigned long",
  "float",
  "void",
  "void *",
  ...basic_out_list,
];

const structP_list = ["HGRABBER", "HMEMBUFFER", "HCODEC", "HFRAMEFILTER"];
const structPp_list = ["HMEMBUFFER *", "HGRABBER *", "HFRAMEFILTER *"];
const enum_list = [
  "COLORFORMAT",
  "CAMERA_PROPERTY",
  "VIDEO_PROPERTY",
  "IMG_FILETYPE",
];
const supportedCTypes = [
  ...basic_list,
  ...structP_list,
  ...structPp_list,
  ...enum_list,
];

const skipList = ["IC_ReleaseMemBuffer", "IC_MemBufferGetDataPtr"];

const regexForCFunctionSignature =
  /typedef\s+(\w+)\s+(?:AC\s+)?(\w+)\s*\((.*)\)/;
const typePattern = `(${supportedCTypes
  .map((i) => i.replace(/\*/g, "\\*"))
  .join("|")})`;
const regexForArgWithoutName = new RegExp(`^${typePattern}$`);
const regexForArgWithName = new RegExp(`^${typePattern}\\s+(\\w+)$`);
/**
 *
 * @param {string} line
 */
function convert(line) {
  line = line.trim();
  const match = line.match(regexForCFunctionSignature);
  if (!match) {
    throw Error(`Invalid line: ${line}`);
  }
  const [, returnType, functionName] = match;
  const params = match[3].trim();
  console.log("[wsttest]", functionName, params);
  if (skipList.includes(functionName)) {
    return "";
  }
  const piecesForArgDef = [];
  const piecesForArgCheck = [];
  const paramNames = [];
  const outParamNameTypePairs = [];
  let argsNum = 0;
  if (params) {
    for (let [idx, arg] of params.split(",").entries()) {
      arg = arg.trim();

      let type = "";
      let name = "";
      const match = arg.match(regexForArgWithoutName);
      if (match) {
        type = match[1];
      } else {
        const match = arg.match(regexForArgWithName);

        if (!match) {
          throw Error(`Invalid argument: ${arg}`);
        }
        type = match[1];
        name = match[2];
      }
      let pieceForArgDef = "";
      let pieceForArgCheck = "";
      const getPieceForArgCheck = (
        checkMethod
      ) => `if (!info[${idx}].${checkMethod}()) {
      Napi::TypeError::New(env, "Wrong type of argument ${idx}").ThrowAsJavaScriptException();
      return env.Undefined();
    };`;
      let paramName = name || `arg${idx}`;
      argsNum++;
      if (type === "char *") {
        pieceForArgCheck = getPieceForArgCheck("isString");
        pieceForArgDef = `${type} ${paramName} = info[${idx}].As<Napi::String>().utf8Value().c_str();`;
      } else if (["int", "long", "float", "unsigned long"].includes(type)) {
        pieceForArgCheck = getPieceForArgCheck("isNumber");
        pieceForArgDef = `${type} ${paramName} = info[${idx}].As<Napi::Number>().int64_t();`;
      } else if (structP_list.includes(type)) {
        pieceForArgDef = `${type} ${paramName} = *info[${idx}].As<Napi::External<${type}>>().Data();`;
      } else if (enum_list.includes(type)) {
        pieceForArgCheck = getPieceForArgCheck("isNumber");
        pieceForArgDef = `${type} ${paramName} = (${type})info[${idx}].As<Napi::Number>().int32_t();`;
      } else if (basic_out_list.includes(type)) {
        argsNum--;
        pieceForArgDef = `${type} ${paramName};`;
        outParamNameTypePairs.push({ name: paramName, type });
      }
      pieceForArgDef && piecesForArgDef.push(pieceForArgDef);
      pieceForArgCheck && piecesForArgCheck.push(pieceForArgCheck);
      paramNames.push(paramName);
    }
  }

  let returnPiece = "Napi::Object retObj = Napi::Object::New(env);";
  // the return type is an object with a property "result" and a property "outArgs"
  if (returnType === "char *") {
    returnPiece += `\nretObj.Set("result", Napi::String::New(env, ret));`;
  } else if (["int", "long", "float", "unsigned long"].includes(returnType)) {
    returnPiece += `\nretObj.Set("result", Napi::Number::New(env, ret));`;
  } else if (["void"].includes(returnType)) {
    returnPiece += `\nretObj.Set("result",env.Undefined());`;
  } else if (structP_list.includes(returnType)) {
    returnPiece += `\nretObj.Set("result",Napi::External<${returnType}>::New(env, &ret));`;
  } else if (enum_list.includes(returnType)) {
    // enum
    returnPiece += `\nretObj.Set("result", Napi::Number::New(env, ret));`;
  } else {
    throw Error(`Unsupported return type: ${returnType}`);
  }
  outParamNameTypePairs.forEach((i) => {
    const { name, type } = i;
    if (["int *", "float *"].includes(type)) {
      returnPiece += `\nretObj.Set("${name}", Napi::Number::New(env, ${name}));`;
    } else if (["char **"].includes(type)) {
      returnPiece += `\nretObj.Set("${name}", Napi::String::New(env, ${name}));`;
    } else {
      throw Error(`Unsupported out param type: ${type}`);
    }
  });
  returnPiece += `\nreturn retObj;`;

  const paramNumCheck = `if (info.Length() != ${argsNum}) {
    Napi::TypeError::New(env, "Wrong number of arguments").ThrowAsJavaScriptException();
    return env.Undefined();
  }`;

  const funcStr = `Napi::Value f_${functionName}(const Napi::CallbackInfo& info) {
    Napi::Env env = info.Env();
    ${paramNumCheck}
    ${piecesForArgDef.join("\n")}
    ${piecesForArgCheck.join("\n")}
    ${functionName} f = (${functionName})GetProcAddress(tisgrabber, "${functionName}");
    if (f == NULL) {
        FreeLibrary(tisgrabber);
        Napi::Error::New(env, "Cannot find function ${functionName} in tisgrabber_x64.dll").ThrowAsJavaScriptException
        return env.undefined();
    };
    ${returnType} ret = f(${paramNames.join(", ")});
    ${returnPiece}
  }`;
  return funcStr;
}

const path = require("path");
const fs = require("fs");
const input = fs.readFileSync(
  path.join(__dirname, "generate_input.txt"),
  "utf8"
);
const lines = input.split("\n");
const output = lines
  .map(convert)
  .filter((i) => i)
  .join("\n");
fs.writeFileSync(path.join(__dirname, "generate_output.txt"), output);
