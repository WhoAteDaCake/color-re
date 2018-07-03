
let toStringAux = (color: Type.color): string => {
  let (v1, v2, v3) = Utils.defloatedTuple(color.value);
  switch (color.spec) {
  | Hex => Printf.sprintf("#%x%x%x", v1, v2, v3)
  | Rgb => Printf.sprintf("rgba(%d, %d, %d, %.2f)", v1, v2, v3, color.opacity)
  | Hsl => Printf.sprintf("hsla(%d, %d%%, %d%%, %.2f)", v1, v2, v3, color.opacity)
  | Hsv => Printf.sprintf("hsva(%d, %d%%, %d%%, %.2f)", v1, v2, v3, color.opacity)
  };
};

let toString = color =>
  switch (color) {
  | None => "Failed"
  | Some(color) => toStringAux(color)
  };