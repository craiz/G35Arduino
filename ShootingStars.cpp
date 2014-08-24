

#include <DebugConfig.h>
#if DEBUG_LIGHT_PROGRAM_SHOOTING_STARS
#define DEBUG_ENABLED 1
#endif
#if DEBUG_ENABLED
#define DebugPrintf(fmt, ...) SerialPrintf(fmt, ##__VA_ARGS__)
#else
#define DebugPrintf(...)
#endif

#include <ShootingStars.h>
#include <WaveUtils.h>

// A range of random sizes to be assigned when a star is created.
#define MIN_STAR_SIZE 3
#define MAX_STAR_SIZE 15

// Speed as number of ticks
// A range of random speeds to be assigned when a star is created.  Lower is faster.
#define MIN_STAR_SPEED 1
#define MAX_STAR_SPEED 4

// Range of time between stars.  Used to determine when new stars
// should be created.
#define MIN_TICK_GAP 0
#define MAX_TICK_GAP 100

// Range of distances between stars.  Used to determine when new stars
// should be created.
#define MIN_POSITION_GAP 0
#define MAX_POSITION_GAP 10

// Hard maximun number of stars
#define MAX_STARS 7


#define DEFAULT_TICK_DELAY 50


// Helper macros for managing stars
#define ENCODE_STAR_VALUE(_color, _offset)  ((_color << 4) | (_offset & 0x0F))
#define DECODE_STAR_COLOR(_value)           ((_value >> 4) & 0x0F)
#define DECODE_STAR_OFFSET(_value)          (_value & 0x0F)


ShootingStars::ShootingStars(G35& g35, ProgramCommand *pCommand)
  : LightProgram(g35)
  , m_pCommand(pCommand)
  , m_nMaxStars(MAX_STARS)
  , m_nActiveStars(0)
  , m_pStars(NULL)
  , m_pOldestStar(NULL)
  , m_pNewestStar(NULL)
  , m_pBulbBuffer(NULL)
  , m_TicksUntilAdd(MIN_TICK_GAP)
  , m_GapUntilAdd(MIN_POSITION_GAP)
  , m_TickGapMin(MIN_TICK_GAP)
  , m_TickGapMax(MAX_TICK_GAP)
  , m_PositionGapMin(MIN_POSITION_GAP)
  , m_PositionGapMax(MAX_POSITION_GAP)
  , m_nTopGap(light_count_)
  , m_Color(WAVE_COLOR_BLACK)
  , m_Size(MIN_STAR_SIZE)
  , m_Speed(MIN_STAR_SPEED)
  , m_fWhiteTip(false)
{
    DebugPrintf("ShootingStars\n");

    delay_default_ = DEFAULT_TICK_DELAY;
}

ShootingStars::~ShootingStars()
{
    if (m_pStars)
    {
        free(m_pStars);
    }
    if (m_pBulbBuffer)
    {
        free(m_pBulbBuffer);
    }
}

color_t GetStarColor(uint8_t encodedValue)
{
    uint8_t r = 0;
    uint8_t g = 0;
    uint8_t b = 0;
    uint8_t offset = DECODE_STAR_OFFSET(encodedValue);
    
    switch (DECODE_STAR_COLOR(encodedValue))
    {
    default:
    case WAVE_COLOR_BLACK:
        break;
    case WAVE_COLOR_RED:
        r = 15;
        break;
    case WAVE_COLOR_YELLOW:
        r = 15;
        g = 15;
        break;
    case WAVE_COLOR_GREEN:
        g = 15;
        break;
    case WAVE_COLOR_CYAN:
        g = 15;
        b = 15;
        break;
    case WAVE_COLOR_BLUE:
        b = 15;
        break;
    case WAVE_COLOR_MAGENTA:
        r = 15;
        b = 15;
        break;
    case WAVE_COLOR_WHITE:
        r = 15;
        g = 15;
        b = 15;
        break;
    }

    if (r)
    {
        r = r - offset;
    }
    if (g)
    {
        g = g - offset;
    }
    if (b)
    {
        b = b - offset;
    }
    return COLOR(r, g, b);
}

void ShootingStars::ParseAndValidateParameters()
{
    // Parse parameters
    m_Size = pattern_ & 0x0F;
    m_Color = (pattern_ >> 4) & 0x0F;
    m_Speed = (option_ >> 4) & 0x0F;
    m_fWhiteTip = (option_ & OPTION_BIT_2);

    // Get extra options if available.
    if (m_pCommand)
    {
        uint8_t *pExtraOptions = (uint8_t *)m_pCommand + sizeof(ProgramCommand);
        m_TickGapMin = pExtraOptions[0];
        m_TickGapMax = pExtraOptions[1];
        m_PositionGapMin = pExtraOptions[2];
        m_PositionGapMax = pExtraOptions[3];
        m_nMaxStars = pExtraOptions[4];
    }

    // Validate parameters and adjust as needed.
    if (m_Size < MIN_STAR_SIZE || m_Size > MAX_STAR_SIZE)
    {
        m_Size = MAX_STAR_SIZE;
    }
    if (m_Speed < MIN_STAR_SPEED || m_Speed > MAX_STAR_SPEED)
    {
        m_Speed = MAX_STAR_SPEED;
    }
    if (m_TickGapMin > m_TickGapMax)
    {
        m_TickGapMin = MIN_TICK_GAP;
        m_TickGapMax = MAX_TICK_GAP;
    }
    if (m_PositionGapMin > m_PositionGapMax)
    {
        m_PositionGapMin = MIN_TICK_GAP;
        m_PositionGapMax = MAX_TICK_GAP;
    }
    if (m_nMaxStars == 0)
    {
        m_nMaxStars = MAX_STARS;
    }
}

bool ShootingStars::Initialize(pattern_t pattern, option_t option, delay_t delay)
{
    DebugPrintf("Initializing...\n");
    LightProgram::Initialize(pattern, option, delay);

    ParseAndValidateParameters();

    // Allocate memory to track the stars.
    DebugPrintf("Allocating %u Stars\n", m_nMaxStars);
    m_pStars = static_cast<STAR*>(malloc(m_nMaxStars * sizeof(STAR)));
    if (!m_pStars)
    {
        DebugPrintf("Failed to allocate Stars\n");
        return false;
    }
    memset(m_pStars, 0, m_nMaxStars * sizeof(STAR));

    // Allocate the bulb buffer
    DebugPrintf("Allocating Bulb Buffer\n");
    m_pBulbBuffer = static_cast<uint8_t*>(malloc(light_count_ * sizeof(light_count_t)));
    if (!m_pBulbBuffer)
    {
        DebugPrintf("Failed to allocate m_BulbBuffer\n");
        return false;
    }
    memset(m_pBulbBuffer, 0, light_count_ * sizeof(light_count_t));

    return true;
}

uint32_t ShootingStars::Do()
{
    // Add star if needed
    if (!IS_WAIT(option_))
    {
        if (IS_RANDOM(option_))
        {
            AddRandomStar(false);
        }
        else
        {
            AddNormalStar(false);
        }
    }

    // Update positions of stars and draw to the bulb buffer.
    UpdateStars();

    // Output star values from the bulb buffer to the light string.
    bool countTopGap = true;
    m_nTopGap = 0;
    for (light_count_t i = 0; i < light_count_; i++)
    {
        color_t color = GetStarColor(m_pBulbBuffer[i]);
        if (countTopGap && color == WAVE_COLOR_BLACK)
        {
            m_nTopGap++;
        }
        else
        {
            countTopGap = false;
        }
        g35_.set_color(i, G35::MAX_INTENSITY, color);
    }

    // Reset the bulb buffer to default (black) color).
    uint8_t default_bulb_value = ENCODE_STAR_VALUE(WAVE_COLOR_BLACK, 0);
    memset(m_pBulbBuffer, default_bulb_value, light_count_ * sizeof(light_count_t));

    return delay_;        
}

void ShootingStars::Kick()
{
    if (IS_WAIT(option_))
    {
        if (IS_RANDOM(option_))
        {
            AddRandomStar(true);
        }
        else
        {
            AddNormalStar(true);
        }
    }
}

void ShootingStars::Update(pattern_t pattern, option_t option, delay_t delay)
{
    DebugPrintf("Updating...\n");
    LightProgram::Update(pattern, option, delay);

    ParseAndValidateParameters();

    Kick();
}

void ShootingStars::AddRandomStar(bool fForce)
{
    // Decide if a new star should be added.
    // If there are no stars, add one.
    // If it is time to add one, do it.
    if (m_pOldestStar == NULL || (m_TicksUntilAdd == 0 && m_GapUntilAdd <= m_nTopGap) || fForce)
    {
        uint8_t color = GetRandomWaveColor(WAVE_COLOR_BLACK, WAVE_COLOR_BLACK, WAVE_COLOR_BLACK);
        uint8_t size = MIN_STAR_SIZE;
        if (m_Size > MIN_STAR_SIZE)
        {
            size = MIN_STAR_SIZE + (rand() % (m_Size - MIN_STAR_SIZE));
        }
        uint8_t speed = MIN_STAR_SPEED;
        if (m_Speed > MIN_STAR_SPEED)
        {
            speed = MIN_STAR_SPEED + (rand() % (m_Speed - MIN_STAR_SPEED));
        }

        if (AddStar(color, size, speed))
        {
            // Pick a new time to add
            m_TicksUntilAdd = m_TickGapMin;
            if (m_TickGapMax > m_TickGapMin)
            {
                m_TicksUntilAdd = m_TickGapMin + (rand() % (m_TickGapMax - m_TickGapMin));
            }

            // Pick a new gap to add
            m_GapUntilAdd = m_PositionGapMin;
            if (m_PositionGapMax > m_PositionGapMin)
            {
                m_GapUntilAdd = m_PositionGapMin + (rand() % (m_PositionGapMax - m_PositionGapMin));
            }
        }
    }
    else
    {
        if (m_TicksUntilAdd > 0)
        {
            m_TicksUntilAdd--;
        }
    }

}

void ShootingStars::AddNormalStar(bool fForce)
{
    // Decide if a new star should be added.
    // If there are no stars, add one.
    // If it is time to add one, do it.
    if (m_pOldestStar == NULL || (m_TicksUntilAdd == 0 && m_GapUntilAdd <= m_nTopGap) || fForce)
    {
        if (AddStar(m_Color, m_Size, m_Speed))
        {
            // Pick a new time to add
            m_TicksUntilAdd = m_TickGapMin;

            // Pick a new gap to add
            m_GapUntilAdd = m_PositionGapMin;
        }
    }
    else
    {
        if (m_TicksUntilAdd > 0)
        {
            m_TicksUntilAdd--;
        }
    }
}

bool ShootingStars::AddStar(uint8_t color, uint8_t size, uint8_t speed)
{
    // We want to add a new star.  See if there is space for one.
    STAR *pStar = NULL;
    for (uint8_t i = 0; i < m_nMaxStars; i++)
    {
        if (!m_pStars[i].Active)
        {
            pStar = &m_pStars[i];
            break;
        }
    }
    if (pStar)
    {
        DebugPrintf("Adding a star (0x%04x)\n", pStar);
        pStar->Active = true;
        pStar->Color = color;
        pStar->Size = size;
        pStar->Speed = speed;
        pStar->Position = -1;       // Next move step will place it at position 0.
        pStar->TicksRemaining = 1;  // Cause it to be moved on next update
        pStar->Next = NULL;

        // Add this as the newest star;
        if (m_pNewestStar)
        {
            // Add new star to list as the newest star.
            m_pNewestStar->Next = pStar;
            m_pNewestStar = pStar;
        }
        else
        {
            // Currently no stars, this is both the newest and oldest.
            m_pNewestStar = pStar;
            m_pOldestStar = pStar;
        }
        m_nActiveStars++;

        return true;
    }
    return false;
}

void ShootingStars::UpdateStars()
{
    DebugPrintf("Updating stars\n");

    // Update tick counts of each star.
    STAR *pCurrentStar = m_pOldestStar;
    STAR *pPreviousStar = NULL;
    while (pCurrentStar)
    {
        pCurrentStar->TicksRemaining--;
        if (pCurrentStar->TicksRemaining == 0)
        {
            pCurrentStar->TicksRemaining = pCurrentStar->Speed;
            pCurrentStar->Position++;
        }

        DrawStar(pCurrentStar);

        // Remove this star if it is no longer visible on the string.
        if (pCurrentStar->Position >= pCurrentStar->Size
            && (pCurrentStar->Position - pCurrentStar->Size) >= (light_count_ - 1))
        {
            STAR* pRemovedStar = pCurrentStar;
            DebugPrintf("Removing a star (0x%04x)\n", pRemovedStar);

            // Special case for removing oldest star
            if (m_pOldestStar == pRemovedStar)
            {
                // Unlink from the head
                m_pOldestStar = pCurrentStar->Next;
                pPreviousStar = NULL; // There is no previous star.
            }
            else
            {
                // Unlink from the middle, previous star is unchanged.
                pPreviousStar->Next = pCurrentStar->Next;
            }
       
            // Special case for removing newest star
            if (m_pNewestStar == pRemovedStar)
            {
                m_pNewestStar = pPreviousStar;
            }

            // Advance current star to the next one
            pCurrentStar = pCurrentStar->Next;

            // Deactivate the removed star.
            memset(pRemovedStar, 0, sizeof(STAR));
            m_nActiveStars--;
        }
        else
        {
            // Move on to the next star
            pPreviousStar = pCurrentStar;
            pCurrentStar = pCurrentStar->Next;
        }
    }
}

void ShootingStars::DrawStar(STAR *pStar)
{
    // Write each star to output buffer.  Oldest to newest.  New stars overlap old stars.

    gradient_t scale = (gradient_t)15 / pStar->Size;
    gradient_t offset = 0;
    uint8_t position;

    DebugPrintf("Star (0x%04x) @ %d\n", pStar, pStar->Position);

    uint8_t size = pStar->Size;
    if (m_fWhiteTip)
    {
        size++;
    }
    bool fTipAdded = false;
    for (uint8_t i = 0; i < size; i++)
    {
        bool fAdjustOffset = true;
        position = pStar->Position - i;
        if (position >= 0 && position < light_count_)
        {
            // TODO: PAUL: Need to scale offset to star size.  Make offset mean color offset, not positional offset.
            if ((offset == 0) && m_fWhiteTip && !fTipAdded)
            {
                m_pBulbBuffer[position] = ENCODE_STAR_VALUE(WAVE_COLOR_WHITE, 0);
                fTipAdded = true; // only want to add the tip once.
                fAdjustOffset = false; // don't adjust the offset for the tip
            }
            else
            {
                m_pBulbBuffer[position] = ENCODE_STAR_VALUE(pStar->Color, (uint8_t)offset);
            }
        }

        if (fAdjustOffset)
        {
            offset = offset + scale;
        }
    }
}

