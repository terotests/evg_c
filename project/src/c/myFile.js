var doSomeFoo = function () {
  var time = new Date().getTime();
  return "<Image src='kala" + time + ".jpg'></Image>";
};

var startTime = new Date().getTime();

function imageStrip() {
  return '                    <View width="100%" >\n                        \n                        \n                        <View margin="10px" margin-top="0px" margin-left="0px" margin-right="0px">\n                            <View width="20%" height="20%" margin="1px" background-color="#b185B8"\n                                border-radius="0%"\n                                overflow="hidden"\n                                >\n                                <Image src="/static/ilves.png" opacity="0.2" width="100%" height="100%"/>\n                            </View>\n                            <View width="20%" height="20%" margin="1px" background-color="#b185B8"\n                                border-radius="0%"\n                                overflow="hidden"\n                                >\n                                <Image src="/static/ilves.png" opacity="0.2" width="100%" height="100%"/>\n                            </View>\n                            <View width="20%" height="20%" margin="1px" background-color="#b185B8"\n                                border-radius="0%"\n                                overflow="hidden"\n                                >\n                                <Image src="/static/ilves.png" opacity="0.2" width="100%" height="100%"/>\n                            </View>\n                            <View width="20%" height="20%" margin="1px" background-color="#b185B8"\n                                border-radius="0%"\n                                overflow="hidden"\n                                >\n                                <Image src="/static/ilves.png" opacity="0.2" width="100%" height="100%"/>\n                            </View>\n                            <View width="20%" height="20%" margin="1px" background-color="#b185B8"\n                                border-radius="0%"\n                                overflow="hidden"\n                                >\n                                <Image src="/static/ilves.png" opacity="0.2" width="100%" height="100%"/>\n                            </View>       \n                            \n                            <View left="0" top="15%"\n                                height="5%"\n                                padding-left="14"\n                                linear-gradient="rgba(0,0,0,0),rgba(0,0,0,0.4)"\n                                padding="3"\n                                ><Label color="#ffffff" margin-left="-2" margin-top="-2" opacity="1" id=\'text\'></Label></View>                \n                        </View>\n                        \n                        \n                    </View>';
}

function createPhone(x, y, content, rotation) {
  content = content ? content : "";
  return (
    '<View width="395" rotate="' +
    rotation +
    '" left="' +
    x +
    '" top="' +
    y +
    '">\n    <View width="395" shadow-radius="10px" background-color="#363156" rotate="30" padding="10" border-radius="20px"\n        >\n\n' +
    '<View width="100%" align="center" padding="6px">\n            <View \n                background-color="#ffffff" width="50px" height="10px"\n                border-radius="15px"\n            />\n  ' +
    '      </View> \n        <View width="375" height="667" overflow="hidden" id="screen" background-color="#ffffff">\n            <View id="scroll" left="0" top="0">' +
    content +
    '</View>\n        </View>      \n        \n        <View width="100%" align="center" padding="6px">\n            <View \n                background-color="#ffffff" width="50px" height="50px"\n                border-radius="50%"\n            />\n        </View>        \n    </View>\n</View>'
  );
}
function createBox(line, x, y, startAngle, speedX, speedY) {
  var x = Math.sin(line * speedX + startAngle) * 100 + x;
  var y = Math.cos(line * speedY + startAngle) * 100 + y;
  return (
    '<View width="30" height="30" border-radius="10%" left="' +
    x +
    '" top="' +
    y +
    '" background-color="rgba(' +
    (line % 255) +
    ',122,0,0.7)"></View>'
  );
}

function createParticle(x, y, width, height, intensity) {
  if (intensity < 0) intensity = 0;
  // return '<View left="'+x+'" top="'+y+'" border-radius="10%" width="10" height="10" background-color="rgba(255,122,0,'+intensity+')"></View>';

  return (
    '<View left="' +
    x +
    '" top="' +
    y +
    '" width="30" height="30" radial-gradient="white, rgba(255,255,255,0.1) 10% , white 30%, rgba(0,0,255,0.1)" border-radius="50%"></View>'
  );
}

function overlay() {
  return '<View width="100%" height="50hp" linear-gradient="rgba(18, 18, 50, 0.3), rgba(242, 162, 242, 0.5)" left="0" top="50hp"></View>';
}

// Should return the view XML ...
function processLine(line) {
  var a = Math.sin((line + 50) * 0.03);

  // Magenta : rgb(255,0,255)
  // CYAN:     rgb(0,255,255)

  var op1 = 0.5 + a * 0.5;
  var op2 = 1 - op1;

  var str = '<View width="100%" height="100hp" background-color="#ffffcc">';

  str += createPhone(line, line, imageStrip(), 15 + a * 10);

  for (var i = 0; i < 10; i++) {
    str += createBox(line, i * 20, i * 20, i / 10, 0.1, 0.12);
  }

  var n = 30;
  for (var i = 0; i < n; i++) {
    var direction = (i / n) * 2 * Math.PI;
    var pos_x = 150 + Math.cos(direction) * line;
    var pos_y = 150 + Math.sin(direction) * line;
    var width = 30;
    var intensity = 1 - line / 60;
    str += createParticle(pos_x, pos_y, width, width, intensity);
  }

  str += overlay();

  str += "</View>";

  return str;
  // return '<View width="100%" height="100hp" background-color=""><View width="'+line+'" height="'+line+'" border-radius="50%" background-color="rgba(255,255,255,'+a+')"></View></View>';
}
