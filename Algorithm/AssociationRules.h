#ifndef ASSOCIATIONRULES_H
#define ASSOCIATIONRULES_H

#include <string>
#include <vector>
#include "DataSet.h"
#include "ECLAT.h"

using namespace std;

struct Rule {
    vector<string> left;
    vector<string> right;
    double confidence;
};

class AssociationRules {
private:
    DataSet& data;
    ECLAT& eclat;
    vector<Rule> all_rules;
    vector<Rule> strong_rules;

    void build_rules(const vector<string>& items, int supp_xy, int idx,
        vector<string>& left, vector<string>& right);

public:
    AssociationRules(DataSet& data, ECLAT& eclat);

    void generate();
    void extract_strong_rules();

    vector<Rule>& get_all_rules();
    vector<Rule>& get_strong_rules();
};

#endif