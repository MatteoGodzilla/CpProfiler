#include "Profilr.h"

Profilr::Profilr(const std::string& path){
    output = std::ofstream(path);
    m_path = path;
    if(output.is_open()){
        output << "{\"traceEvents\": [";
    }
}

void Profilr::writeResults(const std::string& name, time_point<high_resolution_clock> start, time_point<high_resolution_clock> end){
    if(output.is_open()){
        if(alreadyWrote){
            output << ",";
        }
        output << "{";
        output << R"("cat":"function",)";
        output << R"("dur":)" << duration_cast<milliseconds>(end-start).count() << ',';
        output << R"("name":")" << name << R"(",)";
        output << R"("ph":"X",)";
        output << R"("pid":0,)";
        output << R"("tid": 0,)";
        output << R"("ts":)" << time_point_cast<milliseconds>(start).time_since_epoch().count();
        output << "}";

        alreadyWrote = true;
        output.flush();
    }
}

void Profilr::writeJSONFooter(){
    output.close();
    output = std::ofstream(m_path, std::ios::app);
    if(output.is_open()){
        output << "],";
        output << R"("displayTimeUnit":"ms")";
        output << "}";
        output.close();
    }
}

//TIMER

Timer::Timer(const std::string& label){
    m_label = label;
    m_start = high_resolution_clock::now();
}

Timer::~Timer(){
    if(m_running){
        stop();
    }
}

void Timer::stop(){
    time_point m_end = high_resolution_clock::now();
    ProfilrInstance.writeResults(m_label,m_start,m_end);
    m_running = false;
}