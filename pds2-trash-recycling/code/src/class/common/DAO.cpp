#ifndef _DAO_CPP_
#define _DAO_CPP_

#include <exception>
#include "../../../header/common/class/DAO.h"

using namespace std;

const string DAO::STORAGE_DIR_PATH = "../storage/";

string DAO::getStorageFilePath(void) {
    return DAO::STORAGE_DIR_PATH + this->getStorageFileName();
};

void DAO::closeStorage(bool writing) {

    // Fecha stream de escrita
    if (writing && this->writingStream.is_open()) {
        this->writingStream.close();
        return;
    }

    // Fecha stream de leitura
    if (!writing && this->readingStream.is_open()) {
        this->readingStream.close();
        return;
    }
}

void DAO::openStorageForWriting(void) {

    this->closeStorage(true);
    this->writingStream.open(this->getStorageFilePath(), ios::app);

    if (!this->writingStream.good())
        throw runtime_error("Falha ao tentar abrir arquivo de armazenamento para escrita (" + this->getStorageFileName() + ")");
}

void DAO::openStorageForReading(void) {

    this->closeStorage(false);
    this->readingStream.open(this->getStorageFilePath(), ios::out);

    if (!this->writingStream.good())
        throw runtime_error("Falha ao tentar abrir arquivo de armazenamento para leitura (" + this->getStorageFileName() + ")");
}

void DAO::deleteOne(const int line) {

    // Abre arquivos (permanente & temporario)
    this->openStorageForReading();
    const string tempFilePath = "temp.txt";
    ofstream tempFile;
    tempFile.open(tempFilePath, ios::out);

    // Transcreve armazenamento para arquivo temporario & remove linha
    string fileLine;
    int i = 0;

    while (getline(this->readingStream, fileLine)) {
        i++;
        if (i == line) continue;
        tempFile << fileLine << endl;
    }

    // Substitui armazenamento pelo arquivo temporario
    tempFile.close();
    this->closeStorage(false);

    const string storagePath = this->getStorageFilePath();
    const char* storagePathStr = storagePath.c_str();
    remove(storagePathStr);
    rename(tempFilePath.c_str(), storagePathStr);
};

DAO::~DAO(void) {
    this->closeStorage(true);
    this->closeStorage(false);
}

#endif
