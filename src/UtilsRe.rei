let where: (('a, 'a) => bool, Belt.List.t('a)) => 'a;

let min: Belt.List.t('a) => 'a;

let max: Belt.List.t('a) => 'a;

let repeatStringAux: (int, string, string) => string;

let repeatString: (int, string) => string;

let splitToChunksAux:
  (int, Js.String.t, list(Js.String.t)) => list(Js.String.t);

let splitToChunks: (int, string) => list(string);

let hexRe: Js.Re.t;

let hexStrToInt: string => int;

let toHex: int => string;

let hex3To6: Js.String.t => Js.String.t;

let hueToRgb: (float, float, float) => float;

let floated: ((int, int, int)) => (float, float, float);

let defloat: ((float, float, float)) => (int, int, int);

let inRangeOf: ('a, 'a, 'a) => 'a;