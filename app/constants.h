#ifndef CONSTANTS_H_
#define CONSTANTS_H_

// -----------------------------------------------------------------------------
// GLOBAL CONSTANTS
// -----------------------------------------------------------------------------
#define HUNDRED_PERCENTS                100U

#define MICROSECONDS_PER_MILLISECOND    1000U
#define MILLISECONDS_PER_SECOND         1000U
#define SECONDS_PER_MINUTE              60U
#define MINUTES_PER_HOUR                60U

#define MILLISECONDS_PER_MINUTE (SECONDS_PER_MINUTE *                      \
                                    MILLISECONDS_PER_SECOND)
#define MILLISECONDS_PER_HOUR   (MINUTES_PER_HOUR *                        \
                                    MILLISECONDS_PER_MINUTE)

#define USEC_TO_MSEC(x)         ((x) / MICROSECONDS_PER_MILLISECOND)
#define MSEC_TO_USEC(x)         ((x) * MICROSECONDS_PER_MILLISECOND)
#define SEC_TO_MSEC(x)          ((x) * MILLISECONDS_PER_SECOND)
#define MIN_TO_MSEC(x)          ((x) * MILLISECONDS_PER_MINUTE)
#define HOUR_TO_MSEC(x)         ((x) * MILLISECONDS_PER_HOUR)
#define HOUR_TO_SEC(x)                                                      \
  (((x) * MINUTES_PER_HOUR) * SECONDS_PER_MINUTE)
#define HZ_TO_MS(x)             ((uint32_t)(MILLISECONDS_PER_SECOND / (x)))

#define MILLIVOLTS_PER_VOLT     1000U
#define MVOLT_TO_VOLT(x)        ((x) / MILLIVOLTS_PER_VOLT)

#endif // CONSTANTS_H_
