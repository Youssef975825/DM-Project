//
// Created by ziad shady hamdy on 11/23/2026.
//

#include "ECLAT.h"

ECLAT::ECLAT(DataSet &data) : data(data) {}

void ECLAT::run() {
    // allow multiple runs on the same object.
    frequent_item_set.clear();
    Level current = level_one();
    prune(current);
    /*
     * assume in the final level
     * items anf ids
     *  a,b,c,d 1,2,3,4
     *  a,b,f,g 2,3,4,5
     *  there is no valid join
     *  then the current will be empty
     */
    while (!current.empty()) {
        frequent_item_set.insert(current.begin(), current.end());
        // candidate
        current = join(current);
        // the next level
        prune(current);
    }
}

void ECLAT::prune(Level &level) const {
    // get the support count.
    const double min_supp = data.get_min_support() * static_cast<double>(data.get_horizontal_items().size());
    for (auto it = level.begin(); it != level.end(); ) {
        if (static_cast<double>(it->second.size()) < min_supp) it = level.erase(it);
        else ++it;
    }
}

ECLAT::Level ECLAT::join(Level &level) {
    Level result;
    for (auto i = level.begin(); i != level.end(); ++i) {
        for (auto j = next(i); j != level.end(); ++j) {
            const ItemSet &a = i->first;
            const ItemSet &b = j->first;
            const int k = static_cast<int>(a.size());

            // first (k - 1) not equal
            if (!equal(a.begin(), a.begin() + (k - 1), b.begin()))
                break;

            // join
            ItemSet merged = a;
            merged.push_back(b.back());

            // intersect between the ids
            set<int> ids;
            ranges::set_intersection(i->second, j->second,
                                     inserter(ids, ids.end()));

            if (!ids.empty())
                result[merged] = std::move(ids);
        }
    }
    return result;
}

ECLAT::Level ECLAT::level_one() const {
    Level result;
    for (auto &[item, ids] : data.get_vertical_items()) {
        ItemSet itm;
        itm.push_back(item);
        result[itm].insert(ids.begin(), ids.end());
    }
    return result;
}

ECLAT::Level &ECLAT::get_frequent_item_set(){
    return frequent_item_set;
}