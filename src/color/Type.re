type spec =
  | Hex
  | Rgb
  | Hsl
  | Hsv;

type color = {
  value: (float, float, float),
  opacity: float,
  spec
};