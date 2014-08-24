
#include <RainbowUtils.h>

color_t GetWheelColor(byte pos)
{
    byte r, g, b;
    switch (pos / 16)
    {
    case 0:
        r = 15 - pos % 16;  // red down
        g = pos % 16;       // green up
        b = 0;              // blue off
        break;
    case 1:
        g = 15 - pos % 16;  // green down
        b = pos % 16;       // blue up
        r = 0;              // red off
        break;
    case 2:
        b = 15 - pos % 16; // blue down
        r = pos % 16;      // red up
        g = 0;             // green off
        break;
    }
    return (COLOR(r,g,b));
}

color_t GetLineRGColor(byte pos)
{
    byte r, g, b;
    switch (pos / 16)
    {
    case 0:
        r = 15 - pos % 16;  // red down
        g = pos % 16;       // green up
        b = 0;              // blue off
        break;
    case 1:
        r = pos % 16;       // red up
        g = 15 - pos % 16;  // green down
        b = 0;              // blue off
        break;
    }
    return (COLOR(r,g,b));
}

color_t GetLineGBColor(byte pos)
{
    byte r, g, b;
    switch (pos / 16)
    {
    case 0:
        r = 0;              // red off
        g = 15 - pos % 16;  // green down
        b = pos % 16;       // blue up
        break;
    case 1:
        r = 0;              // red off
        g = pos % 16;       // green up
        b = 15 - pos % 16;  // blue down
        break;
    }
    return (COLOR(r,g,b));
}

color_t GetLineBRColor(byte pos)
{
    byte r, g, b;
    switch (pos / 16)
    {
    case 0:
        r = pos % 16;       // red up
        g = 0;              // green off
        b = 15 - pos % 16;  // blue down
        break;
    case 1:
        r = 15 - pos % 16;  // red down
        g = 0;              // green off
        b = pos % 16;       // blue up
        break;
    }
    return (COLOR(r,g,b));
}

// This color wheel variation cycles through all possible color variations.
// There are 90 positions (0-89)
color_t GetSmoothWheelColor(byte pos)
{
    byte r, g, b;
    switch (pos / 15)
    {
        case 0: // Red -> Yellow
            r = 15;             // red full
            g = pos % 15;       // green up
            b = 0;              // blue off
            break;
        case 1: // Yellow -> Green
            r = 15 - pos % 15;  // red down
            g = 15;             // green full
            b = 0;              // blue off
            break;
        case 2: // Green -> Cyan
            r = 0;              // red off
            g = 15;             // green full
            b = pos % 15;       // blue up
            break;
        case 3: // Cyan -> Blue
            r = 0;              // red off
            g = 15 - pos % 15;  // green down
            b = 15;             // blue full
            break;
        case 4: // Blue -> Magenta
            r = pos % 15;       // red up
            g = 0;              // green off
            b = 15;             // blue full
            break;
        case 5: // Magenta -> Red
            r = 15;             // red full
            g = 0;              // green off
            b = 15 - pos % 15;  // blue down
            break;
    }

    return COLOR(r, g, b);
}

