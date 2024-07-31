/* ************************************************************************
> File Name:     log.h
> Author:        Hongtao Wang
> mail:          1196354180@qq.com
> Created Time:  Wed 24 Jul 2024 03:36:10 PM CST
> Description:   
 ************************************************************************/

#ifndef __WHT_LOG_H__
#define __WHT_LOG_H__

#include <string>
#include <stdint.h>
#include <memory>

namespace wht{

//日志事件
class LogEvent{
public:
    typedef std::shared_ptr<LogEvent> ptr;
    LogEvent();
private:
    const char* m_file = nullptr; // 文件名
    int32_t m_line = 0;           //行号
    uint32_t m_elapse = 0;        //程序启动到现在的毫秒数
    uint32_t m_threadId = 0;      //线程id
    uint32_t m_fiberId = 0;       //协程id
    uint64_t m_time;              //时间戳
    std::string m_content;
};

//日志级别
class LogLevel{
public:
    enum Level{
        DEBUG = 1,
        INFO = 2,
        WARN = 3,
        ERROR = 4,
        FATAL = 5
    };
};


//日志格式器
class LogFormatter{
public:
    typedef std::shared_ptr<LogFormatter> ptr;

    std::string format(LogEvent::ptr event);
private:
};

//日志输出地
class LogAppender{
public:
    typedef std::shared_ptr<LogAppender> ptr;
    virtual ~LogAppender(){}

    void log(LogLevel::Level level, LogEvent::ptr event);
private:
    LogLevel::Level m_level;

};

//日志输出器
class Logger{
public:
    typedef std::shared_ptr<Logger> ptr;

    Logger(const std::string& name = "root");
    void log(LogLevel::Level level, const LogEvent& event);
private:
    std::string m_name;
    LogLevel::Level m_level;
    LogAppender::ptr Appender;
};

//输出到控制台的Appender
class StdoutLogAppender : public LogAppender{

};

//输出到文件的Appender
class FileLogAppender : public LogAppender{

};

}

#endif