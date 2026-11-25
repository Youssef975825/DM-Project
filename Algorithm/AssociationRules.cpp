//
// Created by ziad shady hamdy on 11/24/2026.
//

#include "AssociationRules.h"

AssociationRules::AssociationRules(const Level &frequent_rules,
                                   const double data_size) : frequent_rules(frequent_rules), data_size(data_size) {
}

vector<Rule> AssociationRules::association_rules() const {
    vector<Rule> result;
    for (const auto &[items, ids]: frequent_rules) {
        const int n = static_cast<int>(items.size());
        if (n < 2)
            continue;
        for (int mask = 1; mask < (1 << n) - 1; mask++) {
            Rule rule;
            for (int i = 0; i < n; i++) {
                if (mask & (1 << i)) {
                    rule.left.push_back(items[i]);
                } else {
                    rule.right.push_back(items[i]);
                }
            }
            rule.support = static_cast<double>(ids.size()) / data_size;
            const double supp_left = static_cast<double>(frequent_rules.at(rule.left).size()) / data_size;
            const double supp_right = static_cast<double>(frequent_rules.at(rule.right).size()) / data_size;
            rule.confidence = rule.support / supp_left;
            const double lift = rule.support / (supp_right * supp_left);
            rule.lift = lift;
            result.push_back(rule);
        }
    }
    return result;
}

vector<Rule> AssociationRules::strong_association_rules(const double min_confidence) const {
    const vector<Rule> rules = association_rules();
    vector<Rule> result;
    for (const auto &rule: rules) {
        if (rule.confidence >= min_confidence) {
            result.push_back(rule);
        }
    }
    return result;
}
