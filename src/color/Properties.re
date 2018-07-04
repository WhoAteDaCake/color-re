let luminocityChannel = chan =>
  if (chan <= 0.03928) {
    chan /. 12.92;
  } else {
    /* Need this here because when put into one line formatter breaks the equation */
    let n1 = (chan +. 0.055) /. 1.055;
    n1 ** 2.4;
  };

let luminosityAux = (color: Type.color) : float => {
  let (r, g, b) = color.value;
  let rLum = 0.2126 *. luminocityChannel(r /. 255.0);
  let gLum = 0.7152 *. luminocityChannel(g /. 255.0);
  let bLum = 0.0722 *. luminocityChannel(b /. 255.0);
  rLum +. gLum +. bLum;
};

/* http://www.w3.org/TR/WCAG20/#relativeluminancedef */
let luminosity = color =>
  Belt.Option.map(Convert.toRgb(color), luminosityAux);

let contrastAux = (lum1, lum2) =>
  if (lum1 > lum2) {
    (lum1 +. 0.05) /. (lum2 +. 0.05);
  } else {
    (lum2 +. 0.05) /. (lum1 +. 0.05);
  };

/* http://www.w3.org/TR/WCAG20/#contrast-ratiodef */
let contrast = (color1, color2) =>
  switch (luminosity(color1)) {
  | None => None
  | Some(lum1) =>
    switch (luminosity(color2)) {
    | None => None
    | Some(lum2) => Some(contrastAux(lum1, lum2))
    }
  };

let isDarkAux = (color: Type.color) : bool => {
  let (r, g, b) = color.value;
  let yiq = (r *. 299.0 +. g *. 587.0 +. b *. 114.0) /. 1000.0;
  yiq < 128.0;
};

/* YIQ equation from http://24ways.org/2010/calculating-color-contrast */
let isDark = color => Belt.Option.map(Convert.toRgb(color), isDarkAux);

let isLight = color => Belt.Option.map(isDark(color), resp => ! resp);

let getOpacityAux = (color: Type.color) : float => color.opacity;

let getOpacity = color => Belt.Option.map(color, getOpacityAux);

let getHueAux = (color: Type.color) : int => {
  let (h, _s, _l) = Convert.toHslAux(color).value;
  int_of_float(h);
};

let getHue = color => Belt.Option.map(color, getHueAux);

let getLightnessAux = (color: Type.color) : int => {
  let (_h, _s, l) = Convert.toHslAux(color).value;
  int_of_float(l);
};

let getLightness = color => Belt.Option.map(color, getLightnessAux);
