type t = ColorType.color;

let fromHex = hex => {
  let spec: t = {value: Hex(UtilsRe.hex3To6(hex)), opacity: 1.0, spec: Hex};
  Some(spec);
};

let fromRgba = ((r, g, b, a)) => {
  let spec: t = {value: Rgb(r, g, b), opacity: a, spec: Rgb};
  Some(spec);
};

let fromRgb = ((r, g, b)) => fromRgba((r, g, b, 1.0));

let fromHsla = ((h, s, l, a)) => {
  let spec: t = {value: Hsl(h, s, l), opacity: a, spec: Hsl};
  Some(spec);
};

let fromHsl = ((h, s, l)) => fromHsla((h, s, l, 1.0));

let fromHsv = ((h, s, v)) => {
  let spec: t = {value: Hsv(h, s, v), opacity: 1.0, spec: Hsv};
  Some(spec);
};