// Class1.cpp
#include "Class1.h"

using namespace ColorNodeSimulator;
using namespace Platform;

Class1::Class1()
{
    m_Count = 0;
    m_ulDelay = 0;
    m_pProgram = NULL;
}

Class1::~Class1()
{
    delete m_pG35StringSimulator;
    delete m_pProgram;
}

bool Class1::Configure(uint16 lightCount)
{
    m_Count = lightCount;
    m_pG35StringSimulator = new G35String();
    //m_pG35StringSimulator = new G35StringWindowSmall();
    m_pG35StringSimulator->Configure(0, m_Count, m_Count, true, STRING_LAYOUT_LINEAR);
    //m_pG35StringSimulator->set_layout(STRING_LAYOUT::STRING_LAYOUT_VERTICAL_LINES);
    return true;
}

bool Class1::SetLightProgram(LightProgramType program, unsigned char pattern, unsigned char option, uint16 delay)
{
    delete m_pProgram;
    m_pProgram = NULL;

    switch (program)
    {
    case LightProgramType::Dissolve:
        {
            byte buffer[66] = {0};
            ProgramCommand* pCommand = (ProgramCommand *)buffer;
            buffer[sizeof(ProgramCommand)] = 0;
            buffer[sizeof(ProgramCommand) + 1] = 3;
            buffer[sizeof(ProgramCommand) + 2] = 0x88;
            buffer[sizeof(ProgramCommand) + 3] = 0x13;
            m_pProgram = new Dissolve(*m_pG35StringSimulator, pCommand);
            break;
        }
    case LightProgramType::DripFill:
        {
            byte buffer[66] = {0};
            ProgramCommand* pCommand = (ProgramCommand *)buffer;
            buffer[sizeof(ProgramCommand) + 0] = 21; // Background color
            buffer[sizeof(ProgramCommand) + 1] = 18; // Fill color
            buffer[sizeof(ProgramCommand) + 2] = 0; // Drip color
            buffer[sizeof(ProgramCommand) + 3] = 1; // Drip size
            buffer[sizeof(ProgramCommand) + 4] = 3; // Fill size
            m_pProgram = new DripFill(*m_pG35StringSimulator, pCommand);
            break;
        }
    case LightProgramType::ShootingStar:
        {
            byte buffer[66] = {0};
            ProgramCommand* pCommand = (ProgramCommand *)buffer;
            buffer[sizeof(ProgramCommand)] = 0;
            buffer[sizeof(ProgramCommand) + 1] = 0;
            buffer[sizeof(ProgramCommand) + 2] = 2;
            buffer[sizeof(ProgramCommand) + 3] = 2;
            m_pProgram = new ShootingStars(*m_pG35StringSimulator, pCommand);
            break;
        }
    case LightProgramType::Wave:
        {
            byte buffer[66] = {0};
            ProgramCommand* pCommand = (ProgramCommand *)buffer;
            buffer[sizeof(ProgramCommand)] = 0; // pixels per wave
            buffer[sizeof(ProgramCommand) + 1] = 0; // wave distribution
            buffer[sizeof(ProgramCommand) + 2] = 1; // position span size
            buffer[sizeof(ProgramCommand) + 3] = 4; // color 1
            buffer[sizeof(ProgramCommand) + 4] = 1; // color 2
            buffer[sizeof(ProgramCommand) + 5] = 4; // color 3
            buffer[sizeof(ProgramCommand) + 6] = 1; // holds for color 1
            buffer[sizeof(ProgramCommand) + 7] = 1; // holds for color 2
            buffer[sizeof(ProgramCommand) + 8] = 0; // holds for color 3
            m_pProgram = new Wave(*m_pG35StringSimulator, pCommand);

            pattern = 3;
            option = (15 << 4) | 0;

            break;
        }
    case LightProgramType::RandomStrobe:
        {
            m_pProgram = new MEORandomStrobe(*m_pG35StringSimulator);
            break;
        }
    case LightProgramType::Solid:
        {
            m_pProgram = new Solid(*m_pG35StringSimulator);
            break;
        }
    case LightProgramType::AlternateDirection:
        {
            m_pProgram = new AlternateDirectionalWave(*m_pG35StringSimulator);
            break;
        }
    case LightProgramType::FadeInFadeOutSingleColors:
        {
            m_pProgram = new FadeInFadeOutSingleColors(*m_pG35StringSimulator);
            break;
        }
    case LightProgramType::ForwardWave:
        {
            m_pProgram = new ForwardWave(*m_pG35StringSimulator);
            break;
        }
	case LightProgramType::SpookyEyes:
		{
            m_pG35StringSimulator->set_light_count(7);
			m_pProgram = new SpookyEyes(*m_pG35StringSimulator);
            //m_pProgram = new Snowflake(*m_pG35StringSimulator);
		}
    }

    if (m_pProgram == NULL)
    {
        __debugbreak();
        return false;
    }

    m_pProgram->Initialize(pattern, option, delay);

    return true;
}

bool Class1::UpdateLightProgram(unsigned char pattern, unsigned char option, uint16 delay)
{
    m_pProgram->Update(pattern, option, delay);
    m_pProgram->Kick();
    return true;
}

bool Class1::KickLightProgram()
{
    m_pProgram->Kick();
    return true;
}

void Class1::DoFrame()
{
    m_ulDelay = 0;
    if (!m_pProgram->IsWaiting())
    {
        m_ulDelay = m_pProgram->Do();
    }
}

color_t get_color(light_count_t bulb);

uint16 Class1::GetColor(unsigned char index)
{
    if (index >= m_Count)
    {
        __debugbreak();
        return 0;
    }
    else
    {
        return get_color((color_t)index);
    }
}

uint32 Class1::GetDelay()
{
    return m_ulDelay;
}
