let inOpacityRange = Utils.inRangeOf(0.0, 1.0);

let opacityAux = (value: float, color: Type.color): Type.color => {
  ...color,
  opacity: inOpacityRange(value)
};
let opacity = (value, color) =>
  Belt.Option.map(color, opacityAux(value));

let opaquerAux = (ratio: float, color: Type.color): Type.color =>
  opacityAux(color.opacity +. color.opacity *. ratio, color);

let opaquer = (ratio, color) =>
  Belt.Option.map(color, opaquerAux(ratio));

let fadeAux = (ratio: float, color: Type.color): Type.color =>
  opacityAux(color.opacity -. color.opacity *. ratio, color);

let fade = (ratio, color) =>
  Belt.Option.map(color, fadeAux(ratio));