module Utils = UtilsRe;

type t = ColorType.color;


let toRgbAux = color => {
 let value = switch color.spec {
  | Hex => 
/* | Hex(hex) =>
   let (r, g, b) = Hex.toRgb(hex) |> Utils.defloat;
   {opacity: color.opacity, value: Rgb(r, g, b)};
 | Hsl(h, s, l) =>
   let (r, g, b) = Hsl.toRgb((h, s, l)) |> Utils.defloat;
   {opacity: color.opacity, value: Rgb(r, g, b)};
 | Hsv(h, s, v) =>
   let (r, g, b) = Hsv.toRgb((h, s, v)) |> Utils.defloat;
   {opacity: color.opacity, value: Rgb(r, g, b)};*/
 | _ => color
  };
  { opacity: color.opacity, spec: Rgb, value}
};

let toRgb = color => Option.map(color, toRgbAux);

/*
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
 let toHsv = rgb => {
   let (r, g, b) = Utils.floated(rgb);
   let r = r /. 255.0;
   let g = g /. 255.0;
   let b = b /. 255.0;
   let v = Utils.max([r, g, b]);
   let diff = v -. Utils.min([r, g, b]);
   if (diff == 0.0) {
     (0.0, 0.0, v);
   } else {
     let s = diff /. v;
     let diffc = c => (v -. c) /. 6.0 /. diff +. 1.0 /. 2.0;
     let rdif = diffc(r);
     let gdif = diffc(g);
     let bdif = diffc(b);
     let h =
       if (r == v) {
         bdif -. gdif;
       } else if (g == v) {
         1.0 /. 3.0 +. rdif -. bdif;
       } else {
         2.0 /. 3.0 +. gdif -. rdif;
       };
     let h =
       if (h < 0.0) {
         h +. 1.0;
       } else if (h > 1.0) {
         h -. 1.0;
       } else {
         h;
       };
     (h *. 360.0, s *. 100.0, v *. 100.0);
   };
 };
 let toHwb = ((rInt, gInt, bInt)) => {
   let (r, g, b) = Utils.floated((rInt, gInt, bInt));
   let (h, _s, _l) = toHsl((rInt, gInt, bInt));
   let w = 1.0 /. 255.0 *. Utils.min([r, g, b]);
   let b = 1.0 -. 1.0 /. 255.0 *. Utils.max([r, g, b]);
   (h, w *. 100.0, b *. 100.0);
 };
 let toHex = ((r, g, b)) =>
   Utils.toHex(r) ++ Utils.toHex(g) ++ Utils.toHex(b);
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
   /* Because of modulo will never be over 5, but to stop compiler warning we do this */
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
   (type t = ColorType.color;h, sl *. 100.0, 

    l *. 100.0);
 };
};

module Hex = {
 let toChunks = hex =>
   Utils.splitToChunks(2, hex) |> List.map(Utils.hexStrToInt);
 let toRgb = hex => {
   let [rHex, gHex, bHex] = toChunks(hex);
   Utils.floated((rHex, gHex, bHex));
 };
 let toHsl = hex => {
   let [rHex, gHex, bHex] = toChunks(hex);
   Rgb.toHsl((rHex, gHex, bHex));
 };
};

let toHslAux = color =>
 switch color.value {
 | Hex(hex) =>
   let (h, s, l) = Hex.toHsl(hex) |> Utils.defloat;
   {opacity: color.opacity, value: Hsl(h, s, l)};
 | Rgb(r, g, b) =>
   let (h, s, l) = Rgb.toHsl((r, g, b)) |> Utils.defloat;
   {opacity: color.opacity, value: Hsl(h, s, l)};
 | Hsv(h, s, v) =>
   let (h, s, l) = Hsv.toHsl((h, s, v)) |> Utils.defloat;
   {opacity: color.opacity, value: Hsl(h, s, l)};
 | _ => color
 };

let toHsl = color => Option.map(color, toHslAux);

let toRgbAux = color =>
 switch color.value {
 | Hex(hex) =>
   let (r, g, b) = Hex.toRgb(hex) |> Utils.defloat;
   {opacity: color.opacity, value: Rgb(r, g, b)};
 | Hsl(h, s, l) =>
   let (r, g, b) = Hsl.toRgb((h, s, l)) |> Utils.defloat;
   {opacity: color.opacity, value: Rgb(r, g, b)};
 | Hsv(h, s, v) =>
   let (r, g, b) = Hsv.toRgb((h, s, v)) |> Utils.defloat;
   {opacity: color.opacity, value: Rgb(r, g, b)};
 | _ => color
 };

let toRgb = color => Option.map(color, toRgbAux);

let toHexAux = color =>
 switch color.value {
 | Rgb(r, g, b) =>
   let value = Rgb.toHex((r, g, b));
   {opacity: color.opacity, value: Hex(value)};
 | Hsl(h, s, l) =>
   let value = Hsl.toRgb((h, s, l)) |> Utils.defloat |> Rgb.toHex;
   {opacity: color.opacity, value: Hex(value)};
 | Hsv(h, s, v) =>
   let value = Hsv.toRgb((h, s, v)) |> Utils.defloat |> Rgb.toHex;
   {opacity: color.opacity, value: Hex(value)};
 | _ => color
 };

let toHex = color => Option.map(color, toHexAux);

let toHsvAux = color =>
 switch color.value {
 | Rgb(r, g, b) =>
   let (h, s, v) = Rgb.toHsv((r, g, b)) |> Utils.defloat;
   {opacity: color.opacity, value: Hsv(h, s, v)};
 | Hsl(h, s, l) =>
   let (h, s, v) = Hsl.toHsv((h, s, l)) |> Utils.defloat;
   {opacity: color.opacity, value: Hsv(h, s, v)};
 | Hex(hex) =>
   let (h, s, v) =
     Hex.toRgb(hex) |> Utils.defloat |> Rgb.toHsv |> Utils.defloat;
   {opacity: color.opacity, value: Hsv(h, s, v)};
 | _ => color
 };

let toHsv = color => Option.map(color, toHsvAux);
*/