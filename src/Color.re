
include Contents;

/*
include FromRe;
include ConvertRe;
*/
/*let inOpacityRange = Utils.inRangeOf(0.0, 1.0);*/

/*
 /* Modifiers */
 let opacity = (value, color) =>
   Option.map(color, color => {...color, opacity: inOpacityRange(value)});

 let opaquer = (ratio, color) =>
   Option.map(color, color =>
     {
       value: color.value,
       opacity: inOpacityRange(color.opacity +. color.opacity *. ratio)
     }
   );

 let fade = (ratio, color) =>
   Option.map(color, color =>
     {
       value: color.value,
       opacity: inOpacityRange(color.opacity -. color.opacity *. ratio)
     }
   );

 /* luminocity */
 let luminocityChannel = chan =>
   if (chan <= 0.03928) {
     chan /. 12.92;
   } else {
     /* Need this here because when put into one line formatter breaks the equation */
     let n1 = (chan +. 0.055) /. 1.055;
     n1 ** 2.4;
   };

 let luminosityAux = rgb => {
   let (r, g, b) = Utils.floated(rgb);
   let rLum = 0.2126 *. luminocityChannel(r /. 255.0);
   let gLum = 0.7152 *. luminocityChannel(g /. 255.0);
   let bLum = 0.0722 *. luminocityChannel(b /. 255.0);
   rLum +. gLum +. bLum;
 };

 /* http://www.w3.org/TR/WCAG20/#relativeluminancedef */
 let luminosity = color =>
   Option.map(toRgb(color), rgb =>
     switch rgb.value {
     | Rgb(r, g, b) => luminosityAux((r, g, b))
     | _ => 0.0
     }
   );

 /* Contrast */
 /* http://www.w3.org/TR/WCAG20/#contrast-ratiodef */
 let contrastAux = (lum1, lum2) =>
   if (lum1 > lum2) {
     (lum1 +. 0.05) /. (lum2 +. 0.05);
   } else {
     (lum2 +. 0.05) /. (lum1 +. 0.05);
   };

 let contrast = (color1, color2) =>
   switch (luminosity(color1)) {
   | None => None
   | Some(lum1) =>
     switch (luminosity(color2)) {
     | None => None
     | Some(lum2) => Some(contrastAux(lum1, lum2))
     }
   };

 /* YIQ equation from http://24ways.org/2010/calculating-color-contrast */
 let isDarkAux = (r, g, b) => {
   let yiq = (r * 299 + g * 587 + b * 114) / 1000;
   yiq < 128;
 };

 let isDark = color =>
   switch (toRgb(color)) {
   | Some(rgb) =>
     switch rgb.value {
     | Rgb(r, g, b) => Some(isDarkAux(r, g, b))
     | _ => None
     }
   | None => None
   };

 let isLight = color =>
   switch (isDark(color)) {
   | Some(resp) => Some(! resp)
   | None => None
   };

 /* Modifiers */
 let rec toString = color =>
   switch color {
   | None => ""
   | Some(color) =>
     switch color.value {
     | Rgb(r, g, b) =>
       Printf.sprintf("rgba(%d, %d, %d, %.2f)", r, g, b, color.opacity)
     | Hsl(h, s, l) =>
       Printf.sprintf("hsla(%d, %d%%, %d%%, %.2f)", h, s, l, color.opacity)
     | Hsv(h, s, v) =>
       Printf.sprintf("hsva(%d, %d%%, %d%%, %.2f)", h, s, v, color.opacity)
     | Hex(str) =>
       if (color.opacity == 1.0) {
         "#" ++ str;
       } else {
         toRgb(Some(color)) |> toString;
       }
     | _ => ""
     }
   }; */