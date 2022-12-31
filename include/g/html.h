//
//  g/HTML.h - HTML Generation.
//
//  Property and Copyright © 2022 Aaron Nathaniel Gray
//

#pragma once

#include <string>
#include <sstream>

class HTML {
public:
    static const std::string br;
    static const std::string nbsp;
    static const std::string tab;

    static std::string Header(std::string title) {
        std::stringstream ss;
        ss <<
            "<head>" "\n"
            "<title>" << title << "</title>" "\n"
            "<style>" "\n"
            "  :link {" "\n"
            "    color: #000000;" "\n"
            "    background-color : transparent;" "\n"
            "    text-decoration: none;" "\n"
            "  }" "\n"
            "  :visited {" "\n"
            "    color: #000000;" "\n"
            "    background-color: transparent;" "\n"
            "    text-decoration: none;" "\n"
            "  }" "\n"
            "  :hover {" "\n"
            "    color: #000000;" "\n"
            "    background-color: transparent;" "\n"
            "    text-decoration: underline;" "\n"
            "  }" "\n"
            "  :active {" "\n"
            "    color: #000000;" "\n"
            "    background-color: transparent;" "\n"
            "    text-decoration: none;" "\n"
            "  }" "\n"
            "  a {" "\n"
            "    font-style: italic;" "\n"
            "  }" "\n"
            "</style>" "\n"
            "</head>" "\n"
            ;
        return ss.str();
    }
    static std::string a_name(std::string string) {
        std::stringstream ss;
        ss << "<a name=\"#" << string << "\">" << string << "</a>";
        return ss.str();
    }
    static std::string a_href(std::string string) {
        std::stringstream ss;
        ss << "<a href=\"#" << string << "\">" << string << "</a>";
        return ss.str();
    }
};

// End g/HTML.h - HTML Generation.
