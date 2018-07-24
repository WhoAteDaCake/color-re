# Reasonml color converter

Reasonml port of [color](https://www.npmjs.com/package/color) fully written in reasonml

## Instalation

`yarn add color-re` or `npm install color-re`

And add package to `bsconfig.json`

```json
{
  "bs-dependencies": ["color-re"]
}
```

## Examples

```ocaml
/* Change the opacity */
Color.(fromRgb((200, 200, 200)) |> opacity(1.5) |> toString) |> Js.log
Color.(fromRgb((200, 200, 200)) |> toHsl |> fade(0.5) |> toString) |> Js.log
Color.(fromRgb((200, 200, 200)) |> toHsl |> opaquer(0.4) |> toString) |> Js.log

/* Color convertions */
Color.(fromRgb((200, 200, 200)) |> toHex |> toHsl |> toHsv |> toString) |> Js.log

/* Color properties */
Color.(fromRgb((200, 200, 200)) |> luminosity) |> Belt.Option.getExn |> Js.log
Color.(fromRgb((200, 200, 200)) |> contrast(fromHex("#aaafff"))) |> Belt.Option.getExn |> Js.log
```

## Features

Pretty much every function has `Aux` caunterpart, which will work on pure `color` type.

### Creation

Supported interfaces for creating `color` type

```ocaml
let fromHex: Js.String.t => option(Type.color); /* Can take in formats of #aaa #aaaaaa */
let fromRgba: ((int, int, int), float) => option(Type.color);
let fromRgb: ((int, int, int)) => option(Type.color);
let fromHsla: ((int, int, int), float) => option(Type.color);
let fromHsl: ((int, int, int)) => option(Type.color);
let fromHsv: ((int, int, int)) => option(Type.color);
```

### Convertion

Supported interfaces from converting colors to different types.
Each convertion function can take `color` type.

```ocaml
let toRgb: option(Type.color) => option(Type.color);
let toHsl: option(Type.color) => option(Type.color);
let toHex: option(Type.color) => option(Type.color);
let toHsv: option(Type.color) => option(Type.color);
```

### Output

There currently is a single function for formatting the color
If it receives `None` value it will return string `"Failed"`

```ocaml
let toString: option(Type.color) => string;
```

### Modifiers

Support functions for modifying the colors.
Can take any `color` type and will convert it back to original once modification is applied

```ocaml
let opacity: (float, option(Type.color)) => option(Type.color);
let opaquer: (float, option(Type.color)) => option(Type.color);
let fade: (float, option(Type.color)) => option(Type.color);
let negate: option(Type.color) => option(Type.color);
let lighten: (float, option(Type.color)) => option(Type.color);
let darken: (float, option(Type.color)) => option(Type.color);
let saturate: (float, option(Type.color)) => option(Type.color);
let desaturate: (float, option(Type.color)) => option(Type.color);
let grayscale: option(Type.color) => option(Type.color);
let rotate: (int, option(Type.color)) => option(Type.color);
```

### Properties

Supported ways of retrieving color properties

```ocaml
let luminocityChannel: float => float;
let luminosity: option(Type.color) => option(float);
let contrast: (option(Type.color), option(Type.color)) => option(float);
let isDark: option(Type.color) => option(bool);
let isLight: option(Type.color) => option(bool);
let getOpacity: option(Type.color) => option(float);
let getHue: option(Type.color) => option(int);
let getLightness: option(Type.color) => option(int);
let getSaturation: option(Type.color) => option(int);
```
