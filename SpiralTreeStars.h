#ifndef INCLUDE_SPIRAL_TREE_STARS_H
#define INCLUDE_SPIRAL_TREE_STARS_H

#include <LightProgram.h>


typedef enum SpiralTreeStarsColors
{
    SpiralTreeStarsColors_Random = 0,
    SpiralTreeStarsColors_Blue,
    SpiralTreeStarsColors_Red,
    SpiralTreeStarsColors_Green,
    SpiralTreeStarsColors_Rainbow,
    SpiralTreeStarsColors_RedGreen,
    SpiralTreeStarsColors_Christmas,
};


typedef enum SpiralTreeStarsMode
{
    SpiralTreeStarsMode_LeftToRight = 0,
    SpiralTreeStarsMode_RightToLeft,
    SpiralTreeStarsMode_ZigZag,
};



class SpiralTreeStars
{
public:
    SpiralTreeStars();

    void SetColors(SpiralTreeStarsColors colors);
    void SetMode(SpiralTreeStarsMode mode);
    void SetWhiteTip(bool white);
    void SetStarGap(uint8_t gap);
    void SetDelay(delay_t delay);
    void SetDefer(bool defer);
    void SetStarSize(uint8_t size);


    void InitializeTree();
    uint32_t Do();

private:

    void SendStarUpdate(uint8_t color);


    uint8_t* m_ColorMap;
    uint8_t m_ColorMapSize;
    uint8_t m_ColorIndex;
    uint8_t m_CycleIndex;
    uint8_t m_CycleSize;
    uint8_t m_ColorCycleSize;
    uint8_t m_CyclesUntilNewColor;
    uint8_t m_StarSize;
    

    uint8_t m_StarGap;
    uint8_t m_CyclesUntilNewStar;


    delay_t m_Delay;

    SpiralTreeStarsMode m_Mode;
    SpiralTreeStarsColors m_Colors;

    bool m_Defer;
    bool m_WhiteTip;
    uint16_t m_Address;
    uint16_t m_NewStarAddress;
};

#endif  // INCLUDE_SPIRAL_TREE_STARS_H



