# evg - Experimental Video Generator

> ⚠️ **EXPERIMENTAL PROJECT** - This is an experimental project and is not intended for production use. The API and functionality may change without notice.

## Overview

EVG (Experimental Video Generator) is a C-based video encoding system that generates video frames programmatically using JavaScript and XML-based UI definitions. The system renders UI components to video frames using Cairo graphics library and encodes them using FFmpeg/libav libraries.

## How It Works

The algorithm works in the following way:

1. **JavaScript Frame Generation**: A JavaScript file (powered by Duktape engine) defines a `processLine(frameNumber)` function that returns XML markup for each video frame
2. **XML Parsing**: The XML markup is parsed using libxml2 to create a UI structure tree
3. **Layout Calculation**: The system calculates layout positions for UI elements (similar to CSS flexbox concepts)
4. **Cairo Rendering**: UI elements are rendered to a Cairo surface with support for:
   - Text rendering with custom fonts (via FreeType)
   - Images
   - SVG paths
   - Gradients (linear and radial)
   - Rounded rectangles
   - Opacity and transformations
5. **Video Encoding**: Frames are encoded to video using FFmpeg/libav libraries

## Command Line Usage

```bash
# Video encoding (JavaScript to video)
./encoder -j <js_file> -o <output> [options]

# XML to PDF conversion
./encoder -i <input_xml> -o <output_pdf>
```

### Options

| Option | Description                                       |
| ------ | ------------------------------------------------- |
| `-j`   | JavaScript file for video frame generation        |
| `-o`   | Output file (video or PDF)                        |
| `-i`   | Input XML file (for PDF mode)                     |
| `-r`   | Framerate in fps (default: 25, range: 1-120)      |
| `-w`   | Video width in pixels (default: 800, max: 7680)   |
| `-h`   | Video height in pixels (default: 600, max: 4320)  |
| `-b`   | Bitrate in kbps (default: 800, range: 100-50000)  |

### Examples

```bash
# Generate video with default settings (800x600, 25fps, 800kbps)
./encoder -j myFile.js -o output.mp4

# Generate HD video at 30fps
./encoder -j myFile.js -o output.mp4 -w 1280 -h 720 -r 30

# Generate Full HD video with high quality
./encoder -j myFile.js -o output.mp4 -w 1920 -h 1080 -r 30 -b 4000

# Generate 4K video at 60fps
./encoder -j myFile.js -o output.mp4 -w 3840 -h 2160 -r 60 -b 20000
```

### JavaScript API

The `processLine(time)` function receives time in seconds as a floating-point number:

- At 25fps: `0.0, 0.04, 0.08, 0.12, ...`
- At 30fps: `0.0, 0.033, 0.067, 0.1, ...`
- At 60fps: `0.0, 0.0167, 0.033, 0.05, ...`

Return an empty string `""`, `false`, or `undefined` to stop video generation.

```javascript
function processLine(time) {
  // Stop after 5 seconds
  if (time > 5.0) {
    return "";
  }

  // Create animation based on time
  var x = Math.sin(time * 2) * 100;
  return '<View left="' + x + '" ...></View>';
}
```

## Technical Components

The system consists of the following main components:

| Component         | File                    | Description                            |
| ----------------- | ----------------------- | -------------------------------------- |
| Video Encoder     | `video_encoder.c`       | Main entry point, video encoding logic |
| UI Structure      | `UIStructure.c/h`       | Data structures for UI elements        |
| XML Parser        | `UIXMLParser.c/h`       | Parses XML markup into UI structure    |
| Layout Calculator | `UICalculateLayout.c/h` | Calculates positions and sizes         |
| Text Rendering    | `UINativeText.c/h`      | Font loading and text rendering        |
| Linked List       | `EVGLinkedList.c/h`     | Generic linked list implementation     |
| JavaScript Engine | `duktape.c/h`           | Embedded Duktape JS engine             |

### External Libraries Used

- **Cairo** - 2D graphics library for rendering
- **FreeType** - Font rendering
- **libxml2** - XML parsing
- **FFmpeg/libav** - Video encoding (libavcodec, libavformat, libavutil)
- **Duktape** - Embedded JavaScript engine
- **GTK3** - GUI toolkit (development headers)

## Installation Requirements

The project requires the following dependencies (as specified in the Dockerfile):

### System Packages (Ubuntu/Debian)

```bash
apt-get install -y gcc
apt-get install -y ffmpeg
apt-get install -y wget
apt-get install -y xz-utils
apt-get install -y build-essential
apt-get install -y libcairo2-dev
apt-get install -y libgtk-3-dev
apt-get install -y libxml2-dev
apt-get install -y libavcodec-dev
apt-get install -y libavutil-dev
apt-get install -y libavformat-dev
apt-get install -y libfreetype6-dev
```

### Duktape JavaScript Engine

Download and extract Duktape:

```bash
wget https://duktape.org/duktape-2.5.0.tar.xz
tar xvf duktape-2.5.0.tar.xz
```

## Building with Docker (Recommended)

Building the Docker image:

```bash
docker build -t evg-video docker
```

Starting the container:

```bash
docker run -it -v $(pwd)/project:/project evg-video /bin/bash
```

## Building from Source

Inside the `project/src/c` directory:

```bash
make
```

## Project Structure

```
evg_c/
├── docker/
│   └── Dockerfile          # Docker build configuration
├── project/
│   ├── bin/
│   │   └── encoder         # Compiled binary
│   └── src/
│       ├── c/              # C source code
│       ├── js/             # JavaScript files
│       └── templates/      # XML template files
├── build.sh
└── README.md
```

## License

This is an experimental project. Please check individual component licenses (especially Duktape and FFmpeg) for usage terms.
