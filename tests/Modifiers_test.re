open Jest;

open Expect;

describe("Modifiers", () => {
 describe("opacity", () => {
   test("it should set opacity", () =>
     expect(Color.(fromRgb((200, 200, 200)) |> opacity(0.5) |> toString))
     |> toBe("rgba(200, 200, 200, 0.50)")
   );
   test("it should stay within bounds", () => {
     expect(Color.(fromRgb((200, 200, 200)) |> opacity(1.5) |> toString))
     |> toBe("rgba(200, 200, 200, 0.00)")
     |> ignore;
     expect(Color.(fromRgb((200, 200, 200)) |> opacity(-2.0) |> toString))
     |> toBe("rgba(200, 200, 200, 0.00)");
   });
 });
 describe("fade", () => {
   test("it should fade opacity", () =>
     expect(Color.(fromRgb((200, 200, 200)) |> fade(0.5) |> toString))
     |> toBe("rgba(200, 200, 200, 0.50)")
   );
   test("it should stay within bounds", () =>
     expect(Color.(fromRgb((200, 200, 200)) |> fade(1.5) |> toString))
     |> toBe("rgba(200, 200, 200, 0.00)")
   );
 });
 describe("opaquer", () => {
   test("it should increase opacity", () =>
     expect(
       Color.(
         fromRgb((200, 200, 200)) |> opacity(0.5) |> opaquer(2.0) |> toString
       )
     )
     |> toBe("rgba(200, 200, 200, 1.00)")
   );
   test("it should stay within bounds", () =>
     expect(Color.(fromRgb((200, 200, 200)) |> opaquer(2.0) |> toString))
     |> toBe("rgba(200, 200, 200, 1.00)")
   );
 });
});