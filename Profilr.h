#pragma once

#include <chrono>
#include <string>
#include <fstream>

#define PROFILING_ACTIVE 1

#ifdef PROFILING_ACTIVE
#define PROFILE_FUNC() Timer t__LINE__ = Timer(__PRETTY_FUNCTION__)
#elif
#define PROFILE_FUNC()
#endif

using namespace std::chrono;

class Profilr{
public:
    Profilr(const std::string& path);
    void writeResults(const std::string& name, time_point<high_resolution_clock> start, time_point<high_resolution_clock> end);
    void writeJSONHeader();
    void writeJSONFooter();
private:
    std::ofstream output;
    std::string m_path;
    bool alreadyWrote = false;
};

static Profilr ProfilrInstance = Profilr("log.json");

class Timer{
public:
    Timer(const std::string& label);
    ~Timer();
    void stop();
private:
    std::string m_label;
    bool m_running = true;
    time_point<high_resolution_clock> m_start;
};