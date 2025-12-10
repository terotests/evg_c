// Test JavaScript file for testing image loading in video encoder
// This file tests loading images from relative paths

function processLine(time) {
  // 5 second animation
  if (time > 5.0) return "";

  var width = 800;
  var height = 600;

  var xml = "";

  // Background
  xml += '<View width="100%" height="100%" background-color="#2C3E50">';

  // Title text
  xml +=
    '<Label left="250" top="30" font-size="32" color="#FFFFFF" text="Image Loading Test"/>';

  // Test image 1 - sample.png (should be in same directory as this JS file)
  // Using relative path
  xml += '<View left="50" top="100" width="200" height="150" ';
  xml += 'background-color="#34495E" border-radius="10">';
  xml += '<View left="0" top="0" width="200" height="150" ';
  xml += 'image-url="sample.png"/>';
  xml += "</View>";

  // Label for image 1
  xml +=
    '<Label left="50" top="260" font-size="16" color="#ECF0F1" text="sample.png (relative)"/>';

  // Test image 2 - debug_frame_000.png (should be in same directory)
  xml += '<View left="300" top="100" width="200" height="150" ';
  xml += 'background-color="#34495E" border-radius="10">';
  xml += '<View left="0" top="0" width="200" height="150" ';
  xml += 'image-url="debug_frame_000.png"/>';
  xml += "</View>";

  // Label for image 2
  xml +=
    '<Label left="300" top="260" font-size="16" color="#ECF0F1" text="debug_frame_000.png"/>';

  // Test image 3 - debug_frame.png
  xml += '<View left="550" top="100" width="200" height="150" ';
  xml += 'background-color="#34495E" border-radius="10">';
  xml += '<View left="0" top="0" width="200" height="150" ';
  xml += 'image-url="debug_frame.png"/>';
  xml += "</View>";

  // Label for image 3
  xml +=
    '<Label left="550" top="260" font-size="16" color="#ECF0F1" text="debug_frame.png"/>';

  // Animation: moving indicator bar
  var barX = 50 + (time / 5.0) * 700;
  xml += '<View left="' + barX + '" top="350" width="50" height="10" ';
  xml += 'background-color="#E74C3C" border-radius="5"/>';

  // Status text
  xml += '<Label left="50" top="380" font-size="18" color="#BDC3C7" ';
  xml += 'text="Time: ' + time.toFixed(2) + 's"/>';

  // Instructions
  xml += '<Label left="50" top="450" font-size="14" color="#7F8C8D" ';
  xml +=
    'text="Images are loaded relative to the JavaScript file directory."/>';

  xml += '<Label left="50" top="480" font-size="14" color="#7F8C8D" ';
  xml += 'text="Note: Only PNG format is supported (Cairo limitation)."/>';

  // Show base path info
  xml += '<Label left="50" top="520" font-size="12" color="#95A5A6" ';
  xml += 'text="Testing: sample.png, debug_frame_000.png, debug_frame.png"/>';

  xml += "</View>";

  return xml;
}
