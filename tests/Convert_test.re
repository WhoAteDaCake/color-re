open Jest;

open Expect;

describe("Convert", () => {
  describe("Rgb", () => {
    test("converting to rgb", () =>
      expect(Color.(fromRgb((200, 200, 200)) |> toRgb |> toString))
      |> toBe("rgba(200, 200, 200, 1.00)")
    );
    test("converting to hsl", () =>
      expect(Color.(fromRgb((200, 200, 200)) |> toHsl |> toString))
      |> toBe("hsla(0, 0%, 78%, 1.00)")
    );
    test("converting to hex", () =>
      expect(Color.(fromRgb((200, 200, 200)) |> toHex |> toString))
      |> toBe("#c8c8c8")
    );
    test("converting to hsv", () =>
      expect(Color.(fromRgb((100, 150, 200)) |> toHsv |> toString))
      |> toBe("hsva(209, 50%, 78%, 1.00)")
    );
  });
  describe("Hsl", () => {
    test("converting to rgb", () =>
      expect(Color.(fromHsl((50, 70, 80)) |> toRgb |> toString))
      |> toBe("rgba(239, 227, 168, 1.00)")
    );
    test("converting to hsl", () =>
      expect(Color.(fromHsl((50, 70, 80)) |> toHsl |> toString))
      |> toBe("hsla(50, 70%, 80%, 1.00)")
    );
    test("converting to hex", () =>
      expect(Color.(fromHsl((50, 70, 80)) |> toHex |> toString))
      |> toBe("#efe3a8")
    );
    test("converting to hsv", () =>
      expect(Color.(fromHsl((50, 70, 80)) |> toHsv |> toString))
      |> toBe("hsva(50, 29%, 94%, 1.00)")
    );
  });
  describe("Hsv", () => {
    test("converting to rgb", () =>
      expect(Color.(fromHsv((300, 60, 80)) |> toRgb |> toString))
      |> toBe("rgba(204, 81, 204, 1.00)")
    );
    test("converting to hsl", () =>
      expect(Color.(fromHsv((300, 60, 80)) |> toHsl |> toString))
      |> toBe("hsla(300, 54%, 55%, 1.00)")
    );
    test("converting to hex", () =>
      expect(Color.(fromHsv((300, 60, 80)) |> toHex |> toString))
      |> toBe("#cc51cc")
    );
    test("converting to hsv", () =>
      expect(Color.(fromHsv((300, 60, 80)) |> toHsv |> toString))
      |> toBe("hsva(300, 60%, 80%, 1.00)")
    );
  });
  describe("Hex", () => {
    test("converting to rgb", () =>
      expect(Color.(fromHex("ffeeff") |> toRgb |> toString))
      |> toBe("rgba(255, 238, 255, 1.00)")
    );
    test("converting to hsl", () =>
      expect(Color.(fromHex("aaffee") |> toHsl |> toString))
      |> toBe("hsla(168, 100%, 83%, 1.00)")
    );
    test("converting to hex", () =>
      expect(Color.(fromHex("aaffee") |> toHex |> toString))
      |> toBe("#aaffee")
    );
    test("converting to hsv", () =>
      expect(Color.(fromHex("aaffee") |> toHsv |> toString))
      |> toBe("hsva(168, 33%, 100%, 1.00)")
    );
  });
});
