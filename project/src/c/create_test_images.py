#!/usr/bin/env python3
"""Create test images for the video encoder image loading test."""

from PIL import Image, ImageDraw

# Create sample.png - red background with text
img = Image.new('RGB', (200, 150), color='red')
draw = ImageDraw.Draw(img)
draw.text((50, 65), 'Sample PNG', fill='white')
img.save('sample.png')
print('Created sample.png')

# Create test.jpg - green background with text  
img2 = Image.new('RGB', (200, 150), color='green')
draw2 = ImageDraw.Draw(img2)
draw2.text((60, 65), 'Test JPG', fill='white')
img2.save('test.jpg')
print('Created test.jpg')

print('Done! Created sample.png and test.jpg')
