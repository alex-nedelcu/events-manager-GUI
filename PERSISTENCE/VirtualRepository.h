//
// Created by Alex Nedelcu on 10.04.2021.
//

#ifndef A89_915_NEDELCU_ALEXANDRU_VIRTUALREPOSITORY_H
#define A89_915_NEDELCU_ALEXANDRU_VIRTUALREPOSITORY_H

#include <vector>

template<class TElem>
class VirtualRepository {
protected:
    std::vector<TElem> m_entities;

public:
    virtual void add(const TElem& newEntity) = 0;

    virtual void remove(const TElem& removeEntity) = 0;

    virtual void update(const TElem& updatedEntity) = 0;

    virtual bool checkExistence(const TElem& searchedEntity) = 0;

    virtual const TElem& get(const TElem& searchedEntity) = 0;

    virtual std::vector<TElem>& getAll() = 0;

    virtual int size() = 0;

    virtual int capacity() = 0;

    virtual void clearRepository() = 0;

    virtual std::string getFilename() = 0;

    virtual void writeDataIntoFile() = 0;
};


#endif //A89_915_NEDELCU_ALEXANDRU_VIRTUALREPOSITORY_H
