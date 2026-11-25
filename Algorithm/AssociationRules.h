//
// Created by IT on 11/24/2026.
//

#ifndef DATAMINING_ASSOCIATIONRULES_H
#define DATAMINING_ASSOCIATIONRULES_H

#include "ECLAT.h"

struct Rule {
    vector<string> left;
    vector<string> right;
    double support;
    double confidence;
    double lift;
};

class AssociationRules {
    using ItemSet = std::vector<std::string>;
    using Level = std::map<ItemSet, std::set<int>>;
    const Level &frequent_rules;
    double data_size;
public:
    explicit AssociationRules(const Level &frequent_rules, double data_size);
    [[nodiscard]] vector<Rule> association_rules() const;
    [[nodiscard]] vector<Rule> strong_association_rules(double min_confidence) const;
};


#endif //DATAMINING_ASSOCIATIONRULES_H
