//
// Created by Alex Nedelcu on 05.05.2021.
//

#ifndef A89_915_NEDELCU_ALEXANDRU_STARTERGUI_H
#define A89_915_NEDELCU_ALEXANDRU_STARTERGUI_H

#include <cstdlib>
#include "../DOMAIN/Date.h"
#include "../DOMAIN/Event.h"
#include "../VALIDATION/Validator.h"
#include "../PERSISTENCE/CSVFileRepository.h"
#include "../BUSINESS/AdminService.h"
#include "../PERSISTENCE/HTMLEventsRepository.h"

class StarterGUI {
public:
    int start(int argc, char** argv);
};


#endif //A89_915_NEDELCU_ALEXANDRU_STARTERGUI_H
