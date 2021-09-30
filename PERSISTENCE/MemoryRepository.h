//
// Created by Alex Nedelcu on 10.04.2021.
//

#ifndef A89_915_NEDELCU_ALEXANDRU_MEMORYREPOSITORY_H
#define A89_915_NEDELCU_ALEXANDRU_MEMORYREPOSITORY_H

#include "../EXCEPTIONS/RepositoryException.h"
#include "VirtualRepository.h"

template<class TElem>
class MemoryRepository : public VirtualRepository<TElem> {
public:
    explicit MemoryRepository();

    virtual void add(const TElem& newEntity) override;

    virtual void remove(const TElem& removeEntity) override;

    virtual void update(const TElem& updatedEntity) override;

    virtual bool checkExistence(const TElem& searchedEntity) override;

    virtual const TElem& get(const TElem& searchedEntity) override;

    virtual std::vector<TElem>& getAll() override;

    virtual int size() override;

    virtual int capacity() override;

    virtual void clearRepository() override;

    virtual std::string getFilename() override;

    virtual void writeDataIntoFile() override;
};

template<class TElem>
MemoryRepository<TElem>::MemoryRepository(): VirtualRepository<TElem>() {
}

template<class TElem>
void MemoryRepository<TElem>::add(const TElem& newEntity) {
    auto clone = std::find(this->m_entities.begin(), this->m_entities.end(), newEntity);
    if (clone != this->m_entities.end())
        throw RepositoryException{"Entity already exists in the repository!\n"};

    this->m_entities.push_back(newEntity);
}

template<class TElem>
void MemoryRepository<TElem>::remove(const TElem& removeEntity) {
    auto entity = std::find(this->m_entities.begin(), this->m_entities.end(), removeEntity);
    if (entity == this->m_entities.end())
        throw RepositoryException{"Entity to be removed does not exist in the repository!\n"};

    this->m_entities.erase(entity);
}

template<class TElem>
void MemoryRepository<TElem>::update(const TElem& updatedEntity) {
    auto entity = std::find(this->m_entities.begin(), this->m_entities.end(), updatedEntity);
    if (entity == this->m_entities.end())
        throw RepositoryException{"Entity to be updated does not exist in the repository!\n"};

    int targetPosition = entity - this->m_entities.begin();
    this->m_entities[targetPosition] = updatedEntity;
}

template<class TElem>
bool MemoryRepository<TElem>::checkExistence(const TElem& searchedEntity) {
    auto entity = std::find(this->m_entities.begin(), this->m_entities.end(), searchedEntity);
    if (entity != this->m_entities.end())
        return true;
    else
        return false;
}

template<class TElem>
const TElem& MemoryRepository<TElem>::get(const TElem& searchedEntity) {
    auto entity = std::find(this->m_entities.begin(), this->m_entities.end(), searchedEntity);
    if (entity == this->m_entities.end())
        throw RepositoryException{"Searched entity does not exist in the repository!\n"};

    return *entity;
}

template<class TElem>
std::vector<TElem>& MemoryRepository<TElem>::getAll() {
    return this->m_entities;
}

template<class TElem>
int MemoryRepository<TElem>::size() {
    return this->m_entities.size();
}

template<class TElem>
int MemoryRepository<TElem>::capacity() {
    return this->m_entities.capacity();
}

template<class TElem>
void MemoryRepository<TElem>::clearRepository() {
    this->m_entities.clear();
}

template<class TElem>
std::string MemoryRepository<TElem>::getFilename() {
    return "";
}

template<class TElem>
void MemoryRepository<TElem>::writeDataIntoFile() {

}

#endif //A89_915_NEDELCU_ALEXANDRU_MEMORYREPOSITORY_H
