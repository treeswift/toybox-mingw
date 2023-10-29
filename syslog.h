#ifndef _SYSLOG_H_
#define _SYSLOG_H_

/* TODO libsyslog (we already have a syslogd!) */

enum SyslogSeverity {
    LOG_EMERG = 0,
    LOG_ALERT,
    LOG_CRIT,
    LOG_ERR,
    LOG_WARNING,
    LOG_NOTICE,
    LOG_INFO,
    LOG_DEBUG,
};

enum SyslogFacility {
    LOG_USER     = (1<<3),
    LOG_KERN     = (0<<3),
    LOG_MAIL     = (2<<3),
    LOG_DAEMON   = (3<<3),
    LOG_AUTH     = (4<<3),
    LOG_SYSLOG   = (5<<3),
    LOG_LPR      = (6<<3),
    LOG_NEWS     = (7<<3),
    LOG_UUCP     = (8<<3),
    LOG_CRON     = (9<<3),
    LOG_AUTHPRIV = (10<<3),
    LOG_FTP      = (11<<3),
};

enum SyslogOptions {
    LOG_PID    = (1<<0),
    LOG_CONS   = (1<<1),
    LOG_ODELAY = (1<<2),
    LOG_NDELAY = (1<<3),
    LOG_NOWAIT = (1<<4),
    LOG_PERROR = (1<<5),
};

inline void openlog(const char *ident, int option, int facility) {}
inline void syslog(int priority, const char *format, ...) {}
inline void closelog() {}

inline void vsyslog(int priority, const char *format, va_list ap) {}

#endif /* _SYSLOG_H_ */
