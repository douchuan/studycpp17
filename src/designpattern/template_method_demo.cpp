#include "template_method_demo.h"

#include <iostream>

int main() {
    CsvExporter csv;
    std::cout << csv.do_export({"a", "b", "c"}) << "\n\n";

    JsonExporter json;
    std::cout << json.do_export({"a", "b", "c"}) << "\n";
    return 0;
}
