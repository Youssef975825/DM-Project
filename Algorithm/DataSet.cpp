//
// Created by ziad shady hamdy on 11/22/2026.
//

#include "DataSet.h"

DataSet::DataSet(ifstream &file, double min_support, double min_conf) {
    this->file = std::move(file);
    if (!this->file.is_open()) {
        throw std::runtime_error("Cannot open file");
    }

    set_min_support(min_support);
    set_min_conf(min_conf);

    // preprocessing
    this->horizontal = preprocess();
    // convert to vertical format
    this->vertical = to_vertical_format();
}


static string trim(const string &s) {
    // string starting or ending with spaces.
    constexpr auto chars = " \t\r\n\"";
    // index of starting pure char
    const int start = static_cast<int>(s.find_first_not_of(chars));
    // item in row is empty
    if (start == string::npos) return "";
    // last index of pure char
    const int end = static_cast<int>(s.find_last_not_of(chars));
    // start index and the length
    return s.substr(start, end - start + 1);
}

static void to_lower(string &s) {
    for (int i = 0; i < s.length(); i++) {
        s[i] = static_cast<char>(tolower(s[i]));
    }
}

map<int, set<string> > DataSet::preprocess() {
    map<int, set<string>> result;
    string line;
    // skip Tid,Items -> the table header
    getline(file, line);

    while (getline(file, line)) {
        // 1, a,b,c,d
        stringstream ss(line);
        string id;
        // id = 1
        getline(ss, id, ',');
        id = trim(id);

        // there is no id for the transaction
        if (id.empty()) continue;
        // a,b,c,d
        string item;

        while (getline(ss, item, ',')) {
            item = trim(item);
            to_lower(item);
            // the item is empty
            if (item.empty()) continue;

            // no duplicate items within a transaction
            result[stoi(id)].insert(item);
        }
    }
    return result;
}

map<string, set<int> > DataSet::to_vertical_format() const {
    map<string, set<int> > result;

    // traverse throw the horizontal data.
    /*
     * horizontal -> 1,a,b,c,d
     * vertical
     * a 1
     * b 1
     * c 1
     * d 1
     */
    for (auto &[id, items] : this->horizontal) {
        for (auto &item : items) {
            result[item].insert(id);
        }
    }
    return result;
}

void DataSet::set_min_support(const double min_supp) {
    if (min_supp <= 0 || min_supp > 1)
        throw invalid_argument("min_support must be in (0, 1]");
    this->min_support = min_supp;
}

double DataSet::get_min_support() const {
    return this->min_support;
}

void DataSet::set_min_conf(const double min_con) {
    if (min_con <= 0 || min_con > 1)
        throw invalid_argument("min_confidence must be in (0, 1]");
    this->min_conf = min_con;
}

double DataSet::get_min_conf() const {
    return this->min_conf;
}

map<string, set<int>> &DataSet::get_vertical_items() {
    return vertical;
}

map<int, set<string>> &DataSet::get_horizontal_items() {
    return horizontal;
}

DataSet::~DataSet() {
    file.close();
    horizontal.clear();
    vertical.clear();
}
