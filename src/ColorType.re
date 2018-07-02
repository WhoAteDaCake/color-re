type value =
  | Hex(string)
  | Rgb(int, int, int)
  | Hsl(int, int, int)
  | Hsw(int, int, int)
  | Hsv(int, int, int);

type spec =
  | Hex
  | Rgb
  | Hsl
  | Hsw
  | Hsv;

type color = {
  value,
  opacity: float,
  spec
};