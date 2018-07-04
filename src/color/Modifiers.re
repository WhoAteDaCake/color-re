let inOpacityRange = Utils.inRangeOf(0.0, 1.0);

let hslModifier = (modifier, color: Type.color) : Type.color => {
  let newColor = Convert.toHslAux(color);
  let (h, s, l) = newColor.value;
  let modified = {...newColor, value: modifier(h, s, l)};

  switch (color.spec) {
  | Hex => Convert.toHexAux(modified)
  | Rgb => Convert.toRgbAux(modified)
  | Hsl => modified
  | Hsv => Convert.toHsvAux(modified)
  };
};

let rgbModifer = (modifier, color: Type.color) : Type.color => {
  let newColor = Convert.toRgbAux(color);
  let (r, g, b) = newColor.value;
  let negatedColor = {...newColor, value: modifier(r, g, b)};

  switch (color.spec) {
  | Hex => Convert.toHexAux(negatedColor)
  | Rgb => negatedColor
  | Hsl => Convert.toHslAux(negatedColor)
  | Hsv => Convert.toHsvAux(negatedColor)
  };
};

let opacityAux = (value: float, color: Type.color) : Type.color => {
  ...color,
  opacity: inOpacityRange(value),
};

let opacity = (value, color) => Belt.Option.map(color, opacityAux(value));

let opaquerAux = (ratio: float, color: Type.color) : Type.color =>
  opacityAux(color.opacity +. color.opacity *. ratio, color);

let opaquer = (ratio, color) => Belt.Option.map(color, opaquerAux(ratio));

let fadeAux = (ratio: float, color: Type.color) : Type.color =>
  opacityAux(color.opacity -. color.opacity *. ratio, color);

let fade = (ratio, color) => Belt.Option.map(color, fadeAux(ratio));

let negate = color =>
  Belt.Option.map(
    color,
    rgbModifer((r, g, b) => (255.0 -. r, 255.0 -. g, 255.0 -. b)),
  );

let lighten = (ratio, color) =>
  Belt.Option.map(color, hslModifier((h, s, l) => (h, s, l +. l *. ratio)));

let darken = (ratio, color) =>
  Belt.Option.map(color, hslModifier((h, s, l) => (h, s, l -. l *. ratio)));

let saturate = (ratio, color) =>
  Belt.Option.map(color, hslModifier((h, s, l) => (h, s +. s *. ratio, l)));

let desaturate = (ratio, color) =>
  Belt.Option.map(color, hslModifier((h, s, l) => (h, s -. s *. ratio, l)));

/* http://en.wikipedia.org/wiki/Grayscale#Converting_color_to_grayscale */
let grayscale = color =>
  Belt.Option.map(
    color,
    rgbModifer((r, g, b) => {
      let value = r *. 0.3 +. g *. 0.59 +. b *. 0.11;
      (value, value, value);
    }),
  );

let rotate = (degrees, color) =>
  Belt.Option.map(
    color,
    hslModifier((h, s, l) => {
      let hue = mod_float(h +. float_of_int(degrees), 360.0);
      let hue = hue < 0.0 ? 360.0 +. hue : hue;
      (hue, s, l);
    }),
  );
