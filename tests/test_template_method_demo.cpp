#include <gtest/gtest.h>

#include "template_method_demo.h"

TEST(TemplateMethodDemoTest, CsvExport) {
    CsvExporter csv;
    std::string result = csv.do_export({"a", "b"});
    EXPECT_NE(result.find("data"), std::string::npos);
    EXPECT_NE(result.find("a"), std::string::npos);
    EXPECT_NE(result.find("---END---"), std::string::npos);
}

TEST(TemplateMethodDemoTest, JsonExport) {
    JsonExporter json;
    std::string result = json.do_export({"x", "y"});
    EXPECT_EQ(result, "[\"x\",\n\"y\",\n]");
}
