/**
 * @name:			Animation.h
 * @description:	Animation Class
 * @author:			Albert Harounian
 * @since:			July 22, 2018
 */

#ifndef __ANIMATION_H__
#define __ANIMATION_H__

#include <Arduino.h>

class Animation {
public:
    typedef void (*StepCallback)(Animation *const, float);

    enum eTimingType {
        Linear, // Default
        PowN2,
        PowN3,
        PowN4,
        PowN5,
        Arc,
        BowShooting,
        Bounce,
        Elastic
    };

    enum eEasingType {
        EaseIn, // Default
        EaseOut,
        EaseInOut
    };

    Animation();

    Animation(uint32_t i_Duration, StepCallback i_StepCallback);

    Animation(uint32_t i_Duration, StepCallback i_StepCallback, boolean i_AutoStart);

    Animation(uint32_t i_Duration, StepCallback i_StepCallback, eEasingType i_EasingType);

    Animation(uint32_t i_Duration, StepCallback i_StepCallback, eEasingType i_EasingType, boolean i_AutoStart);

    Animation(uint32_t i_Duration, StepCallback i_StepCallback, eTimingType i_TimingType);

    Animation(uint32_t i_Duration, StepCallback i_StepCallback, eTimingType i_TimingType, boolean i_AutoStart);

    Animation(uint32_t i_Duration, StepCallback i_StepCallback, eTimingType i_TimingType, eEasingType i_EasingType);

    Animation(uint32_t i_Duration, StepCallback i_StepCallback, eTimingType i_TimingType, eEasingType i_EasingType, boolean i_AutoStart);

    uint32_t GetDuration();

    void SetDuration(uint32_t i_Duration);

    StepCallback GetStepCallback();

    void SetStepCallback(StepCallback i_StepCallback);

    eTimingType GetTimingType();

    void SetTimingType(eTimingType i_TimingType);

    eEasingType GetEasingType();

    void SetEasingType(eEasingType i_EasingType);

    boolean GetAutoStart();

    void SetAutoStart(boolean i_AutoStart);

    uint32_t GetTimeDelayMilliseconds();

    void SetTimeDelayMilliseconds(uint32_t i_StepTimeMilliseconds);

    uint8_t GetStepTimeMilliseconds();

    void SetStepTimeMilliseconds(uint8_t i_StepTimeMilliseconds);

    void Start();

    void Stop();

    void Refresh();

    Animation *Next(Animation *i_Next);

protected:
    typedef float (*TimingFunction)(float);

    uint32_t m_Duration = 0;
    uint32_t m_StartTime = 0;
    eTimingType m_TimingType;
    eEasingType m_EasingType;
    StepCallback m_StepCallback = NULL;
    Animation *m_Next = NULL;
    boolean m_AutoStart = false;
    uint16_t m_Id = 0;
    uint32_t m_TimeDelayMilliseconds = 0;
    uint8_t m_StepTimeMilliseconds = 0;

    static uint32_t m_CurrentTime;

    void init(uint32_t i_Duration, StepCallback i_StepCallback, eTimingType i_TimingType, eEasingType i_EasingType, boolean i_AutoStart);

    float progress(float i_TimeFraction);

//    static TimingFunction easingOut(TimingFunction i_TimingFunction);

//    TimingFunction easingInOut(TimingFunction i_TimingFunction);

    TimingFunction getTimingFunction();

    static float timingLinear(float i_TimeFraction);

    static float timingPowN2(float i_TimeFraction);

    static float timingPowN3(float i_TimeFraction);

    static float timingPowN4(float i_TimeFraction);

    static float timingPowN5(float i_TimeFraction);

    static float timingArc(float i_TimeFraction);

    static float timingBowShooting(float i_TimeFraction);

    static float timingBounce(float i_TimeFraction);

    static float timingElastic(float i_TimeFraction);
};


#endif
