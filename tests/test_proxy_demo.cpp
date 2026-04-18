#include <gtest/gtest.h>

#include "proxy_demo.h"

TEST(ProxyDemoTest, LazyLoad) {
    Proxy proxy;
    EXPECT_FALSE(proxy.is_loaded());
    std::string r = proxy.request();
    EXPECT_TRUE(proxy.is_loaded());
    EXPECT_NE(r.find("RealSubject response"), std::string::npos);
}
