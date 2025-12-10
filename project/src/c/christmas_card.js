// Christmas Card Border Animation
// Decorative frame with bells, holly leaves, and berries
// Center area left empty for adding an image

function processLine(time) {
  // 8 second loop animation
  if (time > 8.0) return "";

  var width = 800;
  var height = 600;
  var centerX = width / 2;
  var centerY = height / 2;

  var xml = "";

  // === Background - Clean white ===
  xml += '<View width="100%" height="100%" background-color="#FFFFFF">';

  // === Holly Leaves Function - Using SVG Path ===
  function drawHollyLeaf(x, y, angle, scale, opacity) {
    // Realistic holly leaf with spiky edges using SVG path
    var leafColor = "rgba(34,139,34," + opacity + ")"; // Forest green
    var darkLeaf = "rgba(0,100,0," + opacity + ")"; // Darker for vein

    // Holly leaf path - classic spiky holly shape (fits in ~24x14 box)
    // Has 5 pointed lobes on each side like real holly
    var hollyPath =
      "M12 0 " + // Start at top center
      "C14 0 15 1 17 0 " + // Small bump to first spike
      "L20 3 L17 4 " + // First right spike
      "L21 6 L18 7 " + // Second right spike
      "L22 9 L19 10 " + // Third right spike
      "L21 12 L17 12 " + // Fourth right spike
      "L18 14 L12 14 " + // Tip and bottom right
      "L6 14 L7 12 " + // Bottom left start
      "L3 12 L5 10 " + // Fourth left spike
      "L2 9 L6 7 " + // Third left spike
      "L3 6 L7 4 " + // Second left spike
      "L4 3 L7 0 " + // First left spike
      "C9 1 10 0 12 0 Z"; // Close back to top

    var leafXml = "";
    var leafWidth = 24 * scale;
    var leafHeight = 16 * scale;

    // For rotation, we'll position leaves at different angles by offsetting
    var offsetX = Math.cos(angle) * 5 * scale;
    var offsetY = Math.sin(angle) * 5 * scale;

    // Main leaf shape
    leafXml +=
      '<View left="' +
      (x - leafWidth / 2 + offsetX) +
      '" top="' +
      (y - leafHeight / 2 + offsetY) +
      '" ' +
      'width="' +
      leafWidth +
      '" height="' +
      leafHeight +
      '" ' +
      'background-color="' +
      leafColor +
      '" ' +
      'path="' +
      hollyPath +
      '"/>';

    // Center vein line
    leafXml +=
      '<View left="' +
      (x - leafWidth / 3 + offsetX) +
      '" top="' +
      (y - 1 + offsetY) +
      '" ' +
      'width="' +
      leafWidth * 0.7 +
      '" height="2" ' +
      'background-color="' +
      darkLeaf +
      '" border-radius="1"/>';

    return leafXml;
  }

  // === Holly Berry Function ===
  function drawBerry(x, y, scale, opacity) {
    var berrySize = 8 * scale;
    var berryColor = "rgba(220,20,60," + opacity + ")"; // Crimson
    var highlight = "rgba(255,100,100," + opacity * 0.6 + ")";

    var berryXml = "";

    // Main berry
    berryXml +=
      '<View left="' +
      (x - berrySize / 2) +
      '" top="' +
      (y - berrySize / 2) +
      '" ' +
      'width="' +
      berrySize +
      '" height="' +
      berrySize +
      '" ' +
      'background-color="' +
      berryColor +
      '" border-radius="50%"/>';

    // Highlight
    berryXml +=
      '<View left="' +
      (x - berrySize / 4) +
      '" top="' +
      (y - berrySize / 3) +
      '" ' +
      'width="' +
      berrySize / 3 +
      '" height="' +
      berrySize / 3 +
      '" ' +
      'background-color="' +
      highlight +
      '" border-radius="50%"/>';

    return berryXml;
  }

  // === Christmas Ornament/Bauble Function ===
  function drawOrnament(x, y, scale, swingAngle, color1, color2, decorType) {
    var ornXml = "";
    var swingOffset = Math.sin(swingAngle) * 8 * scale;
    var ornSize = 70 * scale;

    // Hanging string
    var stringColor = "rgba(180,160,100,0.9)";
    ornXml +=
      '<View left="' +
      (x - 1 + swingOffset * 0.3) +
      '" top="' +
      (y - 30 * scale) +
      '" ' +
      'width="2" height="' +
      35 * scale +
      '" ' +
      'background-color="' +
      stringColor +
      '"/>';

    // Gold cap at top
    var capWidth = 16 * scale;
    var capHeight = 12 * scale;
    ornXml +=
      '<View left="' +
      (x - capWidth / 2 + swingOffset * 0.5) +
      '" top="' +
      (y - 5 * scale) +
      '" ' +
      'width="' +
      capWidth +
      '" height="' +
      capHeight +
      '" ' +
      'background-color="#B8860B" border-radius="3"/>';

    // Cap ring
    ornXml +=
      '<View left="' +
      (x - 6 * scale + swingOffset * 0.3) +
      '" top="' +
      (y - 10 * scale) +
      '" ' +
      'width="' +
      12 * scale +
      '" height="' +
      8 * scale +
      '" ' +
      'border-color="#DAA520" border-width="2" border-radius="50%"/>';

    // Main ornament ball
    ornXml +=
      '<View left="' +
      (x - ornSize / 2 + swingOffset) +
      '" top="' +
      (y + 5 * scale) +
      '" ' +
      'width="' +
      ornSize +
      '" height="' +
      ornSize +
      '" ' +
      'radial-gradient="' +
      color1 +
      ", " +
      color2 +
      '" ' +
      'border-radius="50%"/>';

    // Decorative pattern based on type
    if (decorType === "stripes") {
      // Curved stripe lines (like on the red ornament)
      for (var s = 0; s < 4; s++) {
        var stripeX = x - ornSize * 0.3 + s * ornSize * 0.2 + swingOffset;
        ornXml +=
          '<View left="' +
          stripeX +
          '" top="' +
          (y + 15 * scale) +
          '" ' +
          'width="3" height="' +
          ornSize * 0.7 +
          '" ' +
          'background-color="rgba(255,255,255,0.3)" border-radius="2"/>';
      }
    } else if (decorType === "lines") {
      // Vertical thin lines (like on the gold ornament)
      for (var s = 0; s < 6; s++) {
        var lineX = x - ornSize * 0.35 + s * ornSize * 0.14 + swingOffset;
        ornXml +=
          '<View left="' +
          lineX +
          '" top="' +
          (y + 12 * scale) +
          '" ' +
          'width="1" height="' +
          ornSize * 0.75 +
          '" ' +
          'background-color="rgba(255,255,255,0.4)" border-radius="1"/>';
      }
    } else if (decorType === "waves") {
      // Horizontal wavy lines (like on the blue ornament)
      for (var w = 0; w < 2; w++) {
        var waveY = y + ornSize * 0.35 + w * ornSize * 0.25;
        ornXml +=
          '<View left="' +
          (x - ornSize * 0.35 + swingOffset) +
          '" top="' +
          waveY +
          '" ' +
          'width="' +
          ornSize * 0.7 +
          '" height="3" ' +
          'background-color="rgba(255,255,255,0.4)" border-radius="2"/>';
      }
    }

    // Main highlight (white shine)
    ornXml +=
      '<View left="' +
      (x - ornSize * 0.25 + swingOffset) +
      '" top="' +
      (y + ornSize * 0.15) +
      '" ' +
      'width="' +
      ornSize * 0.3 +
      '" height="' +
      ornSize * 0.4 +
      '" ' +
      'background-color="rgba(255,255,255,0.35)" border-radius="50%"/>';

    return ornXml;
  }

  // === Pine Branch Function ===
  function drawPineBranch(x, y, angle, scale, opacity) {
    var branchXml = "";
    var darkGreen = "rgba(34,85,34," + opacity + ")";
    var lightGreen = "rgba(60,120,60," + opacity + ")";
    var stemColor = "rgba(80,50,20," + opacity + ")";

    // Main stem
    var stemLength = 80 * scale;
    var stemWidth = 6 * scale;

    // Draw needle clusters along the branch
    var needleCount = 12;
    for (var n = 0; n < needleCount; n++) {
      var progress = n / needleCount;
      var nx = x + Math.cos(angle) * progress * stemLength;
      var ny = y + Math.sin(angle) * progress * stemLength;

      // Needles pointing outward from stem
      var needleLength =
        (15 + Math.random() * 10) * scale * (1 - progress * 0.3);
      var needleWidth = 3 * scale;

      // Upper needles
      for (var u = 0; u < 3; u++) {
        var upAngle = angle - 0.8 - u * 0.2;
        var upX = nx + Math.cos(upAngle) * needleLength;
        var upY = ny + Math.sin(upAngle) * needleLength;
        var nColor = (n + u) % 2 === 0 ? darkGreen : lightGreen;

        branchXml +=
          '<View left="' +
          (nx - needleWidth / 2) +
          '" top="' +
          Math.min(ny, upY) +
          '" ' +
          'width="' +
          needleWidth +
          '" height="' +
          Math.abs(upY - ny + needleLength * 0.5) +
          '" ' +
          'background-color="' +
          nColor +
          '" border-radius="2"/>';
      }

      // Lower needles
      for (var d = 0; d < 3; d++) {
        var downAngle = angle + 0.8 + d * 0.2;
        var downY = ny + Math.sin(downAngle) * needleLength;
        var nColor = (n + d) % 2 === 0 ? lightGreen : darkGreen;

        branchXml +=
          '<View left="' +
          (nx - needleWidth / 2) +
          '" top="' +
          ny +
          '" ' +
          'width="' +
          needleWidth +
          '" height="' +
          needleLength * 0.8 +
          '" ' +
          'background-color="' +
          nColor +
          '" border-radius="2"/>';
      }
    }

    return branchXml;
  }

  // === Red Ribbon Bow Function ===
  function drawBow(x, y, scale, opacity) {
    var bowXml = "";
    var redColor = "rgba(180,30,30," + opacity + ")";
    var darkRed = "rgba(120,10,10," + opacity + ")";

    // Left loop
    bowXml +=
      '<View left="' +
      (x - 22 * scale) +
      '" top="' +
      (y - 12 * scale) +
      '" ' +
      'width="' +
      18 * scale +
      '" height="' +
      20 * scale +
      '" ' +
      'background-color="' +
      redColor +
      '" border-radius="50% 50% 30% 30%"/>';

    // Right loop
    bowXml +=
      '<View left="' +
      (x + 4 * scale) +
      '" top="' +
      (y - 12 * scale) +
      '" ' +
      'width="' +
      18 * scale +
      '" height="' +
      20 * scale +
      '" ' +
      'background-color="' +
      redColor +
      '" border-radius="50% 50% 30% 30%"/>';

    // Center knot
    bowXml +=
      '<View left="' +
      (x - 6 * scale) +
      '" top="' +
      (y - 5 * scale) +
      '" ' +
      'width="' +
      12 * scale +
      '" height="' +
      10 * scale +
      '" ' +
      'background-color="' +
      darkRed +
      '" border-radius="30%"/>';

    // Tail ribbons
    bowXml +=
      '<View left="' +
      (x - 8 * scale) +
      '" top="' +
      (y + 3 * scale) +
      '" ' +
      'width="' +
      6 * scale +
      '" height="' +
      18 * scale +
      '" ' +
      'background-color="' +
      redColor +
      '" border-radius="2"/>';

    bowXml +=
      '<View left="' +
      (x + 2 * scale) +
      '" top="' +
      (y + 3 * scale) +
      '" ' +
      'width="' +
      6 * scale +
      '" height="' +
      18 * scale +
      '" ' +
      'background-color="' +
      redColor +
      '" border-radius="2"/>';

    return bowXml;
  }

  // === Animation timing ===
  var bellSwing = time * 2; // Ornament swinging speed (slower, gentle)
  var sparklePhase = time * 2;

  // === Draw Pine Branches across the top ===
  // Layer of pine branches creating a natural garland effect
  for (var b = 0; b < 12; b++) {
    var branchX = 50 + b * 65;
    var branchY = -10 + Math.sin(b * 0.8) * 15;
    var branchAngle = 0.3 + Math.sin(b * 0.5) * 0.4;
    xml += drawPineBranch(
      branchX,
      branchY,
      branchAngle,
      0.9 + Math.sin(b) * 0.2,
      1.0
    );
  }

  // Second layer of branches (overlapping)
  for (var b = 0; b < 10; b++) {
    var branchX = 80 + b * 70;
    var branchY = 5 + Math.sin(b * 0.6 + 1) * 10;
    var branchAngle = 0.5 + Math.sin(b * 0.7) * 0.3;
    xml += drawPineBranch(branchX, branchY, branchAngle, 0.8, 0.9);
  }

  // === Draw Hanging Ornaments ===
  // Gold ornament (left) - with vertical lines
  xml += drawOrnament(180, 60, 0.9, bellSwing, "#D4A84B", "#8B6914", "lines");
  xml += drawBow(180, 25, 0.6, 1.0);

  // Red ornament (center) - with diagonal stripes
  xml += drawOrnament(
    400,
    80,
    1.0,
    bellSwing + 0.5,
    "#B84C4C",
    "#8B1A1A",
    "stripes"
  );
  xml += drawBow(400, 40, 0.7, 1.0);

  // Blue/teal ornament (right) - with wavy lines
  xml += drawOrnament(
    620,
    55,
    0.85,
    bellSwing + 1.0,
    "#5B8BA0",
    "#2F5D6E",
    "waves"
  );
  xml += drawBow(620, 20, 0.6, 1.0);

  // === Sparkle Effects on ornaments ===
  for (var s = 0; s < 8; s++) {
    var sparkleX = 120 + s * 90;
    var sparkleY = 20 + Math.sin(s * 1.3) * 30;
    var sparkleOpacity = 0.4 + Math.abs(Math.sin(sparklePhase + s * 0.9)) * 0.5;
    var sparkleSize = 2 + Math.sin(sparklePhase + s) * 1.5;

    xml +=
      '<View left="' +
      sparkleX +
      '" top="' +
      sparkleY +
      '" ' +
      'width="' +
      sparkleSize +
      '" height="' +
      sparkleSize +
      '" ' +
      'background-color="rgba(255,255,255,' +
      sparkleOpacity +
      ')" ' +
      'border-radius="50%"/>';
  }

  xml += "</View>";

  return xml;
}
