#include <bits/stdc++.h>

#include "Algorithm/DataSet.h"
#include "Algorithm/ECLAT.h"
#include "Algorithm/AssociationRules.h"
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    // Read data from the csv file
    ifstream file("data.csv");
    DataSet data(file, 0.6, 0.7);
    ECLAT eclat(data);

    eclat.run();

    for (const auto &[items, ids] : eclat.get_frequent_item_set()) {
        for (const auto &item : items) cout << item << " ";
        cout << "(support = " << ids.size() << ")" << endl;
    }
    AssociationRules rules(data, eclat);
    rules.generate();

    cout << "Strong Rules:\n";

    for (const auto& r : rules.get_strong_rules())
    {
		cout << "for Left: \n";
        for (const auto& item : r.left)
        {
            cout << item << " ";
        }
        cout << "for Right: \n";
        for (const auto& item : r.right) 
        {
            cout << item << " ";
            cout << "(confidence =" << r.confidence << "." << '\n';
        }
        
    }
    return 0;
}