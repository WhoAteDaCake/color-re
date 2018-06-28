# Reasonml color converter

Mainly inspired by [color](https://www.npmjs.com/package/color)

## Current color support

```ocaml
let fromHex: Js.String.t => option(color);

let fromRgba: ((int, int, int, float)) => option(color);

let fromRgb: ((int, int, int)) => option(color);

let fromHsla: ((int, int, int, float)) => option(color);

let fromHsl: ((int, int, int)) => option(color);

let fromHsv: ((int, int, int)) => option(color);
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

## Instalation

`yarn add color-re` or `npm install color-re`

And add package to `bsconfig.json`

```json
{
  "bs-dependencies": ["color-re"]
}
```
