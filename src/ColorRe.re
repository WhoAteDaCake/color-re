let hexRe = [%bs.re "/^#?([a-f\\d]{2})([a-f\\d]{2})([a-f\\d]{2})$/i"];

let hexStrToInt = n => Pervasives.int_of_string("0x" ++ n);

let where = (fn, arr) =>
  Belt.List.reduce(arr, List.nth(arr, 0), (a, b) => fn(a, b) ? a : b);

let min = arr => where((a, b) => a < b, arr);

let max = arr => where((a, b) => a > b, arr);

let toHex = c => {
  let str = Printf.sprintf("%x", c);
  if (String.length(str) == 1) {
    "0" ++ str;
  } else {
    str;
  };
};

let nullableArrayToList = nArray =>
  Js.Array.reduceRight(
    (arr, s) =>
      switch (Js.Nullable.toOption(s)) {
      | None => arr
      | Some(x) => [x, ...arr]
      },
    [],
    nArray
  );

let hueToRgb = (p, q, t) => {
  let t = t < 0.0 ? t +. 1.0 : t;
  let t = t > 1.0 ? t -. 1.0 : t;
  if (t < 1.0 /. 6.0 /* 1/6 */) {
    p +. (q -. p) *. 6.0 *. t;
  } else if (t < 0.5 /* 1/2 */) {
    q;
  } else if (t < 2.0 /. 3.0 /* 2/3 */) {
    p +. (q -. p) *. (2.0 /. 3.0 -. t) *. 0.6;
  } else {
    p;
  };
};

let rgbToHex = rgb =>
  switch rgb {
  | None => None
  | Some((r, g, b)) => Some("#" ++ toHex(r) ++ toHex(g) ++ toHex(b))
  };

let hexToRgb = hexOpt =>
  switch hexOpt {
  | None => None
  | Some(hex) =>
    switch (Js.Re.exec(hex, hexRe)) {
    | Some(results) =>
      let rgb =
        Js.Re.captures(results)
        |> Js.Array.sliceFrom(1) /* Removes total match */
        |> nullableArrayToList
        |> List.map(hexStrToInt);
      if (List.length(rgb) == 3) {
        Some((List.nth(rgb, 0), List.nth(rgb, 1), List.nth(rgb, 2)));
      } else {
        None;
      };
    | None => None
    }
  };

let rgbToHsl = rgbOpt =>
  switch rgbOpt {
  | None => None
  | Some((r1, g1, b1)) =>
    let rgb = [r1, g1, b1] |> List.map(n => float_of_int(n) /. 255.0);
    let [r, g, b] = rgb;
    let mx = max(rgb);
    let mn = min(rgb);
    let l = (mx +. mn) /. 2.0;
    let (h, s) =
      if (mx == mn) {
        (0.0, 0.0);
      } else {
        let d = mx -. mn;
        let s = l > 0.5 ? d /. (2.0 -. mx -. mn) : d /. (mx +. mn);
        let h =
          if (r > g && r > b) {
            (g -. b) /. d +. (g < b ? 6.0 : 0.0);
          } else if (g > b) {
            (b -. r) /. d +. 2.0;
          } else {
            (r -. g) /. d +. 4.0;
          };
        (h /. 6.0, s);
      };
    Some((
      Pervasives.int_of_float(h *. 360.0),
      Pervasives.int_of_float(s *. 100.0),
      Pervasives.int_of_float(l *. 100.0)
    ));
  };

let rgbaToHsla = rgbaOpt =>
  switch rgbaOpt {
  | None => None
  | Some((r, g, b, a)) =>
    Belt.Option.map(rgbToHsl(Some((r, g, b))), (h, s, l) => Some((h, s, l, a)))
  };

let hslToRgb = hslOpt =>
  switch hslOpt {
  | None => None
  | Some((h1, s1, l1)) =>
    let h = Pervasives.float_of_int(h1) /. 360.0;
    let s = Pervasives.float_of_int(s1) /. 100.0;
    let l = Pervasives.float_of_int(l1) /. 100.0;
    let (r, g, b) =
      if (s == 0.0) {
        (l, l, l);
      } else {
        let q = l < 0.5 ? l *. (1.0 +. s) : l +. s -. l *. s;
        let p = 2.0 *. l -. q;
        (
          hueToRgb(p, q, h +. 1.0 /. 3.0),
          hueToRgb(p, q, h),
          hueToRgb(p, q, h -. 1.0 /. 3.0)
        );
      };
    Some((
      Pervasives.int_of_float(r *. 250.0),
      Pervasives.int_of_float(g *. 250.0),
      Pervasives.int_of_float(b *. 250.0)
    ));
  };