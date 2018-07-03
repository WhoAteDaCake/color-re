module Option = Belt.Option;

module Hsv = {
  let toRgb = ((h , s, v)) => {
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
  let toHsl = ((h, s, v)) => {
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

module Hsl = {
 let toRgb = ((h, s, l)) => {
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
};

let toRgbAux = (color: Type.color): Type.color => {
  let value = switch color.spec {
    | Hex => color.value
    | Rgb => color.value
    | Hsl => Hsl.toRgb(color.value)
    | Hsv => Hsv.toRgb(color.value)
  };
  { opacity: color.opacity, spec: Rgb, value }
};

let toRgb = color => Option.map(color, toRgbAux);