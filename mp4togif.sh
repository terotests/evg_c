#!/bin/bash
# Convert MP4 video to high-quality animated GIF
# Usage: ./mp4togif.sh input.mp4 output.gif [width]

INPUT="$1"
OUTPUT="$2"
WIDTH="${3:-400}"

if [ -z "$INPUT" ] || [ -z "$OUTPUT" ]; then
    echo "Usage: $0 input.mp4 output.gif [width]"
    echo "  width: optional, default 400 pixels"
    exit 1
fi

if [ ! -f "$INPUT" ]; then
    echo "Error: Input file '$INPUT' not found"
    exit 1
fi

echo "Converting $INPUT to $OUTPUT (width: ${WIDTH}px)..."

# Two-pass GIF creation for best quality:
# Pass 1: Generate optimal palette
# Pass 2: Create GIF using that palette

ffmpeg -y -i "$INPUT" -vf "fps=15,scale=${WIDTH}:-1:flags=lanczos,palettegen=stats_mode=diff" /tmp/palette.png

ffmpeg -y -i "$INPUT" -i /tmp/palette.png -lavfi "fps=15,scale=${WIDTH}:-1:flags=lanczos[x];[x][1:v]paletteuse=dither=bayer:bayer_scale=5:diff_mode=rectangle" "$OUTPUT"

rm -f /tmp/palette.png

echo "Done! Created $OUTPUT"
ls -lh "$OUTPUT"
