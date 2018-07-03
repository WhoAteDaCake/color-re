
let toStringAux = (color: Type.color): string => {
  let (v1, v2, v3) = Utils.defloatedTuple(color.value);
  switch (color.spec) {
  | Rgb => Printf.sprintf("rgba(%d, %d, %d, %.2f)", v1, v2, v3, color.opacity)
  | _ => ""
  };
};

let toString = color =>
  switch (color) {
  | None => ""
  | Some(color) => toStringAux(color)
  };
  /*switch color {
  | None => ""
  | Some(color) =>
    switch color.value {
    | Rgb(r, g, b) =>
      Printf.sprintf("rgba(%d, %d, %d, %.2f)", r, g, b, color.opacity)
    | Hsl(h, s, l) =>
      Printf.sprintf("hsla(%d, %d%%, %d%%, %.2f)", h, s, l, color.opacity)
    | Hsv(h, s, v) =>
      Printf.sprintf("hsva(%d, %d%%, %d%%, %.2f)", h, s, v, color.opacity)
    | Hex(str) =>
      if (color.opacity == 1.0) {
        "#" ++ str;
      } else {
        toRgb(Some(color)) |> toString;
      }
    | _ => ""
    }
  };
  */