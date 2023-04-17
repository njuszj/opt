# ifndef LOGGER_H
# define LOGGER_H

# include <iostream>
# include <fstream>
# include <string>
# include <time.h>
# include <stdio.h>
# include <stdlib.h>

using std::cout;
using std::string;
using std::endl;
using std::to_string;
using std::ios;

string currTime(){
    // 获取当前时间，并规范表示
    char tmp[64];
    time_t ptime;
    time(&ptime);
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&ptime));
    return string(tmp);
}

class Logger{
public:
    enum log_level{debug, info, warning, error};             // 日志等级
    enum log_target{file, terminal, file_and_terminal};      // 日志输出目标
private:
    std::ofstream outfile;      // 将日志输出到文件的流对象
    log_target target;          // 日志输出目标
    string path;                // 日志文件路径
    log_level level;            // 日志等级
    void output(string text, log_level act_level);            // 输出时调用的公共函数
public:
    Logger();  // 默认构造函数
    Logger(log_target target, log_level level, string path);
    void DEBUG(string text);
    void INFO(string text);
    void WARNING(string text);
    void ERROR(string text);
};

extern Logger logger;

# endif