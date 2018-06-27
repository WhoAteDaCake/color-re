module Utils = UtilsRe;

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

/* Converter */
let fromHex = hex => Some({value: Hex(Utils.hex3To6(hex)), opacity: 1.0});

let fromRgba = ((r, g, b, a)) => Some({value: Rgb(r, g, b), opacity: a});

let fromRgb = ((r, g, b)) => fromRgba((r, g, b, 1.0));

let fromHsla = ((h, s, l, a)) => Some({value: Hsl(h, s, l), opacity: a});

let fromHsl = ((h, s, l)) => fromHsla((h, s, l, 1.0));

let fromHsv = ((h, s, v)) => Some({value: Hsv(h, s, v), opacity: 1.0});

module Rgb = {
  let toHsl = rgb => {
    let (r, g, b) = Utils.floated(rgb);
    let r = r /. 255.0;
    let g = g /. 255.0;
    let b = b /. 255.0;
    let max = Utils.max([r, g, b]);
    let min = Utils.min([r, g, b]);
    let delta = max -. min;
    let h =
      if (max == min) {
        0.0;
      } else if (r == max) {
        (g -. b) /. delta;
      } else if (g == max) {
        2.0 +. (b -. r) /. delta;
      } else {
        4.0 +. (r -. g) /. delta;
      };
    let h = Utils.min([h *. 60.0, 360.0]);
    let h = h < 0.0 ? h +. 360.0 : h;
    let l = (min +. max) /. 2.0;
    let s =
      if (max == min) {
        0.0;
      } else if (l <= 0.5) {
        delta /. (max +. min);
      } else {
        delta /. (2.0 -. max -. min);
      };
    (h, s *. 100.0, l *. 100.0);
  };
  let toHwb = ((rInt, gInt, bInt)) => {
    let (r, g, b) = Utils.floated((rInt, gInt, bInt));
    let (h, _s, _l) = toHsl((rInt, gInt, bInt));
    let w = 1.0 /. 255.0 *. Utils.min([r, g, b]);
    let b = 1.0 -. 1.0 /. 255.0 *. Utils.max([r, g, b]);
    (h, w *. 100.0, b *. 100.0);
  };
  let toHex = ((r, g, b)) =>
    "#" ++ Utils.toHex(r) ++ Utils.toHex(g) ++ Utils.toHex(b);
};

module Hsl = {
  let toRgb = hsl => {
    let (h, s, l) = Utils.floated(hsl);
    let h = h /. 360.0;
    let s = s /. 100.0;
    let l = l /. 100.0;
    if (s == 0.0) {
      let tmp = l *. 255.0;
      (tmp, tmp, tmp);
    } else {
      let q = l < 0.5 ? l *. (1.0 +. s) : l +. s -. l *. s;
      let p = 2.0 *. l -. q;
      (
        Utils.hueToRgb(p, q, h +. 1.0 /. 3.0) *. 255.0,
        Utils.hueToRgb(p, q, h) *. 255.0,
        Utils.hueToRgb(p, q, h -. 1.0 /. 3.0) *. 255.0
      );
    };
  };
  let toHsv = hsl => {
    let (h, s, l) = Utils.floated(hsl);
    let s = s /. 100.0;
    let l = l /. 100.0;
    let smin = s;
    let lmin = Utils.min([l, 0.01]);
    /* Calcs */
    let l = l *. 2.0;
    let s = s *. (l <= 1.0 ? l : 2.0 -. l);
    let smin = smin *. (lmin <= 1.0 ? lmin : 2.0 -. lmin);
    let v = (l +. s) /. 2.0;
    let sv = l == 0.0 ? 2.0 *. smin /. (lmin +. smin) : 2.0 *. s /. (l +. s);
    (h, sv *. 100.0, v *. 100.0);
  };
};

module Hsv = {
  let toRgb = hsv => {
    let (h, s, v) = Utils.floated(hsv);
    let h = h /. 60.0;
    let s = s /. 100.0;
    let v = v /. 100.0;
    let hi = mod_float(h, 6.0) |> int_of_float;
    let f = h -. floor(h);
    let p = 255.0 *. v *. (1.0 -. s);
    let q = 255.0 *. v *. (1.0 -. s *. f);
    let t = 255.0 *. v *. (1.0 -. s *. (1.0 -. f));
    let v = v *. 255.0;
    switch hi {
    | 0 => (v, t, p)
    | 1 => (q, v, p)
    | 2 => (p, v, t)
    | 3 => (p, q, v)
    | 4 => (t, p, v)
    /* Because of module will never be over 5, but to stop compiler warning we do this */
    | _ => (v, p, q)
    };
  };
  let toHsl = hsv => {
    let (h, s, v) = Utils.floated(hsv);
    let s = s /. 100.0;
    let v = v /. 100.0;
    let vmin = Utils.max([v, 0.01]);
    let l = (2.0 -. s) *. v;
    let lmin = (2.0 -. s) *. vmin;
    let sl = s *. vmin;
    let sl = sl /. (lmin <= 1.0 ? lmin : 2.0 -. lmin);
    let l = l /. 2.0;
    (h, sl *. 100.0, l *. 100.0);
  };
};

/* module Hsw => {
     let toHsl = (color, (h, s, w)) => {
       {
         value:
           Hsl(
             Pervasives.int_of_float(h),
             Pervasives.int_of_float(s *. 100.0),
             Pervasives.int_of_float(l *. 100.0)
           ),
         opacity: color.opacity
       };
     };
   }; */
let toHslAux = color =>
  switch color.value {
  | Rgb(r, g, b) =>
    let (h, s, l) = Rgb.toHsl((r, g, b)) |> Utils.defloat;
    {opacity: color.opacity, value: Hsl(h, s, l)};
  | Hsl(_h, _s, _l) => color
  | _ => color
  };

let toHsl = color => Belt.Option.map(color, toHslAux);

/* Modifiers */
let opaquer = (ratio, color) =>
  switch color {
  | Some(color) => Some({value: color.value, opacity: color.opacity *. ratio})
  | None => None
  };

let fade = (ratio, color) =>
  switch color {
  | Some(color) => Some({value: color.value, opacity: color.opacity *. ratio})
  | None => None
  };

let toString = color =>
  switch color {
  | None => ""
  | Some(color) =>
    switch color.value {
    | Rgb(r, g, b) =>
      Printf.sprintf("rgba(%d, %d, %d, %f)", r, g, b, color.opacity)
    | Hsl(h, s, l) =>
      Printf.sprintf("hsl(%d, %d, %d, %.2f)", h, s, l, color.opacity)
    | Hex(str) =>
      if (color.opacity == 1.0) {
        str;
      } else {
        "";
      }
    | _ => ""
    }
  };