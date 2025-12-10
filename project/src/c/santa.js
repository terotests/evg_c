// Santa Claus Sleigh Ride Animation
// A silhouette of Santa's sleigh with reindeer flying across a night sky

function processLine(time) {
  // 8 second animation
  if (time > 8.0) return "";

  // === SVG PATHS ===

  // Reindeer silhouette (simplified, facing right)
  var reindeerPath =
    "M0,20 L5,15 L8,18 L10,10 L12,5 L15,8 L14,12 L18,10 L22,12 L20,15 L25,14 L30,16 L28,20 L32,22 L30,28 L25,26 L20,28 L15,26 L10,28 L5,25 L0,28 Z M12,3 L14,0 L16,4 M16,3 L18,0 L19,4";

  // Sleigh silhouette
  var sleighPath =
    "M0,15 Q5,5 15,5 L45,5 Q55,5 55,15 L55,25 Q55,35 45,35 L10,35 Q0,35 0,25 Z M5,35 Q0,40 5,45 L15,45 Q20,40 15,35 M40,35 Q35,40 40,45 L50,45 Q55,40 50,35";

  // Santa in sleigh (simplified silhouette)
  var santaPath =
    "M20,5 Q25,-5 30,5 L35,5 Q38,0 35,5 L35,15 L15,15 L15,5 Z M22,15 L22,25 L32,25 L32,15 M18,25 L18,30 L35,30 L35,25";

  // Star path
  var starPath =
    "M0,-10 L2,-3 L10,-3 L4,2 L6,10 L0,5 L-6,10 L-4,2 L-10,-3 L-2,-3 Z";

  // Moon crescent
  var moonPath = "M0,0 A40,40 0 1,1 0,80 A30,30 0 1,0 0,0";

  // === ANIMATION CALCULATIONS ===

  // Sleigh moves from right to left across the sky
  var sleighX = 900 - time * 120; // Move left over time
  var sleighY = 150 + Math.sin(time * 2) * 20; // Gentle bobbing

  // Slight rotation for dynamic feel
  var sleighRotate = Math.sin(time * 3) * 3;

  // Reindeer positions (4 reindeer in formation)
  var reindeerSpacing = 45;
  var reindeerLeadX = sleighX - 60;

  // Leg animation for reindeer (galloping effect)
  var legPhase = time * 8;

  // Stars twinkling
  var stars = [];
  var starPositions = [
    { x: 50, y: 50 },
    { x: 150, y: 80 },
    { x: 250, y: 40 },
    { x: 350, y: 100 },
    { x: 450, y: 60 },
    { x: 550, y: 90 },
    { x: 650, y: 45 },
    { x: 750, y: 75 },
    { x: 100, y: 150 },
    { x: 300, y: 180 },
    { x: 500, y: 140 },
    { x: 700, y: 170 },
    { x: 80, y: 250 },
    { x: 200, y: 220 },
    { x: 400, y: 260 },
    { x: 600, y: 230 },
  ];

  for (var i = 0; i < starPositions.length; i++) {
    var twinkle = 0.5 + Math.sin(time * 3 + i * 0.7) * 0.5;
    var starSize = 3 + Math.sin(time * 4 + i) * 1;
    stars.push(
      '<View left="' +
        starPositions[i].x +
        '" top="' +
        starPositions[i].y +
        '" width="' +
        starSize +
        '" height="' +
        starSize +
        '" background-color="#ffffff" border-radius="50%" opacity="' +
        twinkle +
        '"/>'
    );
  }

  // Build reindeer elements (2 rows of 2)
  var reindeer = [];
  for (var r = 0; r < 4; r++) {
    var row = Math.floor(r / 2);
    var col = r % 2;
    var rx = reindeerLeadX - row * reindeerSpacing;
    var ry = sleighY - 10 + col * 25 - 12;
    var bounce = Math.sin(legPhase + r * 0.5) * 5;

    reindeer.push(
      '<View left="' +
        rx +
        '" top="' +
        (ry + bounce) +
        '" width="35" height="30" opacity="1">' +
        '<View width="35" height="30" background-color="#4a3728" path="' +
        reindeerPath +
        '"/>' +
        "</View>"
    );
  }

  // Reins connecting reindeer to sleigh
  var reinsY = sleighY + 5;

  // Snow particles falling
  var snowflakes = [];
  for (var s = 0; s < 30; s++) {
    var sx = (s * 27 + time * 30) % 850;
    var sy = (s * 31 + time * 50) % 600;
    var ssize = 2 + (s % 3);
    var sopacity = 0.3 + (s % 5) * 0.1;
    snowflakes.push(
      '<View left="' +
        sx +
        '" top="' +
        sy +
        '" width="' +
        ssize +
        '" height="' +
        ssize +
        '" background-color="#ffffff" border-radius="50%" opacity="' +
        sopacity +
        '"/>'
    );
  }

  // Ground with snow
  var groundY = 520;

  // Trees silhouette positions
  var trees = [];
  var treePositions = [50, 150, 280, 380, 500, 620, 720];
  for (var t = 0; t < treePositions.length; t++) {
    var treeHeight = 60 + (t % 3) * 20;
    var treeX = treePositions[t];
    trees.push(
      '<View left="' +
        treeX +
        '" top="' +
        (groundY - treeHeight) +
        '" width="40" height="' +
        treeHeight +
        '">' +
        '<View left="15" top="' +
        (treeHeight - 20) +
        '" width="10" height="20" background-color="#2d1810"/>' +
        '<View left="0" top="0" width="40" height="' +
        (treeHeight - 15) +
        '" background-color="#1a472a" path="M20,0 L40,' +
        (treeHeight - 15) +
        " L0," +
        (treeHeight - 15) +
        ' Z"/>' +
        "</View>"
    );
  }

  // "HO HO HO" text appearing
  var hoText = "";
  if (time > 2 && time < 4) {
    var hoOpacity = Math.min(1, time - 2);
    hoText =
      '<Label left="' +
      (sleighX - 30) +
      '" top="' +
      (sleighY - 50) +
      '" font-size="24" color="#ffffff" opacity="' +
      hoOpacity +
      '" text="HO HO HO!"/>';
  }

  // Moon
  var moonGlow = 0.8 + Math.sin(time * 0.5) * 0.1;

  return (
    "" +
    '<View width="100%" height="100%" background-color="#0a0a20">' +
    // Sky gradient
    '<View left="0" top="0" width="100%" height="70%" linear-gradient="#0a0a20, #1a1a40"/>' +
    // Moon
    '<View left="650" top="30" width="80" height="80" opacity="' +
    moonGlow +
    '">' +
    '<View width="80" height="80" background-color="#fffacd" border-radius="50%"/>' +
    '<View left="15" top="5" width="60" height="60" background-color="#0a0a20" border-radius="50%"/>' +
    "</View>" +
    // Stars
    stars.join("") +
    // Snowflakes
    snowflakes.join("") +
    // Reindeer
    reindeer.join("") +
    // Connection lines (reins) - simplified as a dark line
    '<View left="' +
    (reindeerLeadX + 30) +
    '" top="' +
    reinsY +
    '" width="' +
    (sleighX - reindeerLeadX - 25) +
    '" height="2" background-color="#3d2817" opacity="0.7"/>' +
    // Sleigh
    '<View left="' +
    sleighX +
    '" top="' +
    sleighY +
    '" width="60" height="50" rotate="' +
    sleighRotate +
    '">' +
    // Sleigh body
    '<View width="55" height="35" background-color="#8b0000" border-radius="10"/>' +
    // Sleigh runners
    '<View left="0" top="30" width="60" height="8" background-color="#4a3728" border-radius="5"/>' +
    // Santa silhouette
    '<View left="10" top="-20" width="35" height="30">' +
    // Body
    '<View left="5" top="10" width="25" height="20" background-color="#cc0000" border-radius="5"/>' +
    // Head
    '<View left="10" top="0" width="15" height="15" background-color="#ffdbac" border-radius="50%"/>' +
    // Hat
    '<View left="8" top="-8" width="18" height="12" background-color="#cc0000" border-radius="3"/>' +
    '<View left="22" top="-10" width="8" height="8" background-color="#ffffff" border-radius="50%"/>' +
    // Beard
    '<View left="8" top="8" width="18" height="10" background-color="#ffffff" border-radius="0 0 10px 10px"/>' +
    "</View>" +
    // Gift sack
    '<View left="35" top="-10" width="20" height="25" background-color="#8b4513" border-radius="10 10 5 5"/>' +
    "</View>" +
    // HO HO HO text
    hoText +
    // Ground snow
    '<View left="0" top="' +
    groundY +
    '" width="100%" height="80" background-color="#f0f8ff"/>' +
    '<View left="0" top="' +
    (groundY - 10) +
    '" width="100%" height="20" linear-gradient="rgba(240,248,255,0), #f0f8ff"/>' +
    // Trees
    trees.join("") +
    // Snow mounds
    '<View left="0" top="' +
    (groundY + 10) +
    '" width="120" height="40" background-color="#ffffff" border-radius="50%"/>' +
    '<View left="200" top="' +
    (groundY + 15) +
    '" width="80" height="30" background-color="#ffffff" border-radius="50%"/>' +
    '<View left="400" top="' +
    (groundY + 5) +
    '" width="150" height="50" background-color="#ffffff" border-radius="50%"/>' +
    '<View left="650" top="' +
    (groundY + 12) +
    '" width="100" height="35" background-color="#ffffff" border-radius="50%"/>' +
    // Title
    '<Label left="20" top="550" font-size="18" color="#ffffff" opacity="0.6" text="Merry Christmas!"/>' +
    "</View>"
  );
}
