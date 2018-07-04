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
          fromRgb((200, 200, 200))
          |> opacity(0.5)
          |> opaquer(2.0)
          |> toString
        ),
      )
      |> toBe("rgba(200, 200, 200, 1.00)")
    );
    test("it should stay within bounds", () =>
      expect(Color.(fromRgb((200, 200, 200)) |> opaquer(2.0) |> toString))
      |> toBe("rgba(200, 200, 200, 1.00)")
    );
  });
  describe("negate", () => {
    test("it should negate colors", () =>
      expect(Color.(fromRgb((200, 200, 200)) |> negate |> toString))
      |> toBe("rgba(55, 55, 55, 1.00)")
    );
    test("it keep original color after negation", () =>
      expect(Color.(fromHsl((50, 70, 80)) |> negate |> toString))
      |> toBe("hsla(230, 70%, 19%, 1.00)")
    );
  });
  describe("lighten", () =>
    test("it should lighten colors", () =>
      expect(
        Color.(fromHsl((200, 50, 60)) |> lighten(0.5) |> getLightness)
        |> Belt.Option.getExn,
      )
      |> toEqual(90)
    )
  );
});
