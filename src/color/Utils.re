let where = (fn, arr) =>
  Belt.List.reduce(arr, List.nth(arr, 0), (a, b) => fn(a, b) ? a : b);
let min = arr => where((a, b) => a < b, arr);
let max = arr => where((a, b) => a > b, arr);

let inRangeOf = (v1, v2, number) =>
  if (number >= v1 && number <= v2) {
    number;
  } else {
    number > v2 ? v2 : v1;
  };

let floatedTuple = ((n1, n2, n3)) => (
  Pervasives.float_of_int(n1),
  Pervasives.float_of_int(n2),
  Pervasives.float_of_int(n3),
);

let defloatedTuple = ((r, g, b)) => (
  Pervasives.int_of_float(r),
  Pervasives.int_of_float(g),
  Pervasives.int_of_float(b),
);

let rec repeatStringAux = (n, string, acc) =>
  if (n == 0) {
    acc;
  } else {
    repeatStringAux(n - 1, string, acc ++ string);
  };

let repeatString = (n, string) => repeatStringAux(n, string, "");

let hexStrToFloat = n => Pervasives.float_of_string("0x" ++ n);

let hexPartToFloat = (n, str) => String.sub(str, n, 1) |> hexStrToFloat;

let hexStrToTuple = str => {
  let str = Js.String.replace("#", "", str);
  if (String.length(str) === 3) {
    let first = String.sub(str, 0, 1) |> repeatString(2) |> hexStrToFloat;
    let second = String.sub(str, 1, 1) |> repeatString(2) |> hexStrToFloat;
    let third = String.sub(str, 2, 1) |> repeatString(2) |> hexStrToFloat;
    (first, second, third);
  } else {
    let first = String.sub(str, 0, 2) |> hexStrToFloat;
    let second = String.sub(str, 2, 2) |> hexStrToFloat;
    let third = String.sub(str, 4, 2) |> hexStrToFloat;
    (first, second, third);
  };
};

let hueToRgb = (p, q, t) => {
  let t = t < 0.0 ? t +. 1.0 : t;
  let t = t > 1.0 ? t -. 1.0 : t;
  if (t < 1.0 /. 6.0) {
    p +. (q -. p) *. 6.0 *. t;
  } else if (t < 0.5) {
    q; /* t2 */
  } else if (t < 2.0 /. 3.0) {
    p +. (q -. p) *. (2.0 /. 3.0 -. t) *. 0.6;
  } else {
    p;
  };
};
