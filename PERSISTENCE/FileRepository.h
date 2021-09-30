//
// Created by Alex Nedelcu on 11.04.2021.
//

#ifndef A89_915_NEDELCU_ALEXANDRU_FILEREPOSITORY_H
#define A89_915_NEDELCU_ALEXANDRU_FILEREPOSITORY_H

#include "../VALIDATION/VirtualValidator.h"
#include <fstream>
#include "../EXCEPTIONS/ValidationException.h"
#include "MemoryRepository.h"

template<class TElem>
class FileRepository : public MemoryRepository<TElem> {
protected:
    std::string m_filename;

    VirtualValidator* m_validator;

public:
    explicit FileRepository(const std::string& filename, VirtualValidator* validator);

    virtual void add(const TElem& newEntity) override;

    virtual void remove(const TElem& removeEntity) override;

    virtual void update(const TElem& updatedEntity) override;

    virtual bool checkExistence(const TElem& searchedEntity) override;

    virtual const TElem& get(const TElem& searchedEntity) override;

    virtual std::vector<TElem>& getAll() override;

    virtual int size() override;

    virtual int capacity() override;

    virtual void clearRepository() override;

    std::string getFilename() override;

    virtual void readDataFromFile() = 0;

    virtual void writeDataIntoFile() override;
};

template<class TElem>
FileRepository<TElem>::FileRepository(const std::string& filename, VirtualValidator* validator)
        :m_filename{filename},
         m_validator{validator} {}

template<class TElem>
void FileRepository<TElem>::add(const TElem& newEntity) {
    this->readDataFromFile();
    MemoryRepository<TElem>::add(newEntity);
    this->writeDataIntoFile();
}

template<class TElem>
void FileRepository<TElem>::remove(const TElem& removeEntity) {
    this->readDataFromFile();
    MemoryRepository<TElem>::remove(removeEntity);
    this->writeDataIntoFile();
}

template<class TElem>
void FileRepository<TElem>::update(const TElem& updatedEntity) {
    this->readDataFromFile();
    MemoryRepository<TElem>::update(updatedEntity);
    this->writeDataIntoFile();
}

template<class TElem>
bool FileRepository<TElem>::checkExistence(const TElem& searchedEntity) {
    this->readDataFromFile();
    return MemoryRepository<TElem>::checkExistence(searchedEntity);
}

template<class TElem>
const TElem& FileRepository<TElem>::get(const TElem& searchedEntity) {
    this->readDataFromFile();
    return MemoryRepository<TElem>::get(searchedEntity);
}

template<class TElem>
std::vector<TElem>& FileRepository<TElem>::getAll() {
    this->readDataFromFile();
    return MemoryRepository<TElem>::getAll();
}

template<class TElem>
int FileRepository<TElem>::size() {
    this->readDataFromFile();
    return MemoryRepository<TElem>::size();
}

template<class TElem>
int FileRepository<TElem>::capacity() {
    this->readDataFromFile();
    return MemoryRepository<TElem>::capacity();
}

template<class TElem>
void FileRepository<TElem>::clearRepository() {
    // clear the file
    std::ofstream file;
    file.open(m_filename, std::ofstream::out | std::ofstream::trunc);
    file.close();

    // clear the dynamic array which holds the entities
    this->m_entities.clear();
}

template<class TElem>
std::string FileRepository<TElem>::getFilename() {
    return m_filename;
}

template<class TElem>
void FileRepository<TElem>::writeDataIntoFile() {
    MemoryRepository<TElem>::writeDataIntoFile();
}


#endif //A89_915_NEDELCU_ALEXANDRU_FILEREPOSITORY_H
