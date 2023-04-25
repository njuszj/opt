#include "../include/logger.h"

string currTime(){
    // 获取当前时间，并规范表示
    char tmp[64];
    time_t ptime;
    time(&ptime);
    strftime(tmp, sizeof(tmp), "%Y-%m-%d %H:%M:%S", localtime(&ptime));
    return string(tmp);
}

void Logger::welcome() {
    std_out << "[WELCOME] " << currTime() << " : " << "=== Start logging ===" << endl;
}

Logger::Logger() : std_out(std::cout), err_out(std::cerr), level(debug) {
    welcome();
}

Logger::Logger(log_level level, std::ostream& std_out, std::ostream& err_out) : std_out(std_out), err_out(err_out), level(level) {
    welcome();
}

void Logger::output(string text, log_level act_level){
    string prefix;
    if(act_level == debug) prefix = "[DEBUG]   ";
    else if(act_level == info) prefix = "[INFO]    ";
    else if(act_level == warning) prefix = "[WARNING] ";
    else if(act_level == error) prefix = "[ERROR]   ";
    else prefix = "";
    string output_content = prefix + currTime() + " : " + text;
    if(act_level == error){
        err_out << output_content << endl;
    }
    else{
        std_out << output_content << endl;
    }
}


void Logger::DEBUG(string text){
    this->output(text, debug);
}

void Logger::INFO(string text){
    this->output(text, info);
}

void Logger::WARNING(string text){
    this->output(text, warning);
}

void Logger::ERROR(string text){

    this->output(text, error);
}

void Logger::setLogLevel(log_level level){
    this->level = level;
}

Logger logger;