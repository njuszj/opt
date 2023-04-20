# ifndef LOGGER_H
# define LOGGER_H

# include <iostream>
# include <fstream>
# include <string>
# include <cstdarg>
# include <time.h>
# include <stdio.h>
# include <stdlib.h>

using std::string;
using std::endl;
using std::to_string;
using std::ios;

string currTime();

class Logger{
public:
    enum log_level{debug, info, warning, error};             // 日志等级
private:
    std::ostream& std_out;            // 标准输出
    std::ostream& err_out;            // 错误输出
    log_level level;                  // 日志等级
    void output(string text, log_level act_level);            // 输出时调用的公共函数
public:
    void welcome();
    Logger();  // 默认构造函数
    Logger(log_level level, std::ostream& std_out, std::ostream& err_out);
    void DEBUG(string text);
    void INFO(string text);
    void WARNING(string text);
    void ERROR(string text);
};

extern Logger logger;

# endif