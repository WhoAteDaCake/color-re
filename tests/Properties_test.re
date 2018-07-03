open Jest;

open Expect;

describe("Properties", () => {
  describe("luminosity", () =>
   test("it should calculate luminosity", () => {
     let luminosity =
       Color.(fromRgb((200, 200, 200)) |> luminosity) |> Belt.Option.getExn;
     expect(luminosity) |> toEqual(0.5775804404296506);
   })
 );
 describe("contrast", () =>
   test("it should calculate contrast", () => {
     let contrast =
       Color.(fromRgb((200, 200, 200)) |> contrast(fromRgb((100, 100, 100))))
       |> Belt.Option.getExn;
     expect(contrast) |> toEqual(3.53690624724583);
   })
 );

 describe("isDark", () => {
   test("it should calculate whether color is not dark", () => {
     let isDark =
       Color.(fromRgb((200, 200, 200)) |> isDark) |> Belt.Option.getExn;
     expect(isDark) |> toBe(false);
   });
   test("it should calculate whether color is dark", () => {
     let isDark =
       Color.(fromRgb((100, 50, 200)) |> isDark) |> Belt.Option.getExn;
     expect(isDark) |> toBe(true);
   });
 });
 describe("isLight", () => {
   test("it should calculate whether color is light", () => {
     let isDark =
       Color.(fromRgb((200, 200, 200)) |> isLight) |> Belt.Option.getExn;
     expect(isDark) |> toBe(true);
   });
   test("it should calculate whether color is not light", () => {
     let isDark =
       Color.(fromRgb((100, 50, 200)) |> isLight) |> Belt.Option.getExn;
     expect(isDark) |> toBe(false);
   });
 });
});