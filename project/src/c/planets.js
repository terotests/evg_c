// Solar System Journey - 60 second animation
// Traverse from outer planets through Saturn and Earth towards the Sun
// Features: 3D projection, elliptical orbits, close flybys, motion trails

function easeInOutCubic(t) {
  return t < 0.5 ? 4 * t * t * t : 1 - Math.pow(-2 * t + 2, 3) / 2;
}

function easeOutQuad(t) {
  return 1 - (1 - t) * (1 - t);
}

// Sci-Fi Typewriter Text Effect
// Returns XML for text that types out character by character with a blinking cursor
function scifiTypewriter(text, x, y, startTime, currentTime, options) {
  options = options || {};
  var charsPerSecond = options.speed || 12;
  var fontSize = options.fontSize || 11;
  var color = options.color || "0,255,100"; // Matrix green
  var bgColor = options.bgColor || "0,40,20";
  var showCursor = options.showCursor !== false;
  var prefix = options.prefix || "> ";

  var elapsed = currentTime - startTime;
  if (elapsed < 0) return "";

  var fullText = prefix + text;
  var charsToShow = Math.floor(elapsed * charsPerSecond);
  charsToShow = Math.min(charsToShow, fullText.length);

  var visibleText = fullText.substring(0, charsToShow);

  // Blinking cursor (blinks every 0.4 seconds)
  var cursorVisible = showCursor && Math.floor(currentTime * 2.5) % 2 === 0;
  var cursorChar = cursorVisible ? "_" : "";

  // Only show cursor while typing or shortly after
  if (
    charsToShow >= fullText.length &&
    elapsed > fullText.length / charsPerSecond + 1
  ) {
    cursorChar = "";
  }

  var displayText = visibleText + cursorChar;

  // Calculate box width based on full text (to prevent jumping)
  var boxWidth = (fullText.length + 2) * fontSize * 0.6;
  var boxHeight = fontSize + 8;

  // Background terminal box
  var xml =
    '<View left="' +
    (x - 4) +
    '" top="' +
    (y - 2) +
    '" ' +
    'width="' +
    boxWidth +
    '" height="' +
    boxHeight +
    '" ' +
    'background-color="rgba(' +
    bgColor +
    ',0.85)" ' +
    'border-color="rgba(' +
    color +
    ',0.6)" border-width="1"/>';

  // The text
  xml +=
    '<Label left="' +
    x +
    '" top="' +
    y +
    '" ' +
    'font-size="' +
    fontSize +
    '" color="rgba(' +
    color +
    ',0.95)" ' +
    'text="' +
    displayText +
    '"/>';

  return xml;
}

// Sci-Fi data readout with multiple lines
function scifiDataPanel(lines, x, y, startTime, currentTime, options) {
  options = options || {};
  var lineDelay = options.lineDelay || 0.8; // seconds between lines
  var fontSize = options.fontSize || 10;
  var lineHeight = fontSize + 6;

  var xml = "";
  for (var i = 0; i < lines.length; i++) {
    var lineStart = startTime + i * lineDelay;
    xml += scifiTypewriter(
      lines[i],
      x,
      y + i * lineHeight,
      lineStart,
      currentTime,
      {
        speed: options.speed || 15,
        fontSize: fontSize,
        color: options.color,
        bgColor: options.bgColor,
        showCursor: i === lines.length - 1, // Only show cursor on last line
        prefix: options.prefix || "> ",
      }
    );
  }
  return xml;
}

// Sci-Fi Targeting Reticle with pointer line and label
// Creates a HUD-style target indicator pointing to an object
function scifiTargetReticle(targetX, targetY, label, options) {
  options = options || {};
  var color = options.color || "0,255,100"; // Matrix green
  var opacity = options.opacity || 0.8;
  var circleRadius = options.circleRadius || 8;
  var lineLength = options.lineLength || 40;
  var fontSize = options.fontSize || 9;
  var showData = options.showData || false;
  var dataText = options.dataText || "";

  var xml = "";

  // Determine which corner to place the label based on screen position
  // Default: label goes to upper-right of target
  var labelOffsetX = lineLength * 0.7;
  var labelOffsetY = -lineLength * 0.7;

  // If target is on right side, flip label to left
  if (targetX > 500) {
    labelOffsetX = -lineLength * 0.7;
  }
  // If target is near top, flip label to bottom
  if (targetY < 100) {
    labelOffsetY = lineLength * 0.7;
  }

  var labelX = targetX + labelOffsetX;
  var labelY = targetY + labelOffsetY;

  // Corner brackets around the target (sci-fi style)
  var bracketSize = circleRadius + 4;
  var bracketThickness = 2;
  var bracketLength = 6;

  // Top-left bracket
  xml +=
    '<View left="' +
    (targetX - bracketSize) +
    '" top="' +
    (targetY - bracketSize) +
    '" ' +
    'width="' +
    bracketLength +
    '" height="' +
    bracketThickness +
    '" ' +
    'background-color="rgba(' +
    color +
    "," +
    opacity +
    ')"/>';
  xml +=
    '<View left="' +
    (targetX - bracketSize) +
    '" top="' +
    (targetY - bracketSize) +
    '" ' +
    'width="' +
    bracketThickness +
    '" height="' +
    bracketLength +
    '" ' +
    'background-color="rgba(' +
    color +
    "," +
    opacity +
    ')"/>';

  // Top-right bracket
  xml +=
    '<View left="' +
    (targetX + bracketSize - bracketLength) +
    '" top="' +
    (targetY - bracketSize) +
    '" ' +
    'width="' +
    bracketLength +
    '" height="' +
    bracketThickness +
    '" ' +
    'background-color="rgba(' +
    color +
    "," +
    opacity +
    ')"/>';
  xml +=
    '<View left="' +
    (targetX + bracketSize - bracketThickness) +
    '" top="' +
    (targetY - bracketSize) +
    '" ' +
    'width="' +
    bracketThickness +
    '" height="' +
    bracketLength +
    '" ' +
    'background-color="rgba(' +
    color +
    "," +
    opacity +
    ')"/>';

  // Bottom-left bracket
  xml +=
    '<View left="' +
    (targetX - bracketSize) +
    '" top="' +
    (targetY + bracketSize - bracketThickness) +
    '" ' +
    'width="' +
    bracketLength +
    '" height="' +
    bracketThickness +
    '" ' +
    'background-color="rgba(' +
    color +
    "," +
    opacity +
    ')"/>';
  xml +=
    '<View left="' +
    (targetX - bracketSize) +
    '" top="' +
    (targetY + bracketSize - bracketLength) +
    '" ' +
    'width="' +
    bracketThickness +
    '" height="' +
    bracketLength +
    '" ' +
    'background-color="rgba(' +
    color +
    "," +
    opacity +
    ')"/>';

  // Bottom-right bracket
  xml +=
    '<View left="' +
    (targetX + bracketSize - bracketLength) +
    '" top="' +
    (targetY + bracketSize - bracketThickness) +
    '" ' +
    'width="' +
    bracketLength +
    '" height="' +
    bracketThickness +
    '" ' +
    'background-color="rgba(' +
    color +
    "," +
    opacity +
    ')"/>';
  xml +=
    '<View left="' +
    (targetX + bracketSize - bracketThickness) +
    '" top="' +
    (targetY + bracketSize - bracketLength) +
    '" ' +
    'width="' +
    bracketThickness +
    '" height="' +
    bracketLength +
    '" ' +
    'background-color="rgba(' +
    color +
    "," +
    opacity +
    ')"/>';

  // Center dot
  var dotSize = 3;
  xml +=
    '<View left="' +
    (targetX - dotSize / 2) +
    '" top="' +
    (targetY - dotSize / 2) +
    '" ' +
    'width="' +
    dotSize +
    '" height="' +
    dotSize +
    '" ' +
    'background-color="rgba(' +
    color +
    "," +
    opacity +
    ')" border-radius="50%"/>';

  // Pointer line from brackets to label (diagonal line made of small segments)
  var segments = 8;
  var dx = (labelX - targetX) / segments;
  var dy = (labelY - targetY) / segments;
  for (var i = 0; i < segments; i++) {
    var sx =
      targetX +
      dx * i +
      (Math.abs(labelOffsetX) > Math.abs(labelOffsetY)
        ? bracketSize * Math.sign(labelOffsetX)
        : 0);
    var sy =
      targetY +
      dy * i +
      (Math.abs(labelOffsetY) > Math.abs(labelOffsetX)
        ? bracketSize * Math.sign(labelOffsetY)
        : 0);
    // Dashed line effect
    if (i % 2 === 0) {
      xml +=
        '<View left="' +
        sx +
        '" top="' +
        sy +
        '" ' +
        'width="' +
        (Math.abs(dx) + 1) +
        '" height="' +
        bracketThickness +
        '" ' +
        'background-color="rgba(' +
        color +
        "," +
        opacity * 0.6 +
        ')"/>';
    }
  }

  // Circle at end of pointer line
  var endCircleRadius = 4;
  xml +=
    '<View left="' +
    (labelX - endCircleRadius) +
    '" top="' +
    (labelY - endCircleRadius) +
    '" ' +
    'width="' +
    endCircleRadius * 2 +
    '" height="' +
    endCircleRadius * 2 +
    '" ' +
    'border-color="rgba(' +
    color +
    "," +
    opacity +
    ')" border-width="1" border-radius="50%"/>';

  // Label background
  var labelWidth = (label.length + 1) * fontSize * 0.65;
  var labelHeight = fontSize + 6;
  var labelBoxX =
    labelOffsetX > 0
      ? labelX + endCircleRadius + 4
      : labelX - labelWidth - endCircleRadius - 4;
  var labelBoxY = labelY - labelHeight / 2;

  xml +=
    '<View left="' +
    labelBoxX +
    '" top="' +
    labelBoxY +
    '" ' +
    'width="' +
    labelWidth +
    '" height="' +
    labelHeight +
    '" ' +
    'background-color="rgba(0,20,10,0.75)" ' +
    'border-color="rgba(' +
    color +
    ',0.5)" border-width="1"/>';

  // Label text
  xml +=
    '<Label left="' +
    (labelBoxX + 4) +
    '" top="' +
    (labelBoxY + 3) +
    '" ' +
    'font-size="' +
    fontSize +
    '" color="rgba(' +
    color +
    ',0.95)" ' +
    'text="' +
    label +
    '"/>';

  // Optional data line below label
  if (showData && dataText) {
    var dataBoxY = labelBoxY + labelHeight + 2;
    var dataWidth = (dataText.length + 1) * (fontSize - 1) * 0.6;
    xml +=
      '<View left="' +
      labelBoxX +
      '" top="' +
      dataBoxY +
      '" ' +
      'width="' +
      dataWidth +
      '" height="' +
      (fontSize + 2) +
      '" ' +
      'background-color="rgba(0,15,8,0.7)"/>';
    xml +=
      '<Label left="' +
      (labelBoxX + 4) +
      '" top="' +
      (dataBoxY + 1) +
      '" ' +
      'font-size="' +
      (fontSize - 1) +
      '" color="rgba(' +
      color +
      ',0.7)" ' +
      'text="' +
      dataText +
      '"/>';
  }

  return xml;
}

// Planet data: name, color, size, semi-major axis, eccentricity, orbit speed, inclination
var planets = [
  {
    name: "Neptune",
    color1: "#4169E1",
    color2: "#1E3A8A",
    size: 38,
    semiMajor: 3000,
    eccentricity: 0.009,
    speed: 0.001,
    inclination: 0.03,
  },
  {
    name: "Uranus",
    color1: "#87CEEB",
    color2: "#5F9EA0",
    size: 35,
    semiMajor: 2500,
    eccentricity: 0.046,
    speed: 0.0015,
    inclination: 0.02,
  },
  {
    name: "Saturn",
    color1: "#F4D03F",
    color2: "#D4AC0D",
    size: 55,
    semiMajor: 1950,
    eccentricity: 0.054,
    speed: 0.002,
    inclination: 0.04,
  },
  {
    name: "Jupiter",
    color1: "#E59866",
    color2: "#A04000",
    size: 70,
    semiMajor: 1400,
    eccentricity: 0.048,
    speed: 0.003,
    inclination: 0.02,
    bands: true,
  },
  {
    name: "Mars",
    color1: "#E74C3C",
    color2: "#922B21",
    size: 20,
    semiMajor: 850,
    eccentricity: 0.093,
    speed: 0.006,
    inclination: 0.03,
  },
  {
    name: "Earth",
    color1: "#3498DB",
    color2: "#1E8449",
    size: 24,
    semiMajor: 650,
    eccentricity: 0.017,
    speed: 0.008,
    inclination: 0.0,
    hasMoon: true,
  },
  {
    name: "Venus",
    color1: "#F5B041",
    color2: "#D68910",
    size: 23,
    semiMajor: 500,
    eccentricity: 0.007,
    speed: 0.01,
    inclination: 0.06,
  },
  {
    name: "Mercury",
    color1: "#BDC3C7",
    color2: "#7F8C8D",
    size: 14,
    semiMajor: 350,
    eccentricity: 0.205,
    speed: 0.015,
    inclination: 0.12,
  },
];

// Stars background
var stars = [];
for (var i = 0; i < 200; i++) {
  var angle = (i * 137.5 * Math.PI) / 180;
  var radius = 50 + ((i * 13) % 800);
  stars.push({
    x: Math.cos(angle) * radius,
    y: Math.sin(angle) * radius,
    z: -500 + ((i * 7) % 1000),
    size: 1 + (i % 3),
    twinkleSpeed: 1 + (i % 4) * 0.5,
  });
}

// Space debris / asteroids - lots of small objects throughout the solar system
var asteroids = [];
for (var i = 0; i < 800; i++) {
  // Distribute asteroids in a disc around the Sun
  // Use golden angle for even distribution
  var goldenAngle = i * 2.39996;
  var distFromSun = 200 + Math.pow((i % 100) / 100, 0.5) * 3500; // 200 to 3700 units

  // Add some randomness using deterministic pseudo-random based on index
  var pseudoRand1 = ((i * 1234567) % 1000) / 1000;
  var pseudoRand2 = ((i * 7654321) % 1000) / 1000;
  var pseudoRand3 = ((i * 2468135) % 1000) / 1000;
  var pseudoRand4 = ((i * 9876543) % 1000) / 1000;

  // Vary the distance and angle
  distFromSun = distFromSun * (0.7 + pseudoRand1 * 0.6);
  var angle = goldenAngle + pseudoRand2 * 0.5;

  // Y position (vertical spread)
  var ySpread = (pseudoRand3 - 0.5) * 400;

  // Orbit speed - slower for distant objects
  var orbitSpeed =
    0.002 + (1 - distFromSun / 4000) * 0.01 + pseudoRand4 * 0.005;

  asteroids.push({
    baseAngle: angle,
    distance: distFromSun,
    y: ySpread,
    speed: orbitSpeed,
    size: 2 + pseudoRand1 * 8, // 2 to 10 pixels base size
    brightness: 0.3 + pseudoRand2 * 0.5, // Varying brightness
    color: pseudoRand3 > 0.5 ? "160,140,120" : "120,110,100", // Brownish/grayish
  });
}

// Additional asteroid belt between Mars and Jupiter
for (var i = 0; i < 400; i++) {
  var pseudoRand1 = ((i * 3141592) % 1000) / 1000;
  var pseudoRand2 = ((i * 2718281) % 1000) / 1000;
  var pseudoRand3 = ((i * 1618033) % 1000) / 1000;

  var beltAngle = (i / 400) * Math.PI * 2 + pseudoRand1 * 0.3;
  var beltDist = 950 + pseudoRand2 * 300; // Between Mars (850) and Jupiter (1400)

  asteroids.push({
    baseAngle: beltAngle,
    distance: beltDist,
    y: (pseudoRand3 - 0.5) * 100, // Flatter distribution in belt
    speed: 0.004 + pseudoRand1 * 0.002,
    size: 1 + pseudoRand2 * 4,
    brightness: 0.2 + pseudoRand3 * 0.4,
    color: "140,130,110",
  });
}

// Catmull-Rom spline interpolation
function catmullRom(p0, p1, p2, p3, t) {
  var t2 = t * t;
  var t3 = t2 * t;
  return (
    0.5 *
    (2 * p1 +
      (-p0 + p2) * t +
      (2 * p0 - 5 * p1 + 4 * p2 - p3) * t2 +
      (-p0 + 3 * p1 - 3 * p2 + p3) * t3)
  );
}

// Get position on path using Catmull-Rom through waypoints
function getPathPosition(waypoints, t) {
  var numSegments = waypoints.length - 1;
  var segment = Math.floor(t * numSegments);
  if (segment >= numSegments) segment = numSegments - 1;
  if (segment < 0) segment = 0;

  var localT = t * numSegments - segment;

  // Get 4 control points for Catmull-Rom
  var i0 = Math.max(0, segment - 1);
  var i1 = segment;
  var i2 = Math.min(numSegments, segment + 1);
  var i3 = Math.min(numSegments, segment + 2);

  return {
    x: catmullRom(
      waypoints[i0].x,
      waypoints[i1].x,
      waypoints[i2].x,
      waypoints[i3].x,
      localT
    ),
    y: catmullRom(
      waypoints[i0].y,
      waypoints[i1].y,
      waypoints[i2].y,
      waypoints[i3].y,
      localT
    ),
    z: catmullRom(
      waypoints[i0].z,
      waypoints[i1].z,
      waypoints[i2].z,
      waypoints[i3].z,
      localT
    ),
  };
}

// Calculate elliptical orbit position
function getOrbitPosition(planet, time) {
  var angle = time * planet.speed * Math.PI * 2;
  var a = planet.semiMajor;
  var e = planet.eccentricity;
  var b = a * Math.sqrt(1 - e * e); // Semi-minor axis

  // Ellipse in orbital plane
  var x = a * Math.cos(angle) - a * e; // Offset by eccentricity
  var y = b * Math.sin(angle);

  // Apply inclination (tilt the orbit)
  var incl = planet.inclination;
  var z = y * Math.sin(incl);
  y = y * Math.cos(incl);

  return { x: x, y: y, z: z };
}

// 3D to 2D projection with look-at direction
// Camera looks FROM (cameraX, cameraY, cameraZ) TOWARD (lookAtX, lookAtY, lookAtZ)
function project3DWithLookAt(
  x,
  y,
  z,
  cameraX,
  cameraY,
  cameraZ,
  lookAtX,
  lookAtY,
  lookAtZ,
  width,
  height
) {
  // Calculate camera basis vectors
  // Forward vector (from camera to look-at point)
  var fwdX = lookAtX - cameraX;
  var fwdY = lookAtY - cameraY;
  var fwdZ = lookAtZ - cameraZ;
  var fwdLen = Math.sqrt(fwdX * fwdX + fwdY * fwdY + fwdZ * fwdZ);
  if (fwdLen < 0.001) return null;
  fwdX /= fwdLen;
  fwdY /= fwdLen;
  fwdZ /= fwdLen;

  // Up vector (world up is -Y, but we use a simple approximation)
  var upX = 0,
    upY = -1,
    upZ = 0;

  // Right vector = forward × up
  var rightX = fwdY * upZ - fwdZ * upY;
  var rightY = fwdZ * upX - fwdX * upZ;
  var rightZ = fwdX * upY - fwdY * upX;
  var rightLen = Math.sqrt(rightX * rightX + rightY * rightY + rightZ * rightZ);
  if (rightLen < 0.001) {
    // Camera looking straight up/down, use different up
    upX = 0;
    upY = 0;
    upZ = 1;
    rightX = fwdY * upZ - fwdZ * upY;
    rightY = fwdZ * upX - fwdX * upZ;
    rightZ = fwdX * upY - fwdY * upX;
    rightLen = Math.sqrt(rightX * rightX + rightY * rightY + rightZ * rightZ);
  }
  rightX /= rightLen;
  rightY /= rightLen;
  rightZ /= rightLen;

  // Recalculate up = right × forward
  upX = rightY * fwdZ - rightZ * fwdY;
  upY = rightZ * fwdX - rightX * fwdZ;
  upZ = rightX * fwdY - rightY * fwdX;

  // Transform point to camera space
  var relX = x - cameraX;
  var relY = y - cameraY;
  var relZ = z - cameraZ;

  // Project onto camera basis
  var camX = relX * rightX + relY * rightY + relZ * rightZ;
  var camY = relX * upX + relY * upY + relZ * upZ;
  var camZ = relX * fwdX + relY * fwdY + relZ * fwdZ; // Distance along view direction

  // Perspective projection
  var focalLength = 400;

  if (camZ < 50) return null; // Behind camera (now positive = in front)

  var scale = focalLength / camZ;
  var screenX = width / 2 + camX * scale;
  var screenY = height / 2 + camY * scale;

  return { x: screenX, y: screenY, scale: scale, depth: camZ };
}

// Legacy wrapper for backward compatibility
function project3D(x, y, z, cameraX, cameraY, cameraZ, width, height) {
  // Default: look toward origin (Sun)
  return project3DWithLookAt(
    x,
    y,
    z,
    cameraX,
    cameraY,
    cameraZ,
    0,
    0,
    0,
    width,
    height
  );
}

// Helper: Convert hex color to RGB string
function hexToRgb(hex) {
  // Remove # if present
  if (hex.charAt(0) === "#") {
    hex = hex.substring(1);
  }

  if (hex.length === 6) {
    var r = parseInt(hex.substring(0, 2), 16);
    var g = parseInt(hex.substring(2, 4), 16);
    var b = parseInt(hex.substring(4, 6), 16);
    return r + "," + g + "," + b;
  }
  return "255,255,255";
}

function processLine(time) {
  // Speed up time for testing (3x speed)
  time = time * 3;

  // End video after 120 seconds (at 3x = 40 real seconds)
  if (time > 120.0) return "";

  var width = 800;
  var height = 600;
  var centerX = width / 2;
  var centerY = height / 2;

  // === FLIGHT PATH DEFINITION ===
  // Planets orbit in X-Y plane around Sun at origin (0,0,0)
  // Camera at positive Z looks down at planets
  // Neptune at ~3000, Uranus ~2500, Saturn ~1950, Jupiter ~1400, Mars ~850, Earth ~650, Venus ~500, Mercury ~350
  var flightPath = [
    // Phase 1: High overview - camera above looking down at solar system (0-15s)
    { time: 0, x: 0, y: 0, z: 5000, lookAt: "sun" }, // Start far above
    { time: 8, x: 500, y: 200, z: 4500, lookAt: "sun" }, // Gentle drift
    { time: 15, x: 1500, y: 500, z: 3500, lookAt: "planet:0" }, // Start moving toward Neptune

    // Phase 2: Fly close to Neptune (15-28s) - Neptune orbits at ~3000 units
    { time: 22, x: 2600, y: 800, z: 800, lookAt: "planet:0" }, // Approaching Neptune
    { time: 28, x: 3100, y: 300, z: 300, lookAt: "planet:0" }, // Very close flyby

    // Phase 3: Neptune to Uranus (28-42s) - Uranus at ~2500 units
    { time: 35, x: 2600, y: 400, z: 600, lookAt: "planet:1" }, // Moving toward Uranus
    { time: 42, x: 2600, y: 200, z: 250, lookAt: "planet:1" }, // Close flyby

    // Phase 4: Uranus to Saturn (42-56s) - Saturn at ~1950 units
    { time: 49, x: 2100, y: 300, z: 500, lookAt: "planet:2" }, // Moving toward Saturn
    { time: 56, x: 2050, y: 100, z: 200, lookAt: "planet:2" }, // Close to Saturn

    // Phase 5: Saturn to Jupiter (56-70s) - Jupiter at ~1400 units
    { time: 63, x: 1550, y: 200, z: 400, lookAt: "planet:3" }, // Moving toward Jupiter
    { time: 70, x: 1500, y: 80, z: 180, lookAt: "planet:3" }, // Close flyby of Jupiter

    // Phase 6: Inner planets tour (70-100s)
    { time: 78, x: 950, y: 100, z: 300, lookAt: "planet:4" }, // Mars flyby
    { time: 86, x: 750, y: 50, z: 200, lookAt: "planet:5" }, // Earth close approach
    { time: 94, x: 580, y: 30, z: 150, lookAt: "planet:6" }, // Venus flyby
    { time: 102, x: 420, y: 20, z: 120, lookAt: "planet:7" }, // Mercury

    // Phase 7: Final approach to Sun (102-120s)
    { time: 110, x: 250, y: 10, z: 200, lookAt: "sun" }, // Approaching Sun
    { time: 120, x: 120, y: 0, z: 180, lookAt: "sun" }, // Close to Sun
  ];

  // Find current segment index
  var segIdx = 0;
  for (var i = 0; i < flightPath.length - 1; i++) {
    if (time >= flightPath[i].time && time < flightPath[i + 1].time) {
      segIdx = i;
      break;
    }
  }
  // Handle time at or past last waypoint
  if (time >= flightPath[flightPath.length - 1].time) {
    segIdx = flightPath.length - 2;
  }

  var segmentStart = flightPath[segIdx];
  var segmentEnd = flightPath[segIdx + 1];

  // Calculate progress within this segment (0 to 1)
  var segmentDuration = segmentEnd.time - segmentStart.time;
  var t = (time - segmentStart.time) / segmentDuration;
  t = Math.max(0, Math.min(1, t));

  // Apply easing for smooth motion
  var smoothT = easeInOutCubic(t);

  // Get 4 control points for Catmull-Rom spline
  var i0 = Math.max(0, segIdx - 1);
  var i1 = segIdx;
  var i2 = segIdx + 1;
  var i3 = Math.min(flightPath.length - 1, segIdx + 2);

  var p0 = flightPath[i0];
  var p1 = flightPath[i1];
  var p2 = flightPath[i2];
  var p3 = flightPath[i3];

  // Interpolate camera position using Catmull-Rom
  var cameraX = catmullRom(p0.x, p1.x, p2.x, p3.x, smoothT);
  var cameraY = catmullRom(p0.y, p1.y, p2.y, p3.y, smoothT);
  var cameraZ = catmullRom(p0.z, p1.z, p2.z, p3.z, smoothT);

  // Determine look-at target - blend between segment start and end targets
  var lookAtX = 0,
    lookAtY = 0,
    lookAtZ = 0;

  // Get look-at position for start of segment
  var startLookX = 0,
    startLookY = 0,
    startLookZ = 0;
  if (segmentStart.lookAt === "sun") {
    startLookX = 0;
    startLookY = 0;
    startLookZ = 0;
  } else if (segmentStart.lookAt.indexOf("planet:") === 0) {
    var pIdx = parseInt(segmentStart.lookAt.substring(7));
    var pPos = getOrbitPosition(planets[pIdx], time);
    startLookX = pPos.x;
    startLookY = pPos.y;
    startLookZ = pPos.z;
  } else {
    startLookX = segmentEnd.x;
    startLookY = segmentEnd.y;
    startLookZ = segmentEnd.z;
  }

  // Get look-at position for end of segment
  var endLookX = 0,
    endLookY = 0,
    endLookZ = 0;
  if (segmentEnd.lookAt === "sun") {
    endLookX = 0;
    endLookY = 0;
    endLookZ = 0;
  } else if (segmentEnd.lookAt.indexOf("planet:") === 0) {
    var pIdx = parseInt(segmentEnd.lookAt.substring(7));
    var pPos = getOrbitPosition(planets[pIdx], time);
    endLookX = pPos.x;
    endLookY = pPos.y;
    endLookZ = pPos.z;
  } else {
    var nextIdx = Math.min(flightPath.length - 1, segIdx + 2);
    endLookX = flightPath[nextIdx].x;
    endLookY = flightPath[nextIdx].y;
    endLookZ = flightPath[nextIdx].z;
  }

  // Smoothly interpolate look-at target
  lookAtX = startLookX + (endLookX - startLookX) * smoothT;
  lookAtY = startLookY + (endLookY - startLookY) * smoothT;
  lookAtZ = startLookZ + (endLookZ - startLookZ) * smoothT;

  // Find which planet we're closest to for UI display
  var closestPlanet = 0;
  var closestDist = 999999;
  for (var i = 0; i < planets.length; i++) {
    var ppos = getOrbitPosition(planets[i], time);
    var dist = Math.sqrt(
      Math.pow(ppos.x - cameraX, 2) +
        Math.pow(ppos.y - cameraY, 2) +
        Math.pow(ppos.z - cameraZ, 2)
    );
    if (dist < closestDist) {
      closestDist = dist;
      closestPlanet = i;
    }
  }

  // Build the scene
  var elementsToRender = [];

  // === Stars with 3D projection (stars use separate lookAt toward distant background) ===
  for (var i = 0; i < stars.length; i++) {
    var star = stars[i];
    var proj = project3DWithLookAt(
      star.x * 10,
      star.y * 10,
      star.z * 10 - 5000,
      cameraX * 0.01,
      cameraY * 0.01,
      cameraZ * 0.01,
      lookAtX * 0.01,
      lookAtY * 0.01,
      lookAtZ * 0.01,
      width,
      height
    );

    if (
      proj &&
      proj.x > -10 &&
      proj.x < width + 10 &&
      proj.y > -10 &&
      proj.y < height + 10
    ) {
      var twinkle =
        0.3 + Math.abs(Math.sin(time * star.twinkleSpeed + i)) * 0.7;
      var starSize = Math.max(1, star.size * proj.scale * 0.5);
      elementsToRender.push({
        depth: 100000,
        xml:
          '<View left="' +
          proj.x +
          '" top="' +
          proj.y +
          '" ' +
          'width="' +
          starSize +
          '" height="' +
          starSize +
          '" ' +
          'background-color="rgba(255,255,255,' +
          twinkle +
          ')" ' +
          'border-radius="50%"/>',
      });
    }
  }

  // === Asteroids / Space Debris ===
  for (var i = 0; i < asteroids.length; i++) {
    var ast = asteroids[i];

    // Calculate current position - asteroids orbit the Sun
    var currentAngle = ast.baseAngle + time * ast.speed;
    var astX = Math.cos(currentAngle) * ast.distance;
    var astZ = Math.sin(currentAngle) * ast.distance;
    var astY = ast.y;

    // Project to screen
    var proj = project3DWithLookAt(
      astX,
      astY,
      astZ,
      cameraX,
      cameraY,
      cameraZ,
      lookAtX,
      lookAtY,
      lookAtZ,
      width,
      height
    );

    if (
      proj &&
      proj.x > -20 &&
      proj.x < width + 20 &&
      proj.y > -20 &&
      proj.y < height + 20
    ) {
      var astSize = Math.max(1, ast.size * proj.scale);

      // Only render if reasonably sized (not too tiny, not huge)
      if (astSize > 0.5 && astSize < 50) {
        var opacity = ast.brightness * Math.min(1, (2 / proj.depth) * 100);
        opacity = Math.min(0.9, Math.max(0.1, opacity));

        elementsToRender.push({
          depth: proj.depth,
          xml:
            '<View left="' +
            (proj.x - astSize / 2) +
            '" top="' +
            (proj.y - astSize / 2) +
            '" ' +
            'width="' +
            astSize +
            '" height="' +
            astSize +
            '" ' +
            'background-color="rgba(' +
            ast.color +
            "," +
            opacity +
            ')" ' +
            'border-radius="50%"/>',
        });
      }
    }
  }

  // === Orbit paths (visible during overview phase) ===
  if (time < 25) {
    var orbitOpacity = time < 20 ? 0.3 : 0.3 * (1 - (time - 20) / 5);

    for (var p = 0; p < planets.length; p++) {
      var planet = planets[p];
      // Draw orbit as series of dots
      var orbitPoints = 60;
      for (var o = 0; o < orbitPoints; o++) {
        var orbitAngle = (o / orbitPoints) * Math.PI * 2;
        var a = planet.semiMajor;
        var e = planet.eccentricity;
        var b = a * Math.sqrt(1 - e * e);

        var ox = a * Math.cos(orbitAngle) - a * e;
        var oy = b * Math.sin(orbitAngle);
        var incl = planet.inclination;
        var oz = oy * Math.sin(incl);
        oy = oy * Math.cos(incl);

        var oproj = project3DWithLookAt(
          ox,
          oy,
          oz,
          cameraX,
          cameraY,
          cameraZ,
          lookAtX,
          lookAtY,
          lookAtZ,
          width,
          height
        );
        if (
          oproj &&
          oproj.x > 0 &&
          oproj.x < width &&
          oproj.y > 0 &&
          oproj.y < height
        ) {
          var dotSize = Math.max(1, 2 * oproj.scale);
          elementsToRender.push({
            depth: oproj.depth + 0.1,
            xml:
              '<View left="' +
              (oproj.x - dotSize / 2) +
              '" top="' +
              (oproj.y - dotSize / 2) +
              '" ' +
              'width="' +
              dotSize +
              '" height="' +
              dotSize +
              '" ' +
              'background-color="rgba(100,100,150,' +
              orbitOpacity +
              ')" ' +
              'border-radius="50%"/>',
          });
        }
      }
    }
  }

  // === Sun ===
  var sunProj = project3DWithLookAt(
    0,
    0,
    0,
    cameraX,
    cameraY,
    cameraZ,
    lookAtX,
    lookAtY,
    lookAtZ,
    width,
    height
  );
  if (sunProj && sunProj.depth > 0) {
    var sunSize = Math.max(5, Math.min(300, 100 * sunProj.scale));

    // Corona
    if (sunSize > 15) {
      var coronaSize = sunSize * 4;
      elementsToRender.push({
        depth: sunProj.depth + 2,
        xml:
          '<View left="' +
          (sunProj.x - coronaSize / 2) +
          '" top="' +
          (sunProj.y - coronaSize / 2) +
          '" ' +
          'width="' +
          coronaSize +
          '" height="' +
          coronaSize +
          '" ' +
          'radial-gradient="rgba(255,200,50,0.2), rgba(255,100,0,0)" ' +
          'border-radius="50%"/>',
      });
    }

    // Sun glow
    var glowSize = sunSize * 2;
    elementsToRender.push({
      depth: sunProj.depth + 1,
      xml:
        '<View left="' +
        (sunProj.x - glowSize / 2) +
        '" top="' +
        (sunProj.y - glowSize / 2) +
        '" ' +
        'width="' +
        glowSize +
        '" height="' +
        glowSize +
        '" ' +
        'radial-gradient="rgba(255,220,100,0.5), rgba(255,150,50,0)" ' +
        'border-radius="50%"/>',
    });

    // Sun core
    elementsToRender.push({
      depth: sunProj.depth,
      xml:
        '<View left="' +
        (sunProj.x - sunSize / 2) +
        '" top="' +
        (sunProj.y - sunSize / 2) +
        '" ' +
        'width="' +
        sunSize +
        '" height="' +
        sunSize +
        '" ' +
        'radial-gradient="#FFFF99, #FF8C00" ' +
        'border-radius="50%"/>',
    });
  }

  // === Planets ===
  for (var p = 0; p < planets.length; p++) {
    var planet = planets[p];
    var pos = getOrbitPosition(planet, time);

    // Project planet position
    var proj = project3DWithLookAt(
      pos.x,
      pos.y,
      pos.z,
      cameraX,
      cameraY,
      cameraZ,
      lookAtX,
      lookAtY,
      lookAtZ,
      width,
      height
    );
    if (!proj) continue;

    var planetSize = planet.size * proj.scale;
    if (planetSize < 1) continue;
    if (proj.x < -planetSize || proj.x > width + planetSize) continue;
    if (proj.y < -planetSize || proj.y > height + planetSize) continue;

    // Planet body
    var planetXml =
      '<View left="' +
      (proj.x - planetSize / 2) +
      '" top="' +
      (proj.y - planetSize / 2) +
      '" ' +
      'width="' +
      planetSize +
      '" height="' +
      planetSize +
      '" ' +
      'radial-gradient="' +
      planet.color1 +
      ", " +
      planet.color2 +
      '" ' +
      'border-radius="50%"/>';

    elementsToRender.push({ depth: proj.depth, xml: planetXml });

    // Jupiter bands effect
    if (planet.bands && planetSize > 20) {
      for (var band = 0; band < 4; band++) {
        var bandY = proj.y - planetSize * 0.3 + band * planetSize * 0.2;
        var bandWidth = planetSize * 0.9;
        var bandHeight = planetSize * 0.08;
        var bandOpacity = 0.3;
        elementsToRender.push({
          depth: proj.depth - 0.01,
          xml:
            '<View left="' +
            (proj.x - bandWidth / 2) +
            '" top="' +
            bandY +
            '" ' +
            'width="' +
            bandWidth +
            '" height="' +
            bandHeight +
            '" ' +
            'background-color="rgba(139,90,43,' +
            bandOpacity +
            ')" ' +
            'border-radius="' +
            bandHeight / 2 +
            '"/>',
        });
      }

      // Great Red Spot
      if (planetSize > 40) {
        var spotX = proj.x + planetSize * 0.15;
        var spotY = proj.y + planetSize * 0.1;
        var spotSize = planetSize * 0.2;
        elementsToRender.push({
          depth: proj.depth - 0.02,
          xml:
            '<View left="' +
            (spotX - spotSize / 2) +
            '" top="' +
            (spotY - spotSize / 2) +
            '" ' +
            'width="' +
            spotSize +
            '" height="' +
            spotSize * 0.6 +
            '" ' +
            'background-color="rgba(200,100,80,0.7)" ' +
            'border-radius="50%"/>',
        });
      }
    }

    // Earth's moon
    if (planet.hasMoon && planetSize > 5) {
      var moonAngle = time * 0.8;
      var moonOrbitRadius = planetSize * 2.5;
      var moonX = pos.x + Math.cos(moonAngle) * planet.size * 1.5;
      var moonY = pos.y + Math.sin(moonAngle) * planet.size * 0.8;
      var moonZ = pos.z + Math.sin(moonAngle) * planet.size * 0.5;

      var moonProj = project3DWithLookAt(
        moonX,
        moonY,
        moonZ,
        cameraX,
        cameraY,
        cameraZ,
        lookAtX,
        lookAtY,
        lookAtZ,
        width,
        height
      );
      if (moonProj) {
        var moonSize = Math.max(2, planetSize * 0.27);
        elementsToRender.push({
          depth: moonProj.depth,
          xml:
            '<View left="' +
            (moonProj.x - moonSize / 2) +
            '" top="' +
            (moonProj.y - moonSize / 2) +
            '" ' +
            'width="' +
            moonSize +
            '" height="' +
            moonSize +
            '" ' +
            'radial-gradient="#D0D0D0, #808080" ' +
            'border-radius="50%"/>',
        });
      }
    }

    // Planet label - Sci-Fi targeting reticle style
    if (
      planetSize > 8 &&
      proj.x > 20 &&
      proj.x < width - 20 &&
      proj.y > 20 &&
      proj.y < height - 20
    ) {
      var reticleOpacity = Math.min(0.9, (planetSize - 6) / 30);

      // Calculate distance from camera to planet
      var distToPlanet = Math.floor(
        Math.sqrt(
          Math.pow(pos.x - cameraX, 2) +
            Math.pow(pos.y - cameraY, 2) +
            Math.pow(pos.z - cameraZ, 2)
        )
      );

      // Determine reticle size based on planet size on screen
      var reticleSize = Math.max(10, Math.min(25, planetSize / 2 + 5));

      elementsToRender.push({
        depth: proj.depth - 1,
        xml: scifiTargetReticle(proj.x, proj.y, planet.name.toUpperCase(), {
          color: "0,255,100",
          opacity: reticleOpacity,
          circleRadius: reticleSize,
          lineLength: 35 + reticleSize,
          fontSize: 9,
          showData: planetSize > 25,
          dataText: "DST:" + distToPlanet,
        }),
      });
    }
  }

  // Sort by depth (far to near)
  elementsToRender.sort(function (a, b) {
    return b.depth - a.depth;
  });

  // Build XML from sorted elements
  var sortedXml = "";
  for (var e = 0; e < elementsToRender.length; e++) {
    sortedXml += elementsToRender[e]["xml"];
  }

  // === UI Overlays - Sci-Fi Style ===
  var uiXml = "";

  // Title sequence with typewriter effect
  if (time < 8) {
    uiXml += scifiTypewriter(
      "SOLAR SYSTEM NAVIGATION",
      centerX - 140,
      30,
      0.5,
      time,
      {
        speed: 18,
        fontSize: 14,
        color: "0,255,120",
        bgColor: "0,30,15",
      }
    );
    uiXml += scifiTypewriter(
      "INITIALIZING FLIGHT PATH...",
      centerX - 120,
      50,
      2.5,
      time,
      {
        speed: 15,
        fontSize: 10,
        color: "0,200,100",
      }
    );
  }

  // Current target / nearest planet - bottom left
  var targetPlanet = planets[closestPlanet];
  var targetDist = Math.floor(closestDist);

  // Calculate when we started approaching this planet (for typewriter reset)
  var approachStartTime = 0;
  for (var i = 0; i < flightPath.length; i++) {
    if (flightPath[i].lookAt === "planet:" + closestPlanet) {
      approachStartTime = flightPath[i].time;
      break;
    }
  }
  if (approachStartTime === 0) approachStartTime = time - 2;

  uiXml += scifiTypewriter(
    "TGT: " + targetPlanet.name.toUpperCase(),
    15,
    height - 55,
    Math.max(0, time - 0.5),
    time,
    {
      speed: 20,
      fontSize: 10,
      color: "0,255,100",
      bgColor: "0,35,15",
      prefix: "",
    }
  );

  uiXml += scifiTypewriter(
    "DST: " + targetDist + " UNITS",
    15,
    height - 38,
    Math.max(0, time - 0.3),
    time,
    {
      speed: 25,
      fontSize: 9,
      color: "0,220,90",
      bgColor: "0,30,12",
      prefix: "",
    }
  );

  // Distance from Sun - bottom right
  var distFromSun = Math.sqrt(
    cameraX * cameraX + cameraY * cameraY + cameraZ * cameraZ
  );
  var distAU = Math.floor((distFromSun / 650) * 100) / 100;

  uiXml += scifiTypewriter(
    "SUN: " + distAU + " AU",
    width - 130,
    height - 38,
    1,
    time,
    {
      speed: 20,
      fontSize: 9,
      color: "255,180,50",
      bgColor: "40,25,0",
      prefix: "",
    }
  );

  // Velocity indicator - top right
  var velocity = Math.floor((distFromSun / (time + 1)) * 10) / 10;
  uiXml += scifiTypewriter(
    "VEL: " + velocity + " U/S",
    width - 120,
    15,
    3,
    time,
    {
      speed: 15,
      fontSize: 9,
      color: "100,200,255",
      bgColor: "10,25,40",
      prefix: "",
    }
  );

  // Mission time - top left
  var missionTime = Math.floor(time * 10) / 10;
  uiXml += scifiTypewriter("T+" + missionTime + "s", 15, 15, 0, time, {
    speed: 30,
    fontSize: 9,
    color: "0,255,100",
    bgColor: "0,30,15",
    prefix: "",
  });

  // Background gradient - gets warmer as we approach Sun
  var bgGradient = "#000008, #050520";
  if (time > 100) {
    var warmth = (time - 100) / 20;
    var r = Math.floor(20 + warmth * 40);
    var g = Math.floor(10 + warmth * 15);
    bgGradient = "#000008, rgb(" + r + "," + g + ",30)";
  }

  return (
    '<View width="100%" height="100%" linear-gradient="' +
    bgGradient +
    '">' +
    sortedXml +
    uiXml +
    "</View>"
  );
}
