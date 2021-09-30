//
// Created by Alex Nedelcu on 17.04.2021.
//

#include "HTMLEventsRepository.h"


HTMLEventsRepository::HTMLEventsRepository(const std::string& filename, VirtualValidator* validator)
        : FileRepository<Event>(filename, validator) {

}

void HTMLEventsRepository::readDataFromFile() {
    std::ifstream HTMLFile;
    HTMLFile.open(this->m_filename);

    if (HTMLFile.is_open()) {
        std::fstream auxFile("aux.csv", std::ios::in | std::ios::out | std::ios::trunc);
        if (auxFile.is_open()) {
            std::string line;
            std::regex attributeLinePattern("^[ /\t]*<td>.+</td>.*$");
            int count = 0;
            while (HTMLFile.peek() != std::ifstream::traits_type::eof()) {
                getline(HTMLFile, line, '\n');
                if (std::regex_match(line, attributeLinePattern)) {
                    count++;
                    int startPosition = line.find("<td>");
                    int endPosition = line.find("</td>");
                    std::string attribute = line.substr(startPosition + 4, endPosition - startPosition - 4);
                    if (count == 9) {
                        auxFile << attribute << std::endl;
                        count = 0;
                    } else {
                        auxFile << attribute << ",";
                    }
                }
            }
        }
        HTMLFile.close();

        this->m_entities.clear();
        Event newEvent;
        auxFile.seekg(0, std::ios::beg);
        while (auxFile.peek() != std::ifstream::traits_type::eof()) {
            auxFile >> newEvent;
            try {
                this->m_validator->validate(newEvent);
                MemoryRepository<Event>::add(newEvent);
            } catch (const ValidationException& vex) {
                continue;
            } catch (const RepositoryException& rex) {
                continue;
            }
        }
        auxFile.close();
    }
}

void HTMLEventsRepository::writeDataIntoFile() {
    std::ofstream HTMLFile;
    HTMLFile.open(this->m_filename);
    std::string beginning = "<!DOCTYPE html>\n"
                            "<html lang=\"en\">\n"
                            "\n"
                            "<head>\n"
                            "    <meta charset=\"UTF-8\">\n"
                            "    <title>Events</title>\n"
                            "</head>\n"
                            "\n"
                            "<body>\n"
                            "<table border=\"3\">\n"
                            "\n"
                            "    <tr>\n"
                            "        <th>ID</th>\n"
                            "        <th>Title</th>\n"
                            "        <th>Description</th>\n"
                            "        <th>Day</th>\n"
                            "        <th>Month</th>\n"
                            "        <th>Year</th>\n"
                            "        <th>Time</th>\n"
                            "        <th>Participants</th>\n"
                            "        <th>Website</th>\n"
                            "    </tr>\n";

    std::string final = "\n"
                        "</table>\n"
                        "</body>\n"
                        "\n"
                        "</html>";

    if (HTMLFile.is_open()) {
        HTMLFile << beginning;
        std::string baseAttributeLine = "\t\t<td>";
        std::string endAttributeLine = "</td>\n";
        std::for_each(this->m_entities.begin(), this->m_entities.end(), [&HTMLFile, &baseAttributeLine, &endAttributeLine](const auto& event) {
            std::string IDLine = baseAttributeLine + std::to_string(event.getID()) + endAttributeLine;
            std::string titleLine = baseAttributeLine + event.getTitle() + endAttributeLine;
            std::string descriptionLine = baseAttributeLine + event.getDescription() + endAttributeLine;
            std::string dayLine = baseAttributeLine + std::to_string(event.getDate().getDay()) + endAttributeLine;
            std::string monthLine = baseAttributeLine + std::to_string(event.getDate().getMonth()) + endAttributeLine;
            std::string yearLine = baseAttributeLine + std::to_string(event.getDate().getYear()) + endAttributeLine;
            std::string timeLine = baseAttributeLine + event.getTime() + endAttributeLine;
            std::string participantsLine = baseAttributeLine + std::to_string(event.getParticipantsNumber()) + endAttributeLine;
            std::string websiteLine = baseAttributeLine + event.getLink() + endAttributeLine;
            HTMLFile << "\t<tr>\n"
                     << IDLine << titleLine << descriptionLine
                     << dayLine << monthLine << yearLine
                     << timeLine << participantsLine << websiteLine
                     << "\t</tr>\n";
        });
        HTMLFile << final;
        HTMLFile.close();
    }
}
