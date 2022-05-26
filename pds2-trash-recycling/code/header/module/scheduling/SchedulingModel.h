#ifndef _SCHEDULING_MODEL_H_
#define _SCHEDULING_MODEL_H_

#include <string>
#include <vector>

#include "../reject-type/RejectTypeModel.h"
#include "../user/UserModel.h"
#include "../meeting-point/MeetingPointModel.h"

using namespace std;

class SchedulingModel {

private:
    int code = 0;
    string date = "";
    int meetingPointCode = 0;
    int donatorCode = 0;
    int receiverCode = 0;
    vector<int> rejectsToBeExchangedCodes;
    bool done = false;

public:

    /** Construtor. */
    SchedulingModel(void) {};

    // Codigo
    int getCode() const { return this->code; }
    void setCode(int code) { this->code = code; }

    // Data
    const string getDate() const { return date; }
    void setDate(const string &date) { this->date = date; }

    // Ponto de Coleta
    int getMeetingPointCode() const { return meetingPointCode; }
    void setMeetingPointCode(int meetingPointCode) { this->meetingPointCode = meetingPointCode; }

    // Doador
    int getDonatorCode() const { return donatorCode; }
    void setDonatorCode(int donatorCode) { this->donatorCode = donatorCode; }

    // Receptor
    int getReceiverCode() const { return receiverCode; }
    void setReceiverCode(int receiverCode) { this->receiverCode = receiverCode; }

    // Lista de Residuos
    const vector<int> getRejectsToBeExchangedCodes() const { return rejectsToBeExchangedCodes; }
    void addRejectToBeExchangedCode(const int rejectCode) { this->rejectsToBeExchangedCodes.push_back(rejectCode); }

    // Realizado?
    bool isDone() const { return done; }
    void setDone(bool done) { this->done = done; }
};

#endif