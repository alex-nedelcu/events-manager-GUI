//
// Created by Alex Nedelcu on 17.04.2021.
//

#ifndef A89_915_NEDELCU_ALEXANDRU_HTMLEVENTSREPOSITORY_H
#define A89_915_NEDELCU_ALEXANDRU_HTMLEVENTSREPOSITORY_H

#include "FileRepository.h"
#include <regex>
#include "../DOMAIN/Event.h"

class HTMLEventsRepository : public FileRepository<Event> {
public:
    explicit HTMLEventsRepository(const std::string& filename, VirtualValidator* validator);

    void readDataFromFile() override;

    void writeDataIntoFile() override;
};


#endif //A89_915_NEDELCU_ALEXANDRU_HTMLEVENTSREPOSITORY_H
