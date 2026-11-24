#include "AssociationRules.h"

AssociationRules::AssociationRules(DataSet& data, ECLAT& eclat)
    : data(data), eclat(eclat) {
}

void AssociationRules::generate() 
{
    all_rules.clear();
    strong_rules.clear();

    auto& freq = eclat.get_frequent_item_set();

    for (auto& [items, ids] : freq)
    {
        if (items.size() < 2) 
            continue;

        vector<string> left, right;

        build_rules(items, (int)ids.size(), 0, left, right);
    }

    extract_strong_rules();
}

void AssociationRules::build_rules(const vector<string>& items, int supp_xy, int idx,
    vector<string>& left, vector<string>& right)
{
    if (idx == (int)items.size())
    {
        // skip empty left or right side
        if (left.empty() || right.empty()) return;

        auto& freq = eclat.get_frequent_item_set();

        auto it = freq.find(left);
        if (it == freq.end())
            return;

        int supp_x = it->second.size();

        if (supp_x == 0) 
            return;

        double conf = (double)supp_xy / supp_x;

        all_rules.push_back(
            { left
            , right,
            conf }
        );
        return;
    }


    left.push_back(items[idx]);
    build_rules(items, supp_xy, idx + 1, left, right);
    left.pop_back();
   

    right.push_back(items[idx]);
    build_rules(items, supp_xy, idx + 1, left, right);
    right.pop_back();
}

void AssociationRules::extract_strong_rules() {
    strong_rules.clear();

    double min_conf = data.get_min_conf();

    for (auto& r : all_rules) {
        if (r.confidence >= min_conf) 
        {
            strong_rules.push_back(r);
        }
    }
}

vector<Rule>& AssociationRules::get_all_rules() 
{
    return all_rules;
}

vector<Rule>& AssociationRules::get_strong_rules()
{
    return strong_rules;
}