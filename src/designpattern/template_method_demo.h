#ifndef STUDYCPP_PATTERN_TEMPLATE_METHOD_H
#define STUDYCPP_PATTERN_TEMPLATE_METHOD_H

// === Template Method (模板方法模式) ===
// 使用场景：框架基类（初始化→处理→收尾）、测试夹具、CSV/JSON 数据导出器，
// 在基类中定义算法骨架，子类重写特定步骤。
#include <string>
#include <vector>

class DataExporter {
   public:
    virtual ~DataExporter() = default;
    // 模板方法：定义导出流程
    std::string do_export(const std::vector<std::string>& data) {
        std::string result = header();
        for (const auto& d : data) result += format_row(d) + "\n";
        result += footer();
        return result;
    }

   private:
    virtual std::string header() const = 0;
    virtual std::string format_row(const std::string& data) const = 0;
    virtual std::string footer() const = 0;
};

class CsvExporter : public DataExporter {
   public:
    std::string header() const override { return "data\n"; }
    std::string format_row(const std::string& data) const override { return data; }
    std::string footer() const override { return "---END---"; }
};

class JsonExporter : public DataExporter {
   public:
    std::string header() const override { return "["; }
    std::string format_row(const std::string& data) const override { return "\"" + data + "\","; }
    std::string footer() const override { return "]"; }
};

#endif  // STUDYCPP_PATTERN_TEMPLATE_METHOD_H
