open Jest;

open Expect;

describe("Color", () => {
  describe("Rgb", () =>
    test("converting to hsl", () =>
      expect(Color.(fromRgb((200, 200, 200)) |> toHsl |> toString))
      |> toBe("hsla(0, 0%, 78%, 1.00)")
    )
  );
  describe("Hsl", () =>
    test("converting to hsl", () =>
      expect(Color.(fromHsl((50, 70, 80)) |> toHsl |> toString))
      |> toBe("hsla(50, 70%, 80%, 1.00)")
    )
  );
  describe("Hsv", () =>
    test("converting to hsl", () =>
      expect(Color.(fromHsv((300, 60, 80)) |> toHsl |> toString))
      |> toBe("hsla(300, 54%, 55%, 1.00)")
    )
  );
  describe("Hex", () =>
    test("converting to hsl", () =>
      expect(Color.(fromHex("aaffee") |> toHsl |> toString))
      |> toBe("hsla(168, 100%, 83%, 1.00)")
    )
  );
});