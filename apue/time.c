#define START_YEAR_OF_SECS                      1970                                    /* 从1970年开始计算秒数 */
#define SECS_PER_DAY                            86400L                                  /* 一天的秒数 */
#define WEEK_VALUE_OF_1970                      4                                       /* 1970年1月1号是星期四 */
#define DAYS_OF_WEEK                            7                                       /* 一周有几天 */
#define LEAP_YEAR(lYear)                        (0 == ((lYear) % 4))                    /* 是否为闰年 */
#define DAYS_IN_YEAR(lDays)                     (LEAP_YEAR(lDays) ? 366 : 365)      /* 一年有几天 */
#define DAYS_OF_MONTH(lMonth)                   (alDaysOfMonth[(lMonth) - 1])           /* 一个月有多少天 */

/* 一年每个月的天数(非闰年) */
static LONG alDaysOfMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
/**
* 将秒数转换成struct tm结构体的函数，该tm结构体内容和linux中定义的struct tm结构体有点差别，
* struct tm 结构体中的年使用的是真实的年份，而不是从1900年开始的年份，月份也是从1月份开始而不是从0开始\n
* @param [IN] long lSeconds 秒数
* @return VOID
*/
struct tm SecToTimeValSelf(IN long lSeconds)
{
    long lLoopIndex         = 0;
    long lHMS               = 0;            /* 小时、分、秒 */
    long lDays              = 0;
    struct tm stTime        = {0};

    lDays = lSeconds / SECS_PER_DAY;

    /* 星期几 */
    stTime.tm_wday = (lDays + WEEK_VALUE_OF_1970) % DAYS_OF_WEEK;        
    
    lHMS = lSeconds % SECS_PER_DAY;

    /* 获取小时、分、秒 */
    stTime.tm_hour = lHMS / 3600;
    stTime.tm_min = (lHMS % 3600) / 60;
    stTime.tm_sec = (lHMS % 3600) % 60;

    /* 现在处于哪一年 */
    for (lLoopIndex = START_YEAR_OF_SECS; lDays >= DAYS_IN_YEAR(lLoopIndex); lLoopIndex++)
    {
        lDays -= DAYS_IN_YEAR(lLoopIndex);
    }
    stTime.tm_year = lLoopIndex;
    stTime.tm_yday = lDays;

    /* 如果是闰年，则2月为29天 */
    if (LEAP_YEAR(stTime.tm_year))
    {
        DAYS_OF_MONTH(2) = 29;
    }
    
    for (lLoopIndex = 1; lDays >= DAYS_OF_MONTH(lLoopIndex); lLoopIndex++)
    {
            lDays -= DAYS_OF_MONTH(lLoopIndex);
    }
    /* 哪个月 */
    stTime.tm_mon = lLoopIndex;

    /* 恢复2月28天作为默认值 */
    DAYS_OF_MONTH(LOG_FEBRUARY) = 28;

    /* 一个月的第几天 */
    stTime.tm_mday = lDays + 1;

    return stTime;
}
