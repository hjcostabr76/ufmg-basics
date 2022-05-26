#ifndef _MEETINGPOINT_MODEL_H_
#define _MEETINGPOINT_MODEL_H_

#include <string>

using namespace std;

class MeetingPointModel {

private:
    int code = 0;
    string name = "";


public:
    MeetingPointModel(void) {};

    // Codigo
    int getCode() const { return this->code; }
    void setCode(int code) { this->code = code; }

    // Nome
    const string getName() const { return this->name; }
    void setName(const string name) { this->name = name; }
};

#endif