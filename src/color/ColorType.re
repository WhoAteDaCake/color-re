type spec =
  | Hex
  | Rgb
  | Hsl
  | Hsw
  | Hsv;

type color = {
  value: (float, float, float),
  opacity: float,
  spec
};