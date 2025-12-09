# Sample Prompts for Testing EVG GenAI

Use these prompts to test the `GENAI_PROMPT.md` system prompt with any AI assistant.

---

## How to Test

1. Copy the entire contents of `GENAI_PROMPT.md` as the **system prompt** (or paste it at the start of your conversation)
2. Use one of the user prompts below
3. The AI should generate a complete JavaScript file you can run with EVG

---

## Test Prompt 1: Loading Spinner (Medium Difficulty)

```
Create a 4-second video showing a loading spinner animation. The spinner should be a circle of 8 dots that rotate around a center point. The background should be dark (#1a1a2e) and the dots should be light blue (#00d4ff). Make each dot fade based on its position in the rotation to create a trailing effect.
```

---

## Test Prompt 2: Fade In/Out Text (Simple)

```
Make a 3-second video with the text "Hello World" centered on screen. The text should fade in from transparent over the first second, stay fully visible for 1 second, then fade out over the last second. Use a white background and black text with font size 64.
```

---

## Test Prompt 3: Bouncing DVD Logo (Medium)

```
Create a 5-second video of a red square (100x100 pixels) that bounces diagonally across the screen like a DVD screensaver logo. When it hits an edge, it should bounce off. Use a black background. The video resolution is 800x600.
```

---

## Test Prompt 4: YouTube Intro (Complex)

```
Generate a 3-second intro animation for a YouTube channel called "TechTips".
- Dark purple to blue gradient background
- The text "TechTips" should slide in from the left side
- A glowing circle should expand from behind the text
- Add a subtle pulsing effect to the final frame
```

---

## Test Prompt 5: Particle Explosion (Complex)

```
Create a 2-second video showing a particle explosion effect. Start with all particles at the center, then have them burst outward in all directions. Use 20 small circles as particles with random colors (reds, oranges, yellows). The background should be black. Particles should slow down as they move outward.
```

---

## Test Prompt 6: Progress Bar (Simple)

```
Make a 5-second video showing a progress bar that fills from 0% to 100%. The bar should be 400 pixels wide and 30 pixels tall, centered on a gray (#333333) background. The filled portion should be green (#00ff00) and the empty portion should be dark gray (#666666). Show the percentage as text above the bar.
```

---

## Test Prompt 7: Countdown Timer (Medium)

```
Create a 5-second countdown video showing numbers 5, 4, 3, 2, 1 in sequence. Each number should:
- Appear in the center of the screen
- Scale up slightly when appearing
- Fade out before the next number appears
Use a dark blue background and white text with font size 120.
```

---

## Test Prompt 8: Rotating Squares (Medium)

```
Make a 4-second video with 3 nested squares rotating at different speeds. The outer square (200x200) rotates slowly, the middle square (140x140) rotates at medium speed in the opposite direction, and the inner square (80x80) rotates quickly. Use different colors for each: red outer, green middle, blue inner. Center everything on a white background.
```

---

## Expected Output Format

The AI should respond with a complete JavaScript file like:

```javascript
function processLine(time) {
  if (time > X) return "";

  // Animation logic here

  return `<View width="100%" height="100%">
        <!-- Generated content -->
    </View>`;
}
```

---

## Running the Generated Code

Save the AI's output to a `.js` file and run:

```bash
./encoder -j generated.js -o output.mp4 -r 30 -w 800 -h 600
```
