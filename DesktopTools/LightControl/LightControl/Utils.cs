using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace LightControl
{
    class Utils
    {
        public List<string> Output = new List<string>();

        public const byte BLACK = 0;
        public const byte WHITE = 1;
        public const byte RED = 2;
        public const byte MAGENTA = 3;
        public const byte BLUE = 4;
        public const byte CYAN = 5;
        public const byte GREEN = 6;
        public const byte YELLOW = 7;

        public const string RED_STRING = "RED";
        public const string GREEN_STRING = "GREEN";
        public const string BLUE_STRING = "BLUE";
        public const string YELLOW_STRING = "YELLOW";
        public const string MAGENTA_STRING = "MAGENTA";
        public const string CYAN_STRING = "CYAN";
        public const string WHITE_STRING = "WHITE";
        public const string BLACK_STRING = "BLACK";

        public byte ColorTextToNumber(string color)
        {
            switch (color.ToUpper())
            {
                case RED_STRING: return RED;
                case GREEN_STRING: return GREEN;
                case BLUE_STRING: return BLUE;
                case YELLOW_STRING: return YELLOW;
                case MAGENTA_STRING: return MAGENTA;
                case CYAN_STRING: return CYAN;
                case WHITE_STRING: return WHITE;
                case BLACK_STRING: return BLACK;
                default: return BLACK;
            }
        }

        public string ColorNumberToText(byte color)
        {
            switch (color)
            {
                case RED: return RED_STRING;
                case GREEN: return GREEN_STRING;
                case BLUE: return BLUE_STRING;
                case YELLOW: return YELLOW_STRING;
                case MAGENTA: return MAGENTA_STRING;
                case CYAN: return CYAN_STRING;
                case WHITE: return WHITE_STRING;
                case BLACK: return BLACK_STRING;
                default: return BLACK_STRING;
            }
        }


        private void SetText(string s)
        {
            Output.Add(s);
        }

        private float NormalizeColorChannel(float value)
        {
            if (value > 15)
            {
                return 15;
            }
            else if (value < 0)
            {
                return 0;
            }
            return value;
        }

        // to make a circular wave pattern (ie blue->white->blue)
        // colors: blue, white, blue
        // holds: 1, 1, 0
        // colorCount: 3
        // rampSize: 15

        // rampIncrements is the number of increments between two colors.
        // 15 is the maximum number of increments.
        //
        // colorCount > 0
        // 1 <= rampIncrements <= 15 
        public void CreateWave(byte[] colors, byte[] holds, byte colorCount, byte rampIncrements)
        {
            // Calculate the size of the wave:
            // All ramps are the same so start with number of ramps x number of colors in a ramp
            // then add all color holds.
            byte waveSize = (byte)((colorCount - 1) * (rampIncrements - 1));
            for (byte i = 0; i < colorCount; i++)
            {
                waveSize += holds[i];
            }
            SetText("Wave Size: " + waveSize + Environment.NewLine);
            // TODO: Allocate buffer to hold wave

            // Calculate the size of each increment in the ramp between colors (ie the slope of the ramp).
            // For example, rampIncrements of 3 means there are 3 steps between min and max values.
            //   0 - 5 - 10 - 15
            float increment = 1;
            if (rampIncrements < 15)
            {
                increment = (15 / (float)rampIncrements);
            }

            for (byte i = 0; i < colorCount; i++)
            {
                // Get color channel values of current color and setup ramp to next color.
                float red = 0;
                float green = 0;
                float blue = 0;

                float redIncrement = 0;
                float greenIncrement = 0;
                float blueIncrement = 0;

                switch (colors[i])
                {
                    case RED:
                        red = 15;
                        redIncrement = -1 * increment;
                        break;
                    case GREEN:
                        green = 15;
                        greenIncrement = -1 * increment;
                        break;
                    case BLUE:
                        blue = 15;
                        blueIncrement = -1 * increment;
                        break;
                    case YELLOW:
                        red = 15;
                        green = 15;
                        redIncrement = -1 * increment;
                        greenIncrement = -1 * increment;
                        break;
                    case MAGENTA:
                        red = 15;
                        blue = 15;
                        redIncrement = -1 * increment;
                        blueIncrement = -1 * increment;
                        break;
                    case CYAN:
                        green = 15;
                        blue = 15;
                        greenIncrement = -1 * increment;
                        blueIncrement = -1 * increment;
                        break;
                    case WHITE:
                        red = 15;
                        green = 15;
                        blue = 15;
                        redIncrement = -1 * increment;
                        greenIncrement = -1 * increment;
                        blueIncrement = -1 * increment;
                        break;
                    case BLACK:
                        red = 0;
                        green = 0;
                        blue = 0;
                        break;
                }

                // Add hold entries of current color.
                for (byte j = 0; j < holds[i]; j++)
                {
                    SetText((int)red + " " + (int)green + " " + (int)blue + Environment.NewLine);
                }

                // Add ramp to next color if there is one.
                if (i < (colorCount - 1))
                {
                    switch (colors[i + 1])
                    {
                        case RED:
                            redIncrement += increment;
                            break;
                        case GREEN:
                            greenIncrement += increment;
                            break;
                        case BLUE:
                            blueIncrement += increment;
                            break;
                        case YELLOW:
                            redIncrement += increment;
                            greenIncrement += increment;
                            break;
                        case MAGENTA:
                            redIncrement += increment;
                            blueIncrement += increment;
                            break;
                        case CYAN:
                            greenIncrement += increment;
                            blueIncrement += increment;
                            break;
                        case WHITE:
                            redIncrement += increment;
                            greenIncrement += increment;
                            blueIncrement += increment;
                            break;
                        case BLACK:
                            break;
                    }

                    for (byte j = 0; j < rampIncrements - 1; j++)
                    {
                        red = NormalizeColorChannel(red + redIncrement);
                        green = NormalizeColorChannel(green + greenIncrement);
                        blue = NormalizeColorChannel(blue + blueIncrement);

                        SetText((int)red + " " + (int)green + " " + (int)blue + Environment.NewLine);
                    }
                }
            }
        }

        // 1 <= primaryCount 
        // 1 <= secondaryCount
        // 2 <= rampCount  <= 16
        public void ColorShift(int primaryColor, int primaryCount, int secondaryColor, int secondaryCount, int rampCount, bool fullWave)
        {
            // Bound input parameters to valid ranges.
            if (primaryCount < 1)
            {
                primaryCount = 1;
            }
            if (secondaryCount < 1)
            {
                secondaryCount = 1;
            }
            if (rampCount < 2 || rampCount > 16)
            {
                rampCount = 16;
            }

            int waveSize = primaryCount + secondaryCount + rampCount - 2;
            if (fullWave)
            {
                waveSize += rampCount - 2;
            }

            SetText("Wave Size: " + waveSize + Environment.NewLine);

            // This is the increment between each step in the ramp between colors.
            // For example, a ramp of 4 will have 3 increments between min and max values.
            //   0 - 5 - 10 - 15
            float rampIncrement = 1;
            if (rampCount < 16)
            {
                rampIncrement = (15 / ((float)rampCount - 1));
            }

            float red = 0;
            float green = 0;
            float blue = 0;

            float redIncrement = 0;
            float greenIncrement = 0;
            float blueIncrement = 0;

            switch (primaryColor)
            {
                case RED:
                    red = 15;
                    redIncrement = -1 * rampIncrement;
                    break;
                case GREEN:
                    green = 15;
                    greenIncrement = -1 * rampIncrement;
                    break;
                case BLUE:
                    blue = 15;
                    blueIncrement = -1 * rampIncrement;
                    break;
                case YELLOW:
                    red = 15;
                    green = 15;
                    redIncrement = -1 * rampIncrement;
                    greenIncrement = -1 * rampIncrement;
                    break;
                case MAGENTA:
                    red = 15;
                    blue = 15;
                    redIncrement = -1 * rampIncrement;
                    blueIncrement = -1 * rampIncrement;
                    break;
                case CYAN:
                    green = 15;
                    blue = 15;
                    greenIncrement = -1 * rampIncrement;
                    blueIncrement = -1 * rampIncrement;
                    break;
                case WHITE:
                    red = 15;
                    green = 15;
                    blue = 15;
                    redIncrement = -1 * rampIncrement;
                    greenIncrement = -1 * rampIncrement;
                    blueIncrement = -1 * rampIncrement;
                    break;
                case BLACK:
                    red = 0;
                    green = 0;
                    blue = 0;
                    break;
            }

            switch (secondaryColor)
            {
                case RED:
                    redIncrement += rampIncrement;
                    break;
                case GREEN:
                    greenIncrement += rampIncrement;
                    break;
                case BLUE:
                    blueIncrement += rampIncrement;
                    break;
                case YELLOW:
                    redIncrement += rampIncrement;
                    greenIncrement += rampIncrement;
                    break;
                case MAGENTA:
                    redIncrement += rampIncrement;
                    blueIncrement += rampIncrement;
                    break;
                case CYAN:
                    greenIncrement += rampIncrement;
                    blueIncrement += rampIncrement;
                    break;
                case WHITE:
                    redIncrement += rampIncrement;
                    greenIncrement += rampIncrement;
                    blueIncrement += rampIncrement;
                    break;
                case BLACK:
                    break;
            }

            // Solid Primary
            for (int i = 0; i < primaryCount; i++)
            {
                SetText((int)red + " " + (int)green + " " + (int)blue + Environment.NewLine);
            }

            // Ramp down to secondary
            for (int i = 0; i < rampCount - 1; i++)
            {
                red = NormalizeColorChannel(red + redIncrement);
                green = NormalizeColorChannel(green + greenIncrement);
                blue = NormalizeColorChannel(blue + blueIncrement);

                SetText((int)red + " " + (int)green + " " + (int)blue + Environment.NewLine);
            }

            // Solid secondary
            for (int i = 1; i < secondaryCount; i++)
            {
                SetText((int)red + " " + (int)green + " " + (int)blue + Environment.NewLine);
            }

            if (fullWave)
            {
                // Ramp back up to primary
                redIncrement *= -1;
                greenIncrement *= -1;
                blueIncrement *= -1;
                for (int i = 0; i < rampCount - 2; i++)
                {
                    red = NormalizeColorChannel(red + redIncrement);
                    green = NormalizeColorChannel(green + greenIncrement);
                    blue = NormalizeColorChannel(blue + blueIncrement);

                    SetText((int)red + " " + (int)green + " " + (int)blue + Environment.NewLine);
                }
            }
        }

        public void GetWheelColor(UInt16 pos)
        {
            int r = 0, g = 0, b = 0;
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

            SetText(r + " " + g + " " + b + Environment.NewLine);

            return;
        }


        // This color wheel variation eliminates the duplicate primary colors (rgb).
        // There are 45 positions (0-44)
        public void GetWheelColor2(UInt16 pos)
        {
            int r = 0, g = 0, b = 0;
            switch (pos / 15)
            {
                case 0:
                    r = 15 - pos % 15;  // red down
                    g = pos % 15;       // green up
                    b = 0;              // blue off
                    break;
                case 1:
                    g = 15 - pos % 15;  // green down
                    b = pos % 15;       // blue up
                    r = 0;              // red off
                    break;
                case 2:
                    b = 15 - pos % 15; // blue down
                    r = pos % 15;      // red up
                    g = 0;             // green off
                    break;
            }

            SetText(r + " " + g + " " + b + Environment.NewLine);

            return;
        }



        /*
Red Yellow Green Cyan Blue Magenta

Red -> Yellow   15
Yellow -> Green 15
Green -> Cyan   15
Cyan -> Blue    15
Blue -> Magenta 15
Magenta -> Red  15

0   -   15 Reds
16  -   31 Yellows
32  -   47 Greens
48  -   63 Cyans
64  -   79 Blues
80  -   95 Magentas
96  -   101 
*/

        // This color wheel variation cycles through all possible color variations.
        // There are 90 positions (0-89)
        public void GetWheelColor3(UInt16 pos)
        {
            int r = 0, g = 0, b = 0;
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

            SetText(r + " " + g + " " + b + Environment.NewLine);

            return;
        }

    }
}
