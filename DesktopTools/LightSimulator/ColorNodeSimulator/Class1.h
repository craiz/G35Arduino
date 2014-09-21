#pragma once

#include <stdio.h>
#include <tchar.h>

#include <Arduino.h>
#include <DebugConfig.h>
#include <G35.h>
#include <G35String.h>
//#include <G35StringSimulator.h>
#include <G35StringWindowSmall.h>
#include <LightProgram.h>
#include <ShootingStars.h>
#include <Dissolve.h>
#include <Chase.h>
#include <DripFill.h>
#include <wave.h>
#include <MEORandomStrobe.h>
#include <ColorNodeCommands.h>
#include <Solid.h>
#include <StockPrograms.h>

namespace ColorNodeSimulator
{
    public enum class LightProgramType
    {
        Dissolve = 0,
        DripFill = 1,
        ShootingStar = 2,
        Wave = 3,
        RandomStrobe = 4,
        Solid = 5,
        AlternateDirection = 6,
        FadeInFadeOutSolidColors = 7,
        ForwardWave = 8,
    };


    public ref class Class1 sealed
    {
    public:
        Class1();
        virtual ~Class1();

        bool Configure(uint16 lightCount);
        bool SetLightProgram(LightProgramType program, unsigned char pattern, unsigned char option, uint16 delay);
        bool UpdateLightProgram(unsigned char pattern, unsigned char option, uint16 delay);
        bool KickLightProgram();

        void DoFrame();
        uint16 GetColor(unsigned char index);
        uint32 GetDelay();
    
    private:
        G35String *m_pG35StringSimulator;
        LightProgram *m_pProgram;
        uint32 m_ulDelay;
        unsigned char m_Count;
    };
}
