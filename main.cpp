#include <bits/stdc++.h>

#include "Algorithm/AssociationRules.h"
#include "Algorithm/DataSet.h"
#include "Algorithm/ECLAT.h"
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Read data from the csv file
    ifstream file("data.csv");
    DataSet data(file, 0.6, 0.7);
    ECLAT eclat(data);

    eclat.run();

    // frequent item set
    const auto n = static_cast<double>(data.get_horizontal_items().size());
    for (const auto &[items, ids] : eclat.get_frequent_item_set()) {
        for (const auto &item : items) cout << item << " ";
        cout << "(support = " << ids.size() / n * 100 << "%)" << endl;
    }

    // Association Rules
    cout << "============================================" << endl;
    cout << "Association Rules:" << endl;
    auto data_size = static_cast<double>(data.get_horizontal_items().size());
    AssociationRules associationRules(eclat.get_frequent_item_set(), data_size);

    auto associations = associationRules.association_rules();
    for (const auto &rule : associations) {
        for (const auto &s : rule.left) {
            cout << s << " ";
        }
        cout << " -> ";
        for (const auto &s : rule.right) {
            cout << s << " ";
        }
        cout << endl;
        cout << "support = " << (rule.support) * 100 << '%' << endl;
        cout << "confidence = " << (rule.confidence) * 100 << '%' << endl;
        cout << "--------------------------------------------" << endl;
    }


    // Strong Association Rules
    cout << "============================================" << endl;
    cout << "Strong Association Rules:" << endl;
    auto strong_associations = associationRules.strong_association_rules(data.get_min_conf());
    for (const auto &rule : strong_associations) {
        for (const auto &s : rule.left) {
            cout << s << " ";
        }
        cout << " -> ";
        for (const auto &s : rule.right) {
            cout << s << " ";
        }
        cout << endl;
        cout << "support = " << rule.support * 100 << '%' << endl;
        cout << "confidence = " << rule.confidence * 100 << '%' << endl;
        cout << "lift = " << rule.lift;
        if (rule.lift > 1) {
            cout << " -> (+) correlation " << endl;
        }
        else if (rule.lift < 1) {
            cout << " -> (-) correlation " << endl;
        }
        else {
            cout << " -> no correlation" << endl;
        }
        cout << "--------------------------------------------" << endl;
    }
    return 0;
}