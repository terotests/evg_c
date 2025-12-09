// TechTips YouTube Intro Animation - 3 seconds
// Dark purple to blue gradient, sliding text, expanding glow circle, pulsing effect

function easeOutCubic(t) {
  return 1 - Math.pow(1 - t, 3);
}

function easeInOutQuad(t) {
  return t < 0.5 ? 2 * t * t : 1 - Math.pow(-2 * t + 2, 2) / 2;
}

// Star positions (pre-calculated for consistency)
// Each star has a 3D position (x, y, z) where z is depth
var stars = [];
// Generate 80 stars with random-ish positions using a seed pattern
for (var i = 0; i < 80; i++) {
  var angle = (i * 137.5 * Math.PI) / 180; // Golden angle for good distribution
  var radius = 50 + ((i * 7) % 350);
  stars.push({
    x: Math.cos(angle) * radius,
    y: Math.sin(angle) * radius,
    z: 0.1 + (i % 10) * 0.1,
    speed: 1.5 + (i % 5) * 0.5,
  });
}

function processLine(time) {
  // End video after 3 seconds
  if (time > 3.0) return "";

  var width = 800;
  var height = 600;
  var centerX = width / 2;
  var centerY = height / 2;

  // === Text slide-in animation (0s to 1.5s) ===
  var slideProgress = Math.min(1, time / 1.5);
  var easedSlide = easeOutCubic(slideProgress);

  // Text starts off-screen left (-400) and slides to center
  var textStartX = -400;
  var textEndX = centerX - 150; // Approximate center for text
  var textX = textStartX + (textEndX - textStartX) * easedSlide;

  // === Glowing circle expansion (starts at 0.3s, expands until 2s) ===
  var circleStartTime = 0.3;
  var circleEndTime = 2.0;
  var circleProgress = 0;
  if (time > circleStartTime) {
    circleProgress = Math.min(
      1,
      (time - circleStartTime) / (circleEndTime - circleStartTime)
    );
  }
  var easedCircle = easeInOutQuad(circleProgress);

  // Circle starts small and expands
  var circleMinSize = 20;
  var circleMaxSize = 350;
  var circleSize =
    circleMinSize + (circleMaxSize - circleMinSize) * easedCircle;

  // Circle glow opacity (fades in then slightly out)
  var circleOpacity = 0;
  if (time > circleStartTime) {
    var fadeInProgress = Math.min(1, (time - circleStartTime) / 0.5);
    circleOpacity = fadeInProgress * 0.6;
    // Slight fade after full expansion
    if (time > 2.0) {
      circleOpacity = 0.6 - (time - 2.0) * 0.2;
    }
  }

  // === Pulsing effect on final frame (after 2s) ===
  var pulseScale = 1;
  var pulseGlow = 0;
  if (time > 2.0) {
    // Subtle pulse using sine wave
    var pulseTime = (time - 2.0) * 4; // 4 pulses per second
    pulseScale = 1 + Math.sin(pulseTime * Math.PI) * 0.03;
    pulseGlow = 0.3 + Math.sin(pulseTime * Math.PI) * 0.2;
  }

  // Text final size with pulse
  var fontSize = Math.floor(72 * pulseScale);
  var textY = centerY - 20;

  // === Glow rings (multiple for better effect) ===
  var glowRings = "";
  if (circleOpacity > 0) {
    // Outer glow ring
    var ring1Size = circleSize * 1.2;
    glowRings +=
      '<View left="' +
      (centerX - ring1Size / 2) +
      '" top="' +
      (centerY - ring1Size / 2) +
      '" ' +
      'width="' +
      ring1Size +
      '" height="' +
      ring1Size +
      '" ' +
      'radial-gradient="rgba(100,150,255,' +
      circleOpacity * 0.3 +
      '), rgba(100,150,255,0)" ' +
      'border-radius="50%"/>';

    // Middle glow ring
    var ring2Size = circleSize;
    glowRings +=
      '<View left="' +
      (centerX - ring2Size / 2) +
      '" top="' +
      (centerY - ring2Size / 2) +
      '" ' +
      'width="' +
      ring2Size +
      '" height="' +
      ring2Size +
      '" ' +
      'radial-gradient="rgba(150,180,255,' +
      circleOpacity * 0.5 +
      '), rgba(100,100,255,0)" ' +
      'border-radius="50%"/>';

    // Inner bright core
    var coreSize = circleSize * 0.5;
    glowRings +=
      '<View left="' +
      (centerX - coreSize / 2) +
      '" top="' +
      (centerY - coreSize / 2) +
      '" ' +
      'width="' +
      coreSize +
      '" height="' +
      coreSize +
      '" ' +
      'radial-gradient="rgba(255,255,255,' +
      circleOpacity * 0.8 +
      '), rgba(200,200,255,0)" ' +
      'border-radius="50%"/>';
  }

  // === Additional pulse glow behind text (after 2s) ===
  var pulseGlowElement = "";
  if (pulseGlow > 0) {
    var glowSize = 400 + Math.sin((time - 2.0) * 4 * Math.PI) * 20;
    pulseGlowElement =
      '<View left="' +
      (centerX - glowSize / 2) +
      '" top="' +
      (centerY - glowSize / 2) +
      '" ' +
      'width="' +
      glowSize +
      '" height="' +
      glowSize +
      '" ' +
      'radial-gradient="rgba(100,180,255,' +
      pulseGlow +
      '), rgba(80,80,200,0)" ' +
      'border-radius="50%"/>';
  }

  // === Text shadow for depth ===
  var shadowOffset = 3;
  var shadowOpacity = 0.5 * easedSlide;

  // === Generate WARP SPEED starfield effect ===
  var starsXml = "";

  // Gentle warp speed - stays relatively constant
  var warpFactor = 1.5 + time * 0.3; // Slow linear increase instead of exponential

  // Only fade stars at the end (not the warp speed)
  var warpFade = 1.0;
  if (time > 2.0) {
    var fadeProgress = (time - 2.0) / 1.0; // 0 to 1 over last second
    warpFade = 1.0 - fadeProgress * 0.9; // Fade brightness to 10%
  }

  for (var i = 0; i < stars.length; i++) {
    var star = stars[i];

    // Animate z position - stars move towards viewer, accelerating
    var zSpeed = 0.3 * warpFactor;
    var z = star.z - time * zSpeed;

    // Wrap around when star passes the viewer
    while (z <= 0.05) {
      z += 1.0;
    }

    // 3D projection - stars spread out as they get closer
    var perspective = 1.0 / z;
    var screenX = centerX + star.x * perspective;
    var screenY = centerY + star.y * perspective;

    // Calculate previous position for streak effect
    var zPrev = z + 0.08 * warpFactor; // How far back the trail goes
    var perspectivePrev = 1.0 / zPrev;
    var screenXPrev = centerX + star.x * perspectivePrev;
    var screenYPrev = centerY + star.y * perspectivePrev;

    // Only render if on screen
    if (
      screenX >= -50 &&
      screenX <= width + 50 &&
      screenY >= -50 &&
      screenY <= height + 50
    ) {
      // Streak length increases with warp speed
      var streakLength = Math.sqrt(
        Math.pow(screenX - screenXPrev, 2) + Math.pow(screenY - screenYPrev, 2)
      );
      streakLength = Math.min(200, streakLength * warpFactor * 0.5);

      // Calculate streak angle
      var angle =
        (Math.atan2(screenY - centerY, screenX - centerX) * 180) / Math.PI;

      // Size increases as star gets closer
      var size = Math.max(1, Math.min(6, 1.5 * perspective));

      // Brightness increases as star gets closer
      var twinkle = 0.7 + Math.abs(Math.sin(time * star.speed + i)) * 0.3;
      var brightness = Math.min(1, perspective * 0.7) * twinkle * warpFade;

      // Color shifts to blue-white at warp speed
      var colorShift = Math.min(1, perspective * 0.6);
      var warpBlue = Math.min(1, warpFactor / 5);
      var r = Math.floor(180 + colorShift * 75 * (1 - warpBlue * 0.3));
      var g = Math.floor(180 + colorShift * 75 * (1 - warpBlue * 0.1));
      var b = 255;

      // Draw star streak (elongated in direction of motion)
      if (streakLength > 3) {
        // Warp streak - stretched star
        starsXml +=
          '<View left="' +
          (screenX - streakLength / 2) +
          '" top="' +
          (screenY - size / 2) +
          '" ' +
          'width="' +
          streakLength +
          '" height="' +
          size +
          '" ' +
          'background-color="rgba(' +
          r +
          "," +
          g +
          "," +
          b +
          "," +
          brightness * 0.8 +
          ')" ' +
          'border-radius="' +
          size / 2 +
          '" ' +
          'rotate="' +
          angle +
          '"/>';

        // Bright head of the streak
        starsXml +=
          '<View left="' +
          (screenX - size / 2) +
          '" top="' +
          (screenY - size / 2) +
          '" ' +
          'width="' +
          size +
          '" height="' +
          size +
          '" ' +
          'background-color="rgba(255,255,255,' +
          brightness +
          ')" ' +
          'border-radius="50%"/>';
      } else {
        // Regular star when not moving fast
        starsXml +=
          '<View left="' +
          (screenX - size / 2) +
          '" top="' +
          (screenY - size / 2) +
          '" ' +
          'width="' +
          size +
          '" height="' +
          size +
          '" ' +
          'background-color="rgba(' +
          r +
          "," +
          g +
          "," +
          b +
          "," +
          brightness +
          ')" ' +
          'border-radius="50%"/>';
      }
    }
  }

  // Add central warp tunnel glow effect
  var warpGlow = Math.min(0.4, (warpFactor - 1) / 10) * warpFade;
  var warpTunnel = "";
  if (warpGlow > 0.05) {
    warpTunnel =
      '<View left="' +
      (centerX - 300) +
      '" top="' +
      (centerY - 300) +
      '" ' +
      'width="600" height="600" ' +
      'radial-gradient="rgba(100,150,255,' +
      warpGlow +
      '), rgba(50,50,150,0)" ' +
      'border-radius="50%"/>';
  }

  return (
    '<View width="100%" height="100%" linear-gradient="135deg, #0a0015, #000033 50%, #000020">' +
    warpTunnel +
    starsXml +
    glowRings +
    pulseGlowElement +
    '<Label left="' +
    (textX + shadowOffset) +
    '" top="' +
    (textY + shadowOffset) +
    '" ' +
    'font-size="' +
    fontSize +
    '" color="rgba(0,0,0,' +
    shadowOpacity +
    ')" ' +
    'text="TechTips" font-family="Sans Bold"/>' +
    '<Label left="' +
    textX +
    '" top="' +
    textY +
    '" ' +
    'font-size="' +
    fontSize +
    '" color="#ffffff" ' +
    'text="TechTips" font-family="Sans Bold"/>' +
    '<Label left="' +
    textX +
    '" top="' +
    (textY - 1) +
    '" ' +
    'font-size="' +
    fontSize +
    '" color="rgba(150,200,255,' +
    0.3 * easedSlide +
    ')" ' +
    'text="TechTips" font-family="Sans Bold"/>' +
    "</View>"
  );
}
