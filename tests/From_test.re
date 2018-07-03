open Jest;

open Expect;

describe("From", () => {
  describe("hex", () => {
    test("6 char hex", () => {
      let converted = Color.fromHex("aaffaa") |> Belt.Option.getExn;
      let manual: Color.color = { value: (170.0, 255.0, 170.0), spec: Hex, opacity: 1.0}; 
      expect(converted) |> toEqual(manual);
    });
  	test("3 char hex", () => {
      let converted = Color.fromHex("afa") |> Belt.Option.getExn;
      let manual: Color.color = { value: (170.0, 255.0, 170.0), spec: Hex, opacity: 1.0}; 
      expect(converted) |> toEqual(manual);
    });
    test("3 char hex with pound sign", () => {
	    let converted = Color.fromHex("#afa") |> Belt.Option.getExn;
	    let manual: Color.color = { value: (170.0, 255.0, 170.0), spec: Hex, opacity: 1.0}; 
      expect(converted) |> toEqual(manual);
	  });
  });
});