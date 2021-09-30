//
// Created by Alex Nedelcu on 10.04.2021.
//

#ifndef A89_915_NEDELCU_ALEXANDRU_CSVFILEREPOSITORY_H
#define A89_915_NEDELCU_ALEXANDRU_CSVFILEREPOSITORY_H

#include <fstream>
#include "../EXCEPTIONS/ValidationException.h"
#include "../VALIDATION/Validator.h"
#include "FileRepository.h"

template<class TElem>
class CSVFileRepository : public FileRepository<TElem> {
public:
    explicit CSVFileRepository(const std::string& filename, VirtualValidator* validator);

    void readDataFromFile() override;

    void writeDataIntoFile() override;
};


template<class TElem>
CSVFileRepository<TElem>::CSVFileRepository(const std::string& filename, VirtualValidator* validator)
        :FileRepository<TElem>(filename, validator) {}

template<class TElem>
void CSVFileRepository<TElem>::readDataFromFile() {
    std::ifstream file;
    file.open(this->m_filename);

    if (file.is_open()) {
        this->m_entities.clear();
        TElem newEntity;
        while (file.peek() != std::ifstream::traits_type::eof()) {
            file >> newEntity;
            try {
                this->m_validator->validate(newEntity);
                MemoryRepository<TElem>::add(newEntity);
            } catch (const ValidationException& vex) {
                continue;
            } catch (const RepositoryException& rex) {
                continue;
            }
        }
        file.close();
    }
}

template<class TElem>
void CSVFileRepository<TElem>::writeDataIntoFile() {
    std::ofstream file;
    file.open(this->m_filename);

    if (file.is_open()) {
        std::for_each(this->m_entities.begin(), this->m_entities.end(), [&file](const auto& iterator) {
            file << iterator << std::endl;
        });
        file.close();
    }
}


#endif //A89_915_NEDELCU_ALEXANDRU_CSVFILEREPOSITORY_H
