# Reasonml color converter

```ocaml
Color.rgbToHsl(Some((0, 100, 50)))
  |> Color.hslToRgb
  |> Color.rgbToHex
  |> Color.hexToRgb
```

## Instalation

`yarn add color-re` or `npm install color-re`

And add package to `bsconfig.json`

```json
{
  "bs-dependencies": ["color-re"]
}
```
