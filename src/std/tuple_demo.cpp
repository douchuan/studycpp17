#include "tuple_demo.h"

#include <iostream>

int main() {
    auto record = make_record();
    auto [id, name, score] = record;
    std::cout << "record: id=" << id << ", name=" << name << ", score=" << score << "\n";

    // unpack_record
    int uid;
    std::string uname;
    double uscore;
    unpack_record(record, uid, uname, uscore);
    std::cout << "via tie: id=" << uid << ", name=" << uname << "\n";

    // get
    std::cout << "get_id: " << get_id(record) << "\n";

    // pair
    auto [q, r] = divide_remainder(17, 5);
    std::cout << "17 / 5 = " << q << " remainder " << r << "\n";

    // make_from_tuple
    auto cfg = build_config();
    std::cout << "config: timeout=" << cfg.timeout << ", host=" << cfg.host << "\n";

    return 0;
}
