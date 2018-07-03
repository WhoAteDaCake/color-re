let fromHex = hex => {
  let spec: Type.color = {value: Utils.hexStrToTuple(hex), opacity: 1.0, spec: Hex};
  Some(spec);
};

let fromRgba = (value, opacity) => {
  let spec: Type.color = {value: Utils.floatedTuple(value), opacity, spec: Rgb};
  Some(spec);
};

let fromRgb = (value) => fromRgba(value, 1.0);

let fromHsla = (value, opacity) => {
  let spec: Type.color = {value: Utils.floatedTuple(value), opacity, spec: Hsl};
  Some(spec);
};

let fromHsl = (value) => fromHsla(value, 1.0);

let fromHsv = (value) => {
  let spec: Type.color = {value: Utils.floatedTuple(value), opacity: 1.0, spec: Hsv};
  Some(spec);
};