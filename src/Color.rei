module Utils = UtilsRe;

module Option = Belt.Option;

type value =
  | Hex(string)
  | Rgb(int, int, int)
  | Hsl(int, int, int)
  | Hsw(int, int, int)
  | Hsv(int, int, int);

type color = {
  value,
  opacity: float
};

let inOpacityRange: float => float;

let fromHex: Js.String.t => option(color);

let fromRgba: ((int, int, int, float)) => option(color);

let fromRgb: ((int, int, int)) => option(color);

let fromHsla: ((int, int, int, float)) => option(color);

let fromHsl: ((int, int, int)) => option(color);

let fromHsv: ((int, int, int)) => option(color);

module Rgb: {
  let toHsl: ((int, int, int)) => (float, float, float);
  let toHsv: ((int, int, int)) => (float, float, float);
  let toHwb: ((int, int, int)) => (float, float, float);
  let toHex: ((int, int, int)) => string;
};

module Hsl: {
  let toRgb: ((int, int, int)) => (float, float, float);
  let toHsv: ((int, int, int)) => (float, float, float);
};

module Hsv: {
  let toRgb: ((int, int, int)) => (float, float, float);
  let toHsl: ((int, int, int)) => (float, float, float);
};

module Hex: {
  let toChunks: string => list(int);
  let toRgb: string => (float, float, float);
  let toHsl: string => (float, float, float);
};

let toHslAux: color => color;

let toHsl: option(color) => option(color);

let toRgbAux: color => color;

let toRgb: option(color) => option(color);

let toHexAux: color => color;

let toHex: option(color) => option(color);

let toHsvAux: color => color;

let toHsv: option(color) => option(color);

let opacity: (float, option(color)) => option(color);

let opaquer: (float, option(color)) => option(color);

let fade: (float, option(color)) => option(color);

let luminocityChannel: float => float;

let luminosityAux: ((int, int, int)) => float;

let luminosity: option(color) => option(float);

let contrastAux: (float, float) => float;

let contrast: (option(color), option(color)) => option(float);

let toString: option(color) => string;