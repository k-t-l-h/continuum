#ifndef FORMATTER_H
#define  FORMATTER_H

#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace pt = boost::property_tree;

struct stringFormatter {
    std::string id;
    std::string description;
};

inline std::string to_json(stringFormatter const &obj) {
    pt::ptree out;
    out.put("response.id", obj.id);
    out.put("response.description", obj.description);
    std::ostringstream oss;
    pt::write_json(oss, out);
    return oss.str();
}

#endif // FORMATTER_H
