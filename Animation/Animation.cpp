#include "Animation.h"

uint32_t Animation::m_CurrentTime = 0;

Animation::Animation() {
    init(0, NULL, Linear, EaseIn, false);
}

Animation::Animation(uint32_t i_Duration, StepCallback i_StepCallback) {
    init(i_Duration, i_StepCallback, Linear, EaseIn, false);
}

Animation::Animation(uint32_t i_Duration, StepCallback i_StepCallback, boolean i_AutoStart) {
    init(i_Duration, i_StepCallback, Linear, EaseIn, i_AutoStart);
}

Animation::Animation(uint32_t i_Duration, StepCallback i_StepCallback, eEasingType i_EasingType) {
    init(i_Duration, i_StepCallback, Linear, i_EasingType, false);
}

Animation::Animation(uint32_t i_Duration, StepCallback i_StepCallback, eEasingType i_EasingType, boolean i_AutoStart) {
    init(i_Duration, i_StepCallback, Linear, i_EasingType, i_AutoStart);
}

Animation::Animation(uint32_t i_Duration, StepCallback i_StepCallback, eTimingType i_TimingType) {
    init(i_Duration, i_StepCallback, i_TimingType, EaseIn, false);
}

Animation::Animation(uint32_t i_Duration, StepCallback i_StepCallback, eTimingType i_TimingType, boolean i_AutoStart) {
    init(i_Duration, i_StepCallback, i_TimingType, EaseIn, i_AutoStart);
}

Animation::Animation(uint32_t i_Duration, StepCallback i_StepCallback, eTimingType i_TimingType, eEasingType i_EasingType) {
    init(i_Duration, i_StepCallback, i_TimingType, i_EasingType, false);
}

Animation::Animation(uint32_t i_Duration, StepCallback i_StepCallback, eTimingType i_TimingType, eEasingType i_EasingType, boolean i_AutoStart) {
    init(i_Duration, i_StepCallback, i_TimingType, i_EasingType, i_AutoStart);
}

uint32_t Animation::GetDuration() { return m_Duration; }

void Animation::SetDuration(uint32_t i_Duration) { m_Duration = i_Duration; }

Animation::StepCallback Animation::GetStepCallback() { return m_StepCallback; }

void Animation::SetStepCallback(StepCallback i_StepCallback) { m_StepCallback = i_StepCallback; }

Animation::eTimingType Animation::GetTimingType() { return m_TimingType; }

void Animation::SetTimingType(eTimingType i_TimingType) { m_TimingType = i_TimingType; }

Animation::eEasingType Animation::GetEasingType() { return m_EasingType; }

void Animation::SetEasingType(eEasingType i_EasingType) { m_EasingType = i_EasingType; }

boolean Animation::GetAutoStart() { return m_AutoStart; }

void Animation::SetAutoStart(boolean i_AutoStart) { m_AutoStart = i_AutoStart; }

uint32_t Animation::GetTimeDelayMilliseconds() { return m_TimeDelayMilliseconds; }

void Animation::SetTimeDelayMilliseconds(uint32_t i_TimeDelayMilliseconds) { m_TimeDelayMilliseconds = i_TimeDelayMilliseconds; }

uint8_t Animation::GetStepTimeMilliseconds() { return m_StepTimeMilliseconds; }

void Animation::SetStepTimeMilliseconds(uint8_t i_StepTimeMilliseconds) { m_StepTimeMilliseconds = i_StepTimeMilliseconds; }

void Animation::Start() {
    m_StartTime = millis();
}

void Animation::Stop() {
    m_StartTime = 0;
}

Animation *Animation::Next(Animation *i_Next) {
    m_Next = i_Next;
    return this;
}

void Animation::Refresh() {
    m_CurrentTime = millis();
    int32_t delta = (m_CurrentTime - m_StartTime - m_TimeDelayMilliseconds);
    if (m_StartTime > 0 && m_Duration > 0 && delta > 0 && (m_StepTimeMilliseconds == 0 || delta % m_StepTimeMilliseconds == 0)) {
        float timeFraction = (float) delta / (float) m_Duration;

        if (timeFraction >= 1) {
            timeFraction = 1;
            Stop();
            if (m_Next != NULL) {
                m_Next->Start();
            }
        }

        timeFraction = progress(timeFraction);

        if (m_StepCallback) {
            m_StepCallback(this, timeFraction);
        }
    }
}

void Animation::init(uint32_t i_Duration, StepCallback i_StepCallback, Animation::eTimingType i_TimingType, eEasingType i_EasingType, boolean i_AutoStart) {
    m_Duration = i_Duration;
    m_StepCallback = i_StepCallback;
    m_TimingType = i_TimingType;
    m_EasingType = i_EasingType;
    m_AutoStart = i_AutoStart;
}

float Animation::progress(float i_TimeFraction) {
    TimingFunction timingFunction = getTimingFunction();

    if (timingFunction) {
        switch (m_EasingType) {
            case EaseOut:
//                return easingInOut(timingFunction)(i_TimeFraction);
                return 1.0f - timingFunction(1.0f - i_TimeFraction);
            case EaseInOut:
//                return easingOut(timingFunction)(i_TimeFraction);
                if (i_TimeFraction <= 0.5f) {
                    return timingFunction(2.0f * i_TimeFraction) / 2.0f;
                } else {
                    return (2.0f - timingFunction(2.0f * (1.0f - i_TimeFraction))) / 2.0f;
                }
            case EaseIn:
                return timingFunction(i_TimeFraction);
        }
    }

    return 0;
}

inline Animation::TimingFunction Animation::getTimingFunction() {
    switch (m_TimingType) {
        case Linear:
            return timingLinear;
        case PowN2:
            return timingPowN2;
        case PowN3:
            return timingPowN3;
        case PowN4:
            return timingPowN4;
        case PowN5:
            return timingPowN5;
        case Arc:
            return timingArc;
        case BowShooting:
            return timingBowShooting;
        case Bounce:
            return timingBounce;
        case Elastic:
            return timingElastic;
    }
    return timingLinear;
}

//inline Animation::TimingFunction Animation::easingOut(TimingFunction i_TimingFunction) {
//    return [i_TimingFunction](float i_TimeFraction) -> float {
//        return 1.0f - i_TimingFunction(1.0f - i_TimeFraction);
//    };
//}
//
//inline Animation::TimingFunction Animation::easingInOut(TimingFunction i_TimingFunction) {
//    return [i_TimingFunction](float i_TimeFraction) -> float {
//        if (i_TimeFraction <= 0.5f) {
//            return i_TimingFunction(2.0f * i_TimeFraction) / 2.0f;
//        } else {
//            return (2.0f - i_TimingFunction(2.0f * (1.0f - i_TimeFraction))) / 2.0f;
//        }
//    };
//}

inline float Animation::timingLinear(float i_TimeFraction) {
    return i_TimeFraction;
}

inline float Animation::timingPowN2(float i_TimeFraction) {
    return pow(i_TimeFraction, 2.0);
}

inline float Animation::timingPowN3(float i_TimeFraction) {
    return pow(i_TimeFraction, 3.0);
}

inline float Animation::timingPowN4(float i_TimeFraction) {
    return pow(i_TimeFraction, 4.0);
}

inline float Animation::timingPowN5(float i_TimeFraction) {
    return pow(i_TimeFraction, 5.0);
}

inline float Animation::timingArc(float i_TimeFraction) {
    return 1 - sin(acos(i_TimeFraction));
}

inline float Animation::timingBowShooting(float i_TimeFraction) {
    float x = 1.5f;
    return pow(i_TimeFraction, 2) * ((x + 1) * i_TimeFraction - x);
}

inline float Animation::timingBounce(float i_TimeFraction) {
    float a = 0, b = 1;
    while (true) {
        if (i_TimeFraction >= (7 - 4 * a) / 11) {
            return -pow((11 - 6 * a - 11 * i_TimeFraction) / 4, 2) + pow(b, 2);
        }
        a += b;
        b /= 2;
    }
}

inline float Animation::timingElastic(float i_TimeFraction) {
    float x = 1.5f;
    return pow(2, 10 * (i_TimeFraction - 1)) * cos(20 * PI * x / 3 * i_TimeFraction);
}